#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <time.h>
#include <linux/rtc.h>
#include <linux/capability.h>

#include <unistd.h>
#include <sys/time.h>

int SetSysDateAndTime(const char *time_str);
void SetHWClockFromSysClock(int utc);

static int rtc_xopen(const char **default_rtc, int flags);
static void write_rtc(time_t t, int utc);

static const char *rtcname;

int main(void)
{
    const char time_str[] = "1989-11-22 11:22:33";
    SetSysDateAndTime(time_str);
    SetHWClockFromSysClock(0);

    system("reboot");

    return 0;
}

int SetSysDateAndTime(const char *time_str)
{
    struct tm time_tm;
    struct timeval time_tv;
    time_t timep;
    int ret;

    if (time_str == NULL)
    {
        fprintf(stderr, "time string args invalid!\n");
        return -1;
    }

    sscanf(time_str, "%d-%d-%d %d:%d:%d", &time_tm.tm_year, &time_tm.tm_mon, &time_tm.tm_mday, &time_tm.tm_hour, &time_tm.tm_min, &time_tm.tm_sec);
    time_tm.tm_year -= 1900;
    time_tm.tm_mon -= 1;
    time_tm.tm_wday = 0;
    time_tm.tm_yday = 0;
    time_tm.tm_isdst = 0;

    timep = mktime(&time_tm);
    time_tv.tv_sec = timep;
    time_tv.tv_usec = 0;

    ret = settimeofday(&time_tv, NULL);
    if (ret != 0)
    {
        fprintf(stderr, "settimeofday failed\n");
        return -2;
    }

    return 0;
}

void SetHWClockFromSysClock(int utc)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    //if (gettimeofday(&tv, NULL))
    //	bb_perror_msg_and_die("gettimeofday() failed");
    write_rtc(tv.tv_sec, utc);
}

static int rtc_xopen(const char **default_rtc, int flags)
{
    int rtc;

    if (!*default_rtc)
    {
        *default_rtc = "/dev/rtc";
        rtc = open(*default_rtc, flags);
        if (rtc >= 0)
            return rtc;
        *default_rtc = "/dev/rtc0";
        rtc = open(*default_rtc, flags);
        if (rtc >= 0)
            return rtc;
        *default_rtc = "/dev/misc/rtc";
    }

    return open(*default_rtc, flags);
}

static void write_rtc(time_t t, int utc)
{
#define RTC_SET_TIME _IOW('p', 0x0a, struct rtc_time) /* Set RTC time    */

    struct tm tm;
    int rtc = rtc_xopen(&rtcname, O_WRONLY);

    tm = *(utc ? gmtime(&t) : localtime(&t));
    tm.tm_isdst = 0;

    ioctl(rtc, RTC_SET_TIME, &tm);

    close(rtc);
}

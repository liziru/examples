#include <time.h>
#include <stdio.h>
#include <string.h>
#include<string>

long str2time(string & datetime)
{
    struct tm tm_time;
    long unixtime;
    strptime(datetime.c_str(), "%Y-%m-%d %H:%M:%S", &tm_time);

    unixtime = mktime(&tm_time);
    return unixtime;
}

int main(int argc, char const *argv[])
{
    
    return 0;
}

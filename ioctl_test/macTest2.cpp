#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/if_arp.h>

#define ETHER_ADDR_LEN 6
#define UP 1
#define DOWN 0
#define NETCARD "enp3s0"

int set_mac_addr(int fd, struct ifreq ifr, unsigned char *mac)
{
    int rtn;

    ifr.ifr_addr.sa_family = ARPHRD_ETHER;
    // strncpy(ifr.ifr_name, (const char *)ifname, IFNAMSIZ - 1);
    memcpy((unsigned char *)ifr.ifr_hwaddr.sa_data, mac, 6);

    if ((rtn = ioctl(fd, SIOCSIFHWADDR, &ifr)) != 0)
    {
        perror("SIOCSIFHWADDR");
    }
    // close(fd);
    return rtn;
}

int if_updown(int fd, struct ifreq ifr, int flag)
{
    int rtn;

    if ((rtn = ioctl(fd, SIOCGIFFLAGS, &ifr)) == 0)
    {
        if (flag == DOWN)
            ifr.ifr_flags &= ~IFF_UP;
        else if (flag == UP)
            ifr.ifr_flags |= IFF_UP;
    }

    if ((rtn = ioctl(fd, SIOCSIFFLAGS, &ifr)) != 0)
    {
        perror("SIOCSIFFLAGS");
    }

    // close(fd);

    return rtn;
}

/*
 * Convert Ethernet address string representation to binary data
 * @param    a    string in xx:xx:xx:xx:xx:xx notation
 * @param    e    binary data
 * @return    TRUE if conversion was successful and FALSE otherwise
 */
int ether_atoe(const char *a, unsigned char *e)
{
    char *c = (char *)a;
    int i = 0;

    memset(e, 0, ETHER_ADDR_LEN);
    for (;;)
    {
        e[i++] = (unsigned char)strtoul(c, &c, 16);
        if (!*c++ || i == ETHER_ADDR_LEN)
            break;
    }
    return (i == ETHER_ADDR_LEN);
}

int ChangeMac(const char *newmac)
{
    unsigned char mac[6];
    int fd;
    struct ifreq ifr;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        return 1;
    }
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, (const char *)NETCARD, IFNAMSIZ - 1);

    if (if_updown(fd, ifr, DOWN) < 0)
    {
        return 2;
    }

    ether_atoe(newmac, mac); // convert into binary.

    if (set_mac_addr(fd, ifr, mac) < 0)
    {
        if_updown(fd, ifr, UP);
        return 3;
    }

    if (if_updown(fd, ifr, UP) < 0)
    {
        if_updown(fd, ifr, UP);
        return 4;
    }

    close(fd);
    return 0;
}

int main(int argc, char const *argv[])
{
    int ret = ChangeMac(argv[1]);
    printf("ret=%d\n",ret);

    return 0;
}

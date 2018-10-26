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
#define CARD_NAME "enp3s0"

int get_mac_addr(char *ifname, unsigned char *mac)
{
    int fd, rtn;
    struct ifreq ifr;

    if (!ifname || !mac)
    {
        return -1;
    }
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        perror("socket");
        return -1;
    }
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, (const char *)ifname, IFNAMSIZ - 1);

    if ((rtn = ioctl(fd, SIOCGIFHWADDR, &ifr)) == 0)
        memcpy(mac, (unsigned char *)ifr.ifr_hwaddr.sa_data, 6);
    close(fd);
    return rtn;
}

int set_mac_addr(char *ifname, char *mac)
{
    int fd, rtn;
    struct ifreq ifr;

    if (!ifname || !mac)
    {
        return -1;
    }
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        perror("socket");
        return -1;
    }
    ifr.ifr_addr.sa_family = ARPHRD_ETHER;
    strncpy(ifr.ifr_name, (const char *)ifname, IFNAMSIZ - 1);
    memcpy((unsigned char *)ifr.ifr_hwaddr.sa_data, mac, 6);

    if ((rtn = ioctl(fd, SIOCSIFHWADDR, &ifr)) != 0)
    {
        perror("SIOCSIFHWADDR");
    }
    close(fd);
    return rtn;
}

int if_updown(char *ifname, int flag)
{
    int fd, rtn;
    struct ifreq ifr;

    if (!ifname)
    {
        return -1;
    }

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        perror("socket");
        return -1;
    }

    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, (const char *)ifname, IFNAMSIZ - 1);

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

    close(fd);

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

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("argc is short.\n"), exit(1);
    }
    //CARD_NAME
    if (if_updown(CARD_NAME, DOWN) < 0)
    {
        perror("on off fails.1.\n");
        exit(1);
    }

    unsigned char mac[6];

    if (get_mac_addr(CARD_NAME, mac) < 0)
    {
        perror("get mac fails\n");
        if_updown(CARD_NAME, UP);
    }

    fprintf(stdout, "%s   mac:   %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\n",
            CARD_NAME, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    // unsigned char *newmac = (unsigned char *)argv + 1;
    printf("newmac:%s\n", *(argv + 1));
    ether_atoe(*(argv + 1), mac);
    printf("binary newmac:%s\n", mac);

    if (set_mac_addr(CARD_NAME, mac) < 0)
    {
        perror(" set macaddr fails.\n");
        goto exit1;
    }

exit1:
    if (if_updown(CARD_NAME, UP) < 0)
    {
        perror("on off fails.2. \n");
        exit(1);
    }

    if (get_mac_addr(CARD_NAME, mac) < 0)
    {
        perror("get mac fails\n");
        if_updown(CARD_NAME, UP);
    }

    fprintf(stdout, "%s   mac:   %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\n",
            CARD_NAME, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);


    return 0;
}

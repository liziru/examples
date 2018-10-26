#include <stdlib.h>
#include <string.h>
// #include <pcap.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ether.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <net/if_arp.h>
#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <net/route.h>
#include <errno.h>
#include <stdio.h>

#define CARD_NAME "enp3s0"

bool SetLocalIp(const char *ipaddr)
{
    if (NULL == ipaddr)
    {
        printf("SetLocalIp: ipaddr is null\n");
        return false;
    }

    int sockfd;

    struct sockaddr_in sin_set_ip;
    struct ifreq ifr_set_ip;

    bzero(&ifr_set_ip, sizeof(ifr_set_ip));

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket create failse...SetLocalIp!\n");
        return false;
    }

    memset(&sin_set_ip, 0, sizeof(sin_set_ip));
    strncpy(ifr_set_ip.ifr_name, CARD_NAME, sizeof(ifr_set_ip.ifr_name) - 1);

    sin_set_ip.sin_family = AF_INET;
    sin_set_ip.sin_addr.s_addr = inet_addr(ipaddr);
    memcpy(&ifr_set_ip.ifr_addr, &sin_set_ip, sizeof(sin_set_ip));

    if (ioctl(sockfd, SIOCSIFADDR, &ifr_set_ip) < 0)
    {
        perror("Not setup interface/n");
        return false;
    }

    ifr_set_ip.ifr_flags |= IFF_UP | IFF_RUNNING;

    //get the status of the device
    if (ioctl(sockfd, SIOCSIFFLAGS, &ifr_set_ip) < 0)
    {
        perror("SIOCSIFFLAGS");
        return false;
    }

    close(sockfd);

    return true;
}

int main(int argc, char *argv[])
{

    if (SetLocalIp(argv[1]) == false)
    {
        perror("fails to change ip.");
        return -1;
    }
    return 0;
}



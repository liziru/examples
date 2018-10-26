#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <net/route.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
    int sockfd;
    struct rtentry route;
    struct sockaddr_in *addr;
    int err = 0;

    // create the socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0))<0)
        {
            perror("socket");
            exit(1);
        }

    memset(&route, 0, sizeof(route));
    addr = (struct sockaddr_in *)&route.rt_gateway;
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = inet_addr("192.168.2.1");

    addr = (struct sockaddr_in *)&route.rt_dst;
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = INADDR_ANY;

    addr = (struct sockaddr_in *)&route.rt_genmask;
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = INADDR_ANY;

    // TODO Add the interface name to the request
    route.rt_flags = RTF_UP | RTF_GATEWAY;
    route.rt_metric = 0;

    if ((err = ioctl(sockfd, SIOCADDRT, &route)) != 0)
    {
        perror("SIOCADDRT failed");
        exit(1);
    }
}
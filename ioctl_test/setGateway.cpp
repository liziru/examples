
#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <errno.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/socket.h>

#include <netinet/in.h>

#include <arpa/inet.h>

#include <sys/ioctl.h>

#include <net/if.h>
#include <net/route.h>

#define NETCARD "enp3s0"

bool SetLocalRoute(char *szGateWay)
{
    int sockfd;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
    {
        return false;
    }

    struct rtentry rmten;
    struct sockaddr_in ic_gateway; // Gateway IP address
    int err;

    memset(&rmten, 0, sizeof(rmten));

    ic_gateway.sin_family = AF_INET;
    ic_gateway.sin_addr.s_addr = inet_addr(szGateWay);
    ic_gateway.sin_port = 0;

    ((struct sockaddr_in *)&rmten.rt_dst)->sin_family = AF_INET;
    ((struct sockaddr_in *)&rmten.rt_dst)->sin_addr.s_addr = 0;
    ((struct sockaddr_in *)&rmten.rt_dst)->sin_port = 0;

    ((struct sockaddr_in *)&rmten.rt_genmask)->sin_family = AF_INET;
    ((struct sockaddr_in *)&rmten.rt_genmask)->sin_addr.s_addr = 0;
    ((struct sockaddr_in *)&rmten.rt_genmask)->sin_port = 0;

    memcpy((void *)&rmten.rt_gateway, &ic_gateway, sizeof(ic_gateway));
    rmten.rt_flags = RTF_UP | RTF_GATEWAY;

    if ((err = ioctl(sockfd, SIOCADDRT, &rmten)) < 0)
    {
        perror("ioctl net error!\n");
        return false;
    }

    close(sockfd);
    return true;
}

int main(int argc, char*argv[])
{
    if (!SetLocalRoute(argv[1]))
    {
        printf("error.");
        return -1;
    }

    return 0;
}

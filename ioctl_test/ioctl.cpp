
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

static void usage()
{

    printf("usage : ipconfig interface \n");

    exit(0);
}

int main(int argc, char **argv)

{

    struct sockaddr_in *addr;

    struct sockaddr sa;

    struct ifreq ifr;

    char *name, *address;

    int sockfd;

    unsigned char mac[6];

    if (argc != 2)

        usage();

    else

        name = argv[1];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    strncpy(ifr.ifr_name, name, IFNAMSIZ - 1);

    if (ioctl(sockfd, SIOCGIFADDR, &ifr) == -1)
        perror("ioctl error"), exit(1);

    addr = (struct sockaddr_in *)&(ifr.ifr_addr);

    address = inet_ntoa(addr->sin_addr);

    printf("inet addr: %s ", address);

    if (ioctl(sockfd, SIOCGIFBRDADDR, &ifr) == -1)

        perror("ioctl error"), exit(1);

    addr = (struct sockaddr_in *)&ifr.ifr_broadaddr;

    address = inet_ntoa(addr->sin_addr);

    printf("broad addr: %s ", address);

    if (ioctl(sockfd, SIOCGIFNETMASK, &ifr) == -1)

        perror("ioctl error"), exit(1);

    addr = (struct sockaddr_in *)&ifr.ifr_addr;

    address = inet_ntoa(addr->sin_addr);

    printf("inet mask: %s ", address);

    printf("\n");

    if (ioctl(sockfd, SIOCGIFHWADDR, &ifr) == -1)

        perror("ioctl error"), exit(1);

    memcpy(&sa, &ifr.ifr_addr, sizeof(struct sockaddr_in));

    memcpy(mac, sa.sa_data, sizeof(mac));

    fprintf(stdout, "%s   mac:   %.2X:%.2X:%.2X:%.2X:%.2X:%.2X/n",
            name, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    exit(0);
}

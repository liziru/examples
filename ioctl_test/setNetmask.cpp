
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

#define NETCARD "enp3s0"

static void usage()
{

    printf("usage : ipconfig interface \n");

    exit(0);
}
bool SetLocalNetMask(char *netMask)
{
    int socketfd;
    
    if (NULL == netMask)
    {
        printf("SetLocalNetMask: netMask is null\n");
        return false;
    }
 
    if((socketfd = socket(AF_INET, SOCK_DGRAM, 0 ) )== -1)
    {  
        perror("socket create failse...SetLocalNetMask!/n");  
        return false;  
    } 
 
    struct ifreq ifr_mask;
    struct sockaddr_in *sin_net_mask;
 
    memset(&ifr_mask, 0, sizeof(ifr_mask));
    strncpy(ifr_mask.ifr_name, NETCARD, sizeof(ifr_mask.ifr_name) - 1);
    sin_net_mask = (struct sockaddr_in *)&ifr_mask.ifr_addr;
    sin_net_mask->sin_family = AF_INET;
    inet_pton(AF_INET, netMask, &sin_net_mask->sin_addr);
 
    if (ioctl(socketfd, SIOCSIFNETMASK, &ifr_mask) < 0)
    {
        printf("socket_netmask ioctl error!\n");
        return false;
    }
 
    close( socketfd );    
    return true;
}

int main(int argc, char **argv)
{

    /*// set mask
    sin_set_ip.sin_family = AF_INET;
    sin_set_ip.sin_addr.s_addr = inet_addr(argv[2]);
    memcpy(&ifr.ifr_addr, &sin_set_ip, sizeof(sin_set_ip));
    strncpy(ifr.ifr_name, name, IFNAMSIZ - 1);

    if (ioctl(sockfd, SIOCSIFNETMASK, &ifr) == -1) //SIOCSIFNETMASK
        perror("ioctl error2"), exit(1);

    // sleep(1); */
    printf("netmask %s\n",argv[1]);
    if (!SetLocalNetMask(argv[1]))
    {
        perror("set error.");
        exit(1);
    }
    exit(0);
}

#include <sys/types.h>
#include <string>
#include <iostream>
#include <ifaddrs.h>
#include <vector>
#include <string.h>
#include <arpa/inet.h>

using namespace std;
#define INET_ADDRSTRLEN 16

vector<uint32_t> getAllIpAddress()
{
    struct ifaddrs *ifaddr, *ifa;
    int family, s, n;
    vector<uint32_t> result;

    if (getifaddrs(&ifaddr) == -1)
    {
        return result;
    }

    for (ifa = ifaddr, n = 0; ifa != NULL; ifa = ifa->ifa_next, n++)
    {
        if (ifa->ifa_addr == NULL)
            continue;

        if (ifa->ifa_addr->sa_family != AF_INET)
            continue;
etlink 协议类型进行数据交换);
    2. netlink是一种异步通信机制，在内核
        //if (strcmp(ifa->ifa_name, "lo") == 0)
        //    continue;

        /* AF_INET */
        result.push_back(((struct sockaddr_in *)ifa->ifa_addr)->sin_addr.s_addr);
    }
    freeifaddrs(ifaddr);
    return result;
}

string ipAddressToString(uint32_t ip)
{
    char result[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, (void *)&ip, result, sizeof(result));

    return string(result);
}

int main(int argc, char const *argv[])
{
    string resip;
    vector<uint32_t> ips = getAllIpAddress();
    if (ips.size() <= 0)
    {
        printf("Error .");
        return -1;
    }
    //printf("ips size:%ud\n",ips.size());
    for (auto ip : ips)
    {
        resip = ipAddressToString(ip);
        printf("result ip is :%s\n",resip.c_str());
    }

    return 0;
}

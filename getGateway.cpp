#include <string.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <net/route.h>

#define PATH_ROUTE "/proc/net/route"

using namespace std;

bool GetIPV4Gateway(const char *pNICName, char *pGateway, unsigned long len)
{
	char buffer[200] = {0};
	unsigned long bufLen = sizeof(buffer);

	unsigned long defaultRoutePara[4] = {0};
	FILE *pfd = fopen(PATH_ROUTE, "r");
	if (NULL == pfd)
	{
		return false;
	}

	while (fgets(buffer, bufLen, pfd))
	{

		if (NULL != strstr(buffer, pNICName))
		{
			printf("buffer:%s\n", buffer);

			sscanf(buffer, "%*s %x %x %x %*x %*x %*x %x %*x %*x %*x\n", (unsigned int *)&defaultRoutePara[1], (unsigned int *)&defaultRoutePara[0], (unsigned int *)&defaultRoutePara[3], (unsigned int *)&defaultRoutePara[2]);

			//如果FLAG标志中有 RTF_GATEWAY
			if (defaultRoutePara[3] & RTF_GATEWAY)
			{
				unsigned long ip = defaultRoutePara[0];
				snprintf(pGateway, len, "%ld.%ld.%ld.%ld", (ip & 0xff), (ip >> 8) & 0xff, (ip >> 16) & 0xff, (ip >> 24) & 0xff);
				break;
			}
		}
	}

	fclose(pfd);
	pfd = NULL;
	return true;
}

int main(int argc, char const *argv[])
{

	char gateway[32] = {0};
	GetIPV4Gateway(argv[1], gateway, 32);

	printf("gateway:%s\n", gateway);
	return 0;
}

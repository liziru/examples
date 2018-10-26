#include <stdio.h>
#include <string.h>

int checkValidIP(const char *ipaddr)
{
    char str[31], temp[31];
    int a, b, c, d;

    if (sscanf(ipaddr, "%d.%d.%d.%d ", &a, &b, &c, &d) == 4 && a >= 0 && a <= 255 && b >= 0 && b <= 255 && c >= 0 && c <= 255 && d >= 0 && d <= 255)
    {
        sprintf(temp, "%d.%d.%d.%d", a, b, c, d); //把格式化的数据写入字符串temp
        if (strcmp(temp, ipaddr) == 0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 1;
    }

    return 0;
}

// www.outofmemory.cn
int main(void)
{
    char str[31], temp[31];
    int a, b, c, d;
#if 0

    while (gets(str) != NULL)
    {
        if (sscanf(str, "%d.%d.%d.%d ", &a, &b, &c, &d) == 4 && a >= 0 && a <= 255 && b >= 0 && b <= 255 && c >= 0 && c <= 255 && d >= 0 && d <= 255)
        {
            sprintf(temp, "%d.%d.%d.%d", a, b, c, d); //把格式化的数据写入字符串temp
            printf("YES\n");

            if(strcmp(temp,str)==0)   
            {  
                printf("YES\n");   
            }   
            else  
            {  
                printf("NO\n");   
            }
        }
        else
        {
            printf("NO\n");
        }
    }
#endif
    while (gets(str) != NULL)
    {
        int ret = checkValidIP(str);
        if (ret != 0)
            printf("NO\n");
        else
            printf("YES\n");
    }

    return 0;
}

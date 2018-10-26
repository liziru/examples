#include <sys/types.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ereg(char *pattern, char *value)
{
    int r, cflags = 0;
    regmatch_t pm[10];
    const size_t nmatch = 10;
    regex_t reg;

    r = regcomp(&reg, pattern, cflags);
    if (r == 0)
    {
        r = regexec(&reg, value, nmatch, pm, cflags);//REG_EXTENDED  REG_ICASE
    }
    regfree(&reg);

    return r;
}

int isValidMac(char *value)
{
    int r; //r=0:valid, else not valid
    char *reg = "^[a-f0-9A-F]\\([a-f0-9A-F]\\:[a-f0-9A-F]\\)\\{5\\}[a-f0-9A-F]$";
    r = ereg(reg, value);
    return r;
}

// www.outofmemory.cn
int main(void)
{
    char str[31];
    int a, b, c, d;

    while (gets(str) != NULL)
    {
        int ret = isValidMac(str);
        if (ret != 0)
            printf("NO\n");
        else
            printf("YES\n");
    }

    return 0;
}

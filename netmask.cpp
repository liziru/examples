#include <string.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <regex.h>

using namespace std;


/*
 * 输出regexXXX调用出错消息
 */
static void regex_emsg(int errorcode, regex_t *preg)
{
    char msg[512] = {'\0'};

    regerror(errorcode, preg, msg, sizeof msg - 1);
    fputs(msg, stderr);
    fputc('\n', stderr);
    return;
}


int ereg(char *pattern, char *value)
{
    int r, cflags = REG_EXTENDED | REG_NEWLINE;
    regmatch_t pm[10];
    const size_t nmatch = 10;
    regex_t reg;

    r = regcomp(&reg, pattern, cflags);
    if (r == 0)
    {
        r = regexec(&reg, value, nmatch, pm, 0);
if(r!=0){
regex_emsg(r,&reg);
}

    }else 
	printf("ready to free.\n");
    regfree(&reg);

    return r;
}


int isValidNetmask(char * netmask)
{
    int r; //r=0:valid, else not valid

//char reg[2018]="^((2[0-4]d|25[0-5]|[0-1]?dd?)\\.){3}(2[0-4]d|25[0-5]|[0-1]?dd?)$";  // error.
char reg[2018]="^(([0-9]|[1-9][0-9]|1[0-9]{1,2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{1,2}|2[0-4][0-9]|25[0-5])$"; // ok.

    r = ereg(reg, (char *)netmask);

    return r;
}


int main(int argc, char *argv[])
{
    printf("netmask:%s\n",argv[1]);
    int ret;

    ret = isValidNetmask(argv[1]);

    if(ret){
        printf("error.\n");
    }else
        printf("### right.\n");

    return 0;
}

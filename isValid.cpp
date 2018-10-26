#include <sys/types.h>
#include <regex.h>

#include <stdio.h>
#include <stdlib.h>

#define IP_PATTERN "^([0-9]|[1-9][0-9]|1[0-9]{1,2}|2[0-4][0-9]|25[0-5]).([0-9]|[1-9][0-9]|1[0-9]{1,2}|2[0-4][0-9]|25[0-5]).([0-9]|[1-9][0-9]|1[0-9]{1,2}|2[0-4][0-9]|25[0-5]).([0-9]|[1-9][0-9]|1[0-9]{1,2}|2[0-4][0-9]|25[0-5])$"


static void regex_emsg(int errorcode, regex_t *preg);

int main(int argc, char *argv[])
{
    regex_t reg;
    regmatch_t match[5];
    int retval;

    if (argc != 2) {
        fprintf(stderr, "usage: %s \n"
                "example: %s 1.2.3.4\n",
                argv[0], argv[0]);
        exit(EXIT_FAILURE);
    }

    retval = regcomp(&reg, IP_PATTERN, REG_EXTENDED | REG_NEWLINE);
    if (retval != 0) 
        regex_emsg(retval, &reg);

    retval = regexec(&reg, argv[1], sizeof match / sizeof match[0], match, 0);
    printf("%s is %s\n", argv[1], retval == 0 ? "legal" : "illegal");
    regfree(&reg);

    /*
     * 如果是正确的ip， 输出详细的匹配过程
     */
    if (retval == 0) {
        int i;
        for (i = 0; i < sizeof match / sizeof match[0]; i++) {
            printf("ip part[%d]: %.*s\n", i, match[i].rm_eo - match[i].rm_so,
                    argv[1] + match[i].rm_so);
        }
    }

    exit(EXIT_SUCCESS);

}


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

    /* filename: regex_checkip.c */
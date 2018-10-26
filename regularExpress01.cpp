#include <cstdio>
#include <regex.h>
#include <string.h>
#include <stdio.h>

int main(){
    regex_t re;
    regmatch_t subs[1024];
    char matched[1024];
    char src[1024]="beginworldendtestbeginworkendtest";
    char pattern[1024] = "begin(.*?)end";

    int err = regcomp(&re, pattern, REG_EXTENDED);
    if (err) {
        printf("regex error");
        return 1;
    }

    const char *ptr = src;
    // 匹配模式字串以及子正则
    err = regexec(&re, ptr, 1024, subs, 0); 
    for (int x = 0; x < 1024 && subs[x].rm_so != -1; ++x) {
        int len = subs[x].rm_eo - subs[x].rm_so;
        memcpy(matched, ptr + subs[x].rm_so, len);
        matched[len] = '\0';
        printf("matched:%s\n", matched);
    }

    regfree(&re);

    return 0;
}
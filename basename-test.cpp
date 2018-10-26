#include <stdio.h>
#include <libgen.h>
#include <string.h>
#include <stdlib.h>
/*
*#RETURN VALUE TABLE#
*                   dirname   basename
*
* /etc/passwd        /etc       passwd
* /etc/home/         /etc/home   home
*    /                  /          /
* /etc/home/fasd     /etc/home   fadf
*   null               .          .
*   ""                  .          .
*   " "                 .          " "
*   Attention——dirname changes param of its,and equal the returned value by itself.
*/ 
int main(int argc, char const *argv[])
{
    /* code */
    char *dirc, *basec, *bname, *dname;
    char path[1024] = "/etc/passwd";
    char ph[1024] = "FAD/etc/home/fadf";
#if 1
    dirc = strdup(path);
    basec = strdup(path);

    printf("dirc=%s, basec=%s\n", dirc, basec);

    dname = dirname(dirc);
    bname = basename(basec);
    printf("dirname=%s, basename=%s\n", dname, bname);
    printf("dirc=%s, basec=%s\n", dirc, basec);

    free(dirc);
    free(basec);
#endif
    printf("------2------\n");

    dirc = strdup(ph);
    basec = strdup(ph);

    printf("dirc=%s, basec=%s\n", dirc, basec);

    dname = dirname(dirc);
    bname = basename(basec);
    printf("dirname=%s, basename=%s\n", dname, bname);
    printf("dirc=%s, basec=%s\n", dirc, basec);

    free(dirc);
    free(basec);

    printf("-------3-----\n");
    char sh[1024] = "/";

    dirc = strdup(sh);
    basec = strdup(sh);

    printf("dirc=%s, basec=%s\n", dirc, basec);

    dname = dirname(dirc);
    bname = basename(basec);
    printf("dirname=%s, basename=%s\n", dname, bname);
    printf("dirc=%s, basec=%s\n", dirc, basec);

    free(dirc);
    free(basec);

 printf("-------4-----\n");
    char *s= NULL;

    //dirc = strdup(s);
    //basec = strdup(s);

    //printf("dirc=%s, basec=%s\n", dirc, basec);

    dname = dirname(s);
    bname = basename(s);
    printf("dirname=%s, basename=%s\n", dname, bname);
    //printf("dirc=%s, basec=%s\n", dirc, basec);

    free(dirc);
    free(basec);

    printf("-------5-----\n");
    char s1[10]= { 0 };

    //dirc = strdup(s1);
    //basec = strdup(s1);

    printf("dirc=%s, basec=%s\n", dirc, basec);

    dname = dirname(s1);
    bname = basename(s1);
    printf("dirname=%s, basename=%s\n", dname, bname);
    printf("dirc=%s, basec=%s\n", dirc, basec);

    free(dirc);
    free(basec);

    return 0;
}

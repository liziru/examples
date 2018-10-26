#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void timer(int sig)
{
    if (SIGALRM == sig)
    {
        printf("time up...\n");
    }
    return;
}

int main(int argc, char const *argv[])
{

    signal(SIGALRM, timer);
    printf("before...\n");
    alarm(3);
    printf("after...\n");

    while(1);
    return 0;
}

#include <stdio.h>

int main(int argc, char const *argv[])
{
    char old[10] = {"eth1"};

    char new[10] = {"eth0"};

    if(rename(old,new) < 0){
                printf("fail.\n");
        perror("reasen ");
    }

    return 0;
}

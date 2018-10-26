#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int i;
    char str[] = "a1296th";
    char accept[] = "1234567h890";
    i = strspn(str, accept);
    printf("str 前 %d 个字符都属于 accept\n", i);

    i = strcspn(str, accept);
    printf("str 前 %d 个字符 不 属于 accept\n", i);

    system("pause");
    return 0;
}
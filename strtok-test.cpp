#include <stdio.h>
#include <string.h>
int main(void)
{
    char buf[] = "hello@boy@this@is@heima";
    //char *temp = strtok(buf, "@");
    // char *temp = strtok(buf, ":");
    // char *temp = strtok(NULL, ":@l");

    char *temp = strtok(buf, ":@l");

    while (temp)
    {
        printf("%s ", temp);
        // temp = strtok(NULL,"@");
        // temp = strtok(NULL,":");
        temp = strtok(NULL, ":l"); //匹配字符和第一次调用的 保持一致。
    }

    return 0;
}
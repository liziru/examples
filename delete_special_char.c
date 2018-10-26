#include <stdio.h>
#include <stddef.h>
/*
 * 从字符串str中删除指定的字符ch
 */
char* delete_special_char(char *str, char ch)
{
    char *temp, *ptr;
    if (str == NULL)
        return NULL;
    for(ptr = str,temp = str; (*ptr) != '\0';ptr++)
    {   
        if( (*ptr) != ch)
            *temp++ = *ptr;
    }   
    *temp = '\0';
    return str;
}
int main()
{
    char s[1000] = "Thye ywriyter wouyld ylike to thank you!";
    char del_ch = 'y';
    char *ret_str;
    ret_str = delete_special_char(s,'y');
 
    puts(ret_str);
 
    return 0;
}

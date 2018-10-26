#include<stdio.h>
#include <stdlib.h>
#include<string.h>

int main()
{
  char s1[] = "http://c.biancheng.net/cpp/xitong/";
  char s2[] = "z -+*";
  if(strlen(s1) == strcspn(s1,s2)){
    printf("s1 is diffrent from s2!\n");
  }else{
    printf("There is at least one same character in s1 and s2!\n");
  }

//   system("pause");
  return 0;
}
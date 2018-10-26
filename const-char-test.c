#include<stdio.h>

void print(const char *s)
{
	
	printf("%s\n",s);

}

int main()
{
	char str[100] = {"helloworld"};
	print(str);


	return 0;
}

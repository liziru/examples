#include<string>
#include<sstream>
#include<iostream>

using namespace std;

//C++方法：将 string 转换为数值
double convertFromString(const string &s)
{
	istringstream i(s);
	double x;
	if (i >> x)
		return x;
	return 0.0;//if error
}

int main(int argc, char const *argv[])
{
    string num="12.1341234";
    double res = convertFromString(num);
    printf("res num is :%lf\n",res);
    return 0;
}

#include<limits.h>

int myAtoi(char * s)
{
    int len =strlen(s);  //获取字符串长度
    long  double num=0; //用long int或者long long都不够案例的最大值输入大
    int i=0;
    int j;
    int flag=1;
    while(*s==' ') //去除前导空格 更新数组长度
    {
        s++;
        len--;
    }

    if(*s=='+')
    {
        s++;
        len--;
    }
    else if(*s=='-')
    {
        flag =-1;
        s++;
        len--;
    }

    int *newnum =(int*)malloc(len * sizeof(int));
    while(*s!='\0' ) //判断是否到字符串末尾
    {
        newnum[i]=(int)*s-48;                 //求出每个数 '0'的AS码为48
        if(newnum[i]>9 || newnum[i]<0)       //若遇到了不是数字 就跳出 代表结束
            break;

        num = num*10 +newnum[i]; //记录新数字
        i++; 
        s++;
	}
    if(flag *num>=INT_MAX ) //判断是否大于2^31
    {
	    return INT_MAX;
    }
    if(flag *num <=INT_MIN )
    {
        return INT_MIN;
    }
    else 
    {
        return flag *num;
    }
	
}
#include<limits.h>
int myAtoi(char * s)
{
    int len =strlen(s);
    int i=0;
    long num=0;
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
    while(*s=='0')
    {
        s++;
    }
    while(*s!='\0' ) //判断是否到字符串末尾
    {
        newnum[i]=(int)*s-48; 
        if(newnum[i]>9 || newnum[i]<0) 
            break;
        i++; 
        s++;
	}
    if(i>10)
    {
        if (flag==-1){
            return INT_MIN;
        }else{
            return INT_MAX;
        }
    }
    for(int j=0;j<i;j++)
    {
        num=num*10+newnum[j];
    }
    num=flag*num;
    if(i==10){
        if(flag==-1)
        {
            if(num<=INT_MIN)
            {
                return INT_MIN;
            }
        }else
        {
            if(num>=INT_MAX)
            {
                return INT_MAX;
            }
        }
    }
	return num;
}
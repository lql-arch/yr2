#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"strbuf5.h"
#include"strbuf4.h"
#include"strbuf3.h"
#include"strbuf2.h"
#include"strbuf1.h"

strbuf **strbuf_split_buf(const char *str, size_t len, int terminator, int max)
{
    int status=0;
    int j=0,k=0;
    int *strt;
    int tlen=0;
    strt=(char*)malloc(len+1);
    for(int i=0;i<len;i++)
    {
        if(str[i]==terminator)
            status++;
    }
    strbuf **s;
    if(status>=max-1)
        s=(strbuf**)malloc(sizeof(strbuf*)*max);
    else   
        s=(strbuf**)malloc(sizeof(strbuf*)*(status+1));
    for(int i=0;i<len;i++)
    {
        if(max<=k)
        {
            break;
        }
        strt[j++]=str[i];
        if(str[i]==terminator)
        {
            if(k==0)
            {
                strbuf_init(s[k],i+2);
                strbuf_grow(s[k],i+1);
                memcmp(s[k]->buf,strt,i+1);
                s[k]->buf[s[k]->len]='\0';
                j=0;
                k++;
            }else
            {
                tlen=i+1-s[k]->len;
                strbuf_init(s[k],tlen+1);
                strbuf_grow(s[k],tlen);
                memcmp(s[k]->buf,strt,tlen);
                s[k]->buf[s[k]->len]='\0';
                j=0;
                k++;
            }
        }
    }
    return s;
}

int strbuf_start(strbuf* sb,const char*str)
{
    int len1=sb->len;
    int len2=strlen(str);
    if (len2>len1)
        return -1;

    int flag=memcmp(sb->buf,str,len1);
    if(flag!=0)
        return 0;
    else   
        return 1;
}

char* str_(const char*str,int begin,int end)
{
    int len1=strlen(str);
    int len2=end-begin;
    char*s;
    s=(char*)malloc(sizeof(char)*(len2+1));
    memcpy(s,str+begin,len2);
    s[len2+1]='\0';
    return s;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"strbuf3.h"

void strbuf_ishalf(strbuf *sb){
    if (sb->len < sb->alloc /2)
    {
        sb->buf=(char*)realloc(sb->buf,sizeof(char)*((sb->alloc/2)+1));
        sb->alloc/=2;
    } 
}

void strbuf_rtrim(strbuf *sb)
{   
    if (sb->buf==NULL || sb->len==0)
    {
        return ;
    }
    int i=0;
    for(i;sb->buf[i]!=' ' && i!=sb->len;i++)
    {}
    sb->len -= i;
    sb->buf=sb->buf + i;
    sb->buf=(char*)realloc(sb->buf,sizeof(char)*sb->alloc+1);
    sb->buf[sb->len]='\0';
    strbuf_ishalf(sb);
}

void strbuf_ltrim(strbuf *sb)
{
    if (sb->buf==NULL || sb->len==0)
    {
        return ;
    }
    int i=0;
    for(i;sb->buf[i]!=' ' && i!=sb->len;i++)
    {}
    sb->len -= i;
    sb->buf[sb->len]='\0';
    strbuf_ishalf(sb);
}

void strbuf_remove(strbuf *sb, size_t pos, size_t len)
{
    if (sb->buf==NULL || sb->len==0)
    {
        return ;
    }
    int l=sb->len - pos - len;
    sb->len -= len;
    memmove(sb->buf+pos,sb->buf+pos+len,l);
    sb->buf[sb->len]='\0';
    strbuf_ishalf(sb);

}

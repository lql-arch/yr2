#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"strbuf2.h"

void strbuf_grow(struct strbuf *sb, size_t extra)
{
    if(sb->alloc==0)
    {
        sb->alloc+=extern;
    }
    else
    {
        while(sb->alloc < sb->len + extern)
        {
            sb->alloc*=2;
        }
    }
    sb->len+=len;
}

void strbuf_add(struct strbuf *sb, const void *data, size_t len)
{
    char*res=(char*)data;
    int l=sb->len;
    strbuf_grow(sb,len);
    sb->buf=(char*)realloc(sizeof(char) * sb->alloc + 1);
    memcpy(sb->buf+l,res,len);
    sb->buf[sb->len]='\0';
}

void strbuf_addch(strbuf *sb, int c)
{
    int l=sb->len;
    strbuf_grow(sb,1);
    sb->buf=(char*)realloc(sizeof(char)*sb->alloc+1);
    sb->buf[l]=(char)c;
    sb->buf[sb->len]='\0';
}

void strbuf_addstr(strbuf *sb, const char *s)
{
    strbuf_add(sb,s,strlen(s));
}

void strbuf_addbuf(strbuf *sb, const struct strbuf *sb2)
{
    strbuf_add(sb,sb2->buf,sb2->len);
}  

static inline void strbuf_setlen(strbuf *sb, size_t len)
{
    sb->len=0;
    strbuf_grow(sb,len);
    sb->buf[sb->len]='\0';
}

static inline size_t strbuf_avail(const strbuf *sb)
{
    size_t len = sb->alloc - sb->len;
    return len;
}

void strbuf_insert(strbuf *sb, size_t pos, const void *data, size_t len)
{  
    if (pos < sb->len)
    {
        sb->len=pos;
        char*res=(char*)data;
        int l=sb->len;
        strbuf_grow(sb,len);
        sb->buf=(char*)realloc(sizeof(char) * sb->alloc + 1);
        memmove(sb->buf+l,res,len);
        sb->buf[sb->len]='\0';
    }
}
#include<stdio.h>
#include<string.h>
#include"strbuf1.h"

void strbuf_malloc(strbuf *sb,size_t alloc){
    sb->buf=(strbuf*)malloc(sizeof(char)*alloc+1);
    sb->buf=NULL;
}


void strbuf_init(strbuf *sb, size_t alloc){
    static strbuf t=_strbuf_init;
    memcpy(sb,&t,sizeof(*sb));
    sb->len=0;
    sb->alloc=alloc;
    if (alloc)
        strbuf_malloc(sb,alloc);
}

void strbuf_attach(strbuf *sb, void *str, size_t len, size_t mem){
    strbuf_release(sb);
    sb->alloc=mem;
    sb->len=len;
    strbuf_malloc(sb,alloc);
    memcpy(sb->buf,str,len);
    sb->buf[sb->len]='\0';
}

void strbuf_release(strbuf *sb){
    if(sb->alloc!=0){
        free(sb->buf);
        strbuf_init(sb,0);
    }
}

void strbuf_swap(strbuf *a, strbuf *b){
    int len = a->len > b->len ? a->len : b->len ;
    int alloc = a->alloc > b->alloc ? a->alloc:b->alloc;
    strbuf *c;
    c=a;
    a=b;
    b=c;
    strbuf_reset(c);
}

char *strbuf_detach(strbuf *sb, size_t *sz)
{
    if (sz)
        *sz=sb->len;
    return sb->buf;
}

int strbuf_cmp(const strbuf *first, const strbuf *second){
    int len = first->len > second->len ? second->len : first->len ;
    int flag = memcmp(first->buf,second->buf,len);
    if (flag)
    {
        return flag;
    }
    return first->len < second->len ? -1 : a->len == b->len;
}#include<stdio.h>
#include<string.h>
#include"strbuf1.h"

void strbuf_malloc(strbuf *sb,size_t alloc){
    sb->buf=(strbuf*)malloc(sizeof(char)*alloc);
    sb->buf=NULL;
}


void strbuf_init(strbuf *sb, size_t alloc){
    static strbuf t=_strbuf_init;
    memcpy(sb,&t,sizeof(*sb));
    sb->len=0;
    sb->alloc=alloc;
    if (alloc)
        strbuf_malloc(sb,alloc);
}

void strbuf_attach(strbuf *sb, void *str, size_t len, size_t mem){
    strbuf_release(sb);
    sb->alloc=mem;
    sb->len=len;
    strbuf_malloc(sb,alloc);
    memcpy(sb->buf,str,len);
    sb->buf[sb->len]='\0';
}

void strbuf_release(strbuf *sb){
    if(sb->alloc!=0){
        free(sb->buf);
        strbuf_init(sb,0);
    }
}

void strbuf_swap(strbuf *a, strbuf *b){
    int len = a->len > b->len ? a->len : b->len ;
    int alloc = a->alloc > b->alloc ? a->alloc:b->alloc;
    strbuf *c;
    c=a;
    a=b;
    b=c;
    strbuf_reset(c);
}

char *strbuf_detach(strbuf *sb, size_t *sz)
{
    if (sz)
        *sz=sb->len;
    return sb->buf;
}

int strbuf_cmp(const strbuf *first, const strbuf *second){
    int len = first->len > second->len ? second->len : first->len ;
    int flag = memcmp(first->buf,second->buf,len);
    if (flag)
    {
        return flag;
    }
    return first->len < second->len ? -1 : a->len == b->len;
}

void strbuf_reset(strbuf *sb){
    if (sb->alloc)
    {
    strbuf_release(sb);
    sb->buf=NULL;
    }
}

void strbuf_reset(strbuf *sb){
    if (sb->alloc)
    {
    strbuf_release(sb);
    sb->buf=NULL;
    }
}
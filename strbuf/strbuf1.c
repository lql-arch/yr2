#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"strbuf1.h"
#include"strbuf2.h"

void strbuf_malloc(strbuf *sb,size_t alloc){
    sb->buf=(strbuf*)malloc(sizeof(char)*alloc+1);
    sb->buf=NULL;
}


void strbuf_init(strbuf *sb, size_t alloc){
    sb->buf=NULL;
    sb->len=0;
    sb->alloc=alloc;
    if (alloc)
        strbuf_malloc(sb,alloc);
}

void strbuf_attach(strbuf *sb, void *str, size_t len, size_t mem){
    strbuf_release(sb);
    sb->alloc=mem;
    sb->len=len;
    strbuf_malloc(sb,mem);
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
    strbuf *c;
    c=a;
    a=b;
    b=c;
}

char *strbuf_detach(strbuf *sb, size_t *sz)
{
    char *res=sb->buf;
    if (sz)
        *sz=sb->len;
    strbuf_init(sb,0);
    return res;
}

int strbuf_cmp(const strbuf *first, const strbuf *second){
    int len = first->len > second->len ? second->len : first->len ;
    int flag = memcmp(first->buf,second->buf,len);
    if (flag)
    {
        return flag;
    }
    return first->len < second->len ? -1 : first->len == second->len;
}

void strbuf_reset(strbuf *sb){
    strbuf_setlen(sb,0);
}
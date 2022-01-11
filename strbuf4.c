#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"strbuf4.h"
#include"strbuf3.h"
#include"strbuf2.h"
#include"strbuf1.h"

__ssize_t read_in_full(char *str,int len,int fd){
    FILE *fp;
    int flag=1;
    if ((fp=fopen(fd,"wb+"))==NUll)
    {
        printf("Can't open %s\n",fd);
        exit(EXIT_FAILURE);
    }
    __ssize_t got=0;
    got=fread(str,1,len,fd);
    if(feof(fp)==0  && got < len){
        flag=-1;
    }else{
        flag=1;
    }
    if (fclose(fp)!=0)
    {
        printf("fclose error");
        exit(EXIT_FAILURE);
    }
    return flag;
}

__ssize_t strbuf_read(struct strbuf *sb, int fd, size_t hint)
{
    size_t len = sb->len;
	size_t alloc = sb->alloc;

    strbuf_grow(sb,hint?hint:8192);
    while(1)
    {
        __ssize_t avail=strbuf_avail(sb);
        __ssize_t realget=read_in_full(sb->buf + sb->len,avail,fd);

        if(realget == -1){
            if(alloc == 0)
                strbuf_release(sb);
            else
                strbuf_setlen(sb,len);
            return -1;
        } 

        sb->len += realget;
        if (realget < avail)
        {
            break;
        }
        strbuf_grow(sb,8192);
    }

    sb->buf[sb->len] = '\0';
    return sb->len - len ;
}

__ssize_t strbuf_read_file(struct strbuf *sb, const char *path, size_t hint)
{
    size_t len = sb->len;
	size_t alloc = sb->alloc;

    strbuf_grow(sb,hint?hint:8192);
    
}

int strbuf_getline(struct strbuf *sb, FILE *fp)
{

}
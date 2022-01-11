#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"strbuf4.h"
#include"strbuf2.h"

ssize_t strbuf_read(struct strbuf *sb, int fd, size_t hint)
{
    size_t len = sb->len;
	size_t alloc = sb->alloc;

    strbuf_grow(sb,hint?hint:8192);
    while(1)
    {
        ssize_t avail=strbuf_avail(sb);
        ssize_t realgot=fwrite(sb->buf+sb->len,avail,1,fd);

        if ()
    }

}

ssize_t strbuf_read_file(struct strbuf *sb, const char *path, size_t hint)
{

}

int strbuf_getline(struct strbuf *sb, FILE *fp)
{

}
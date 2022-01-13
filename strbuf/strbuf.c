#include"strbuf.h"
#define MAX 128

void strbuf_malloc(struct strbuf *sb,size_t alloc){
    sb->buf=(struct strbuf*)malloc(sizeof(char)*alloc+1);
    sb->buf=NULL;
}


void strbuf_init(struct strbuf *sb, size_t alloc){
    sb->buf=NULL;
    sb->len=0;
    sb->alloc=alloc;
    if (alloc)
        strbuf_malloc(sb,alloc);
}

void strbuf_attach(struct strbuf *sb, void *str, size_t len, size_t mem){
    strbuf_release(sb);
    sb->alloc=mem;
    sb->len=len;
    strbuf_malloc(sb,mem);
    memcpy(sb->buf,str,len);
    sb->buf[sb->len]='\0';
}

void strbuf_release(struct strbuf *sb){
    if(sb->alloc!=0){
        free(sb->buf);
        strbuf_init(sb,0);
    }
}

void strbuf_swap(struct strbuf *a, struct strbuf *b){
    struct strbuf *c;
    c=a;
    a=b;
    b=c;
}

char *strbuf_detach(struct strbuf *sb, size_t *sz)
{
    char *res=sb->buf;
    if (sz)
        *sz=sb->len;
    strbuf_init(sb,0);
    return res;
}

int strbuf_cmp(const struct strbuf *first, const struct strbuf *second){
    int len = first->len > second->len ? second->len : first->len ;
    int flag = memcmp(first->buf,second->buf,len);
    if (flag)
    {
        return flag;
    }
    return first->len < second->len ? -1 : first->len == second->len;
}

void strbuf_reset(struct strbuf *sb){
    strbuf_setlen(sb,0);
}

void strbuf_grow(struct strbuf *sb, size_t extra)
{
    if(sb->alloc==0)
    {
        sb->alloc+=extra;
    }
    else
    {
        while(sb->alloc < sb->len + extra)
        {
            sb->alloc*=2;
        }
    }
    sb->len+=extra;
}

void strbuf_add(struct strbuf *sb, const void *data, size_t len)
{
    char*res=(char*)data;
    int l=sb->len;
    strbuf_grow(sb,len);
    sb->buf=(char*)realloc(sb->buf,sizeof(char) * sb->alloc + 1 );
    memcpy(sb->buf+l,res,len);
    sb->buf[sb->len]='\0';
}

void strbuf_addch(struct strbuf *sb, int c)
{
    int l=sb->len;
    strbuf_grow(sb,1);
    sb->buf=(char*)realloc(sb->buf,sizeof(char) * (sb->alloc+1));
    sb->buf[l]=(char)c;
    sb->buf[sb->len]='\0';
}

void strbuf_addstr(struct strbuf *sb, const char *s)
{
    strbuf_add(sb,s,strlen(s));
}

void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2)
{
    strbuf_add(sb,sb2->buf,sb2->len);
}  

void strbuf_setlen(struct strbuf *sb, size_t len)
{
    int alloc=sb->alloc ? sb->alloc :0;
    if (len>alloc)
    {
        exit(EXIT_FAILURE);
        fprintf(stderr,"error:len > alloc");
    }
    sb->len=len;
    sb->buf[sb->len]='\0';
}

size_t strbuf_avail(const struct strbuf *sb)
{
    size_t len = sb->alloc - sb->len;
    return len;
}

void strbuf_insert(struct strbuf *sb, size_t pos, const void *data, size_t len)
{  
    if (pos < sb->len)
    {
        sb->len=pos;
        char*res=(char*)data;
        int l=sb->len;
        strbuf_grow(sb,len);
        sb->buf=(char*)realloc(sb->buf,sizeof(char) * (sb->alloc + 1));
        memmove(sb->buf+l,res,len);
        sb->buf[sb->len]='\0';
    }
}

__ssize_t _read_in_full(char *str,int len,int fd)
{   
    char s[MAX]={0};
    char *obj=(char*)malloc(MAX);
    sprintf(s,MAX,"proc/self/fd/%d",fd);
    if(readlink(s,obj,MAX)<0)
    {
        sprintf(stderr,"readlink() error\n");
    }
    int flag=_read_in_full(str,len,obj);
    return flag;
}

__ssize_t read_in_full(char *str,int len,char* fd){
    FILE *fp;
    int flag=1;
    if ((fp=fopen(fd,"wb+"))==NULL)
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

int strbuf_getwholeline(struct strbuf *sb, FILE *fp, int end)
{
    int ch;
    if (feof(fp)!=0)
        return EOF;
    strbuf_reset(sb);

    while((ch=getc(fp)) != EOF)
    {
        if(strbuf_avail(sb)==0)
            strbuf_grow(sb,1);
        sb->buf[sb->len++]=ch;
        if(ch == end )
            break;
    }

    if (ch == EOF && sb->len == 0)
        return EOF;
    
    sb->buf[sb->len] = '\0';
    return 0;
}

__ssize_t strbuf_read(struct strbuf *sb, int fd, size_t hint)
{
    size_t len = sb->len;
	size_t alloc = sb->alloc;

    strbuf_grow(sb,hint?hint:8192);
    while(1)
    {
        __ssize_t avail=strbuf_avail(sb);
        __ssize_t realget=_read_in_full(sb->buf + sb->len,avail,fd);

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
    while(1)
    {
        __ssize_t avail=strbuf_avail(sb);
        __ssize_t realget=read_in_full(sb->buf + sb->len,avail,path);

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

int strbuf_getline(struct strbuf *sb, FILE *fp)
{
    if (strbuf_getwholeline(sb, fp, '\n')!=0)
		return EOF;
	if (sb->len && sb->buf[sb->len - 1] == '\n') 
	{
		strbuf_setlen(sb, sb->len - 1);
		if (sb->len && sb->buf[sb->len - 1] == '\r') 
			strbuf_setlen(sb, sb->len - 1);
	}
	return 0;
}

struct strbuf **strbuf_split_buf(const char *str, size_t len, int terminator, int max)
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
    struct strbuf **s;
    if(status>=max-1)
        s=(struct strbuf**)malloc(sizeof(struct strbuf*)*max);
    else   
        s=(struct strbuf**)malloc(sizeof(struct strbuf*)*(status+1));
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
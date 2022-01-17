#include"strbuf.h"
#define MaX 128
char strbuf_sp[1];

void strbuf_init(struct strbuf *sb, size_t alloc)
{
    static struct strbuf s={.buf=strbuf_sp};
    memcpy(sb,&s,sizeof(*sb));
    sb->len=0;
    sb->alloc=alloc;
    if(alloc)
        sb->buf=(char*)malloc(sizeof(char)*(alloc));
}

void strbuf_attach(struct strbuf *sb, void *str, size_t len, size_t alloc)
{
    //strbuf_release(sb);
    strbuf_init(sb,alloc);
    //sb->alloc = alloc ;
    sb->len = len;
    sb->buf = (char*)str;
    //sb->buf[sb->len]='\0';
}

void strbuf_release(struct strbuf *sb){
    if(sb->alloc!=0){
        free(sb->buf);
        // sb->buf=NULL;
        // sb->len=0;
        // sb->alloc=0;
        strbuf_init(sb,0);
    }
}

void strbuf_swap(struct strbuf *a, struct strbuf *b){
    void *swap_a = a;
	void *swap_b = b;
	unsigned char swap_buffer[sizeof(*a)];
	memcpy(swap_buffer, swap_a, sizeof(*a));
	memcpy(swap_a, swap_b, sizeof(*b));
	memcpy(swap_b, swap_buffer, sizeof(*a));
}

char *strbuf_detach(struct strbuf *sb, size_t *sz)
{
    char *res = sb->buf;
    if (sz!=NULL)
        *sz=sb->alloc;
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
    if (first->len < second->len)
    {
        return -1;
    }
    return first->len != second->len;
}

void strbuf_reset(struct strbuf *sb){
    strbuf_setlen(sb,0);
}

void strbuf_grow(struct strbuf *sb, size_t extra)
{
    if(!sb->alloc)
    {
        sb->alloc += extra +1 ;
        sb->buf = NULL;
        sb->buf = (char*)malloc(sb->alloc);
    }
    else
    {
        while(sb->alloc < sb->len + extra +1 )
        {
            sb->alloc*=2;
        }
    }
    if(!sb->alloc)
        sb->buf[0]='\0';
    sb->buf=(char*)realloc(sb->buf,sb->alloc +1);
}   

void strbuf_add(struct strbuf *sb, const void *data, size_t len)
{
    char*res=(char*)data;
    int l=sb->len;
    strbuf_grow(sb,len);
    //sb->buf=(char*)realloc(sb->buf,sizeof(char) * sb->alloc);
    memcpy(sb->buf+l,res,len);
    sb->len +=len;
    sb->buf[sb->len]='\0';
}

void strbuf_addch(struct strbuf *sb, int c)
{
    strbuf_grow(sb,2);
    //sb->buf=(char*)realloc(sb->buf,sizeof(char) * (sb->alloc));
    sb->buf[sb->len]=c;
    sb->len += 1 ;
    sb->buf[sb->len]='\0';
}

void strbuf_addstr(struct strbuf *sb, const char *s)
{
    //strbuf_add(sb,s,strlen(s));
    int len=strlen(s);
    char*res=(char*)s;
    int l=sb->len;
    strbuf_grow(sb,len+1);
    //sb->buf=(char*)realloc(sb->buf,sizeof(char) * sb->alloc);
    memcpy(sb->buf+l,res,len);
    sb->len +=len;
    sb->buf[sb->len]='\0';
}

void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2)
{
    //strbuf_add(sb,sb2->buf,sb2->len);
    int len=sb2->len;
    char*res=sb2->buf;
    int l=sb->len;
    strbuf_grow(sb,len+1);
    //sb->buf=(char*)realloc(sb->buf,sizeof(char) * sb->alloc);
    memcpy(sb->buf+l,res,len);
    sb->len +=len;
    sb->buf[sb->len]='\0';
}  

void strbuf_setlen(struct strbuf *sb, size_t len)
{
    int alloc= sb->alloc ? sb->alloc :0;
    if (len>alloc)
    {
        exit(EXIT_FAILURE);
        fprintf(stderr,"error:len > alloc");
    }
    sb->len=len;
    if(sb->buf != strbuf_sp)
        sb->buf[sb->len]='\0';
    else
        fprintf(stdout,"it is not used.");

}

size_t strbuf_avail(const struct strbuf *sb)
{
    size_t len;
    len = sb->alloc - sb->len -1 ;
    return len;
}

void strbuf_insert(struct strbuf *sb, size_t pos, const void *data, size_t len)
{  
    if (!sb->alloc)
    {
        fprintf(stderr,"Error :alloc ==0 in strbuf_insert ");
    }
    if (pos < sb->len)
    {
        char *res;
        int l = sb->len-pos ;
        res=(char*)malloc(l+1);
        for(int i=pos;i<sb->len;i++)
        {
            res[i-pos]=sb->buf[i];
        }
        res[l]='\0';
        strbuf_grow(sb,len);
        sb->len += len ;
        //sb->buf=(char*)realloc(sb->buf,sizeof(char) * (sb->alloc));
        memmove(sb->buf+pos,(char*)data,len);
        memmove(sb->buf+pos+len,res,l);
        sb->buf[sb->len]='\0';
        free(res);
    }
}

void strbuf_ltrim(struct strbuf *sb)
{   
    if (sb->buf==NULL || sb->len==0)
    {
        return ;
    }
    int len=0;
    char res[sb->len];
    int flag=1;
    for(int k=0;k<sb->len;k++)
    {
        if(!(sb->buf[k]==' '||sb->buf[k]=='\t'||sb->buf[k]=='\n'))
        {
            flag=0;
        }
        if((sb->buf[k]==' '||sb->buf[k]=='\t'||sb->buf[k]=='\n') && flag==1)
        {
            continue;
        }
        res[len++]=sb->buf[k];
    }

    sb->len = len ;
    for(int k=0;k<len;k++)
    {
        sb->buf[k]=res[k];
    }

    sb->buf[sb->len]='\0';
}
void strbuf_rtrim(struct strbuf *sb)
{
    if (sb->buf==NULL || sb->len==0)
    {
        return ;
    }
    int i=sb->len-1;
    for(;(sb->buf[i]==' '||sb->buf[i]=='\t'||sb->buf[i]=='\n') && i!=sb->len;i--)
    {}
    sb->len = i+1;
    sb->buf[sb->len]='\0';
}

void strbuf_remove(struct strbuf *sb, size_t pos, size_t len)
{
    if (sb->buf==NULL || sb->len==0)
    {
        return ;
    }
    int l=sb->len - pos - len;
    sb->len -= len;
    memmove(sb->buf+pos,sb->buf+pos+len,l);
    sb->buf[sb->len]='\0';

}

// ssize_t read_in_full(char *str,int len,const char* fd){
//     FILE *fp;
//     int flag=1;
//     if ((fp=fopen(fd,"rb+"))==NULL)
//     {
//         printf("Can't open %s\n",fd);
//         exit(EXIT_FAILURE);
//      }
//     ssize_t got=0;
//     got=fread(str,1,len,fp);
//     if(feof(fp)==0  && got < len){
//         flag=-1;
//     }else{
//         flag=1;
//     }
//     if (fclose(fp)!=0)
//     {
//         printf("fclose error");
//         exit(EXIT_FAILURE);
//     }
//     return flag;
// }

ssize_t read_full(char *str,int len,int fd)
{   
    int p;
    int num=0;
    while(len>0)
    {
        p = read(fd,str,len);
        if(p < 0 )
        {
            return -1;
        }
        if (p == 0 )
        {
            break;
        }
        num += p;
        len -= p;
        str += p;
    }
    return num;
}

ssize_t strbuf_read(struct strbuf *sb, int fd, size_t hint)
{
    size_t len = sb->len;
	size_t alloc = sb->alloc;

    strbuf_grow(sb,hint? hint : 8192);
    //sb->buf=(char*)realloc(sb->buf,sizeof(char)*sb->alloc);
    while(1)
    {
        ssize_t avail=strbuf_avail(sb);
        ssize_t realget=read_full(sb->buf + sb->len,avail,fd);

        if(realget < 0){
            if(alloc == 0)
                strbuf_release(sb);
            else
                strbuf_setlen(sb,len);
            return -1;
        } 

        sb->len += realget;
        if (realget < avail)
            break;
        strbuf_grow(sb,8192);
    }

    sb->buf[sb->len] = '\0';
    return sb->len - len ;
}

// ssize_t strbuf_read_file(struct strbuf *sb, const char *path, size_t hint)
// {
//     size_t len = sb->len;
// 	size_t alloc = sb->alloc;
//
//     strbuf_grow(sb,hint?hint:8192);
//     while(1)
//     {
//         ssize_t avail=strbuf_avail(sb);
//         ssize_t realget=read_in_full(sb->buf + sb->len,avail,path);
//
//         if(realget == -1){
//             if(alloc == 0)
//                 strbuf_release(sb);
//             else
//                 strbuf_setlen(sb,len);
//             return -1;
//         } 
//
//         sb->len += realget;
//         if (realget < avail)
//         {
//             break;
//         }
//         strbuf_grow(sb,8192);
//     }
//
//     sb->buf[sb->len] = '\0';
//     return sb->len - len ;
// }

int strbuf_getTheLine(struct strbuf *sb, FILE *fp, int end1,int end2)
{
    int ch;
    if (feof(fp))
        return EOF;
    //strbuf_reset(sb);

    while((ch=fgetc(fp)) != EOF)
    {
        if(strbuf_avail(sb)==0)
        {
            strbuf_grow(sb,1);
            //sb->buf=(char*)realloc(sb->buf,sb->alloc +1);
        }
        sb->buf[sb->len++]=ch;
        if(ch == end1 || ch == end2 )
            break;
    }

    if (ch == EOF && sb->len == 0)
        return EOF;

    sb->buf[sb->len] = '\0';
    return 0;
}

int strbuf_getline(struct strbuf *sb, FILE *fp)
{
    if (strbuf_getTheLine(sb, fp, '\n','\r')!=0)
		return EOF;
	if (sb->len && sb->buf[sb->len - 1] == '\n') 
		strbuf_setlen(sb, sb->len - 1);
    if (sb->len && sb->buf[sb->len - 1] == '\r') 
		strbuf_setlen(sb, sb->len - 1);
	return 0;
}

// struct strbuf **strbuf_split_buf(const char *str, size_t len, int terminator, int max)
// {
//     struct strbuf **res=NULL;
//     struct strbuf *sb;
//     int num=0;
//     char *s;
//     int aLen=len;
//     char *sp=(char*)malloc(len+1);
//     memcpy(sp,str,len+1);
//     sp[len]='\0';
//
//     while(len>0)
//     {
//
//         aLen=len;
//         if ( num + 1 < max) {
// 			s = (char*)memchr(sp, terminator, len);
//             if(s)
//                 aLen = s - sp + 1;
//             // while( memcmp(sp,s,2) )
//             // {
//             //     memmove(sp,sp+1,len-1);
//             //     s = (char*)memchr(sp, terminator, len);
//             //     aLen = s - sp + 1;
//             // }
//         }
//
//         sb = (struct strbuf*)malloc(sizeof(struct strbuf));
//         strbuf_init(sb,aLen);
//         if (s)
//             strbuf_add(sb,sp,aLen-1);
//         else 
//             strbuf_add(sb,sp,aLen);
//
//
//         if(!res)
//         {
//             res=(struct strbuf**)malloc(sizeof(struct strbuf*));
//             res[num++]= sb;
//         }else
//         {
//             res=(struct strbuf**)realloc(res,sizeof(struct strbuf*)*(num+2));
//             res[num++]= sb;
//         }
//
//         len -= aLen;
//         sp += aLen;
//     }
//     res=(struct strbuf**)realloc(res,sizeof(struct strbuf*)*(num+1));
//     res[num] = NULL;
//     return res;
// }

// struct strbuf **strbuf_split_buf(const char *str, size_t len, int terminator, int max)
// {
//     struct strbuf **res=NULL;
//     if(max<0)
//     {
//         return res;
//     }
//     struct strbuf *sb;
//     int alloc=0;
//     int num=0;
//     char *s;
//     char t[2];
//     char *sp=(char*)malloc(len+1);
//     int aLen=len;
//
//     t[0]=terminator;
//     t[1]='\0';
//     memcpy(sp,str,len+1);
//     s=strtok(sp,t);
//
//     while(len>0 && num < max)
//     {
//         sb = (struct strbuf*)malloc(sizeof(struct strbuf));
//         aLen=strlen(s);
//         strbuf_init(sb,aLen+1);
//         strbuf_add(sb,sp,aLen);
//         if(!res)
//         {
//             res=(struct strbuf**)malloc(sizeof(struct strbuf*)*2);
//             res[num++]= sb;
//         }else
//         {
//             res=(struct strbuf**)realloc(res,sizeof(struct strbuf*)*(num+2));
//             res[num++]= sb;
//         }
//         aLen += 1;
//         len -= aLen;
//         sp +=aLen;
//     }
//
//     res=(struct strbuf**)realloc(res,sizeof(struct strbuf*)*(num+1));
//     res[num] = NULL;
//   
//     return res;
// }

bool strbuf_begin_judge(char* target_str, const char* str, int strnlen)
{
    if(strnlen==0)
    {
        return true;
    }
    int len1=strlen(str);
    int len2=strnlen;
    if (len1>len2)
        return false;
    int flag=memcmp(target_str,str,len1);
    if(flag!=0)
        return false;
    else   
        return true;
}

char* strbuf_get_mid_buf(char* target_buf, int begin, int end, int len)
{
    if(len<1)
        return NULL;   
    int len2=end-begin;
    char*s;
    s=(char*)malloc(sizeof(char)*(len2+1));
    memcpy(s,target_buf+begin,len2+1);
    s[len2]='\0';
    return s;
}

struct strbuf **strbuf_split_buf(const char *str, size_t len, int terminator, int max)
{
    struct strbuf **ret=NULL;
    int num=0;
    struct strbuf *sb;
    char *p;
    char sp[len+1];
    char t[2];
    t[0]=terminator;
    t[1]='\0';
    memcpy(sp,str,len+1);  

    for(int i=0;i<len;i++)
    {
        if(sp[i]=='\0')
            sp[i]='#';
    }

    p=strtok(sp,t);

    while(p && num < max)
    {
        int alen = strlen(p);
        for(int i=0;i<alen;i++)
        {
            if(p[i]=='#')
            {
                p[i]='\0';
            }
        }

        sb=(struct strbuf*)malloc(sizeof(struct strbuf));
		strbuf_init(sb, alen);
		strbuf_add(sb, p, alen);

        ret=(struct strbuf**)realloc(ret,sizeof(struct strbuf*)*(num+2));
		ret[num++] = sb;

        p=strtok(NULL,t);
    }

    if(ret==NULL)
        ret=(struct strbuf**)realloc(ret,sizeof(struct strbuf*)*(num+1));
	ret[num] = NULL;
    
	return ret;
}

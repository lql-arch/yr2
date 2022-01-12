typedef struct strbuf {
  int len;     //当前缓冲区（字符串）长度
  int alloc;   //当前缓冲区（字符串）容量
  char *buf;   //缓冲区（字符串）
}strbuf;

__ssize_t _read_in_full(char *str,int len,int fd);

__ssize_t read_in_full(char *str,int len,char* fd);

int strbuf_getwholeline(strbuf *sb, FILE *fp, int end);

__ssize_t strbuf_read(struct strbuf *sb, int fd, size_t hint);	
//为 sb 直接扩容 hint ? hint : 8192 大小， 然后将文件描述符为 fd 的所有文件内容读取到 sb 中。

__ssize_t strbuf_read_file(struct strbuf *sb, const char *path, size_t hint);	
//为 sb 直接扩容 hint ? hint : 8192 大小， 然后将路径为 path 的所有文件内容读取到 sb 中。

int strbuf_getline(struct strbuf *sb, FILE *fp);	
//将 将文件句柄为 fp 的一行内容读取到 sb 。
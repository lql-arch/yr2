typedef struct strbuf {
  int len;     //当前缓冲区（字符串）长度
  int alloc;   //当前缓冲区（字符串）容量
  char *buf;   //缓冲区（字符串）
}strbuf;

struct strbuf **strbuf_split_buf(const char *str, size_t len, int terminator, int max);
/*
* 将长度为 len 的字符串 str 根据切割字符
* terminator 切成多个 strbuf,并从结果返回，
* max 可以用来限定最大切割数量。
*/

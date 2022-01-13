typedef struct strbuf {
  int len;     //当前缓冲区（字符串）长度
  int alloc;   //当前缓冲区（字符串）容量
  char *buf;   //缓冲区（字符串）
}strbuf;

strbuf **strbuf_split_buf(const char *str, size_t len, int terminator, int max);
/*
* 将长度为 len 的字符串 str 根据切割字符
* terminator 切成多个 strbuf,并从结果返回，
* max 可以用来限定最大切割数量。
*/

//实现判断一个 strbuf 是否以指定字符串开头的功能
int strbuf_start(strbuf* sb,const char*str);

//获取字符串从坐标 [begin, end) 的所有内容(可以分成引用和拷贝两个模式)
char* str_(const char*str,int begin,int end);
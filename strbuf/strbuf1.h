typedef struct strbuf {
  int len;     //当前缓冲区（字符串）长度
  int alloc;   //当前缓冲区（字符串）容量
  char *buf;   //缓冲区（字符串）
}strbuf;

void strbuf_malloc(strbuf *sb,size_t alloc);

void strbuf_init(strbuf *sb, size_t alloc);	
//初始化 sb 结构体，容量为 alloc。

void strbuf_attach(strbuf *sb, void *str, size_t len, size_t alloc);	
//将字符串填充到 sb 中，长度为 len, 容量为 alloc。

void strbuf_release(strbuf *sb);	
//释放 sb 结构体的内存。

void strbuf_swap(strbuf *a, strbuf *b);	
//交换两个 strbuf。

char *strbuf_detach(strbuf *sb, size_t *sz);	
//将 sb 中的原始内存取出，并获得其长度。

int strbuf_cmp(const strbuf *first, const strbuf *second);	
//比较两个 strbuf 的内存是否相同。

void strbuf_reset(strbuf *sb);	//清空 sb。

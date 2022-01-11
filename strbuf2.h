typedef struct strbuf {
  int len;     //当前缓冲区（字符串）长度
  int alloc;   //当前缓冲区（字符串）容量
  char *buf;   //缓冲区（字符串）
}strbuf;

void strbuf_grow(struct strbuf *sb, size_t extra);	
//将 sb 的长度扩大 extra。

void strbuf_add(struct strbuf *sb, const void *data, size_t len);	
//向 sb 追加长度为 len 的数据 data。

void strbuf_addch(struct strbuf *sb, int c);	
//向 sb 追加一个字符 c。

void strbuf_addstr(struct strbuf *sb, const char *s);	
//向 sb 追加一个字符串 s。

void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2);	
//向一个 sb 追加另一个 strbuf的数据。

static inline void strbuf_setlen(struct strbuf *sb, size_t len);	
//设置 sb 的长度 len。

static inline size_t strbuf_avail(const struct strbuf *sb);	
//计算 sb 目前仍可以向后追加的字符串长度。

void strbuf_insert(struct strbuf *sb, size_t pos, const void *data, size_t len);	
//向 sb 内存坐标为 pos 位置插入长度为 len 的数据 data。
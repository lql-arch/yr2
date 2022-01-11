typedef struct strbuf {
  int len;     //当前缓冲区（字符串）长度
  int alloc;   //当前缓冲区（字符串）容量
  char *buf;   //缓冲区（字符串）
}strbuf;

void strbuf_ishalf(strbuf *sb);

void strbuf_rtrim(struct strbuf *sb);	
//去除 sb 缓冲区左端的所有 空格，tab, '\t'。
void strbuf_ltrim(struct strbuf *sb);	
//去除 sb 缓冲区右端的所有 空格，tab, '\t'。
void strbuf_remove(struct strbuf *sb, size_t pos, size_t len);	
//删除 sb 缓冲区从 pos 坐标长度为 len 的内容。
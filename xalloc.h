#ifndef XALLOC
#define XALLOC

void memory_error(void);
void *xmalloc(size_t size);
void *xrealloc(void *ptr, size_t size);

#endif

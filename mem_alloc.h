#ifndef MEM_ALLOC
#define MEM_ALLOC

#include <stdlib.h>

void mem_err();
void *guarded_malloc(size_t size);
void *guarded_realloc(void *ptr, size_t size);

#endif
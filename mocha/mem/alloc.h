#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifndef _MEM_ALLOC_H
#define _MEM_ALLOC_H

void *malloc(size_t size);
void free(void *ptr);
void mempool_init(size_t heap_size);
void init_alloc();

#endif

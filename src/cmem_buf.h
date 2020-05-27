#ifndef CMEM_BUF_H
#define CMEM_BUF_H

#include <stdint.h>

void init_cmem();
int alloc_cmem_buffer(unsigned int size, unsigned int align, void **cmem_buf);
void free_cmem_buffer(void *cmem_buffer);
int dma_buf_do_cache_operation(int dma_buf_fd, uint32_t cache_operation);
#endif //CMEM_BUF_H

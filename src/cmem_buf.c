#include "cmem_buf.h"
#include <stdio.h>
#include <unistd.h>
#include <ti/cmem.h>
#include <linux/dma-buf.h>
#include <sys/ioctl.h>

#define CMEM_BLOCKID CMEM_CMABLOCKID

CMEM_AllocParams cmem_alloc_params = {
	CMEM_HEAP,	/* type */
	CMEM_CACHED,	/* flags */
	1		/* alignment */
};

void init_cmem()
{
	CMEM_init();
}

int alloc_cmem_buffer(unsigned int size, unsigned int align, void **cmem_buf)
{
	cmem_alloc_params.alignment = align;

	*cmem_buf = CMEM_alloc2(CMEM_BLOCKID, size,
		&cmem_alloc_params);

	if(*cmem_buf == NULL){
		printf("CMEM allocation failed");
		return -1;
	}
	printf("CMEM buffer pointer is 0x%x\n",(uint32_t) *cmem_buf );
	return CMEM_export_dmabuf(*cmem_buf);
}

void free_cmem_buffer(void *cmem_buffer)
{
	CMEM_free(cmem_buffer, &cmem_alloc_params);
}

int dma_buf_do_cache_operation(int dma_buf_fd, uint32_t cache_operation) 
{
	int ret;
	struct dma_buf_sync sync;
	sync.flags = cache_operation;

	ret = ioctl(dma_buf_fd, DMA_BUF_IOCTL_SYNC, &sync);

	return ret;
}


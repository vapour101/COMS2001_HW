/*
 * mm_alloc.c
 *
 * Stub implementations of the mm_* routines. Remove this comment and provide
 * a summary of your allocator's design here.
 */

#include "mm_alloc.h"

#include <stdlib.h>
#include <string.h>

/* Your final implementation should comment out this macro. */
#define MM_USE_STUBS
static struct s_block tail;
static struct s_block head = {0, &tail, NULL, 0, NULL};
static struct s_block tail = {0, NULL, &head, 0, NULL};

void* mm_malloc(size_t size)
{
	for (s_block_ptr blk = head.next; blk != &tail; blk = blk->next)
	{
		if (blk->free == 0 || blk->size < size)
			continue;
		
		split_block(blk, size);
		blk->free = 0;
		return blk->ptr;
	}
	
	s_block_ptr blk = extend_heap(tail.prev, size);
	blk->free = 0;
	return blk->ptr;
}

void* mm_realloc(void* ptr, size_t size)
{
	void* newLoc = mm_malloc(size);
	memcpy(newLoc, ptr, size);
	mm_free(ptr);
	return newLoc;
}

void mm_free(void* ptr)
{
	s_block_ptr blk = get_block(ptr);
	blk->free = 1;
	fusion(blk);
}

s_block_ptr fusion(s_block_ptr b)
{
	if (b->prev->free == 1)
		fusion(b->prev);
	
	if (b->next->free == 1)
	{
		b->next->next->prev = b;
		b->size += BLOCK_SIZE + b->next->size;
		b->next = b->next->next;
		
		fusion(b);
	}
	
	return b;
}

s_block_ptr get_block (void* p)
{
	for (s_block_ptr blk = head.next; blk != &tail; blk = blk->next)
		if (blk->ptr <= p && p  < (void*)(blk->data + blk->size))
			return blk;
		
	return NULL;
}

void split_block (s_block_ptr b, size_t s)
{
	if ((b->size - BLOCK_SIZE) < s)
		return;
	
	s_block_ptr newBlock = (s_block_ptr)( ((char*)b) + BLOCK_SIZE + s );
	
	newBlock->size = (b->size - BLOCK_SIZE - s);
	b->size = BLOCK_SIZE + s;
	
	newBlock->next = b->next;
	b->next = newBlock;
	
	newBlock->prev = b;
	if (newBlock->next)
		newBlock->next->prev = newBlock;
	
	newBlock->free = 1;
	newBlock->ptr = (void*) newBlock->data;
}

s_block_ptr extend_heap (s_block_ptr last , size_t s)
{
	s_block_ptr blk = (s_block_ptr) sbrk(BLOCK_SIZE + s);
	
	blk->size = s;
	blk->next = &tail;
	tail.prev = blk;
	blk->prev = last;
	blk->free = 1;
	blk->ptr = (void*) blk->data;
	
	last->next = blk;
	
	return blk;
}

/*!  Dynamic memory allocator - first fit */

#define _FF_SIMPLE_C_
#include <lib/ff_simple.h>
#include <stdio.h>

#ifndef ASSERT
#include ASSERT_H
#endif

/*!
 * Initialize dynamic memory manager
 * \param mem_segm Memory pool start address
 * \param size Memory pool size
 * \return memory pool descriptor
*/
void *ffs_init(void *mem_segm, size_t size)
{
	size_t start, end;
	ffs_hdr_t *chunk, *border;
	ffs_mpool_t *mpool;

	ASSERT(mem_segm && size > sizeof(ffs_hdr_t) * 2);

	/* align all on 'size_t' (if already not aligned) */
	start = (size_t) mem_segm;
	end = start + size;
	ALIGN_FW(start);
	mpool = (void *) start;		/* place mm descriptor here */
	start += sizeof(ffs_mpool_t);
	ALIGN(end);

	mpool->first = NULL;

	if (end - start < 2 * HEADER_SIZE)
		return NULL;

	border = (ffs_hdr_t *) start;
	border->size = sizeof(size_t);
	MARK_USED(border);

	chunk = GET_AFTER(border);
	chunk->size = end - start - 2 * sizeof(size_t);
	MARK_FREE(chunk);
	CLONE_SIZE_TO_TAIL(chunk);

	border = GET_AFTER(chunk);
	border->size = sizeof(size_t);
	MARK_USED(border);

	ffs_insert_chunk(mpool, chunk); /* first and only free chunk */

	
	void* chunks[100];
	// inicijalno zauzimanje
	for(int i = 0; i < 25; i++){
		chunks[i] = ffs_alloc(mpool, (size_t) 128);
	}

	for(int i = 0; i < 25; i++){
		chunks[i + 25] = ffs_alloc(mpool, (size_t) 256);
	}
	
	for(int i = 0; i < 25; i++){
		chunks[i + 50] = ffs_alloc(mpool, (size_t) 512);
	}
	
	for(int i = 0; i < 25; i++){
		chunks[i + 75] = ffs_alloc(mpool, (size_t) 1024);
	}
	
	// brisanje
	for(int i = 0; i < 100; i++){
		if(chunks[i] != NULL){
			printf("Deleteing chunk %n in init\n", i);
			ffs_free(mpool, chunks[i]);
		}
	}

	printf("Init finished\n");
	

	return mpool;
}

/*!
 * Get free chunk with required size (or slightly bigger)
 * \param mpool Memory pool to be used (if NULL default pool is used)
 * \param size Requested chunk size
 * \return Block address, NULL if can't find adequate free chunk
 */
void *ffs_alloc(ffs_mpool_t *mpool, size_t size)
{
	ffs_hdr_t *iter, *chunk;

	ASSERT(mpool);

	size += sizeof(size_t) * 2; /* add header and tail size */
	if (size < HEADER_SIZE)
		size = HEADER_SIZE;

	/* align request size to higher 'size_t' boundary */
	ALIGN_FW(size);

	iter = mpool->first;
	while (iter != NULL && iter->size < size){
		iter = iter->next;
	}

	if (iter == NULL){
		printf("No adequate free chunk found\n");
		return NULL; /* no adequate free chunk found */
	}

	printf("Adequate free chunk found: ");
	if (iter->size == size + HEADER_SIZE)
	{
		printf("Chunk is the same size\n");
		/* split chunk */
		/* first part remains in free list, just update size */
		iter->size -= size;
		CLONE_SIZE_TO_TAIL(iter);

		chunk = GET_AFTER(iter);
		chunk->size = size;
	}
	else { /*return null*/
		printf("Chunk is not the same size\n");
		return NULL; /* no adequate free chunk found */
	}

	MARK_USED(chunk);
	CLONE_SIZE_TO_TAIL(chunk);

	return ((void *) chunk) + sizeof(size_t);
}

/*!
 * Free memory chunk
 * \param mpool Memory pool to be used (if NULL default pool is used)
 * \param chunk Chunk location (starting address)
 * \return 0 if successful, -1 otherwise
 */
int ffs_free(ffs_mpool_t *mpool, void *chunk_to_be_freed)
{
	ffs_hdr_t *chunk;

	ASSERT(mpool && chunk_to_be_freed);

	chunk = chunk_to_be_freed - sizeof(size_t);
	ASSERT(CHECK_USED(chunk));

	MARK_FREE(chunk); /* mark it as free */

	/* insert chunk in free list */
	ffs_insert_chunk(mpool, chunk);

	/* set chunk tail */
	CLONE_SIZE_TO_TAIL(chunk);

	return 0;
}

/*!
 * Routine that removes a chunk from 'free' list (free_list)
 * \param mpool Memory pool to be used
 * \param chunk Chunk header
static void ffs_remove_chunk(ffs_mpool_t *mpool, ffs_hdr_t *chunk)
{
	if (chunk == mpool->first) /* first in list?
		mpool->first = chunk->next;
	else
		chunk->prev->next = chunk->next;

	if (chunk->next != NULL)
		chunk->next->prev = chunk->prev;
}
*/

/*!
 * Routine that insert a chunk into 'free' list (free_list)
 * \param mpool Memory pool to be used
 * \param chunk Chunk header
 */
static void ffs_insert_chunk(ffs_mpool_t *mpool, ffs_hdr_t *chunk)
{
	chunk->next = mpool->first;
	chunk->prev = NULL;

	if (mpool->first)
		mpool->first->prev = chunk;

	mpool->first = chunk;
}

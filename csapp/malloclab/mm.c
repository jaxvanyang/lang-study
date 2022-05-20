/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 *
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include "mm.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "ateam",
    /* First member's full name */
    "Harry Bovik",
    /* First member's email address */
    "bovik@cs.cmu.edu",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""};

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8
#define WSIZE 4
#define DSIZE 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~0x7)

#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

#define MAX(x, y) ((x) > (y) ? (x) : (y))

// Pack a size and allocated bit into a word
#define PACK(size, alloc) ((size) | (alloc))

// Read and write a word at address p
#define GET(p) (*(unsigned int *)(p))
#define PUT(p, val) (*(unsigned int *)(p) = (val))

// Read the size and allocated fields from address p
// Note: p must be a header or footer address
#define GET_SIZE(p) (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

// Given block ptr bp, compute address of its header and footer
#define HDRP(bp) ((char *)(bp)-WSIZE)
// Header block needed
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

// Given block ptr bp, compute address of next and previous blocks
#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(((char *)(bp)-WSIZE)))
#define PREV_BLKP(bp) ((char *)(bp) - GET_SIZE(((char *)(bp)-DSIZE)))

// heap pointer range
static void *heap_listp;
static void *heap_endp;

/*
 * mm_init - initialize the malloc package.
 */
int mm_init(void) {
  // we can use page size as allocation unit to improve performance
  // size_t pagesize = ALIGN(mem_pagesize());
  size_t min_size = 4 * WSIZE;  // total size of padding and helper blocks
  size_t alloc_size = min_size;

  if ((heap_listp = mem_sbrk(alloc_size)) == (void *)-1) {
    return -1;
  }

  PUT(heap_listp, 0);                       // Alignment padding
  PUT(heap_listp + WSIZE, PACK(DSIZE, 1));  // Prologue header
  PUT(heap_listp + DSIZE, PACK(DSIZE, 1));  // Prologue footer

  // Create a free block if specified size is larger than minimum size
  if (alloc_size > min_size) {
    PUT(heap_listp + 3 * WSIZE, alloc_size - 4 * WSIZE);  // Free block header
    PUT(heap_listp + alloc_size - DSIZE,
        alloc_size - 4 * WSIZE);  // Free block footer
  }
  PUT(heap_listp + alloc_size - WSIZE, 1);  // Epilogue header
  heap_endp = heap_listp + alloc_size;
  heap_listp += 2 * DSIZE;

  // if (!mm_check()) {
  //   fprintf(stderr, "mm_init: mm_check failed\n");
  //   exit(EXIT_FAILURE);
  // }
  return 0;
}

/*
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size) {
  size_t alloc_size =
      ALIGN(size + DSIZE);  // Align block size, including header and footer
  void *bp;

  // fprintf(stderr, "size = %d, alloc_size = %d\n", size, alloc_size);

  // Find suitable block
  for (bp = heap_listp; bp != heap_endp; bp = NEXT_BLKP(bp)) {
    if (GET_ALLOC(HDRP(bp))) continue;
    if (GET_SIZE((HDRP(bp))) >= alloc_size) break;
  }

  if (bp == heap_endp) {
    void *prev_bp = PREV_BLKP(bp);
    size_t shrink_size = alloc_size;

    // extends the free block at heap end if possible to decrease the alloc_size
    if (!GET_ALLOC(HDRP(prev_bp))) {
      shrink_size -= GET_SIZE(HDRP(prev_bp));
      bp = prev_bp;
    }

    if (mem_sbrk(shrink_size) == (void *)-1) {
      return NULL;
    }

    // If extending succeed, update heap range
    heap_endp += shrink_size;
    PUT(HDRP(heap_endp), 1);  // Move the epilogue header to the new end
    // Write header and footer of the new block
    PUT(HDRP(bp), PACK(alloc_size, 1));
    PUT(FTRP(bp), PACK(alloc_size, 1));
  } else {
    // Split a block from the suitable block
    size_t remain_size = GET_SIZE(HDRP(bp)) - alloc_size;

    if (remain_size <= DSIZE) {
      // if remain size is too small, just mark the block as allocated
      GET(HDRP(bp)) |= 1;
      GET(FTRP(bp)) |= 1;
    } else {
      // Resize the old block
      PUT(HDRP(bp), PACK(alloc_size, 1));
      PUT(FTRP(bp), PACK(alloc_size, 1));
      // Create a new block
      char *next_bp = NEXT_BLKP(bp);
      PUT(HDRP(next_bp), remain_size);
      PUT(FTRP(next_bp), remain_size);
    }
  }

  // if (!mm_check()) {
  //   fprintf(stderr, "mm_malloc(%d): mm_check failed\n", size);
  //   exit(EXIT_FAILURE);
  // }

  return bp;
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr) {
  if (ptr == NULL) {
    return;
  }

  // Check if the block is in the heap
  if (ptr < heap_listp || ptr >= heap_endp) {
    return;
  }

  // Check if the block is already free
  if (!GET_ALLOC(HDRP(ptr))) return;

  // Coalesce free blocks in different conditions
  char *prev_bp = PREV_BLKP(ptr);
  char *next_bp = NEXT_BLKP(ptr);
  if (!GET_ALLOC(HDRP(prev_bp))) {
    if (GET_ALLOC(HDRP(next_bp))) {
      // prev free & next allocated, coalesce prev and cur
      GET(HDRP(prev_bp)) += GET_SIZE(HDRP(ptr));
      PUT(FTRP(prev_bp), GET(HDRP(prev_bp)));
    } else {
      // prev free & next free, coalesce prev, cur and next
      GET(HDRP(prev_bp)) += GET_SIZE(HDRP(ptr)) + GET_SIZE(HDRP(next_bp));
      PUT(FTRP(prev_bp), GET(HDRP(prev_bp)));
    }
  } else if (GET_ALLOC(HDRP(next_bp))) {
    // prev allocated & next allocated, only modify cur's alloc bit
    GET(HDRP(ptr)) ^= 1;
    GET(FTRP(ptr)) ^= 1;
  } else {
    // prev allocated & next free, coalesce cur and next
    GET(HDRP(ptr)) += GET_SIZE(HDRP(next_bp));
    PUT(FTRP(ptr), GET(HDRP(ptr)));
  }

  // if (!mm_check()) {
  //   fprintf(stderr, "mm_free: mm_check failed\n");
  //   exit(EXIT_FAILURE);
  // }
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size) {
  void *next_bp, *new_ptr;
  size_t old_size = GET_SIZE(HDRP(ptr));
  size_t align_size = ALIGN(size + DSIZE);
  size_t remain_size;
  size_t next_size;

  // modify the old block in place if it satisfies the size requirement
  if (align_size <= old_size) {
    remain_size = old_size - align_size;
    // if the remaining size is too small, just return without modification
    if (remain_size <= DSIZE) return ptr;

    // if the remaining size is large enough, split the block
    PUT(HDRP(ptr), PACK(align_size, 1));  // modified header
    PUT(FTRP(ptr), PACK(align_size, 1));  // modified footer
    next_bp = NEXT_BLKP(ptr);
    PUT(HDRP(next_bp), remain_size);  // new block header
    PUT(FTRP(next_bp), remain_size);  // new block footer
    return ptr;
  }

  // try to extend the block if it is not large enough
  next_bp = NEXT_BLKP(ptr);
  next_size = GET_SIZE(HDRP(next_bp));
  if (!GET_ALLOC(HDRP(next_bp)) && next_size + old_size >= align_size) {
    // remaining size of the next block
    remain_size = next_size + old_size - align_size;
    // if the remaining size is too small, just merge the next block fully
    if (remain_size <= DSIZE) {
      GET(HDRP(ptr)) += next_size;
      PUT(FTRP(ptr), GET(HDRP(ptr)));
      return ptr;
    }

    // if the remaining size is large enough, split the next block
    PUT(HDRP(ptr), PACK(align_size, 1));  // modified header
    PUT(FTRP(ptr), PACK(align_size, 1));  // modified footer
    next_bp = NEXT_BLKP(ptr);
    PUT(HDRP(next_bp), remain_size);  // new block header
    PUT(FTRP(next_bp), remain_size);  // new block footer
    return ptr;
  }

  // allocate a new block and copy the old data
  mm_free(ptr);               // free the old block
  new_ptr = mm_malloc(size);  // try to allocate a new block
  if (new_ptr == NULL) return NULL;
  memmove(new_ptr, ptr, old_size - DSIZE);  // copy the old data
  return new_ptr;
}

int mm_check(void) {
  char *bp, *next_bp;
  int i;

  fprintf(stderr, "Checking heap consistency...\n");
  for (i = 0, bp = heap_listp; bp != heap_endp; ++i, bp = next_bp) {
    next_bp = NEXT_BLKP(bp);
    fprintf(stderr, "%d: bp = %p, next_bp = %p, size = %d, alloc = %d\n", i, bp,
            next_bp, GET_SIZE(HDRP(bp)), GET_ALLOC(HDRP(bp)));
    if (bp >= next_bp) {
      fprintf(stderr, "%d: Computation of the next block pointer error\n", i);
      return 0;
    }
    if (GET_SIZE(HDRP(bp)) == 0) {
      fprintf(stderr, "%d: Warning: block size equals to 0\n", i);
    }

    // Check header validity
    if (GET_ALLOC(HDRP(bp)) > 1) {
      fprintf(stderr, "%d: Bad block header alloc bit\n", i);
      return 0;
    }

    // Check free block footer validity
    if (!GET_ALLOC(HDRP(bp))) {
      if (GET(FTRP(bp)) != GET(HDRP(bp))) {
        fprintf(stderr, "%d: Unmatched header and footer\n", i);
        return 0;
      }
      if (GET_ALLOC(FTRP(bp)) > 1) {
        fprintf(stderr, "%d: Bad block footer alloc bit\n", i);
        return 0;
      }
    }
  }

  return 1;
}
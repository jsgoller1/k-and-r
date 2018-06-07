#include "malloc_j.h"
#include <stdio.h>

// malloc_j(): a general purpose storage allocator; returns
// a pointer to a chunk of bytes usable for any purpose.
void *malloc_j(size_t bytes) {
  if (bytes == 0) {
    printf("malloc_j() | warning: must allocate at least 1B (0 requested).\n");
    return NULL;
  }

  if (bytes > INIT_PAGE_SIZE - sizeof(header)) {
    printf("malloc_j() | warning: %d bytes exceeds max size allowed (%lu B).\n",
           bytes, INIT_PAGE_SIZE - sizeof(header));
    return NULL;
  }
  // printf("malloc_j() | %d bytes requested.\n", nbytes);

  // determine how large an acceptable free chunk must be, in multiples of
  // sizeof(header); if we find one that's too big, we will need to split
  // it into two chunks, which must both be at least sizeof(header)+1 in size.
  size_t units = (bytes + sizeof(header) - 1) / sizeof(header) + 1;

  // walk the list until either we come back to the start or we find a suitable
  // block
  header *p, *prev_node;
  for (prev_node = free_list, p = free_list->next; units > p->size;
       prevp = p, p = p->next) {
    if (p == free_list && p < prev_node) {
      printf("malloc_j() | error: no suitable blocks in free list.\n");
      return NULL;
    }
  }

  // p->size is too big; create a new chunk from the tail
  // of p and return that
  if (p->size > units) {
    // allocate the tail end
    p->size = nunits;
    p += p->size;
    p->size = units;
  }
  // p->size == nbytes; remove from list and return
  else {
    prev_node->next = p->next;
  }

  return p + sizeof(header);
}

// calloc_j(): same as malloc, but creates an array of count * size length and
// all bytes to zero
void *calloc_j(const size_t size, const size_t count) {
  size_t total_bytes = size * count;
  void *space = malloc_j(total_bytes);
  memset(space, 0, total_bytes);
  return space;
}

#pragma once

#define PAGE_SIZE       4096    // 4KB
#define PAGE_SHIFT      12      // 2^12

void *alloc_pages(int order);
void free_pages(void *address, int order);
void page_allocator_init(void);

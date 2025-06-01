#include "kernel.h"
#include "page_allocator.h"
#include "console.h"

extern char __heap_start[];
extern char __heap_end[];

#define MAX_ORDER       9

struct Page {
        int dummy;
};

struct Page pagelist[(512 * 1024 * 1024) / PAGE_SIZE];

#define KB(_npages)     ((_npages) << 2)

static inline unsigned int address_to_index(uint64_t address)
{
        return (address - (uint64_t)__heap_start) / PAGE_SIZE;
}

static struct Page *address_to_page(uint64_t address)
{
        return &pagelist[address_to_index(address)];
}

static unsigned int page_to_index(struct Page *page)
{
        return page - pagelist;
}

static uint64_t page_to_address(struct Page *page)
{
        return (uint64_t)__heap_start + page_to_index(page) * PAGE_SIZE;
}

void *alloc_pages(int order)
{
        struct Page *page = NULL;

        // allocate page

        if (page)
                return (void *)page_to_address(page);
        else
                return NULL;
}

#define PA2PFN(_pa)             ((uint64_t)(_pa) >> PAGE_SHIFT)
#define PFN2PA(_pfn)            ((_pfn) << PAGE_SHIFT)

void free_pages(void *address, int order)
{
        struct Page *page;

        page = address_to_page((uint64_t)address);

        // free pages!
}

void page_allocator_init (void)
{
        puts("heap ");
        puth((uint64_t)__heap_start);
        puts("-");
        puth((uint64_t)__heap_end);
        puts(" ");
        puth((uint64_t)__heap_end - (uint64_t)__heap_start);
        puts(" Bytes\n");

        for (uint64_t s = (uint64_t)__heap_start; s < (uint64_t)__heap_end; s += PAGE_SIZE) {
                free_pages((void *)s, 0);
        }
}

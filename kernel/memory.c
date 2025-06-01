#include "kernel.h"
#include "process.h"
#include "page_allocator.h"
#include "util.h"
#include "app_loader.h"
#include "console.h"
#include "segmentation.h"
#include "memory.h"

struct Entry {
  unsigned int present : 1;
  unsigned int writable : 1;
  unsigned int user_accessible : 1;
  unsigned int write_through_caching : 1;
  unsigned int disable_cache : 1;
  unsigned int accessed : 1;
  unsigned int dirty : 1;
  unsigned int huge_page : 1;
  unsigned int global : 1;
  unsigned int available1 : 3;
  unsigned long long physical_address : 40;
  unsigned int available2 : 11;
  unsigned int no_execute : 1;
} __attribute__((packed));

uint64_t *kernel_cr3;

#define PIDX(_level, _addr) (((_addr) >> (12 + ((_level) - 1) * 9)) & 0x1ff)

struct Entry *pagetable_walk(uint64_t *cr3, uint64_t virtual_address)
{
        return NULL;
}

static void map_user_page(uint64_t *cr3, uint64_t va, uint64_t pa)
{
        ;
}

void copy_userspace_memory(struct Process *newproc, struct Process *proc)
{
        struct Entry *pte;
        void *code, *oldcode;
        void *stack, *oldstack;
        uint64_t *process_cr3;

        process_cr3 = alloc_pages(0);
        if (!process_cr3)
                return;
        memset(process_cr3, 0, PAGE_SIZE);

        newproc->pagetable = process_cr3;

        // map kernel code

        // copy user code

        // copy user stack
}

void init_process_pagetable(struct Process *process, struct App *app)
{
        uint64_t *process_cr3;
        void *code, *stack;

        process_cr3 = alloc_pages(0);
        if (!process_cr3)
                return;
        memset(process_cr3, 0, PAGE_SIZE);

        process->pagetable = process_cr3;

        // map kernel code

        // map user code
        // user code starts at app->elf_program_start

        // map user stack
        // [USERSTACK_BOTTOM-USERSTACK_TOP)
}

void load_process_pagetable(struct Process *process)
{
        uint64_t *pagetable = process->pagetable;

        // load tss
        tss.rsp0 = (uint64_t)process->kernel_stack + PAGE_SIZE;

        asm volatile ("mov %0, %%cr3" :: "r"(pagetable));
}

void init_virtual_memory() {
        // Save kernel cr3 register value
        asm volatile ("mov %%cr3, %0" : "=r"(kernel_cr3));
}

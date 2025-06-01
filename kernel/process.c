#include "kernel.h"
#include "process.h"
#include "memory.h"
#include "page_allocator.h"
#include "util.h"
#include "console.h"
#include "app_loader.h"
#include "segmentation.h"
#include "fs.h"

#define NPROC           256

void trapret(void);
void context_switch(uint64_t *prev_sp, uint64_t *next_sp);

static uint64_t kernel_sp;
struct Process *current_process;

static struct Process process_table[NPROC];
static unsigned int process_id = 0;

static unsigned int alloc_process_id(void)
{
        return process_id++;
}

static struct Process *alloc_process(void)
{
        for (int i = 0; i < NPROC; i++) {
                if (process_table[i].state == NONE) {
                        process_table[i].state = CREATED;
                        return &process_table[i];
                }
        }

        return NULL;
}

static void dump_process_table(void)
{
        for (int i = 0; i < NPROC; i++) {
                if (process_table[i].state != NONE) {
                        // print process state
                }
        }
}

static void free_process(struct Process *process)
{
        free_pages(process->kernel_stack, 0);
        process->state = NONE;
}

#define EFLAGS_IF             (1 << 9)

static uint64_t kernel_cs(void)
{
        uint64_t cs;

        asm volatile ("mov  %%cs, %0" : "=r" (cs));

        return cs;
}

static uint64_t kernel_ss(void)
{
        uint64_t ss;

        asm volatile ("mov  %%ss, %0" : "=r" (ss));

        return ss;
}

static struct Process *new_process(struct App *app)
{
        struct Process *process;
        void *stack_pointer;
        uint64_t rflags;

        process = alloc_process();
        if (!process)
                return NULL;

        process->process_id = alloc_process_id();

        process->kernel_stack = alloc_pages(0);
        if (!process->kernel_stack)
                return NULL;
        memset(process->kernel_stack, 0, PAGE_SIZE);

        strcpy(process->name, app->name);

        // init_process_pagetable(process, app);

        stack_pointer = process->kernel_stack + PAGE_SIZE;
        stack_pointer -= sizeof(struct TrapFrame);

        asm volatile (
                "pushfq\n"
                "pop  %0\n" : "=r" (rflags)
        );

        ((struct TrapFrame *)stack_pointer)->cs = kernel_cs();
        // ((struct TrapFrame *)stack_pointer)->cs = (SEG_UCODE << 3) | DPL_USER;
        ((struct TrapFrame *)stack_pointer)->rflags = rflags | EFLAGS_IF;
        ((struct TrapFrame *)stack_pointer)->ss = kernel_ss();
        // ((struct TrapFrame *)stack_pointer)->ss = (SEG_UDATA << 3) | DPL_USER;
        ((struct TrapFrame *)stack_pointer)->rip = (uint64_t)app->entrypoint;
        // ((struct TrapFrame *)stack_pointer)->rsp = (uint64_t)USERSTACK_TOP;

        process->tf = (struct TrapFrame *)stack_pointer;

        stack_pointer -= sizeof(struct Context);
        ((struct Context *)stack_pointer)->rip = (uint64_t)trapret;

        process->rsp = (uint64_t)stack_pointer;

        // enqueue process in Ready Queue
        process->state = READY;

        return process;
}

void wakeup_process(struct Process *process)
{
        ;
}

void sleep_process(struct Process *process)
{
        ;
}

int exit_process(struct Process *process, int ret)
{
        return -1;
}

int fork_process(struct Process *process)
{
        struct Process *newproc;
        void *stack_pointer;

        newproc = alloc_process();
        newproc->process_id = alloc_process_id();

        newproc->kernel_stack = alloc_pages(0);
        if (!newproc->kernel_stack)
                return -1;

        strcpy(newproc->name, process->name);

        // Copy user memory from process to newproc

        // copy trapframe to newproc

        // set stack pointer to newproc

        newproc->parent = process;
        newproc->state = READY;

        return newproc->process_id;
}

int exec(struct Process *proc, char *name)
{
        struct App app = {0};
        char *code = alloc_pages(0);
        if (!code)
                return -1;
        memset(code, 0, PAGE_SIZE);

        read_file(name, code);

        if (app_elf_parse(&app, name, code) < 0)
                goto err;

        init_process_pagetable(proc, &app);
        proc->tf->rip = app.entrypoint;
        proc->tf->rsp = (uint64_t)USERSTACK_TOP;
        proc->tf->rflags |= EFLAGS_IF;

        load_process_pagetable(proc);
        return 0;
err:
        free_pages(code, 0);
        return -1;
}

int wait_process(struct Process *process, int *status)
{
        return -1;
}

static void make_app1_process(void)
{
        struct App app = {0};
        extern char _binary____apps_app1_start[];
        app_elf_parse(&app, "app1", _binary____apps_app1_start);

        memmove((void*)app.load_start, (void*)app.elf_program_start, app.program_size);

        new_process(&app);
}

static void make_app2_process(void)
{
        struct App app = {0};
        extern char _binary____apps_app2_start[];
        app_elf_parse(&app, "app2", _binary____apps_app2_start);

        memmove((void*)app.load_start, (void*)app.elf_program_start, app.program_size);

        new_process(&app);
}

static void make_app3_process(void)
{
        struct App app = {0};
        extern char _binary____apps_app3_start[];
        app_elf_parse(&app, "app3", _binary____apps_app3_start);

        memmove((void*)app.load_start, (void*)app.elf_program_start, app.program_size);

        new_process(&app);
}

void init_process(void)
{
        make_app1_process();
        make_app2_process();
        make_app3_process();
}

static int i = 0;

struct Process *scheduler_next_process(struct Process *prev_process)
{
        // stub
        return &process_table[0];
}

void preempt_schedule(unsigned long long sp)
{
        schedule();
}

void schedule(void) {
        struct Process *proc;
        uint64_t *prevsp;

        proc = scheduler_next_process(current_process);

        if (proc->state != READY) {
                // bug
                for (;;)
                        ;
        }

        proc->state = RUNNING;
        if (!current_process)
                prevsp = &kernel_sp;
        else
                prevsp = &current_process->rsp;

        // load_process_pagetable(proc);

        current_process = proc;

        context_switch(prevsp, &proc->rsp);
}

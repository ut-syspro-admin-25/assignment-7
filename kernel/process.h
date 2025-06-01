#pragma once

#include "kernel.h"

enum ProcessState {
        NONE,
        CREATED,
        READY,
        RUNNING,
        BLOCKING,
        ZOMBIE,
};

struct TrapFrame {
        uint64_t rax;
        uint64_t rbx;
        uint64_t rcx;
        uint64_t rdx;
        uint64_t rdi;
        uint64_t rsi;
        uint64_t rbp;
        uint64_t r8;
        uint64_t r9;
        uint64_t r10;
        uint64_t r11;
        uint64_t r12;
        uint64_t r13;
        uint64_t r14;
        uint64_t r15;
        uint64_t errno;
        uint64_t rip;
        uint64_t cs;
        uint64_t rflags;
        uint64_t rsp;
        uint64_t ss;
} __attribute__((packed));

struct Context { 
        uint64_t r15;
        uint64_t r14;
        uint64_t r13;
        uint64_t r12;
        uint64_t rbx;
        uint64_t rbp;
        uint64_t rip;
} __attribute__((packed));

struct Process {
        struct Process *parent;

        enum ProcessState state;
        unsigned int process_id;
        char name[32];
        void *kernel_stack;
        uint64_t rsp;
        struct TrapFrame *tf;

        int exitstatus;

        uint64_t *pagetable;
};

void schedule(void);
void preempt_schedule(unsigned long long sp);
void init_process(void);
int exit_process(struct Process *process, int ret);
int fork_process(struct Process *process);
int wait_process(struct Process *process, int *status);
void wakeup_process(struct Process *process);
void sleep_process(struct Process *process);
int exec(struct Process *proc, char *name);

extern struct Process *current_process;

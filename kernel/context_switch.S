// void context_switch(uint64_t *prev_sp, uint64_t *next_sp);
// prev_sp in %rdi
// next_sp in %rsi
.global context_switch
context_switch:
        // push non-volatile registers
        // %rip was pushed by caller
        pushq   %rbp
        pushq   %rbx
        pushq   %r12
        pushq   %r13
        pushq   %r14
        pushq   %r15

        // save stack pointer
        movq    %rsp, (%rdi)
        // restore next stack pointer 
        movq    (%rsi), %rsp

        // restore non-volatile registers
        popq    %r15
        popq    %r14
        popq    %r13
        popq    %r12
        popq    %rbx
        popq    %rbp

        ret

.global lapic_intr_handler
lapic_intr_handler:
        pushq $0      // padding for errno
        pushq %r15
        pushq %r14
        pushq %r13
        pushq %r12
        pushq %r11
        pushq %r10
        pushq %r9
        pushq %r8
        pushq %rbp
        pushq %rsi
        pushq %rdi
        pushq %rdx
        pushq %rcx
        pushq %rbx
        pushq %rax
        mov %rsp, %rdi
        call lapic_intr_handler_internal
        popq %rax
        popq %rbx
        popq %rcx
        popq %rdx
        popq %rdi
        popq %rsi
        popq %rbp
        popq %r8
        popq %r9
        popq %r10
        popq %r11
        popq %r12
        popq %r13
        popq %r14
        popq %r15
        addq $8, %rsp // errno
        iretq

.global keyboard_intr_handler
keyboard_intr_handler:
        pushq $0      // padding for errno
        pushq %r15
        pushq %r14
        pushq %r13
        pushq %r12
        pushq %r11
        pushq %r10
        pushq %r9
        pushq %r8
        pushq %rbp
        pushq %rsi
        pushq %rdi
        pushq %rdx
        pushq %rcx
        pushq %rbx
        pushq %rax
        mov %rsp, %rdi
        call keyboard_intr_handler_internal
        popq %rax
        popq %rbx
        popq %rcx
        popq %rdx
        popq %rdi
        popq %rsi
        popq %rbp
        popq %r8
        popq %r9
        popq %r10
        popq %r11
        popq %r12
        popq %r13
        popq %r14
        popq %r15
        addq $8, %rsp // errno
        iretq

.global fault_handler
fault_handler:
        pushq %r15
        pushq %r14
        pushq %r13
        pushq %r12
        pushq %r11
        pushq %r10
        pushq %r9
        pushq %r8
        pushq %rbp
        pushq %rsi
        pushq %rdi
        pushq %rdx
        pushq %rcx
        pushq %rbx
        pushq %rax
        mov %rsp, %rdi
        call fault_handler_internal
        popq %rax
        popq %rbx
        popq %rcx
        popq %rdx
        popq %rdi
        popq %rsi
        popq %rbp
        popq %r8
        popq %r9
        popq %r10
        popq %r11
        popq %r12
        popq %r13
        popq %r14
        popq %r15
        addq $8, %rsp // errno
        iretq

.global syscall_handler
syscall_handler:
        pushq $0      // padding for errno
        pushq %r15
        pushq %r14
        pushq %r13
        pushq %r12
        pushq %r11
        pushq %r10
        pushq %r9
        pushq %r8
        pushq %rbp
        pushq %rsi
        pushq %rdi
        pushq %rdx
        pushq %rcx
        pushq %rbx
        pushq %rax
        mov %rsp, %rdi
        call syscall_handler_internal
        popq %rax
        popq %rbx
        popq %rcx
        popq %rdx
        popq %rdi
        popq %rsi
        popq %rbp
        popq %r8
        popq %r9
        popq %r10
        popq %r11
        popq %r12
        popq %r13
        popq %r14
        popq %r15
        addq $8, %rsp // errno
        iretq

.global trapret
trapret:
        popq %rax
        popq %rbx
        popq %rcx
        popq %rdx
        popq %rdi
        popq %rsi
        popq %rbp
        popq %r8
        popq %r9
        popq %r10
        popq %r11
        popq %r12
        popq %r13
        popq %r14
        popq %r15
        addq $8, %rsp // errno
        iretq

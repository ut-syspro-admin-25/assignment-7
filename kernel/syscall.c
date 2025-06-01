#include "util.h"
#include "console.h"
#include "process.h"

static unsigned long long syscall(unsigned long long syscall_id,
                                  unsigned long long arg1,
                                  unsigned long long arg2,
                                  unsigned long long arg3) {
        unsigned long long ret = -1;

        return ret;
}

unsigned long long syscall_handler_internal(unsigned long long sp) {
        unsigned long long syscall_id = 0, arg1 = 0, arg2 = 0, arg3 = 0;
        struct TrapFrame *tf = (struct TrapFrame *)sp;

        // %rax is syscall id
        // %rdi is arg1
        // %rsi is arg2
        // %rdx is arg3

        return syscall(syscall_id, arg1, arg2, arg3);
}

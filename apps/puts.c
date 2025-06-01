#include "syscalls.h"

void main(void)
{
        syscall_puts("hello from sh!\n");
        syscall_exit(0);
}

#include "syscalls.h"

static void chomp(char *buf, int n)
{
        for (int i = 0; i < n; i++) {
                if (buf[i] == '\n')
                        buf[i] = 0;
        }
}

void main(void)
{
        char buf[128];
        int n;
        int pid, status;

        syscall_puts("sh starting...\n");

        for (;;) {
                for (int i = 0; i < 128; i++)
                        buf[i] = 0;
                
                syscall_puts("> ");
                n = syscall_read(buf, 128);
                if (n <= 0) {
                        syscall_puts("read err");
                        continue;
                }

                chomp(buf, n);

                pid = syscall_fork();
                if (pid == 0) {
                        syscall_exec(buf);
                        syscall_puts("err");
                }
                syscall_wait(&status);
        }
}

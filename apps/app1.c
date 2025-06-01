// app1
#include "syscalls.h"

char *str = "Hello from app1\n";

void main(void)
{
        while (1) {
                // TODO: Say hello from here by issuing `puts` syscall
                // syscall_puts(str);

                volatile int i = 100000000;
                while (i--);
        }

        for (;;)
                ;
}

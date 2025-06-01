// app2
#include "syscalls.h"

const char *str = "Hello from app2\n";

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

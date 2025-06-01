// app3
#include "syscalls.h"

const char *str = "Hello from app3\n";

int main(void)
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

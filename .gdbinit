target remote :1234
file kernel/kernel.elf
set substitute-path /work/kernel ./kernel
b console_read
c

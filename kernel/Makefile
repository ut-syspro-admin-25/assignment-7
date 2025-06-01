CC = gcc
CFLAGS = -ggdb -Wall -Wextra -nostdinc -nostdlib -fno-builtin -fno-common
CFLAGS += -fno-stack-check -fno-stack-protector -mno-stack-arg-probe
LDFLAGS = --no-relax

OBJS = kernel.o segmentation.o hardware.o load_gdt.o font.o interrupt.o interrupt_handler.o lapic_timer.o syscall.o memory.o
OBJS += console.o acpi_pm_timer.o page_allocator.o process.o context_switch.o util.o app_loader.o ramdisk.o fs.o ioapic.o keyboard.o

APPS += ../apps/app1 ../apps/app2 ../apps/app3

all: kernel.elf

kernel.elf: $(OBJS) $(APPS)
	ld $(LDFLAGS) -T kernel.elf.ld -o $@ $(OBJS) -b binary $(APPS) ../fs.img

kernel: $(OBJS) $(APPS)
	ld $(LDFLAGS) -T kernel.ld -o $@ $(OBJS) -b binary $(APPS) ../fs.img

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $<

%.o:%.s
	gcc $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o kernel kernel.elf

.PHONY: all debug clean

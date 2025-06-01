CFLAGS := -Wall -Og -g -MD -ffreestanding -nostdinc -nostdlib -nostartfiles
LDFLAGS := -g -nostdlib -Wl,--build-id=none -static --no-relax

objs-app1 += syscall.o app1.o
objs-app2 += syscall.o app2.o
objs-app3 += syscall.o app3.o
objs-sh += syscall.o sh.o
objs-puts += syscall.o puts.o

all: app1 app2 app3 sh puts
	cp $+ ../kernel_fs/

.SUFFIXES : .c .S .o

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	@$(CC) $(CFLAGS) -c $< -o $@

app1: $(objs-app1)
	$(LD) -nostdlib -N -e main -Ttext 0x104000000 -o $@ $+
	#$(LD) -nostdlib -N -e main -Ttext 0xffff800000000000 -o $@ $+

app2: $(objs-app2)
	$(LD) -nostdlib -N -e main -Ttext 0x105000000 -o $@ $+
	#$(LD) -nostdlib -N -e main -Ttext 0xffff800000000000 -o $@ $+

app3: $(objs-app3)
	$(LD) -nostdlib -N -e main -Ttext 0x106000000 -o $@ $+
	#$(LD) -nostdlib -N -e main -Ttext 0xffff800000000000 -o $@ $+

sh: $(objs-sh)
	$(LD) -nostdlib -N -e main -Ttext 0xffff800000000000 -o $@ $+

puts: $(objs-puts)
	$(LD) -nostdlib -N -e main -Ttext 0xffff800000000000 -o $@ $+

clean:
	rm -f $(objs-app1) $(objs-app2) $(objs-app3) $(objs-sh) $(objs-puts) app1 app2 app3 sh puts

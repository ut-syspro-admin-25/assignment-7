CFLAGS := -Wall -Og -g -MD -ffreestanding -nostdinc -nostdlib -nostartfiles
CFLAGS += -I ../
LDFLAGS := -g -nostdlib -Wl,--build-id=none -static --no-relax

objs-app1 += syscall.o app1.o
objs-app2 += syscall.o app2.o
objs-app3 += syscall.o app3.o

all: app1 app2 app3

.SUFFIXES : .c .S .o

%.o: %.c
	@echo CC $@
	@$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	@echo CC $@
	@$(CC) $(CFLAGS) -c $< -o $@

app1: $(objs-app1)
	$(LD) -nostdlib -N -e main -Ttext 0x1000 -o $@ $(objs-app1)

app2: $(objs-app2)
	$(LD) -nostdlib -N -e main -Ttext 0x1000 -o $@ $(objs-app2)

app3: $(objs-app3)
	$(LD) -nostdlib -N -e main -Ttext 0x1000 -o $@ $(objs-app3)

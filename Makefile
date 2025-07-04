DOCKER_IMAGE_NAME = syspro
DOCKER_CONTAINER_NAME = syspro-builder

all: bootloader kernel apps copy

local:
	cp /usr/share/ovmf/OVMF.fd $(CURDIR)
	make

bootloader:
	make all -C bootloader

kernel: apps fs.img
	make all -C kernel

apps:
	make all -C apps

fs.img: apps
	cp apps/app1 apps/app2 apps/app3 kernel_fs/
	dd if=/dev/zero of=fs.img count=10000
	mkfs -t ext2 -d kernel_fs/ -v fs.img -b 1024

qemu:
	qemu-system-x86_64 -m 4G -bios ./OVMF.fd -drive format=raw,file=fat:rw:./fs -smp 4\
		-netdev user,id=n1,hostfwd=tcp::8080-:80 -device virtio-net-pci,netdev=n1\
		-object filter-dump,id=f1,netdev=n1,file=dump.pcap \
		-monitor unix:qemu-monitor-socket,server,nowait

qemu-gdb:
	qemu-system-x86_64 -m 4G -bios ./OVMF.fd -drive format=raw,file=fat:rw:./fs -smp 4\
		-netdev user,id=n1,hostfwd=tcp::8080-:80 -device virtio-net-pci,netdev=n1\
		-object filter-dump,id=f1,netdev=n1,file=dump.pcap \
		-S -gdb tcp::1234

copy: bootloader kernel apps
	mkdir -p fs/EFI/BOOT
	cp bootloader/BOOTX64.EFI fs/EFI/BOOT/
	cp kernel/kernel.elf ./fs/
	cp apps/app1 ./fs/
	cp apps/app2 ./fs/
	cp apps/app3 ./fs/

monitor:
	socat - unix:qemu-monitor-socket

docker-build: Dockerfile
	docker build -t $(DOCKER_IMAGE_NAME) --no-cache=true\
	  --build-arg USER_ID=$(shell id -u)\
	  --build-arg GROUP_ID=$(shell id -g) .

docker-make:
	docker run -it --name $(DOCKER_CONTAINER_NAME) -v $(CURDIR):/work $(DOCKER_IMAGE_NAME) make || :
	docker cp $(DOCKER_CONTAINER_NAME):/usr/share/ovmf/OVMF.fd $(CURDIR)
	docker container rm $(DOCKER_CONTAINER_NAME)

clean:
	rm -r fs || :
	rm OVMF.fd dump.pcap || :
	make clean -C bootloader || :
	make clean -C kernel || :
	make clean -C apps || :
	docker container rm -f $(DOCKER_CONTAINER_NAME) || :

.PHONY: all bootloader kernel apps copy docker-run docker-build qemu clean

CC = aarch64-elf

CFLAGS = \
	-O3 \
	-Wall \
	-Werror \
	-std=gnu99 \
	-nostdlib \
	-nostartfiles \
	-ffreestanding \

LDFLAGS = \
	-nostdlib \
	-nostartfiles

BINARY = kernel8

IMAGE = bin/$(BINARY).img

LOADER_ELF = bin/$(BINARY).elf

LDSCRIPT = linker.lds

INCLUDE = -Iinclude

SOURCES += $(shell find -name "*.c")
SOURCES += $(shell find -name "*.S")

OBJECTS = $(patsubst %.c,%.c.o,$(patsubst %.S,%.S.o,$(SOURCES)))

all: build clean

%.c.o: %.c
	$(CC)-gcc $(CFLAGS) $(INCLUDE) -c $^ -o $@

%.S.o: %.S
	$(CC)-gcc $(CFLAGS) $(INCLUDE) -c $^ -o $@

$(IMAGE): $(OBJECTS)
	$(info $(OBJECTS))
	$(CC)-ld $(LDFLAGS) $(OBJECTS) -T $(LDSCRIPT) -o $(LOADER_ELF)
	$(CC)-objcopy $(LOADER_ELF) -O binary $(IMAGE)

build: $(IMAGE)
	
config:
	rm bin/config.txt
	@printf "boot_delay=1\nenable_uart=1" > bin/config.txt

install:
	sudo mount /dev/$(SDCARD)1 /mnt
	sudo cp bin/* /mnt
	wait
	sudo umount /mnt

package: build clean config

clean:
	rm -rf $(OBJECTS) $(LOADER_ELF)

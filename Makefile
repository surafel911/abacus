# User configuration 

SDCARD = sdd

# Do not edit
CC = aarch64-elf

CFLAGS = \
		-O3 \
		-Wall \
		-Werror \
		-std=gnu99 \
		-nostdlib \
		-nostartfiles \
		-ffreestanding \

LIBRARY = -lgcc

LIBRARY_DIR = -L/usr/aarch64-elf/libc/usr/lib/

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

OBJECTS = $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(SOURCES)))

all: build clean

%.o: %.c
	$(CC)-gcc $(CFLAGS) $(INCLUDE) $(LIBRARY_DIR) $(LIBRARIES) -c $^ -o $@

%.o: %.S
	$(CC)-gcc $(CFLAGS) $(INCLUDE) $(LIBRARY_DIR) $(LIBRARIES) -c $^ -o $@

$(IMAGE): $(OBJECTS)
	$(info $(OBJECTS))
	$(CC)-ld $(LDFLAGS) $(OBJECTS) -T $(LDSCRIPT) -o $(LOADER_ELF)
	$(CC)-objcopy $(LOADER_ELF) -O binary $(IMAGE)

build: $(IMAGE)
	
config:
	@printf "boot_delay=1\nforce_turbo=1\nenable_uart=1" >> bin/config.txt

install:
	sudo mount /dev/$(SDCARD)1 /mnt
	sudo cp bin/* /mnt
	sleep 2.5
	sudo umount /mnt

package: build clean config install

clean:
	rm -rf $(OBJECTS) $(LOADER_ELF)

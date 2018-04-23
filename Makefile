# User configuration 

SDCARD = sdd



# Do not edit
CC = aarch64-elf

CFLAGS = \
		-Og \
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

OBJECTS = $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(SOURCES)))

$(info $(OBJECTS))

all: build clean

%.o: %.c
	$(CC)-gcc $(CFLAGS) $(INCLUDE) -c $^ -o $@

%.o: %.S
	$(CC)-gcc $(CFLAGS) $(INCLUDE) -c $^ -o $@

$(IMAGE): $(OBJECTS)
	$(CC)-ld $(LDFLAGS) $(OBJECTS) -T $(LDSCRIPT) -o $(LOADER_ELF)
	$(CC)-objcopy $(LOADER_ELF) -O binary $(IMAGE)

build: $(IMAGE)
	
config:
	@printf "boot_delay=1\nforce_turbo=1\nenable_uart=1" >> bin/config.txt

clean:
	rm -rf $(OBJECTS) $(LOADER_ELF)

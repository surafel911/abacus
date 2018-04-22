CC = aarch64-elf

CFLAGS = \
		-Og \
		-Wall \
		-Werror \
		-std=gnu99 \
		-ffreestanding \
		-nostdinc \
		-nostdlib \
		-nostartfiles \

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

%.o: %.S
	$(CC)-gcc $(CFLAGS) $(INCLUDE) $^ -o $@

%.o: %.c
	$(CC)-gcc $(CFLAGS) $(INCLUDE) $^ -o $@

$(IMAGE): $(OBJECTS)
	$(CC)-ld $(OBJECTS) -T $(LDSCRIPT) -o $(LOADER_ELF)
	$(CC)-objcopy $(LOADER_ELF) -O binary $(IMAGE)

build: $(IMAGE)



clean:
	rm -rf $(OBJECTS) $(LOADER_ELF)

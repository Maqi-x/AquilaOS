CC = clang++
AS = nasm
LD = ld.lld

CFLAGS = --target=i686-elf -Wall -Wextra -m32 -ffreestanding -Iinclude -nostdlib -fno-stack-protector -c
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T link.ld

KERNEL_SOURCES = kernel/kernel.cpp drivers/hardware/ports.cpp kernel/panic.cpp drivers/keyboard/input.cpp drivers/misc/memory.cpp drivers/vga/screen.cpp lib/msg.cpp lib/string.cpp apps/terminal/terminal.cpp apps/terminal/commands.cpp app/tinypad/tinypad.cpp drivers/hardware/cpu.cpp
KERNEL_OBJECTS = bin/kernel.o bin/ports.o bin/panic.o bin/input.o bin/memory.o bin/screen.o bin/msg.o bin/string.o bin/terminal.o bin/commands.o bin/tinypad.o bin/cpu.o
KERNEL_SOURCES_ASM = boot/boot.asm
KERNEL_OBJECTS_ASM = bin/boot.o

all: bin $(KERNEL_OBJECTS) $(KERNEL_OBJECTS_ASM) kernel.bin

bin:
	mkdir bin

kernel.bin: $(KERNEL_OBJECTS) $(KERNEL_OBJECTS_ASM)
	$(LD) $(LDFLAGS) $^ -o $@

$(KERNEL_OBJECTS_ASM): $(KERNEL_SOURCES_ASM)
	$(AS) $(ASFLAGS) -o $@ $^

bin/%.o: kernel/%.cpp
	$(CC) $(CFLAGS) -o $@ $<

bin/%.o: drivers/keyboard/%.cpp
	$(CC) $(CFLAGS) -o $@ $<

bin/%.o: drivers/misc/%.cpp
	$(CC) $(CFLAGS) -o $@ $<

bin/%.o: drivers/vga/%.cpp
	$(CC) $(CFLAGS) -o $@ $<

bin/%.o: drivers/hardware/%.cpp
	$(CC) $(CFLAGS) -o $@ $<

bin/%.o: lib/%.cpp
	$(CC) $(CFLAGS) -o $@ $<

bin/%.o: apps/terminal/%.cpp
	$(CC) $(CFLAGS) -o $@ $<

bin/%.o: apps/tinypad/%.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(KERNEL_OBJECTS) $(KERNEL_OBJECTS_ASM) kernel.elf

run:
	qemu-system-x86_64 -kernel kernel.bin

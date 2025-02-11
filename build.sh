#!/bin/bash
cd "$(dirname "$0")" || exit

io::ShowError() {
  code="$1"
  msg="${*:2}"
  printf "\033[1;31m[ ERROR ]:\033[91m $msg\033[0m\n"
  exit "$code"
}

if [[ $1 == "clean" ]]; then
  rm -f bin/* objects/*
  exit
fi

CompilationAsmErrorExit=2
CompilationCppErrorExit=3
LinkingErrorExit=4
ErrorExit=1

CC="clang++"
AC="nasm"
LD="ld.lld"

CFLAGS="-Wall -Wextra -m32 -ffreestanding -Iinclude -nostdlib -fno-stack-protector -c -fno-exceptions -fno-rtti -fno-use-cxa-atexit"
ASFLAGS="-f elf32"
LDFLAGS="-m elf_i386 -T link.ld"

KERNEL_SOURCES=(
  "kernel/kernel.cpp"
  "drivers/hardware/ports.cpp"
  "kernel/panic.cpp"
  "drivers/keyboard/input.cpp"
  "lib/map.cpp"
  "lib/time.cpp"
  "apps/AquSh/tests.cpp"
  "drivers/misc/memory.cpp"
  "drivers/vga/screen.cpp"
  "lib/msg.cpp"
  "lib/string.cpp"
  "apps/AquSh/AquSh.cpp"
  "apps/AquSh/commands.cpp"
  "apps/AquilNote/AquilNote.cpp"
  "drivers/hardware/cpu.cpp"
)

KERNEL_OBJECTS=(
  "../objects/kernel.o"
  "../objects/ports.o"
  "../objects/panic.o"
  "../objects/input.o"
  "../objects/map.o"
  "../objects/time.o"
  "../objects/tests.o"
  "../objects/memory.o"
  "../objects/screen.o"
  "../objects/msg.o"
  "../objects/string.o"
  "../objects/AquSh.o"
  "../objects/commands.o"
  "../objects/AquilNote.o"
  "../objects/cpu.o"
)

KERNEL_SOURCES_ASM=("boot/boot.asm")
KERNEL_OBJECTS_ASM=("../objects/boot.o")

mkdir -p bin
mkdir -p objects
cd src || io::ShowError $ErrorExit "Can't find the src directory, you are probably running this script from the wrong place, go to the root directory where you have AquilaOS and run ./build.sh"

for i in "${!KERNEL_SOURCES_ASM[@]}"; do
  $AC $ASFLAGS -o "${KERNEL_OBJECTS_ASM[i]}" "${KERNEL_SOURCES_ASM[i]}" || io::ShowError $CompilationAsmErrorExit "There was a problem while compiling file $i!"
done

for i in "${!KERNEL_SOURCES[@]}"; do
  $CC $CFLAGS -o "../objects/$(basename "${KERNEL_SOURCES[i]}" .cpp).o" "${KERNEL_SOURCES[i]}"|| io::ShowError $CompilationCppErrorExit "There was a problem while compiling file $i!"
done

$LD $LDFLAGS "${KERNEL_OBJECTS[@]}" "${KERNEL_OBJECTS_ASM[@]}" -o ../bin/kernel.bin || io::ShowError $LinkingErrorExit "There was a problem when linking objects"

if [[ $1 == "run" ]]; then
  qemu-system-x86_64 -kernel ../bin/kernel.bin || io::ShowError $ErrorExit "There was a problem when booting via QEMU, try manually booting via \`qemu-system-x86_64 -kernel bin/kernel.bin\`"
fi

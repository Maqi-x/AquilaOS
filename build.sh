#!/bin/bash

# ***************************************************************************** #
#                                   AquilaOS                                    #
# (c) 2025 Maqix                                                                #
#                                                                               #
# You should receive AquilaOS license with this source code. If not - check:    #
#  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md                      #
# ***************************************************************************** #

cd "$(dirname "$0")" || exit

# ---------------------- Constants ---------------------- #
CompilationAsmErrorExit=2
CompilationCppErrorExit=3
LinkingErrorExit=4
ErrorExit=1

CXX="clang++"
AC="nasm"
LD="ld.lld"

CXXFLAGS="-Wall -Wextra -m32 -ffreestanding -nostdlib -fno-stack-protector -c -fno-exceptions -fno-rtti -fno-use-cxa-atexit"
INCLUDEPATH=("include")
ASFLAGS="-f elf32"
LDFLAGS="-m elf_i386 -T link.ld"
QEMUFLAGS="-audiodev sdl,id=audio0 -machine pcspk-audiodev=audio0"

BUILD="../objects"
OUTDIR="bin"
OUT="kernel.elf"

# -------------------------- Before build ----------------------- #
source "scripts/utils.sh"

if [[ $1 == "clean" ]]; then
	rm -f bin/* objects/*
	exit
fi

# ---------------------- Compiling Sources ---------------------- #
mkdir -p bin objects
cd src || ShowError $ErrorExit "Can't find the src directory, you are probably running this script from the wrong place, go to the root directory where you have AquilaOS and run ./build.sh"

SOURCES=($(find . -name "*.cpp"))
SOURCES_ASM=($(find boot -name "*.asm"))

OBJECTS=()

for src in "${SOURCES[@]}"; do
	obj="$BUILD/$(basename "${src%.cpp}.o")"
	if [[ ! -f "$obj" || "$(stat -c %Y "$src")" -gt "$(stat -c %Y "$obj")" ]]; then
		((total++))
	fi
	OBJECTS+=("$obj")
done

if [[ $total -gt 0 ]]; then
	ShowInfo "Compiling sources..."
	for src in "${SOURCES[@]}"; do
		obj="$BUILD/$(basename "${src%.cpp}.o")"

		if [[ ! -f "$obj" || "$(stat -c %Y "$src")" -gt "$(stat -c %Y "$obj")" ]]; then
			$CXX $CXXFLAGS "${INCLUDEPATH[@]/#/-I}" -c "$src" -o "$obj" || ShowError $CompilationCppErrorExit "Compilation failed for $src"
			((compiled++))
			printf "\033[1;33m[%3d%% ]\033[93m %s \033[0m-> \033[93;1m%s\n\033[0m" "$((compiled * 100 / total))" "$src" "$obj"
		fi
	done
fi

# ---------------------- Compiling Assembly Sources ---------------------- #
for asmFile in "${SOURCES_ASM[@]}"; do
	obj="$BUILD/$(basename "$asmFile" .asm).o"
	if [[ ! -f "$obj" || "$(stat -c %Y "$asmFile")" -gt "$(stat -c %Y "$obj")" ]]; then
		((total++))
	fi
	OBJECTS+=("$obj")
done

if [[ $total -gt 0 ]]; then
	ShowInfo "Compiling assembly sources..."
	for asmFile in "${SOURCES_ASM[@]}"; do
		obj="$BUILD/$(basename "$asmFile" .asm).o"

		if [[ ! -f "$obj" || "$(stat -c %Y "$asmFile")" -gt "$(stat -c %Y "$obj")" ]]; then
			$AC $ASFLAGS -o "$obj" "$asmFile" || ShowError $CompilationAsmErrorExit "There was a problem while compiling $asmFile!"
			((compiled++))
			printf "\033[1;33m[%3d%% ]\033[93m %s \033[0m-> \033[93;1m%s\n\033[0m" "$((compiled * 100 / total))" "$asmFile" "$obj"
		fi
	done
fi

# ------------------------ Linking Objects ------------------------ #
ShowInfo "Linking..."
$LD $LDFLAGS "${OBJECTS[@]}" -o "../$OUTDIR/$OUT" || ShowError $LinkingErrorExit "There was a problem when linking objects"

# ------------------------ Finishing Build ------------------------ #
ShowSuccess "Build completed: $OUT"

if [[ $1 == "run" ]]; then
	qemu-system-x86_64 -kernel "../$OUTDIR/$OUT" $QEMUFLAGS || ShowError $ErrorExit "There was a problem when booting via QEMU, try manually booting via \`qemu-system-x86_64 -kernel bin/kernel.bin\`"
fi

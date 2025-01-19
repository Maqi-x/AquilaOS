; -------------------------------------------------------------------------
;                                   AquilaOS
; (c) 2022-2024 Interpuce
; 
; You should receive AquilaOS license with this source code. If not - check:
;  https://github.com/Interpuce/AquilaOS/blob/main/LICENSE.md
; -------------------------------------------------------------------------

; If you are editing this file on a Visual Studio Code, please download
; extension for x86 assembly syntax, because Visual Studio Code don't
; highlight Assembly language without additional extensions.

; boot.asm configures everything (including Multiboot Header required by GRUB
; and other bootloaders to see AquilaOS) and loads the kernel main function
; from /kernel/kernel.c

bits 32

; Multiboot Header section. Required by some bootloaders (including GRUB, that
; AquilaOS uses in the current state) to see binary as operating system.
section .multiboot
    align 4
    dd 0x1BADB002
    dd 0x00
    dd -(0x1BADB002 + 0x00)

section .text

; The main function where AquilaOS starts. It is also declared in
; linker script (/compile/linker.ld), defined in /kernel/kernel.c
; file.
global start
extern main

start:
    cli ; Clear interrupts
    call main ; Call the main function (from /kernel/kernel.c)
    hlt ; Halt the proccessor

; eclair was here (twice)

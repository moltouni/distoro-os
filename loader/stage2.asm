org 0x500
bits 16

jmp _main

%include "stdio.inc"
%include "gdt.inc"
%include "a20.inc"
%include "fat12.inc"

bits 16

welcome	db	"Preparing to load kernel...", 13, 10, 0
point	db	"We are here...", 13, 10, 0

_main:
	cli
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ax, 0x9000
	mov ss, ax
	mov sp, 0xffff
	sti
	
	mov si, welcome
	call PrintString16

	call LoadGDT
	call enableA20

	xor ebx, ebx
	mov eax, 0xc00
	mov es, ax
	call LoadFile16

	cli
	mov eax, cr0
	or eax, 1
	mov cr0, eax

	jmp CODE_DESC:Stage3

bits 32

Stage3:

	mov ax, DATA_DESC
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov esp, 0x90000

	call ClearScreen32
	
	mov esi, point
	call PrintString32
	
	call MoveIt
	jmp CODE_DESC:KernelLocationP

	cli
	hlt

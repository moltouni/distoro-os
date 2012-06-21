bits 16

LoadGDT:
	cli
	pusha
	lgdt [toc]
	sti
	popa
	ret

gdt_data:

	dd	0
	dd	0
	
	dw	0xffff
	dw	0x0
	db	0x0
	db 	10011010b
	db	11001111b
	db	0x0

	dw	0xffff
	dw	0x0
	db	0x0
	db	10010010b
	db	11001111b
	db	0x0

	dw	0xffff
	dw	0x0
	db	0x0
	db	11111010b
	db	11001111b
	db	0x0

	dw	0xffff
	dw	0x0
	db	0x0
	db	11110010b
	db	11001111b
	db	0x0
	
	
gdt_end:

toc:
	dw 	gdt_end - gdt_data - 1
	dd	gdt_data

%define	NULL_DESC	0
%define CODE_DESC	0x8
%define	DATA_DESC	0x10

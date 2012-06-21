bits 16

inputWait:
	in al, 0x64
	test al, 10b
	jnz inputWait
	ret

outputWait:
	in al, 0x64
	test al, 01b
	jz outputWait
	ret

enableA20:
	cli
	pusha

	call inputWait
	mov al, 0xad
	out 0x64, al

	call inputWait
	mov al, 0xd0
	out 0x64, al

	call outputWait
	xor ax, ax
	in al, 0x60
	or al, 10b
	push ax

	call inputWait
	mov al, 0xd1
	out 0x64, al
	call inputWait

	pop ax
	out 0x60, al
	call inputWait

	mov al, 0xae
	out 0x64, al
	call inputWait
	
	popa
	sti
	ret

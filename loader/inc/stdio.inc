bits 16

PrintString16:
	pusha
PrintString16Loop:
	mov ah, 0x0e
	mov al, [si]
	cmp al, 0x0
	je PrintString16Kraj
	xor bx, bx
	inc si
	int 0x10
	jmp PrintString16Loop
PrintString16Kraj:
	popa
	ret

bits 32

tx	db		0
ty	db		0
%define VIDMEM		0xb8000
%define	MAX_S 		80
%define	MAX_R		25
%define	CHAR_ATTRIB	14

positionToRAM:
	
	xor eax, eax
	xor ebx, ebx

	mov edi, VIDMEM

	mov al, [tx]
	mov bl, 2
	mul bl
	add edi, eax

	xor eax, eax
	xor ebx, ebx
	mov al, [ty]
	mov bl, 2
	mul bl
	mov bl, MAX_S
	mul bl
	add edi, eax

	ret

MoveCursor:
	pusha
	
	xor eax, eax
	xor ebx, ebx
	mov al, [ty]
	mov ebx, MAX_S
	mul ebx
	add al, [tx]
	mov ebx, eax

	mov al, 0xf
	mov dx, 0x3d4
	out dx, al

	mov al, bl
	mov dx, 0x3d5
	out dx, al

	mov al, 0xe
	mov dx, 0x3d4
	out dx, al

	mov al, bh
	mov dx, 0x3d5
	out dx, al
	
	popa
	ret

PrintChar32:
	pusha

	push bx
	call positionToRAM
	pop bx

	cmp bl, 0x0a
	jnz PrintChar32Ispisi

PrintChar32Row:
	mov [tx], byte 0
	inc byte [ty]
	jmp PrintChar32Dalje

PrintChar32Ispisi:
	mov dl, bl
	mov dh, CHAR_ATTRIB
	mov [edi], dx

	inc byte [tx]
	cmp [tx], byte MAX_S
	je PrintChar32Row

PrintChar32Dalje:
	
	call MoveCursor
	
	popa
	ret

PrintString32:
	pusha

PrintString32Pon:
	mov bl, [esi]
	cmp bl, 0
	je PrintString32Kraj
	inc esi
	call PrintChar32
	jmp PrintString32Pon

PrintString32Kraj:
	
	popa
	ret

ClearScreen32:
	pusha
	
	mov [tx], byte 0
	mov [ty], byte 0
	
ClearScreen32Loop:
	cmp [ty], byte 25
	je ClearScreen32Kraj
	mov dl, ' '
	mov dh, CHAR_ATTRIB
	call positionToRAM
	mov [edi], dx
	inc byte [tx]
	cmp [tx], byte 80
	jne ClearScreen32Loop 

	mov [tx], byte 0
	inc byte [ty]

	jmp ClearScreen32Loop

ClearScreen32Kraj:
	
	mov [tx], byte 0
	mov [ty], byte 0
	call MoveCursor
	
	popa
	ret

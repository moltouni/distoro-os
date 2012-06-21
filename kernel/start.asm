[bits 32]
global start
global idt_load
global exc0
global exc1
global exc2
global exc3
global exc4
global exc5
global exc6
global exc7
global exc8
global exc9
global exc10
global exc11
global exc12
global exc13
global exc14
global exc15
global exc16
global exc17
global exc18
global exc19
global exc20
global exc21
global exc22
global exc23
global exc24
global exc25
global exc26
global exc27
global exc28
global exc29
global exc30
global exc31

global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15


extern main
extern idtp
extern isr_manager

start:
	
	cli
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov esp, 0x90000
	mov ebp, esp
	
	call main
	
	cli
	hlt

idt_load:
	lidt [idtp]
	ret

isr_entry:
	pusha
	push ds
	push es
	push fs
	push gs

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov eax, esp
	push eax

	mov eax, isr_manager
	call eax

	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8
	iret

irq0:
	cli
	push byte 0
	push byte 32
	jmp isr_entry

irq1:
	cli
	push byte 0
	push byte 33
	jmp isr_entry

irq2:
	cli
	push byte 0
	push byte 34
	jmp isr_entry

irq3:
	cli
	push byte 0
	push byte 35
	jmp isr_entry

irq4:
	cli
	push byte 0
	push byte 36
	jmp isr_entry

irq5:
	cli
	push byte 0
	push byte 37
	jmp isr_entry

irq6:
	cli
	push byte 0
	push byte 38
	jmp isr_entry

irq7:
	cli
	push byte 0
	push byte 39
	jmp isr_entry

irq8:
	cli
	push byte 0
	push byte 40
	jmp isr_entry

irq9:
	cli
	push byte 0
	push byte 41
	jmp isr_entry

irq10:
	cli
	push byte 0
	push byte 42
	jmp isr_entry

irq11:
	cli
	push byte 0
	push byte 43
	jmp isr_entry

irq12:
	cli
	push byte 0
	push byte 44
	jmp isr_entry

irq13:
	cli
	push byte 0
	push byte 45
	jmp isr_entry

irq14:
	cli
	push byte 0
	push byte 46
	jmp isr_entry

irq15:
	cli
	push byte 0
	push byte 47
	jmp isr_entry

exc0:
	cli
	push byte 0
	push byte 0
	jmp isr_entry

exc1:
	cli
	push byte 0
	push byte 1
	jmp isr_entry

exc2:
	cli
	push byte 0
	push byte 2
	jmp isr_entry

exc3:
	cli
	push byte 0
	push byte 3
	jmp isr_entry

exc4:
	cli
	push byte 0
	push byte 4
	jmp isr_entry

exc5:
	cli
	push byte 0
	push byte 5
	jmp isr_entry

exc6:
	cli
	push byte 0
	push byte 6
	jmp isr_entry

exc7:
	cli
	push byte 0
	push byte 7
	jmp isr_entry

exc8:
	cli
	push byte 8
	jmp isr_entry

exc9:
	cli
	push byte 0
	push byte 9
	jmp isr_entry

exc10:
	cli
	push byte 10
	jmp isr_entry

exc11:
	cli
	push byte 11
	jmp isr_entry

exc12:
	cli
	push byte 12
	jmp isr_entry

exc13:
	cli
	push byte 13
	jmp isr_entry

exc14:
	cli
	push byte 14
	jmp isr_entry

exc15:
	cli
	push byte 0
	push byte 15
	jmp isr_entry

exc16:
	cli
	push byte 0
	push byte 16
	jmp isr_entry

exc17:
	cli
	push byte 0
	push byte 17
	jmp isr_entry

exc18:
	cli
	push byte 0
	push byte 18
	jmp isr_entry

exc19:
	cli
	push byte 0
	push byte 19
	jmp isr_entry

exc20:
	cli
	push byte 0
	push byte 20
	jmp isr_entry

exc21:
	cli
	push byte 0
	push byte 21
	jmp isr_entry

exc22:
	cli
	push byte 0
	push byte 22
	jmp isr_entry

exc23:
	cli
	push byte 0
	push byte 23
	jmp isr_entry

exc24:
	cli
	push byte 0
	push byte 24
	jmp isr_entry

exc25:
	cli
	push byte 0
	push byte 25
	jmp isr_entry

exc26:
	cli
	push byte 0
	push byte 26
	jmp isr_entry

exc27:
	cli
	push byte 0
	push byte 27
	jmp isr_entry

exc28:
	cli
	push byte 0
	push byte 28
	jmp isr_entry

exc29:
	cli
	push byte 0
	push byte 29
	jmp isr_entry

exc30:
	cli
	push byte 0
	push byte 30
	jmp isr_entry

exc31:
	cli
	push byte 0
	push byte 31
	jmp isr_entry


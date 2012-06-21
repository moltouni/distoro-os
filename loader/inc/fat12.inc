bits 16

bpbBytesPerSector	dw	512
bpbSectorsPerCluster	db	1
bpbReservedSectors	dw	1
bpbNumberOfFATs		db	2
bpbRootEntries		dw	224
bpbTotalSectors		dw	2880
bpbMedia		db	0xf0
bpbSectorsPerFAT	dw	9
bpbSectorsPerTrack	dw	18
bpbHeadsPerCylinder	dw	2
bpbHiddenSectors	dd	0
bpbTotalSectorsBig	dd	0
bsDriveNumber		db	0
bsUnused		db	0
bsExtBootSignature	db	0x29
bsSerialNumber		dd	0x12345678
bsVolumeLabel		db	"Mario Novak"
bsFileSystem		db	"FAT12   "

FSRootStart		dw	0x0
FSDataStart		dw	0x0
FSFATStart		dw	0x0

FSRootSize		dw	0x0
FSFATSize		db	0x0

FSCylinder		db	0x0
FSHead			db	0x0
FSSector		db	0x0

FSFileName		db	"KERNEL  BIN"
FSFileCluster		dw	0x0
FSFileSize		dd	0x0

NoFile			db	"Can't find file you requested!", 10, 13, 0
%define KernelLocationR 0xc000
%define KernelLocationP 0x100000

Stage1Info:
	
	xor eax, eax
	xor ebx, ebx
	xor ecx, ecx
	mov bx, 0x7c0b
	mov cx, 25
	add bx, cx
	mov al, [bx]
	mov [bsDriveNumber], al

	mov bx, 0x7c0b
	mov ax, 53
	add bx, ax
	mov cx, [bx]
	mov [FSRootStart], cx

	mov ax, 2
	add bx, ax
	mov cx, [bx]
	mov [FSDataStart], cx
	
	mov ax, 2
	add bx, ax
	mov cx, [bx]
	mov [FSFATStart], cx

	mov ax, 2
	add bx, ax
	mov cx, [bx]
	mov [FSRootSize], cx

	mov ax, 2
	add bx, ax
	mov cx, [bx]
	mov [FSFATSize], cl

	ret

FindFileSuccess:
	
	add bx, 0x1a
	mov ax, [bx]
	mov [FSFileCluster], ax

	add bx, 0x2
	mov eax, [bx]
	mov [FSFileSize], eax
	
	ret

FindFile:
	xor eax, eax
	xor ebx, ebx
	xor ecx, ecx

	mov bx, 0x7f00
	mov cx, 224

FindFileLoop:
	cmp cx, 0
	je FindFileEnd
	
	mov si, FSFileName
	push cx
	push bx
	mov cx, 11
	
Compare:
	mov ax, [si]
	mov dx, [bx]
	cmp al, dl
	jne CompareEnd
	inc si
	inc bx
	dec cx
	cmp cx, 0
	jne Compare

CompareEnd:
	pop bx
	pop cx
	je FindFileSuccess
	
	dec cx
	add bx, 0x20
	jmp FindFileLoop

FindFileEnd:
	
	mov si, NoFile
	call PrintString16
	cli
	hlt

	ret

ReadSectors:

	mov ah, 0x0
	mov dl, [bsDriveNumber]
	int 0x13
	jc ReadSectors

	mov al, [bpbSectorsPerCluster]
	mov ah, 0x2
	mov dl, [bsDriveNumber]
	int 0x13
	jc ReadSectors

	ret

LBA2CHS:
	xor dx, dx
	mov cx, [bpbSectorsPerTrack]
	div cx
	inc dl
	mov [FSSector], dl
	
	xor dx, dx
	div word [bpbHeadsPerCylinder]
	mov byte [FSHead], dl
	
	mov byte [FSCylinder], al

	ret

Cluster2LBA:
	mov ax, [FSFileCluster]
	mov cx, 0x2
	sub ax, cx
	xor cx, cx
	mov cl, [bpbSectorsPerCluster]
	mul cx
	mov cx, [FSDataStart]
	add ax, cx

	ret

Popuni:
	mov ch, [FSCylinder]
	mov dh, [FSHead]
	mov cl, [FSSector]
	ret

NextCluster:
	xor eax, eax
	xor ebx, ebx
	mov ax, [FSFileCluster]
	mov bx, 0x3
	mul bx
	mov bx, 0x2
	div bx
	mov bx, 0x9b00
	add ax, bx
	
	mov bx, ax
	mov ax, [bx]
	
	push ax
	
	xor edx, edx
	mov ax, [FSFileCluster]
	mov bx, 0x2
	div bx
	cmp dx, 0x0
	
	pop ax
	je NextClusterPar
	shr ax, 4
	jmp NextClusterIzracunato
NextClusterPar:
	mov bx, 0x0fff
	and ax, bx
NextClusterIzracunato:
	mov [FSFileCluster], ax

	cmp ax, 0x002
	jl NextClusterEOF
	cmp ax, 0xfef
	jg NextClusterEOF
	mov ax, 0x1
	jmp NextClusterEnd

NextClusterEOF:
	mov ax, 0x0
	
NextClusterEnd:
	
	ret

LoadFile16:
	pusha
	
	push bx
	call Stage1Info
	call FindFile

	pop bx
	
LoadFile16Loop:
	call Cluster2LBA
	call LBA2CHS
	call Popuni
	call ReadSectors
	push bx
	call NextCluster
	pop bx

	cmp ax, 0x1
	jne LoadFile16End
	add bx, 0x200
	jmp LoadFile16Loop

LoadFile16End:
	
	popa
	ret

bits 32

MoveIt:
	pusha

	xor edx, edx
	mov eax, [FSFileSize]
	mov ebx, 0x4
	div ebx
	mov ecx, eax
	
	cmp edx, 0x0
	je MoveItDodajNe
	add ecx, 0x1
MoveItDodajNe:
	mov eax, KernelLocationR 
	mov ebx, KernelLocationP

MoveKernelLoop:
	
	mov edx, [eax]
	mov [ebx], edx
	add eax, 0x4
	add ebx, 0x4
	
	dec ecx
	cmp ecx, 0x0
	je MoveKernelVan
	jmp MoveKernelLoop

MoveKernelVan:
	
	popa
	ret

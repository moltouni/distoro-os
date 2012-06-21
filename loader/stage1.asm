org	0x7c00
bits	16

start: jmp _main

times 	0xb-$+start 	db 	0

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
bsDriveNumber		db	0x80 ; 0x80
bsUnused		db	0
bsExtBootSignature	db	0x29
bsSerialNumber		dd	0x12345678
bsVolumeLabel		db	"Mario Novak"
bsFileSystem		db	"FAT12   "

welcome	db	"E", 0
FSRootStart	dw	0x13
FSDataStart	dw	0x5
FSFATStart	dw	0x0
FSRootSize	dw	14
FSFATSize	db	0x0
FSCylinder	db	0x0
FSHead		db	0x0
FSSector	db	0x0
FSFileName	db	"STAGE2  BIN"
FSFileCluster	dw	0x0

_main:
	
	mov ax, cs
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ax, 0x7e0
	mov ss, ax
	mov sp, 0x00ff
	
	mov [bsDriveNumber], dl
	
RootStart:
	xor ax, ax
	xor dx, dx
	mov al, byte [bpbNumberOfFATs]
	mul word [bpbSectorsPerFAT]
	add ax, [bpbReservedSectors]
	mov [FSRootStart], ax
	mov [FSDataStart], ax

RootSize:
	xor ax, ax
	xor dx, dx
	mov ax, 0x20
	mul word [bpbRootEntries]
	div word [bpbBytesPerSector]
	mov [FSRootSize], ax
	add [FSDataStart], ax

	mov bx, [FSRootStart]
	call ToCHS
	mov ax, 0x7f0
	mov es, ax
	xor bx, bx
	mov al, byte [FSRootSize]
	call StaviNutra
	call ReadSectors
	
	call FindFile

FATSuccess:
	
	mov dx, [es:di + 0x1a]
	mov [FSFileCluster], dx
	
FATStart:
	mov word ax, [bpbReservedSectors]
	mov [FSFATStart], ax

FATSize:
	xor ax, ax
	mov al, byte [bpbNumberOfFATs]
	mul word [bpbSectorsPerFAT]
	mov [FSFATSize], al

	mov bx, [FSFATStart]
	call ToCHS
	mov ax, 0x9b0
	mov es, ax
	xor bx, bx
	mov al, [FSFATSize]
	call StaviNutra
	call ReadSectors
	
	call ReadFile
	jmp 0x50:0x0

	hlt

StaviNutra:
	mov ch, [FSCylinder]
	mov cl, [FSSector]
	mov dh, [FSHead]
	ret

ReadFile:
	mov ax, 0
	push ax

ReadFileLoop:
	call DataWhere
	call ToCHS
	mov al, [bpbSectorsPerCluster]
	call StaviNutra
	mov bx, 0x50
	mov es, bx
	pop bx
	call ReadSectors
	
	xor ax, ax
	mov al, byte [bpbSectorsPerCluster]
	mul word [bpbBytesPerSector]
	add ax, bx
	push ax
	

	mov ax, [FSFileCluster]
	mov bx, 0x3
	mul bx
	mov bx, 0x2
	div bx

	add ax, 0x9b00
	mov bx, ax
	mov cx, [bx]
	
	mov ax, [FSFileCluster]
	mov bx, 0x2
	mov dx, 0x0
	div bx
	cmp dx, 0x1
	je nepar
	
	and ch, 1111b
	mov ax, cx
	
	jmp tipVan

nepar:
	xor ax, ax
	mov al, cl
	mov bx, 0x10
	div bl
	mov bx, ax

	xor ax, ax
	mov al, ch
	mov cx, 0x10
	mul cx
	add ax, bx
tipVan:
	mov [FSFileCluster], ax
	cmp ax, 0x2
	jge moze
	jmp krajDaljeCitanja
moze:
	cmp ax, 0xfef
	jle ReadFileLoop
krajDaljeCitanja:
	cmp ax, 0xff8
	jle greskaCluster
	pop dx
	ret
greskaCluster:
	hlt
	ret

DataWhere:
	mov ax, [FSFileCluster]
	sub ax, 0x02
	add ax, [FSDataStart]
	mul byte [bpbSectorsPerCluster]
	mov bx, ax
	ret



LoadFAT:
	jmp FATSuccess

FindFile:
	mov cx, [bpbRootEntries]

	mov ax, 0x7f0
	mov es, ax
	mov di, 0x0

FindFileLoop:
	
	push cx
	mov cx, 11
	mov si, FSFileName
	push di
	rep cmpsb
	pop di
	je LoadFAT
	
	pop cx
	add di, 0x20
	loop FindFileLoop
	
	mov si, welcome
	call PrintString
	hlt

ToCHS:
	
	xor dx, dx
	mov ax, bx
	mov cx, [bpbSectorsPerTrack]
	div cx
	add dx, 1
	mov [FSSector], dl

	xor dx, dx
	div word [bpbHeadsPerCylinder]
	mov byte [FSHead], dl
	
	mov byte [FSCylinder], al

	ret


ReadSectors:

ResetDisk:
	mov ah, 0x00
	mov dl, [bsDriveNumber]
	int 0x13
	jc ResetDisk

	mov ah, 0x02
	mov dl, [bsDriveNumber]
	int 0x13
	jc ReadSectors
	ret

PrintString:
	mov ah, 0x0e
	mov al, [si]
	inc si
	cmp al, 0
	je PrintStringEnd
	xor bx, bx
	int 0x10
	jmp PrintString

PrintStringEnd:
	ret

times 510 - ($-$$) db 0
dw 0xaa55

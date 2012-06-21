#!/bin/bash

nasm -f elf32 -o kernel/bin/start.o kernel/start.asm

/usr/local/cross/bin/i586-elf-gcc -c -Wall -Wextra -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -std=c99 -o kernel/bin/idt.o kernel/lib/idt.c 
/usr/local/cross/bin/i586-elf-gcc -c -Wall -Wextra -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -std=c99 -o kernel/bin/isr.o kernel/lib/isr.c 
/usr/local/cross/bin/i586-elf-gcc -c -Wall -Wextra -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -std=c99 -o kernel/bin/scrn.o kernel/lib/scrn.c 
/usr/local/cross/bin/i586-elf-gcc -c -Wall -Wextra -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -std=c99 -o kernel/bin/system.o kernel/lib/system.c 
/usr/local/cross/bin/i586-elf-gcc -c -Wall -Wextra -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -std=c99 -o kernel/bin/math.o kernel/lib/math.c 
/usr/local/cross/bin/i586-elf-gcc -c -Wall -Wextra -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -std=c99 -o kernel/bin/irq.o kernel/lib/irq.c 
/usr/local/cross/bin/i586-elf-gcc -c -Wall -Wextra -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -std=c99 -o kernel/bin/exc.o kernel/lib/exc.c 
/usr/local/cross/bin/i586-elf-gcc -c -Wall -Wextra -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -std=c99 -o kernel/bin/time.o kernel/lib/time.c 

/usr/local/cross/bin/i586-elf-gcc -c -Wall -Wextra -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -std=c99 -o kernel/bin/kernel.o kernel/kernel.c 

/usr/local/cross/bin/i586-elf-ld -T comp/link.ld -o kernel/bin/kernel.bin kernel/bin/start.o kernel/bin/kernel.o kernel/bin/idt.o kernel/bin/isr.o kernel/bin/scrn.o kernel/bin/system.o kernel/bin/math.o kernel/bin/irq.o kernel/bin/exc.o kernel/bin/time.o

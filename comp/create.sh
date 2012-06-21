#!/bin/bash

cd ..
clear
echo -e "\t\t\t\tCreating Distoro Operating System!"
echo -en "\n\t\t\t     "; date "+%H:%M:%S  %d-%m-%Y"; echo

if [ -f ./disk ]; then rm ./disk; fi

echo -e "/-----------------------------------------------------/"
echo -e "\t\tCREATING file \"disk\"\n"
dd if=/dev/zero of=disk count=2880


echo -e "\n\n/-----------------------------------------------------/"
echo -e "\t\tCREATING FAT12\n"
sudo mkfs.msdos -h 0 -f 2 -F 12 -i 12345678 -n "Mario Novak" -r 224 -R 1 -s 1 -a -v disk


echo -e "\n\n/-----------------------------------------------------/"
echo -e  "\t\tSTAGE 1\n"
nasm -i "loader/inc/" -f bin -o loader/bin/stage1.bin loader/stage1.asm
sudo dd if=loader/bin/stage1.bin of=disk conv=notrunc

echo -e "\n\n/-----------------------------------------------------/"
echo -e "\t\tSTAGE 2\n"
nasm -i "loader/inc/" -f bin -o loader/bin/stage2.bin loader/stage2.asm
sudo mount -o loop disk /media/elem
sudo cp -v loader/bin/stage2.bin /media/elem
sudo umount /media/elem

echo -e "\n\n/-----------------------------------------------------/"
echo -e "\t\tKERNEL\n"
comp/compileAndLink.sh
sudo mount -o loop disk /media/elem
sudo cp -v kernel/bin/kernel.bin /media/elem
sudo umount /media/elem

echo -e "\n\n/-----------------------------------------------------/"
bochs

echo -e "\n\n\ndistoro.os@gmail.com\n\nMario Novak"

# /bin/bash

nasm -f elf32 ./assembly/output.asm -o ./assembly/objects/output.o
ld -m elf_i386 ./assembly/objects/output.o -o ./execs/output
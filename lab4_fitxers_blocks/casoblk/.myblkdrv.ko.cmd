cmd_/home/dreapab/lab5/casoblk/myblkdrv.ko := ld -r -m elf_x86_64 -z max-page-size=0x200000 -T ./scripts/module-common.lds --build-id  -o /home/dreapab/lab5/casoblk/myblkdrv.ko /home/dreapab/lab5/casoblk/myblkdrv.o /home/dreapab/lab5/casoblk/myblkdrv.mod.o ;  true
all: gettimeofday getclock getclock-syscall curtime sbrk sbrk-incdec sched_yield getpid write-to-disk read-from-disk forkwait

write-to-disk: write-to-disk.c
	gcc -O -o $@ $<

read-from-disk: read-from-disk.c
	gcc -O -o $@ $<

sbrk: sbrk.c
	gcc -O -o $@ $<

sbrk-incdec: sbrk-incdec.c
	gcc -O -o $@ $<

sched_yield: sched_yield.c
	gcc -O -o $@ $<

getpid: getpid.c
	gcc -O -o $@ $<

gettimeofday: gettimeofday.c
	gcc -O -o $@ $<

getclock: getclock.c
	gcc -O -o $@ $<

getclock-syscall: getclock-syscall.c
	gcc -O -o $@ $<

curtime: curtime.c
	gcc -O -o $@ $<

forkwait: forkwait.c
	gcc -O -o $@ $<

clean:
	rm -f write-to-disk write-to-disk.o read-from-disk read-from-disk.o \
              sbrk sbrk.o sched_yield sched_yield.o getpid getpid.o \
              gettimeofday gettimeofday.o getclock getclock.o \
              getclock-syscall getclock-syscall.o curtime curtime.o forkwait.o

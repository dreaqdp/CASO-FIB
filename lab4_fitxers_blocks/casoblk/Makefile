
ifneq ($(KERNELRELEASE),)

 # for kbuild

obj-m := myblkdrv.o
myblkdrv-y := interface.o implementation.o

else

 # normal Makefile

KDIR ?= /lib/modules/`uname -r`/build

default:
	$(MAKE) -C $(KDIR) M=$$PWD

endif

clean:
	rm -rf \
.built-in.o.cmd          \
.implementation.o.cmd    \
.interface.o.cmd         \
.myblkdrv.ko.cmd         \
.myblkdrv.mod.o.cmd      \
.myblkdrv.o.cmd          \
.tmp_versions            \
Module.symvers           \
built-in.o               \
implementation.o         \
interface.o              \
modules.order            \
myblkdrv.ko              \
myblkdrv.mod.c           \
myblkdrv.mod.o           \
myblkdrv.o


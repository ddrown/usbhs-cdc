ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
obj-m  := cdc-acm.o

else
# normal makefile - set this directory to the kernel build directory
#KDIR = /lib/modules/$(shell uname -r)/build
KDIR = /lib/modules/6.4.7-100.fc37.x86_64/build

.PHONY: default clean

default:
	$(MAKE) -C $(KDIR) M=$$PWD

clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean

endif

obj-m :=  proc_test.o  
KERNELDIR ?= ~/works/projects/NM81/lmxe-linux-2.6.29.6

PWD :=$(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	cp  proc_test.ko  /tftpboot 
clean:
	rm -rf *.o  *.ko *.mod.c *.order *.symvers



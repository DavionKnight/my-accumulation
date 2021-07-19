obj-m :=  proc_test.o  
KERNELDIR ?= ~/works/projects/H20PN-2000/linux-2.6-cloud-2000

PWD :=$(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	cp  proc_test.ko  /tftpboot 
clean:
	rm -rf *.o  *.ko *.mod.c *.order *.symvers



obj-m := led.o
KERNELDIR := /home/user/work/rk3288_android/kernel
PWD := $(shell pwd)
modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
	rm -rf *.o *~core .depend .*.cmd *.ko *.mod.c *.order *.symvers .tmp_versions

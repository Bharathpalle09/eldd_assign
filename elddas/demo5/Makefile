obj-m = splitfile.o
splitfile-objs= demo5.o demo5b.o demo5c.o

modules:
	make -C /lib/modules/`uname -r`/build M=`pwd` modules

clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean

.phony: modules clean
	

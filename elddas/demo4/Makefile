obj-m = splitfile.o
splitfile-objs=demo4.o demo4a.o

modules:
	make -C /lib/modules/`uname -r`/build M=`pwd` modules

clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean

.phony: modules clean
	

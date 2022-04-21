# Used to learn linking from CSAPP.

all: intr intl intc prog2r prog2l prog2c

# run time library interpositioning
intr: int.c mymalloc.c
	gcc -Wall -DRUNTIME -shared -fpic -o mymalloc.so mymalloc.c -ldl
	gcc -o intr int.c
	# LD_PRELOAD="./mymalloc.so" ./intr

# link time library interpositioning
intl: int.c mymalloc.c
	gcc -DLINKTIME -c mymalloc.c
	gcc -c int.c
	gcc -Wl,--wrap,malloc -Wl,--wrap,free -o intl int.o mymalloc.o

# compile time library interpositioning
intc: int.c mymalloc.c
	gcc -DCOMPILETIME -c mymalloc.c
	gcc -I. -c int.c
	gcc -o intc int.o mymalloc.o

# daynamic linking when running
prog2r: dll.o
	gcc -rdynamic -o prog2r dll.o -ldl

# daynamic linking when linking
prog2l: main2.o libvector.so
	gcc -o prog2l main2.o libvector.so

# compiling shared library must use -fpic
# so here we cannot use auto-generated addvec.o or multvec.o
libvector.so: addvec.c multvec.c
	gcc -shared -fpic -o libvector.so addvec.c multvec.c

# static linking when compiling
prog2c: main2.o libvector.a
	gcc -static -o prog2c main2.o ./libvector.a
	# or
	# gcc -static -o prog2c main2.o -L. -lvector

libvector.a: addvec.o multvec.o
	ar rcs libvector.a addvec.o multvec.o

.PHONY: clean
clean:
	-rm *.a *.o *.so prog* intc intl intr

all: integral
integral: integral.o functions.o test.o utility.o
	gcc -m32 -o integral integral.o functions.o utility.o
integral.o: integral.c lib.h
	gcc -std=c99 -m32 -c -o integral.o integral.c
functions.o: functions.asm
	nasm -f elf32 -o functions.o functions.asm
test.o: test.c
	gcc -std=c99 -m32 -c -o test.o test.c
utility.o: utility.c
	gcc -std=c99 -m32 -c -o utility.o utility.c
test: all
	./integral --test-root 1:2:-2.0:-1.0:0.0001:2.5
	./integral --test-root 2:3:1.0:2.0:0.0001:-1
	./integral --test-root 1:3:2.0:3.0:0.0001:-2
	./integral --test-integral 1:-2.0:2.5:0.0001:-7.875
	./integral --test-integral 2:-1:2.5:0.0001:7.875
	./integral --test-integral 3:-2:-1:0.0001:0.75
clean:
	rm -f integral.o functions.o test.o utility.o

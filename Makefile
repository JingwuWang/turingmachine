turing: turing.o
turing.o: turing.c  
	gcc -c turing.c -o turing.o

.PHONY:clean
clean:
	-rm -rf *.o
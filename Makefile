turing: turing.o TM-parser.o TM-sim.o
turing.o: turing.c  
	gcc -c turing.c -o turing.o
add.o: TM-parser.c
	gcc -c TM-parser.c -o TM-parser.o  #加-c 指定生成为可重链接.o文件
sub.o: TM-sim.c
	gcc -c TM-sim.c -o TM-sim.o

.PHONY:clean
clean:
	-rm -rf *.o
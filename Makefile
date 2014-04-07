fsrv: server.o main.c test
	gcc $(CFLAGS) -o fsrv main.c server.o

server.o: server.h server.c
	gcc $(CFLAGS) -c server.c

test: *.o *.c *.h tests/*.c
	gcc $(CFLAGS) -o test tests/main.c; ./test

clean: 
	rm test fsrv

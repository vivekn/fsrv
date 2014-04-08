fsrv: server.o headers.o main.c test
	gcc $(CFLAGS) -o fsrv main.c server.o

server.o: server.h server.c
	gcc $(CFLAGS) -c server.c

test: *.o *.c *.h tests/*.c
	gcc $(CFLAGS) -o test tests/main.c; ./test

headers.o: headers.h headers.c
	gcc $(CFLAGS) -c headers.c

clean: 
	rm test fsrv
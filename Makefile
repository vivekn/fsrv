CFLAGS=-Wall 

fsrv: server.o headers.o handlers.o main.c test
	gcc $(CFLAGS) main.c server.o headers.o handlers.o -o fsrv

server.o: server.h server.c
	gcc $(CFLAGS) -c server.c

test: *.o *.c *.h tests/*.c
	gcc $(CFLAGS) -o test tests/main.c; ./test

headers.o: headers.h headers.c
	gcc $(CFLAGS) -c headers.c

handlers.o: handlers.h handlers.c headers.h 
	gcc $(CFLAGS) -c handlers.c

clean: 
	rm test fsrv *.o

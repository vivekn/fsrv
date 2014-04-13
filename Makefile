CFLAGS=-Wall
INCLUDE=-I./includes

fsrv: server.o headers.o handlers.o main.c test
	gcc $(CFLAGS) main.c server.o headers.o handlers.o -o fsrv $(INCLUDE)

server.o: server.h server.c
	gcc $(CFLAGS) -c server.c $(INCLUDE)

test: *.c *.h tests/*.c
	gcc $(CFLAGS) -o test tests/main.c; ./test

headers.o: headers.h headers.c
	gcc $(CFLAGS) -c headers.c $(INCLUDE)

handlers.o: handlers.h handlers.c headers.h 
	gcc $(CFLAGS) -c handlers.c $(INCLUDE)

clean: 
	rm test fsrv *.o

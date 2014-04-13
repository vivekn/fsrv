CFLAGS=-Wall
INCLUDE=-I./includes

fsrv: server.o response.o handlers.o main.c test
	gcc $(CFLAGS) main.c server.o response.o handlers.o -o fsrv $(INCLUDE)

server.o: server.h server.c
	gcc $(CFLAGS) -c server.c $(INCLUDE)

test: *.c *.h tests/*.c
	gcc $(CFLAGS) -o test tests/main.c; ./test

response.o: response.h response.c
	gcc $(CFLAGS) -c response.c $(INCLUDE)

handlers.o: handlers.h handlers.c response.h 
	gcc $(CFLAGS) -c handlers.c $(INCLUDE)

clean: 
	rm test fsrv *.o

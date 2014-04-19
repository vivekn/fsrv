CFLAGS=-Wall 
INCLUDE=-I./includes

all: fsrv fsrv-pf fsrv-t
	touch all

fsrv: server.o response.o handlers.o main.c test
	gcc $(CFLAGS) main.c server.o response.o handlers.o -o fsrv $(INCLUDE)

fsrv-pf: prefork.o response.o handlers.o main.c test
	gcc $(CFLAGS) main.c prefork.o response.o handlers.o -o fsrv-pf $(INCLUDE)

fsrv-t: threaded.o response.o handlers.o main.c test
	gcc $(CFLAGS) main.c threaded.o response.o handlers.o -o fsrv-t $(INCLUDE)

server.o: server.h server.c
	gcc $(CFLAGS) -c server.c $(INCLUDE)

prefork.o: server.h prefork.c
	gcc $(CFLAGS) -c prefork.c $(INCLUDE)
	
threaded.o: server.h threaded.c
	gcc $(CFLAGS) -c threaded.c $(INCLUDE)
	
test: *.c *.h tests/*.c
	gcc $(CFLAGS) -o test tests/main.c; ./test

response.o: response.h response.c
	gcc $(CFLAGS) -c response.c $(INCLUDE)

handlers.o: handlers.h handlers.c response.h response.c
	gcc $(CFLAGS) -c handlers.c $(INCLUDE)

clean: 
	rm test fsrv *.o

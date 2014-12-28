UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
CFLAGS=-Wall -Drestrict=__restrict -std=gnu99
else # Mac/Darwin
CFLAGS=-Wall
endif


INCLUDE=-I./includes -I.

all: fsrv fsrv-pf
	touch all

fsrv: server.o response.o handlers.o main.c 
	gcc $(CFLAGS) main.c server.o response.o handlers.o -o fsrv $(INCLUDE)

fsrv-pf: prefork.o response.o handlers.o main.c 
	gcc $(CFLAGS) main.c prefork.o response.o handlers.o -o fsrv-pf $(INCLUDE)

fsrv-t: threaded.o response.o handlers.o main.c 
	gcc $(CFLAGS) main.c threaded.o response.o handlers.o -o fsrv-t $(INCLUDE)

server.o: server.h server.c
	gcc $(CFLAGS) -c server.c $(INCLUDE)

prefork.o: server.h prefork.c
	gcc $(CFLAGS) -c prefork.c $(INCLUDE)
	
threaded.o: server.h threaded.c
	gcc $(CFLAGS) -c threaded.c $(INCLUDE)

fstring.o: fstring.h fstring.c
	gcc $(CFLAGS) -c fstring.c $(INCLUDE)
	
test: *.c *.h tests/*.c fstring.o
	gcc $(CFLAGS) tests/main.c fstring.o -o test $(INCLUDE); ./test 
response.o: response.h response.c
	gcc $(CFLAGS) -c response.c $(INCLUDE)

handlers.o: handlers.h handlers.c response.h response.c
	gcc $(CFLAGS) -c handlers.c $(INCLUDE)

clean: 
	rm test fsrv *.o

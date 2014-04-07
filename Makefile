fsrv: server.o main.c
	gcc $(CFLAGS) -o fsrv main.c server.o
server.o: server.h server.c
	gcc $(CFLAGS) -c server.c


CC = gcc
CFLAGS = -Wall -I$(IDIR) -lws2_32 -lwsock32

server: scompile srun
client: ccompile crun

scompile:
	$(CC) server.c $(CFLAGS) -o server

srun:
	./server

ccompile:
	$(CC) client.c $(CFLAGS) -o client

crun:
	./client

clean:
	del /f client.exe server.exe
CC = gcc
CFLAGS = -Werror -Wall -g -I$(IDIR) -lws2_32 -lwsock32

IDIR = ./include/
SRCDIR = ./src/

SERVER_SOURCE = $(wildcard ${SRCDIR}server/*.c) \
				$(wildcard ${SRCDIR}other/*.c)
CLIENT_SOURCE = $(wildcard ${SRCDIR}client/*.c) \
				$(wildcard ${SRCDIR}other/*.c)

server: server_compile server_run
client: client_compile client_run

server_compile:
	$(CC) $(SERVER_SOURCE) $(CFLAGS) -o server

server_run:
	./server

client_compile:
	$(CC) $(CLIENT_SOURCE) $(CFLAGS) -o client

client_run:
	./client

clean:
	del /f client.exe server.exe
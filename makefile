CC = gcc
CFLAGS = -Werror -Wall -g -I$(IDIR)

IDIR = ./include/
SRCDIR = ./src/

OS_NAME = $(shell uname)

SERVER_SOURCE = $(wildcard ${SRCDIR}server/*.c) \
				$(wildcard ${SRCDIR}other/*.c)
CLIENT_SOURCE = $(wildcard ${SRCDIR}client/*.c) \
				$(wildcard ${SRCDIR}other/*.c)

all: clean server_compile client_compile

server: clean server_compile

server_compile:
ifeq ($(OS_NAME), Linux)
	$(CC) $(SERVER_SOURCE) $(CFLAGS) -o server -lpthread
else
	$(CC) $(SERVER_SOURCE) $(CFLAGS) -o server -lws2_32 -lwsock32
endif

client: clean client_compile

client_compile:
ifeq ($(OS_NAME), Linux)
	$(CC) $(CLIENT_SOURCE) $(CFLAGS) -o client -lpthread
else
	$(CC) $(CLIENT_SOURCE) $(CFLAGS) -o client -lws2_32 -lwsock32
endif

clean:
ifeq ($(OS_NAME), Linux)
	rm -f ./client ./server
else
	del /f client.exe server.exe
endif

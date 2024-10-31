#ifndef OS_DIRECTIVES_H
#define OS_DIRECTIVES_H

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
#elif unix
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;
    typedef int SOCKET;
#endif

#endif //OS_DIRECTIVES_H

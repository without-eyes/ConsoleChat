#ifndef CONSOLECHAT_COMMON_H
#define CONSOLECHAT_COMMON_H

#include <winsock2.h>
#include <stdbool.h>

#define MAX_MESSAGE_LENGTH 256

int initializeWinsock();

void enterIPAddressAndPort(char **inputtedIPAddress, int *port);

bool isValidIpAddress(char *ipAddress);

void setupSocketAddress(SOCKADDR_IN* addr, char *ipAddress, int port);

#endif //CONSOLECHAT_COMMON_H

#ifndef CONSOLECHAT_COMMON_H
#define CONSOLECHAT_COMMON_H

#include "../../include/other/os_directives.h"
#include <stdbool.h>

#define MAX_MESSAGE_LENGTH 256

int initializeWinsock(void);

void enterIPAddressAndPort(char **inputtedIPAddress, int *port);

bool isValidIpAddress(const char *ipAddress);

void setupSocketAddress(SOCKADDR_IN *addr, const char *ipAddress, int port);

#endif //CONSOLECHAT_COMMON_H

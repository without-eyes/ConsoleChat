#ifndef CONSOLECHAT_COMMON_H
#define CONSOLECHAT_COMMON_H

#include <winsock2.h>
#define MAX_MESSAGE_LENGTH 256

int initializeWinsock();

void setupSocketAddress(SOCKADDR_IN* addr);

#endif //CONSOLECHAT_COMMON_H

#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>


#define DEFAULT_BUFLEN 512

extern char recvbuf[DEFAULT_BUFLEN];
extern char sendbuf[DEFAULT_BUFLEN];

int comopen(TCHAR* server);
int comsend(int len);
int comrecv();
void comclose(TCHAR* server);
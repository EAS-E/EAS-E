#include "stdafx.h"
#include "comlib.h"

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_PORT "27016"

char recvbuf[DEFAULT_BUFLEN];
char sendbuf[DEFAULT_BUFLEN];

SOCKET ConnectSocket = INVALID_SOCKET;


int comopen(TCHAR* server) {

		int iResult;
		WSADATA wsaData;
		struct addrinfo *result = NULL,
			*ptr = NULL,
			hints;

		// Initialize Winsock
		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			printf("WSAStartup failed with error: %d\n", iResult);
			return iResult;
		}

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		// convert server name/ip_address from TCHAR to PCSTR
		unsigned len;
		wcstombs_s(&len, nullptr, 0, server, _TRUNCATE);
		char *pmb = (char *)malloc(len);
		wcstombs_s(&len, pmb, len, server, _TRUNCATE);

		// Resolve the server address and port
		iResult = getaddrinfo(pmb, DEFAULT_PORT, &hints, &result);
		if (iResult != 0) {
			printf("getaddrinfo failed with error: %d\n", iResult);
			WSACleanup();
			return iResult;
		}

		// Attempt to connect to an address until one succeeds
		for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
			// Create a SOCKET for connecting to server
			ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
			if (ConnectSocket == INVALID_SOCKET) {
//				printf("socket failed with error: %ld\n", WSAGetLastError());
				WSACleanup();
				return WSAGetLastError();
			}

			// Connect to server.
			iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
			if (iResult == SOCKET_ERROR) {
				closesocket(ConnectSocket);
				ConnectSocket = INVALID_SOCKET;
				continue;
			}
			break;
		}

		freeaddrinfo(result);

		if (ConnectSocket == INVALID_SOCKET) {
			printf("Unable to connect to server!\n");
			WSACleanup();
			return 1;
		}
		return 0;
	}

int comsend(int len) {

	int iResult;

	iResult = send(ConnectSocket, sendbuf, len, 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	printf("Bytes Sent: %ld\n", iResult);
	return 0;
}

int comrecv() {

	int iResult;

	iResult = recv(ConnectSocket, recvbuf, DEFAULT_BUFLEN, 0);
	if (iResult > 0)
		printf("Bytes received: %d %s\n", iResult, recvbuf);
	else if (iResult == 0)
		printf("Connection closed\n");
	else
		printf("recv failed with error: %d\n", WSAGetLastError());
	return iResult;
}

void comclose(TCHAR* server) {

	closesocket(ConnectSocket);
	WSACleanup();
}


#include "stdafx.h"
#include "Strsafe.h"
#include "EASserver.h"

//#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include<process.h>

/*
	The message header format and other aspects of this communication protocol have a history.
	The early effort here was allocated to an early collaborator on the project.
	Out of collegial respect, this author accepted what was offered.
	It seemed like the right thing to do, at the time; now, it has been somewhat revisited...
*/

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib") ??

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27016"

#define commbuffhdr 46

char* ActionNames[] = { "CRNewETY","CRNewETI", "FETCHETI","UPDATEET","DELETEET", "COMMBLKS", "  SVRPLY" };

struct threadData {
	int *clientSocket;
};

void MyFunction(void* Arg)
{
	threadData* Client = (threadData*)Arg;
	SOCKET ClientSocket = *Client->clientSocket;
	int iResult, iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	char sendbuf[DEFAULT_BUFLEN];

	do {
		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);

		if (iResult > 0)
			printf("Bytes received: %d\n", iResult);
		else if (iResult == 0) {
			printf("\nClient has closed connection\n\n");
			WRITECATALOG_F();
		}
		else {
			printf("recv failed: %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
		}

		int i = 0;
		if (iResult > 0) {			// got some data...

			char actionName[9];
			char actionEntitySSId[9];
			char actionEntityTypeId[9];
			char actionEntityId[9];
			char actionSlotDash[9];
			char actionDataLength[9];

			int entitySSId = 0;
			int entityTypeId = 0;
			int entityId = 0;
			int dash = 0;
			int dataLength = 0;
			char actionDataSave[512];


			snprintf(actionName, 9, "%s", recvbuf);
			printf("Request:  %s", actionName);

			snprintf(actionEntitySSId, 9, "%s", recvbuf + 8);
			entitySSId = atoi(actionEntitySSId);
			printf(" ssId %6d", entitySSId);

			snprintf(actionEntityTypeId, 9, "%s", recvbuf + 16);
			entityTypeId = atoi(actionEntityTypeId);
			printf(" typeId %6d", entityTypeId);

			snprintf(actionEntityId, 9, "%s", recvbuf + 24);
			entityId = atoi(actionEntityId);
			printf(" instanceId %6d", entityId);

			snprintf(actionSlotDash, 9, "%s", recvbuf + 32);
			dash = atoi(actionSlotDash);
			printf(" slotDash %6d", dash);

			snprintf(actionDataLength, 6, "%s", recvbuf + 40);
			dataLength = atoi(actionDataLength);
			printf(" data length %5d\n", dataLength);

			dataLength = dataLength - 46;
			for (int i = 0; i < dataLength; i++)
				actionDataSave[i] = recvbuf[i + 46];
			printf("\n");

			char actionResult = 'S';		// presumptive success result

			if (strcmp(actionName, ActionNames[0]) == 0) {				// new entity type

				if (REGETYPE_F(entitySSId, entityTypeId))
					char actionResult = 'S';		// success result
				dataLength = 1;

			}
			else if (strcmp(actionName, ActionNames[1]) == 0) {			// request new entity instance

				CREETYPE(entitySSId, entityTypeId, entityId, dash);
				printf("allocated slot: %6d dash: %6d\n", entityId, dash);
				dataLength = 1;
			}

			else if (strcmp(actionName, ActionNames[2]) == 0) {			// fetch instance

				dataLength = FETCHINST_F(entitySSId, entityTypeId, entityId, dash, actionDataSave);
				for (int i = 0; i < dataLength; i++)
					sendbuf[i + 46] = actionDataSave[i];
			}

			else if (strcmp(actionName, ActionNames[3]) == 0) {			// store/update instance

				UPDATEINST_F(entitySSId, entityTypeId, entityId, dash, dataLength, actionDataSave);
				dataLength = 1;
			}

			else if (strcmp(actionName, ActionNames[4]) == 0) {			// delete instance data.
				dataLength = 1;
			}

			else if (strcmp(actionName, ActionNames[5]) == 0) {			// commit changed logical blocks
				WRITELBLKS_F();
				dataLength = 1;
			}
			int totalLength = commbuffhdr + dataLength;			// the only response with payload is "fetch"
																// all others are simple 'S' reply..
																// ..or data in hdr; datalength = 1 is a flag!

			snprintf(sendbuf, 9, "%s", ActionNames[6]);			// server reply
			snprintf((sendbuf + 8), 9, "%8d", entitySSId);		// subsystem id - integer
			snprintf((sendbuf + 16), 9, "%8d", entityTypeId);	// entity-in-subsystem id - integer
			snprintf((sendbuf + 24), 9, "%8d", entityId);		// instance id = slot number
			snprintf((sendbuf + 32), 9, "%8d", dash);			// slot dash number
			snprintf((sendbuf + 40), 6, "%5d", totalLength);	// message length

			if (dataLength == 1)
				snprintf((sendbuf), dataLength + 1, "%c\n", actionResult);

			if (true) { // ?? - this is all debug trace 
				for (i = 0; i < totalLength; i++)
					printf("%c", sendbuf[i]);
				printf("\n");
			}

			iSendResult = send(ClientSocket, sendbuf, totalLength, 0);
			if (iSendResult == SOCKET_ERROR) {
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(ClientSocket);
				WSACleanup();
			}
		}

	} while (iResult > 0);

	// shutdown the connection since we're done
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		//return 1;
	}

	closesocket(ClientSocket);

	_endthreadex(0);
}


void LISTENERINIT_F() {

	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return;
	}

	// Create a SOCKET for listening for client requests
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return;
	}

	printf("\n SERVER IS RUNNING ...");

	iResult = 0;	// just a place to break if needed for debug...

	while (1)
	{
		// Accept a client communication
		ClientSocket = accept(ListenSocket, NULL, NULL);
		if (ClientSocket == INVALID_SOCKET) {
			printf("accept failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			return;
		}

		printf("\n\nCreating NEW client thread:\n\n");

		threadData* args = (threadData*)malloc(sizeof threadData);

		args->clientSocket = (int *)&ClientSocket;

		_beginthread(MyFunction, 0, args);

	}
	return;
}

void* ALLOCNEWBLK_F(int size) {

	return (void*)calloc(1, size);
}

void PUTDATA_R(void* data, void* blkaddr, int segcount, int thisseg, int segsize, int datasize) {

	char* from;
	char* to;
	char buff[512] = { 0 };
	int count;

	from = (char*)data;
	from = from + (segcount * segsize);

	to = (char*)blkaddr;
	to = to + (thisseg - 1) * segsize;

	count = datasize;
	if (count > segsize)
		count = segsize;

	memcpy(to, from, count);

	memcpy(buff, to, count);	// debug
}

void GETDATA_R(void* data, void* blkaddr, int segcount, int thisseg, int segsize, int datasize) {

	char* from;
	char* to;
	int count;
	char buff[512] = { 0 };

	to = (char*)data;
	to = to + (segcount * segsize);

	from = (char*)blkaddr;
	from = from + (thisseg - 1) * segsize;

	count = datasize;
	if (count >= segsize)
		count = segsize;
	memcpy(to, from, count);

	memcpy(buff, to, count);	// debug inspection
}

FILE* pFile;
int pblksize;

void OPENDATA_R(int bsize) {

	pblksize = bsize;

	fopen_s(&pFile, "pdata", "r+b");
	if (pFile == NULL)
		fopen_s(&pFile, "pdata", "w+b");

}
void* READBLK_F(int offset) {
	void* blk;

	blk = (void*)calloc(1, pblksize);
	fseek(pFile, offset, SEEK_SET);
	fread(blk, pblksize, 1, pFile);
	return blk;
}
int WRITEBLK_F(void* blkaddr) {
	int offset;

	fseek(pFile, 0, SEEK_END);
	offset = ftell(pFile);
	fwrite(blkaddr, pblksize, 1, pFile);
	fflush(pFile);
	return offset;
}


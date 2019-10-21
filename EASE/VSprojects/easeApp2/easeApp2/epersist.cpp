#include "stdafx.h"
#include "malloc.h"
#include "epersist.h"
#include "comlib.h"
#include "easlib.h"

#define commbuffhdr 46

Etxt* persistentServer = NULL;
char actionEntityId[9];
char actionSlotDash[9];
int persistSlot = 0;
int slotDash = 0;

void E_PCONNECT_R(Etxt* server) {

	typeInfo* info;

	if (comopen(server->tValue) == 0) {
		WTX_R(E_TXTLIT_F(_T("Persistent server connected: ")));
		WTX_R(server);
		WTL_R();
		persistentServer = server;

		info = f_typeInfos;
		while (info) {
			if (info->emap != 0)
				registerType(info->ssId, info->entId);
			info = info->s_typeInfo;
		}
		WTX_R(E_TXTLIT_F(_T("Persistent entity types registered with: ")));
		WTX_R(server);
		WTL_R();
	}
}

void E_PDISCONNECT_R(Etxt* server) {
	comclose(server->tValue);
	WTX_R(E_TXTLIT_F(_T("Persistent server disconnected: ")));
	WTX_R(server);
	WTL_R();
}


int registerType(int ssId, int etypeId) {

	bool success = false;

	snprintf(sendbuf, 9, "%s", "CRNewETY");			// action - define entity type
	snprintf((sendbuf + 8), 9, "%8d", ssId);			// subsystem id
	snprintf((sendbuf + 16), 9, "%8d", etypeId);		// entity-in-subsystem id
	snprintf((sendbuf + 24), 9, "%8d", 0);				// instance id = slot number
	snprintf((sendbuf + 32), 9, "%8d", 0);				// slot dash number
	snprintf((sendbuf + 40), 6, "%5d", commbuffhdr);	// message length - all header; no data
	if (comsend(commbuffhdr) == 0) {
		if (comrecv() > 0) {
			if (recvbuf[0] == (char)'S')
				return 0;
		}
	}
	return -1;
}

int newInstance(iRef* iref) {

	bool success = false;

	// client needs definition of return message giving the persistent id issued by the server in response!

	snprintf(sendbuf, 9, "%s", "CRNewETI");			// action - allocate new persistent instance id
	snprintf((sendbuf + 8), 9, "%8d", iref->ssId);		// subsystem id - integer
	snprintf((sendbuf + 16), 9, "%8d", iref->typeId);	// entity-in-subsystem id - integer
	snprintf((sendbuf + 24), 9, "%8d", 0);				// instance id = slot number
	snprintf((sendbuf + 32), 9, "%8d", 0);				// slot dash number
	snprintf((sendbuf + 40), 6, "%5d", commbuffhdr);	// message length - all header; no data payload
	if (comsend(commbuffhdr) == 0) {
		if (comrecv() > 0) {
			if (recvbuf[0] == (char)'S') {
				// if success, read persistent slot number ( and dash?) from recvbuffer
				snprintf(actionEntityId, 9, "%s", recvbuf + 24);
				persistSlot = atoi(actionEntityId);
				iref->persistId = persistSlot;
				snprintf(actionSlotDash, 9, "%s", recvbuf + 32);
				slotDash = atoi(actionSlotDash);
				iref->dash = slotDash;
				return 0;
			}
		}
	}
	return -1;
}

int recordInstance(iRef* iref, int len) {

	bool success = false;

	// sendbuffer has been formatted by invoker - len includes header size

	snprintf(sendbuf, 9, "%s", "UPDATEET");			// action - store persistent instance data
	snprintf((sendbuf + 8), 9, "%8d", iref->ssId);			// subsystem id
	snprintf((sendbuf + 16), 9, "%8d", iref->typeId);		// entity-in-subsystem id
	snprintf((sendbuf + 24), 9, "%8d", iref->persistId);	// instance id = slot number
	snprintf((sendbuf + 32), 9, "%8d", iref->dash);			// slot dash number
	snprintf((sendbuf + 40), 6, "%5d", len);				// size of header+data

	if (comsend(len) == 0)   {
		if (comrecv() > 0) {
			if (recvbuf[0] == (char)'S')
				return 0;
		}
	}
	return -1;
}

int retrieveInstance(iRef* iref) {

	bool success = false;
	int dataLength;

	snprintf(sendbuf, 9, "%s", "FETCHETI");				// action - retrieve persistent instance data
	snprintf((sendbuf + 8), 9, "%8d", iref->ssId);			// subsystem id
	snprintf((sendbuf + 16), 9, "%8d", iref->typeId);		// entity-in-subsystem id
	snprintf((sendbuf + 24), 9, "%8d", iref->persistId);	// instance id = slot number
	snprintf((sendbuf + 32), 9, "%8d", iref->dash);			// slot dash number
	snprintf((sendbuf + 40), 6, "%5d", commbuffhdr);		// size of header  - no data

	if (comsend(commbuffhdr) == 0) {
		dataLength = comrecv();
		return dataLength;
	}
	return -1;
}

int deleteInstance(iRef* iref) {

	bool success = false;

	snprintf(sendbuf, 9, "%s", "DELETEET");				// action - delete persistent instance data
	snprintf((sendbuf + 8), 9, "%8d", iref->ssId);			// subsystem id
	snprintf((sendbuf + 16), 9, "%8d", iref->typeId);		// entity-in-subsystem id
	snprintf((sendbuf + 24), 9, "%8d", iref->persistId);	// instance id = slot number
	snprintf((sendbuf + 32), 9, "%8d", iref->dash);			// slot dash number
	snprintf((sendbuf + 40), 6, "%5d", commbuffhdr);		// size of header  - no data

	if (comsend(commbuffhdr) == 0) {
		if (comrecv() > 0) {
			if (recvbuf[0] == (char)'S')
				return 0;
		}
	}
	return -1;
}


int commitChanges() {

	bool success = false;
	snprintf(sendbuf, 9, "%s", "COMMBLKS");				// action - write changed data blocks
	snprintf((sendbuf + 8), 9, "%8d", 0);
	snprintf((sendbuf + 16), 9, "%8d", 0);
	snprintf((sendbuf + 24), 9, "%8d", 0);
	snprintf((sendbuf + 32), 9, "%8d", 0);
	snprintf((sendbuf + 40), 6, "%5d", commbuffhdr);		// size of header  - no data

	if (comsend(commbuffhdr) == 0) {
		if (comrecv() > 0) {
			if (recvbuf[0] == (char)'S')
				return 0;
		}
	}
	return -1;
}

int ebuffpack(int* eptr, const int* mapptr) {
	int i;
	int j;
	int esize;
	int offset;
	int varoffset;
	Etxt* txt;
	iRef* iref;
	char zerobuff[4] = { 0 };
	unsigned char buff[512];

	esize = (*mapptr);	// get entity size
	mapptr++;				// skip..		
	i = (*mapptr);			// get attribute count
	mapptr++;				// skip..

	memcpy(buff + commbuffhdr, eptr, esize);	// copy entire content of entity
	varoffset = commbuffhdr + esize;					// initial offset for variable data
	offset = commbuffhdr;								// entity data - past comm buffer header

	while (i) {
		j = (*mapptr);		// map value

//		if (j == 1) {		// int - skip over the copied value (see incr below)
//		}
		if (j == 2) {		// float
			eptr++;
			offset = offset + 4;
		}
		if (j == 3) {		// text; overwrite with offset to appended copy
			txt = (Etxt*)(*eptr);
			if (txt) {
				(*(buff + offset)) = varoffset;
				(*(buff + varoffset)) = txt->tLength;
				varoffset = varoffset + 4;
				memcpy(buff + varoffset, txt->tValue, (txt->tLength * sizeof(TCHAR)));
				varoffset = varoffset + (txt->tLength * sizeof(TCHAR));
				varoffset = ((varoffset + 3) & 0xFFFC);		// align
			}
			else
				memcpy(buff + offset, zerobuff, 4);

		}
		if (j == 4) {		// in-memory pointer: will not be valid - zero out
			memcpy(buff + offset, zerobuff, 4);
		}
		if (j == 5) {		// persistent pointer; overwrite with offset to copied values
			iref = (iRef*)(*eptr);
			if (iref) {
				//WTX_R(E_TXTLIT_F(_T("Iref at: ")));
				//WTI_R(varoffset, 4);
				//WTL_R();
				(*(buff + offset)) = varoffset;
				memcpy(buff + varoffset, (char*)iref, 16);
				varoffset = varoffset + 16;
			}
			else 
				memcpy(buff + offset, zerobuff, 4);	// null iRef
		}

		mapptr++;
		offset = offset + 4;
		eptr++;
		i--;
	}

	memcpy(sendbuf, buff, varoffset);
	return varoffset;
}

iRef* iRefMatch(iRef* iref) {

	typeInfo* info;
	iRef* aref;

	info = f_typeInfos;
	while (info) {
		if (info->ssId == iref->ssId & info->entId == iref->typeId)
			break;
		info = info->s_typeInfo;
	}
	if (info == NULL) {
		E_ERROR_R(301);
		return NULL;
	}

	aref = info->f_irefs;
	while (aref) {
		if (aref->persistId == iref->persistId)
			break;
		aref = aref->s_irefs;
	}
	if (aref) {
		delete iref;
		aref->refcount++;
		return aref;
	}
	iref->s_irefs = info->f_irefs;
	info->f_irefs = iref;
	return iref;
}

int* ebuffunpack(const int* mapptr) {

	int* eptr;
	int i;
	int j;
	int foffset;
	int varoffset;
	int esize;
	Etxt* txt;
	iRef* iref;
	unsigned char buff[512];

	int* entity;

	esize = (*mapptr);		// entity size
	mapptr++;				// skip..		
	i = (*mapptr);			// attribute count
	mapptr++;				// skip..	

	eptr = (int*)calloc(1, esize);
	entity = eptr;			// save the address

	memcpy(buff, recvbuf, 512);

	memcpy(eptr, buff + commbuffhdr, esize);		// copy entire content of entity
	foffset = commbuffhdr;							// offset to fixed data - entity fields
	varoffset = commbuffhdr + esize;				// offset to appended variable data


	while (i) {
		j = (*mapptr);		// map value

//		if (j == 1) {		// int - skip over the copied value (see incr below)
//		}
		if (j == 2) {		// float
			eptr++;			// ..skip 2nd word in entity layout
			foffset = foffset + 4;
		}
		if (j == 3) {		// text; get offset to appended copy
			varoffset = (*(buff + foffset));
			if (varoffset) {
				txt = (Etxt*)calloc(1, sizeof(Etxt));
				txt->tLength = (*(buff + varoffset));
				varoffset = varoffset + 4;
				txt->tValue = (TCHAR*)calloc(txt->tLength + 1, sizeof(TCHAR));
				memcpy(txt->tValue, buff + varoffset, (txt->tLength * sizeof(TCHAR)));
				txt->refCount = 1;
				(*eptr) = (int)txt;
			}
		}
		if (j == 5) {		// persistent pointer; overwrite with offset to copied values
			varoffset = (*(buff + foffset));
			if (varoffset < 0)
				j = 6;
			if (varoffset) {
				//WTX_R(E_TXTLIT_F(_T("Iref at: ")));
				//WTI_R(varoffset, 4);
				//WTL_R();
				iref = (iRef*)calloc(1, sizeof(iRef));
				memcpy(iref, buff + varoffset, 16);
				iref->refcount = 1;

				iref = iRefMatch(iref);		// do we already know this iRef?
				(*eptr) = (int)iref;
			}
		}

		mapptr++;
		eptr++;
		foffset = foffset + 4;
		i--;
	}
	struct eInstHdr* e;
	e = (struct eInstHdr*)entity; // for debug..
	return entity;
}


void E_RECORD_R() {

	iRef* iref;
	const int* mapptr;
	int* eptr;
	int i;
	int j;
	int offset;
	typeInfo* info;
	iRef* irefAttr;
	int bufflen;

	//	comopen(_T("192.168.1.65"));
	//	comopen(_T("75.60.237.58"));
	//	comopen(_T("localhost"));

	WTX_R(E_TXTLIT_F(_T("Now recording persistent entity instances:")));
	WTL_R();
	WTX_R(E_TXTLIT_F(_T("iRef  ssid  slot   dash")));
	WTL_R();

	info = f_typeInfos;
	while (info) {
		if (info->emap != 0) {
			iref = info->f_irefs;
			while (iref) {
				WTX_R(info->ename);
				WTS_R(2);
				WTI_R(iref->persistId, 4);
				WTS_R(2);
				WTI_R(iref->dash, 2);
				WTX_R(E_TXTLIT_F(_T(" > ")));

				mapptr = info->emap;
				offset = *mapptr;
				eptr = (int*)iref->maddr;

				bufflen = ebuffpack(eptr, mapptr);		// pack sendbuf
				recordInstance(iref, bufflen);

				mapptr++;		// skip size field
				i = (*mapptr);	// count
				mapptr++;		// skip count
				while (i) {
					j = (*mapptr); // map value
					if (j == 1) {
						WTI_R(*eptr, 4);
						WTS_R(4);
					}
					if (j == 3) {
						WTS_R(2);
						WTX_R((Etxt*)*eptr);
						offset = offset + ((Etxt*)*eptr)->tLength + 4;
					}
					if (j == 5) {
						WTX_R(E_TXTLIT_F(_T(" iRef[")));
						irefAttr = (iRef*)*eptr;
						if (irefAttr) {
							WTI_R(irefAttr->ssId, 4);
							WTI_R(irefAttr->typeId, 4);
							WTI_R(irefAttr->persistId, 4);
							WTI_R(irefAttr->dash, 2);
						}
						WTX_R(E_TXTLIT_F(_T("] ")));
						offset = offset + 12;
					}
					mapptr++;
					eptr++;
					i--;
				}
				WTL_R();

				//if (iref->ssId > 0) {		// debug/test only - keep sets
				//	eptr = (int*)iref->maddr;
				//	iref->maddr = 0;
				//	delete eptr;
				//}

				iref = iref->s_irefs;
			}
		}				
		info = info->s_typeInfo;
	}
	WTX_R(E_TXTLIT_F(_T("End of recording")));
	WTL_R();

	commitChanges();

}


void persistFetch(iRef* iref) {

	typeInfo* info;
	int len;
	
	info = f_typeInfos;
	while (info) {
		if (info->ssId == iref->ssId & info->entId == iref->typeId)
			break;
		info = info->s_typeInfo;
	}
	len = retrieveInstance(iref);
	if (len > 0)
		iref->maddr = (eInstHdr*)ebuffunpack(info->emap);
}


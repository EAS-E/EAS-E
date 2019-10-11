
#pragma once

#include "stdafx.h"

struct iRef {
	int ssId;
	int typeId;
	struct eInstHdr* maddr;
	int refcount;
	int dbId;
	void* emap;
	iRef* s_irefs;
};


struct eInstHdr {
	int DBID;
	int entID;
	struct E_CARD* f_memberships;	// every entity may belong to multiple sets
	struct E_PCARD* f_pmemberships;	// every persistent entity may belong to multiple persistent sets
};

//struct E_INSTH {
//	int SSID;
//	int ENTID;
//	void* F_MSHIPS;
//};

struct membership {
	struct eInstHdr hdr;
	struct membership* s_members;
	struct membership* p_members;
	struct membership* s_memberships;
	struct membership* p_memberships;
	struct LIFO_SET* owningSet;
	struct eInstHdr* member;
//	struct Etxt* ownerSetName;
};
struct OLIFO_SET {
	struct eInstHdr hdr;
	struct membership* f_members;		// a set has a linked list of memberships which point to member entities
	struct membership* l_members;
	int membercount;
	struct Etxt* setName;
};
struct SET {
	int SSID;
	int ENTID;
	struct membership* f_members;		// a set has a linked list of memberships which point to member entities
	struct membership* l_members;
	int membercount;
	struct Etxt* setName;
};


#define FIFO_SET SET
#define LIFO_SET SET
#define RANKED_SET SET

struct Etxt {
	int refCount;						// reference count
	int tLength;
	TCHAR* tValue;
	int offset;							// file position.. not used
};

char* fetch(iRef* iref);

void easinit();
//void E_FFIRST_R(void* set, void* ent);
//void E_FLAST_R(void* set, void* ent);
//eInstHdr* E_RMVFRST_F(void* set);
//eInstHdr* F_EASSET_F(void* set);
//eInstHdr* S_EASSET_F(void* ent, Etxt* setname);
//int N_EASSET_F(void* set);
void E_FRANK_R(void* E1, void* E2, int(fn)(void*, void*));
void E_PFRANK_R(void* E1, void* E2, int(fn)(void*, void*));
eInstHdr* E_INITSET_F(Etxt* setname, int dbId, int entId);
iRef* E_PINITSET_F(Etxt* setname, int dbId, int entId);
void E_DELSET_R(void* set);
void E_PDELSET_R(void* set);
eInstHdr* E_CREATE_F(int dbId, int entId, int size);
iRef* E_PCREATE_F(int dbId, int entId, int size);
void E_DESTROY_R( void* ptr);
void E_PDESTROY_R(void* ptr);
void E_TXTINC_R(Etxt* txt);
void E_TXTD_R(Etxt*& txt);
void E_TXTDEL_R(Etxt* txt);
int LENGTH_F(Etxt* txt);
int ACHAR_F(Etxt* txt, int index);
void QACHAR_F(Etxt* txt, int index, int val);
Etxt* E_TXTLIT_F(TCHAR* lit);
void E_TXTASG_R(Etxt** totxt, Etxt* fromtxt);
int E_TXTEQL_F(Etxt* txt1, Etxt* txt2);
int E_TXTNEQ_F(Etxt* txt1, Etxt* txt2);
Etxt* CONCAT_F(Etxt* txt1, Etxt* txt2);
Etxt* SUBSTR_F(Etxt* txt1, int begin, int len);
void QSUBSTR_F(Etxt* txt1, int begin, int len, Etxt* val);
void OPENO_R(int unit, Etxt* filename);
void OPENI_R(int unit, Etxt* filename);
void CLOSE_R(int unit);
void WTX_R(Etxt* txt);
void WTB_R(int col);				// write as B n 
void WTS_R(int spcs);				// write as S n
void WTI_R(int value, int width);	// write as I n
void WTT_R(Etxt* str, int width);	// write as T n
void WTL_R();						// write as / (output line buffer)
void RDB_R(int col);
void RDL_R();						// read as /
int RDI_F(int width);				//  read as I n
int RDN_F();						// read an integer - space delimited
Etxt* RDX_F();						// read as T *
Etxt* RDT_F(int width);
Etxt* RDS_F();						// true T *
void* RES_F(int dim, int hdr);
Etxt* ITOT_F(int value);
void E_RECORD_R();
void addPtype(int ssid, int entid, const int* map);

struct UIB_R {
	int EOF_V;
	int RRECLEN_V;
};

struct UIB {
	int EOF_V;
	int	RRECLEN_V;
};

struct easlib_sys {
	int     READ_V;
	int     WRITE_V;
	struct UIB* UIB_R;
	struct UIB* UIB_W;
	int		E_FOUND_V;
};
extern easlib_sys* easlib;

struct typeInfo {
	int ssId;
	int entId;
	const int* emap;
	iRef* f_irefs;
	typeInfo* s_typeInfo;
};


int XMLOPEN_F(Etxt* schema);
int XMLFINDELEM_F(Etxt* elem);
int XMLFINDCHILD_F(Etxt* elem);
void XMLINTO();
void XMLOUTOF();
int XMLLATTR_F(Etxt* attrname);	// return Logical (bool?) attribute value
int XMLIATTR_F(Etxt* attrname);	// return Integer attribute value
Etxt* XMLTATTR_F(Etxt* attrname);	// return Text attribute value
Etxt* XMLGETDATA_F();				// return Text value
Etxt* XMLGETCHILDDATA_F();		// return Text value

// temporary helper fns for persistence
void txtasg(char* to, char* from);
char* dref(char* eptr, int offset);
void* aref(char* eptr, int offset);
void* apref(char* eptr, int offset);
void* lasg(char* eptr);
void createset(Etxt* name, char* setp);
void filefirst(char* setp, char* ent);
char* removefirst(char* setp);
void easg(char* eptr, iRef* val);
void eunasg(char* eptr);

//struct E_CARD {
//	int DBID;
//	int entID;
//	struct E_CARD* S_MEMBERS;
//	struct E_CARD* S_MSHIPS;
//	struct E_INSTH* MEMBER;
//	struct E_SETHDR* OWNRSET;
//};
//extern int Z_E_CARD;
//
//struct E_INSTH {
//	int DBID;
//	int entID;
//	struct E_CARD* F_MEMBERS;
//	struct E_CARD* F_MSHIPS;
//};
//extern int Z_E_PINSTH;
//
//struct E_SETHDR {
//	int DBID;
//	int entID;
//	struct E_CARD* F_MEMBERS;
//	int MCOUNT;
//	Etxt* SETNAME;
//};
//extern int Z_E_SETHDR;
//

//struct E_PCARD {
//	int DBID;
//	int entID;
//	struct E_PCARD* S_PMEMBERS;
//	struct E_PCARD* S_PMSHIPS;
//	struct E_PINSTH* PMEMBER;
//	struct EPSETHDR* POWNRSET;
//};
//extern int Z_E_PCARD;
//
//struct E_PINSTH {
//	int DBID;
//	int entID;
//	struct E_PCARD* F_PMEMBERS;
//	struct E_PCARD* F_PMSHIPS;
//};
//extern int Z_E_PINSTH;
//
//struct E_PSETHDR {
//	int DBID;
//	int entID;
//	struct E_PCARD* F_PMEMBERS;
//	int PMCOUNT;
//	Etxt* PSETNAME;
//};
//extern int Z_E_PSETHDR;
//
//void d_E_PSETHDR(struct E_PSETHDR* &EPTR);
////struct E_PSETHDR* c_E_PSETHDR();
//void d_E_PINSTH(struct E_PINSTH* &EPTR);
////struct E_PINSTH* c_E_PINSTH();
//void d_E_PCARD(struct E_PCARD* &EPTR);
//struct iRef* c_E_PCARD();
//
//iRef* F_PEASSET_F(void* set);
//

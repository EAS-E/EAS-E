
#pragma once

#include "stdafx.h"
#include "easopts.h"

struct iRef {		// note: 1st 4 fields must be contiguous
	int ssId;
	int typeId;
	int persistId;
	int dash;
	int refcount;
	struct eInstHdr* maddr;
	iRef* s_irefs;
};


struct eInstHdr {
	int DBID;
	int entID;
	void* dummy1;
	void* dummy2;
	//struct E_CARD* f_memberships;	// every entity may belong to multiple sets
	//struct E_PCARD* f_pmemberships;	// every persistent entity may belong to multiple persistent sets
};



struct Etxt {
	int refCount;						// reference count
	int tLength;
	TCHAR* tValue;
	int offset;							// file position.. not used
};

char* fetch(iRef* iref);

void easinit();
void E_FRANK_R(void* E1, void* E2, int(fn)(void*, void*));
void E_PFRANK_R(void* E1, void* E2, int(fn)(void*, void*));
void E_DELSET_R(void* set);
void E_PDELSET_R(void* set);
eInstHdr* E_CREATE_F(int subsysid, int entId, int size);
iRef* E_PCREATE_F(int subsysid, int entId, int size);
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
void USE_R(int unit, int inout);
void WTX_R(Etxt* txt);
void WTB_R(int col);				// write as B n 
void WTS_R(int spcs);				// write as S n
void WTI_R(int value, int width);	// write as I n
void WTT_R(Etxt* str, int width);	// write as T n
void WDD_R(double val, int width, int decimal);	// formatted write
void WTL_R();						// write as / (output line buffer)
void RDB_R(int col);				// begin read at col
void RDL_R();						// read as /
int RDI_F(int width);				// read as I n
int RDN_F();
double RDD_F(int width, int decimal);		// formatted read 
double RDU_F();
Etxt* RDX_F();						// free-format text
Etxt* RDT_F(int width);				// read text - width
Etxt* RDS_F();						// read as T * delimiter-to-delimiter
void* RES_F(int dim, int hdr);
Etxt* ITOT_F(int value);
void addEType(Etxt* ename, int ssid, int entid, const int* map);
Etxt* E_TYPENAME_F(void* eptr);
void E_ERROR_R(int E_ERROR);
iRef* RDP_F();
void WTP_R(void* p);


struct UIB_R {		// these must match easlib.cpp uib.r/uib_w field ordering - and easelibsys
	int RRECLEN_V;
	int RCOL_V;
	int ROPENERR_V;
	int EOF_V;
};

struct UIB_W {
	int WRECLEN_V;
	int WCOL_V;
	int WOPENERR_V;
};

struct easlib_sys {
	int     READ_V;
	int     WRITE_V;
	struct UIB_R* UIB_R;
	struct UIB_W* UIB_W;
	int		E_FOUND_V;
	int		E_SAVE_V;
};
extern easlib_sys* easlib;

struct typeInfo {
	Etxt* ename;
	int ssId;
	int entId;
	const int* emap;
	iRef* f_irefs;
	typeInfo* s_typeInfo;
};
extern typeInfo* f_typeInfos;

void easlib_init();

//int XMLOPEN_F(Etxt* schema);
//int XMLFINDELEM_F(Etxt* elem);
//int XMLFINDCHILD_F(Etxt* elem);
//void XMLINTO();
//void XMLOUTOF();
//int XMLLATTR_F(Etxt* attrname);	// return Logical (bool?) attribute value
//int XMLIATTR_F(Etxt* attrname);	// return Integer attribute value
//Etxt* XMLTATTR_F(Etxt* attrname);	// return Text attribute value
//Etxt* XMLGETDATA_F();				// return Text value
//Etxt* XMLGETCHILDDATA_F();		// return Text value

// temporary helper fns for persistence
//void txtasg(char* to, char* from);
//char* dref(char* eptr, int offset);
//void* aref(char* eptr, int offset);
//void* apref(char* eptr, int offset);
//void* lasg(char* eptr);
void easg(char* eptr, iRef* val);
void eunasg(char* eptr);


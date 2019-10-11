#pragma once
#include "easlib.h"


#define _LGBLKREP
#define _PERSISTTYPE
#define _SLOT

struct LGBLKREP {
struct eInstHdr hdr;
int BLKNUM;
int F_FREESEGS;
int N_FREESEGS;
void* SEGARR_PTR;
struct LGBLKREP* S_LBLKS;
void* BLKADDR;
int CHANGED;
int BLKOFFSET;
};
#define Z_LGBLKREP sizeof(LGBLKREP)
struct PERSISTTYPE {
struct eInstHdr hdr;
int SSID;
int ETYPEID;
void* SLOTARR_PTR;
int NSLOTS;
struct PERSISTTYPE* S_PTYPES;
};
#define Z_PERSISTTYPE sizeof(PERSISTTYPE)
struct SLOT {
struct eInstHdr hdr;
int ISINUSE;
int DASH;
int DATASIZE;
int LOGICALBLK;
int FIRSTSEG;
int NSEGS;
int MORELGBLK;
int LOCKSTATUS;
};
#define Z_SLOT sizeof(SLOT)
void d_SLOT(struct SLOT*& EPTR);
struct SLOT* c_SLOT();
void d_PERSISTTYPE(struct PERSISTTYPE*& EPTR);
struct PERSISTTYPE* c_PERSISTTYPE();
void d_LGBLKREP(struct LGBLKREP*& EPTR);
struct LGBLKREP* c_LGBLKREP();
int WRITELBLKS_F();
void WRITECATALOG_F();
void COPYFROM(struct SLOT* ASLOT, void* DATA);
int FETCHINST_F(int ID1, int ID2, int PID, int DASHNUM, void* DATA);
void COPYTO(void* DATA, struct SLOT* ASLOT);
struct LGBLKREP* FINDLBLK_F(int N);
void FREESEGS(struct SLOT* ASLOT);
struct LGBLKREP* GETBLK_F(int N);
int UPDATEINST_F(int ID1, int ID2, int PID, int DASHNUM, int ESIZE, void* DATA);
void CREETYPE(int ID1, int ID2, int& SLOTNUM, int& DASHNUM);
int REGETYPE_F(int ID1, int ID2);

struct EASserver_sys {
struct eInstHdr hdr;
struct LGBLKREP* LGBLKREP;
struct PERSISTTYPE* PERSISTTYPE;
struct SLOT* SLOT;
struct PERSISTTYPE* F_PTYPES;
struct LGBLKREP* F_LBLKS;
struct LGBLKREP* L_LBLKS;
};
extern EASserver_sys* EASserver;

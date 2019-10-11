#include "stdafx.h"
#include "malloc.h"
#include "libopts.h"
#include "math.h"
#include "EASserver.h"
#include "ConsoleApplication1.h"

void EASserver_addTypes() {
#ifdef _LGBLKREP
addEType(E_TXTLIT_F(_T("LGBLKREP")), 3001,   12, 0);
#endif
#ifdef _PERSISTTYPE
addEType(E_TXTLIT_F(_T("PERSISTTYPE")), 3001,   11, 0);
#endif
#ifdef _SLOT
addEType(E_TXTLIT_F(_T("SLOT")), 3001,   10, 0);
#endif
}
EASserver_sys* EASserver;

void EASserver_init() {
EASserver = (EASserver_sys*)E_CREATE_F( 0,3001, sizeof(EASserver_sys));
EASserver_sets();
EASserver_addTypes();
}
void EASserver_sets() {
       return;
}
void d_SLOT(struct SLOT*& EPTR) {
       E_DESTROY_R(EPTR);
       EPTR = (struct SLOT*)0;
       return;
}
struct SLOT* c_SLOT() {
struct SLOT* EPTR= 0;
struct SLOT* rval = 0;
       EPTR = (struct SLOT*)E_CREATE_F(3001, 10, Z_SLOT);
       rval = (struct SLOT*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void d_PERSISTTYPE(struct PERSISTTYPE*& EPTR) {
       E_DESTROY_R(EPTR);
       EPTR = (struct PERSISTTYPE*)0;
       return;
}
struct PERSISTTYPE* c_PERSISTTYPE() {
struct PERSISTTYPE* EPTR= 0;
struct PERSISTTYPE* rval = 0;
       EPTR = (struct PERSISTTYPE*)E_CREATE_F(3001, 11, Z_PERSISTTYPE);
       rval = (struct PERSISTTYPE*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void d_LGBLKREP(struct LGBLKREP*& EPTR) {
       E_DESTROY_R(EPTR);
       EPTR = (struct LGBLKREP*)0;
       return;
}
struct LGBLKREP* c_LGBLKREP() {
struct LGBLKREP* EPTR= 0;
struct LGBLKREP* rval = 0;
       EPTR = (struct LGBLKREP*)E_CREATE_F(3001, 12, Z_LGBLKREP);
       rval = (struct LGBLKREP*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
int WRITELBLKS_F() {
struct LGBLKREP* LBLK= 0;
int rval = 0;
       LBLK = (struct LGBLKREP*)EASserver->F_LBLKS;
next0001:
       if ( !  ( LBLK != 0 ) ) {
       goto done0001;
       }
       if (LBLK->CHANGED != 0) {
       LBLK->BLKOFFSET = WRITEBLK_F(LBLK->BLKADDR);
       WTX_R(E_TXTLIT_F(_T("Block ")));
       WTI_R(LBLK->BLKNUM, 4);
       WTX_R(E_TXTLIT_F(_T(" written at ")));
       WTI_R(LBLK->BLKOFFSET, 6);
       WTL_R();
       LBLK->CHANGED = 0;
       }
       LBLK = (struct LGBLKREP*)LBLK->S_LBLKS;
       goto next0001;
done0001:
       rval = (int)0;
goto retlbl;
retlbl:
       return rval;
}
void WRITECATALOG_F() {
struct PERSISTTYPE* PTYPE= 0;
struct SLOT* ASLOT= 0;
int I= 0;
int SAVWRITE= 0;
void** SLOTARR= 0;
struct LGBLKREP* LBLK= 0;
int* SEGARR= 0;
       SAVWRITE = easlib->WRITE_V;
       OPENO_R(2, E_TXTLIT_F(_T("ptypes.txt")));
       USE_R(2, 2);
       PTYPE = (struct PERSISTTYPE*)EASserver->F_PTYPES;
next0001:
       if ( !  ( PTYPE != 0 ) ) {
       goto done0001;
       }
       WTI_R(PTYPE->SSID, 6);
       WTI_R(PTYPE->ETYPEID, 6);
       WTI_R(PTYPE->NSLOTS, 6);
       WTL_R();
       SLOTARR = (void**)PTYPE->SLOTARR_PTR;
       I = 1;
       goto test0002;
next0002:
       I = I+1;
test0002:
       if (I > PTYPE->NSLOTS) {
       goto done0002;
       }
       ASLOT = (struct SLOT*)SLOTARR[I];
       if (ASLOT != 0) {
       WTI_R(I, 6);
       WTI_R(ASLOT->ISINUSE, 2);
       WTI_R(ASLOT->DASH, 4);
       WTI_R(ASLOT->LOGICALBLK, 6);
       WTI_R(ASLOT->FIRSTSEG, 3);
       WTI_R(ASLOT->NSEGS, 3);
       WTI_R(ASLOT->DATASIZE, 4);
       }
       else {
       WTI_R(0, 6);
       }
       WTL_R();
       goto next0002;
done0002:
       PTYPE = (struct PERSISTTYPE*)PTYPE->S_PTYPES;
       goto next0001;
done0001:
       CLOSE_R(2);
       OPENO_R(2, E_TXTLIT_F(_T("plblks.txt")));
       USE_R(2, 2);
       LBLK = (struct LGBLKREP*)EASserver->F_LBLKS;
next0003:
       if ( !  ( LBLK != 0 ) ) {
       goto done0003;
       }
       SEGARR = (int*)LBLK->SEGARR_PTR;
       WTI_R(LBLK->BLKNUM, 6);
       WTI_R(LBLK->BLKOFFSET, 6);
       WTI_R(LBLK->N_FREESEGS, 6);
       WTI_R(LBLK->F_FREESEGS, 6);
       WTS_R(4);
       I = 1;
       goto test0004;
next0004:
       I = I+1;
test0004:
       if (I > 4) {
       goto done0004;
       }
       WTI_R(SEGARR[I], 3);
       goto next0004;
done0004:
       WTL_R();
       LBLK = (struct LGBLKREP*)LBLK->S_LBLKS;
       goto next0003;
done0003:
       CLOSE_R(2);
       USE_R(SAVWRITE, 2);
       goto retlbl;
retlbl:
       return;
}
void COPYFROM(struct SLOT* ASLOT, void* DATA) {
int SIZE= 0;
struct LGBLKREP* LBLK= 0;
int* SEGARR= 0;
int SEG= 0;
int N= 0;
int I= 0;
       LBLK = (struct LGBLKREP*)GETBLK_F(ASLOT->LOGICALBLK);
       SEGARR = (int*)LBLK->SEGARR_PTR;
       N = ASLOT->NSEGS;
       SIZE = ASLOT->DATASIZE;
       SEG = ASLOT->FIRSTSEG;
       WTX_R(E_TXTLIT_F(_T("Reading ")));
       WTI_R(N, 2);
       WTX_R(E_TXTLIT_F(_T(" segments at ")));
       WTI_R(ASLOT->FIRSTSEG, 2);
       WTX_R(E_TXTLIT_F(_T(" block ")));
       WTI_R(LBLK->BLKNUM, 4);
       WTL_R();
next0001:
       if ( !  ( N > 0 ) ) {
       goto done0001;
       }
       GETDATA_R(DATA, LBLK->BLKADDR, I, SEG, 64, SIZE);
       SEG = SEGARR[SEG];
       SIZE = SIZE-64;
       N = N-1;
       I = I+1;
       goto next0001;
done0001:
       goto retlbl;
retlbl:
       return;
}
int FETCHINST_F(int ID1, int ID2, int PID, int DASHNUM, void* DATA) {
struct PERSISTTYPE* PTYPE= 0;
void** SLOTARR= 0;
struct SLOT* ASLOT= 0;
int ESIZE= 0;
int rval = 0;
       PTYPE = (struct PERSISTTYPE*)EASserver->F_PTYPES;
next0001:
       if ( !  ( PTYPE != 0 ) ) {
       goto done0001;
       }
       if (PTYPE->SSID == ID1 & PTYPE->ETYPEID == ID2) {
       goto done0001;
       }
       PTYPE = (struct PERSISTTYPE*)PTYPE->S_PTYPES;
       goto next0001;
done0001:
       if (PTYPE == 0) {
       rval = (int)-1;
goto retlbl;
       }
       SLOTARR = (void**)PTYPE->SLOTARR_PTR;
       ASLOT = (struct SLOT*)SLOTARR[PID];
       if (ASLOT->DASH != DASHNUM) {
       WTX_R(E_TXTLIT_F(_T("Warning - dash number mismatch in fetch")));
       WTL_R();
       }
       ESIZE = ASLOT->DATASIZE;
       WTX_R(E_TXTLIT_F(_T("Fetching instance: ")));
       WTI_R(ID1, 5);
       WTI_R(ID2, 5);
       WTI_R(PID, 5);
       WTI_R(DASHNUM, 3);
       WTI_R(ESIZE, 5);
       WTL_R();
       COPYFROM(ASLOT, DATA);
       rval = (int)ESIZE;
goto retlbl;
retlbl:
       return rval;
}
void COPYTO(void* DATA, struct SLOT* ASLOT) {
int SIZE= 0;
struct LGBLKREP* LBLK= 0;
int* SEGARR= 0;
int SEG= 0;
int N= 0;
int I= 0;
       LBLK = (struct LGBLKREP*)GETBLK_F(ASLOT->LOGICALBLK);
       SEGARR = (int*)LBLK->SEGARR_PTR;
       N = ASLOT->NSEGS;
       SIZE = ASLOT->DATASIZE;
       WTX_R(E_TXTLIT_F(_T("Allocate ")));
       WTI_R(N, 2);
       WTX_R(E_TXTLIT_F(_T(" segments at ")));
       WTI_R(ASLOT->FIRSTSEG, 2);
       WTX_R(E_TXTLIT_F(_T(" block ")));
       WTI_R(LBLK->BLKNUM, 4);
       WTL_R();
next0001:
       if ( !  ( N > 0 ) ) {
       goto done0001;
       }
       SEG = LBLK->F_FREESEGS;
       PUTDATA_R(DATA, LBLK->BLKADDR, I, SEG, 64, SIZE);
       SIZE = SIZE-64;
       LBLK->F_FREESEGS = SEGARR[SEG];
       LBLK->N_FREESEGS = LBLK->N_FREESEGS-1;
       N = N-1;
       I = I+1;
       goto next0001;
done0001:
       SEGARR[SEG] = (int)0;
       LBLK->SEGARR_PTR = (void*)SEGARR;
       SEGARR = (int*)0;
       LBLK->CHANGED = 1;
       goto retlbl;
retlbl:
       return;
}
struct LGBLKREP* FINDLBLK_F(int N) {
struct LGBLKREP* LBLK= 0;
int* SEGARR= 0;
struct LGBLKREP* rval = 0;
       LBLK = (struct LGBLKREP*)EASserver->F_LBLKS;
next0001:
       if ( !  ( LBLK != 0 ) ) {
       goto done0001;
       }
       if (LBLK->N_FREESEGS >= N) {
       goto done0001;
       }
       LBLK = (struct LGBLKREP*)LBLK->S_LBLKS;
       goto next0001;
done0001:
       if (LBLK == 0) {
       LBLK= c_LGBLKREP();
       SEGARR = (int*)calloc(4 + 1, sizeof(int));
       SEGARR[0] = (int)(4);
       N = 1;
       goto test0002;
next0002:
       N = N+1;
test0002:
       if (N > 4-1) {
       goto done0002;
       }
       SEGARR[N] = (int)N+1;
       goto next0002;
done0002:
       LBLK->SEGARR_PTR = (void*)SEGARR;
       LBLK->F_FREESEGS = 1;
       LBLK->N_FREESEGS = 4;
       if (EASserver->F_LBLKS == 0) {
       EASserver->F_LBLKS = (struct LGBLKREP*)LBLK;
       LBLK->BLKNUM = 1;
       }
       else {
       EASserver->L_LBLKS->S_LBLKS = (struct LGBLKREP*)LBLK;
       LBLK->BLKNUM = EASserver->L_LBLKS->BLKNUM+1;
       }
       EASserver->L_LBLKS = (struct LGBLKREP*)LBLK;
       LBLK->BLKADDR = (void*)ALLOCNEWBLK_F(4*64);
       }
       rval = (struct LGBLKREP*)LBLK;
goto retlbl;
retlbl:
       return rval;
}
void FREESEGS(struct SLOT* ASLOT) {
struct LGBLKREP* LBLK= 0;
int* SEGARR= 0;
int I= 0;
       if (ASLOT->NSEGS != 0) {
       LBLK = (struct LGBLKREP*)GETBLK_F(ASLOT->LOGICALBLK);
       SEGARR = (int*)LBLK->SEGARR_PTR;
       I = ASLOT->FIRSTSEG;
next0001:
       if ( !  ( SEGARR[I] != 0 ) ) {
       goto done0001;
       }
       I = SEGARR[I];
       goto next0001;
done0001:
       SEGARR[I] = (int)LBLK->F_FREESEGS;
       LBLK->F_FREESEGS = ASLOT->FIRSTSEG;
       ASLOT->FIRSTSEG = 0;
       ASLOT->NSEGS = 0;
       ASLOT->LOGICALBLK = 0;
       LBLK->SEGARR_PTR = (void*)SEGARR;
       }
       goto retlbl;
retlbl:
       return;
}
struct LGBLKREP* GETBLK_F(int N) {
struct LGBLKREP* LBLK= 0;
struct LGBLKREP* rval = 0;
       LBLK = (struct LGBLKREP*)EASserver->F_LBLKS;
next0001:
       if ( !  ( LBLK != 0 ) ) {
       goto done0001;
       }
       if (LBLK->BLKNUM == N) {
       goto done0001;
       }
       LBLK = (struct LGBLKREP*)LBLK->S_LBLKS;
       goto next0001;
done0001:
       if (LBLK->BLKADDR == 0) {
       WTX_R(E_TXTLIT_F(_T("Reading block ")));
       WTI_R(LBLK->BLKNUM, 4);
       WTX_R(E_TXTLIT_F(_T(" from offset ")));
       WTI_R(LBLK->BLKOFFSET, 6);
       WTL_R();
       LBLK->BLKADDR = (void*)READBLK_F(LBLK->BLKOFFSET);
       }
       rval = (struct LGBLKREP*)LBLK;
goto retlbl;
retlbl:
       return rval;
}
int UPDATEINST_F(int ID1, int ID2, int PID, int DASHNUM, int ESIZE, void* DATA) {
struct PERSISTTYPE* PTYPE= 0;
int S= 0;
int N= 0;
void** SLOTARR= 0;
struct SLOT* ASLOT= 0;
struct LGBLKREP* LBLK= 0;
int rval = 0;
       PTYPE = (struct PERSISTTYPE*)EASserver->F_PTYPES;
next0001:
       if ( !  ( PTYPE != 0 ) ) {
       goto done0001;
       }
       if (PTYPE->SSID == ID1 & PTYPE->ETYPEID == ID2) {
       goto done0001;
       }
       PTYPE = (struct PERSISTTYPE*)PTYPE->S_PTYPES;
       goto next0001;
done0001:
       if (PTYPE == 0) {
       rval = (int)-1;
goto retlbl;
       }
       WTX_R(E_TXTLIT_F(_T("Updating instance: ")));
       WTI_R(ID1, 5);
       WTI_R(ID2, 5);
       WTI_R(PID, 5);
       WTI_R(DASHNUM, 3);
       WTI_R(ESIZE, 5);
       WTL_R();
       SLOTARR = (void**)PTYPE->SLOTARR_PTR;
       ASLOT = (struct SLOT*)SLOTARR[PID];
       if (ASLOT->DASH != DASHNUM) {
       WTX_R(E_TXTLIT_F(_T("Warning - dash number mismatch in update")));
       WTL_R();
       }
       S = ESIZE;
next0002:
       if ( !  ( S > 64 ) ) {
       goto done0002;
       }
       N = N+1;
       S = S-64;
       goto next0002;
done0002:
       if (S > 0) {
       N = N+1;
       }
       if (N != ASLOT->NSEGS) {
       FREESEGS(ASLOT);
       LBLK = (struct LGBLKREP*)FINDLBLK_F(N);
       ASLOT->LOGICALBLK = LBLK->BLKNUM;
       ASLOT->FIRSTSEG = LBLK->F_FREESEGS;
       ASLOT->NSEGS = N;
       }
       ASLOT->DATASIZE = ESIZE;
       COPYTO(DATA, ASLOT);
       rval = (int)0;
goto retlbl;
retlbl:
       return rval;
}

void easinit() {
EASserver_init();
easlib_init();
}
void main() {
struct PERSISTTYPE* PTYPE= 0;
struct SLOT* ASLOT= 0;
int I= 0;
void** SLOTARR= 0;
int EXISTS= 0;
struct LGBLKREP* LBLK= 0;
int* SEGARR= 0;
       easinit();
       OPENO_R(6, E_TXTLIT_F(_T("serverlog.txt")));
       USE_R(6, 2);
       OPENI_R(1, E_TXTLIT_F(_T("ptypes.txt")));
       USE_R(1, 1);
       if (easlib->UIB_R->ROPENERR_V == 0) {
next0001:
       if ( !  ( easlib->UIB_R->EOF_V != 2 ) ) {
       goto done0001;
       }
       PTYPE= c_PERSISTTYPE();
       PTYPE->S_PTYPES = (struct PERSISTTYPE*)EASserver->F_PTYPES;
       EASserver->F_PTYPES = (struct PERSISTTYPE*)PTYPE;
       PTYPE->SSID = RDI_F(6);
       PTYPE->ETYPEID = RDI_F(6);
       PTYPE->NSLOTS = RDI_F(6);
       RDL_R();
       SLOTARR = (void**)calloc(PTYPE->NSLOTS + 1, sizeof(void*));
       SLOTARR[0] = (void*)(PTYPE->NSLOTS);
       PTYPE->SLOTARR_PTR = (void*)SLOTARR;
       I = 1;
       goto test0002;
next0002:
       I = I+1;
test0002:
       if (I > PTYPE->NSLOTS) {
       goto done0002;
       }
       EXISTS = RDI_F(6);
       if (EXISTS != 0) {
       ASLOT= c_SLOT();
       SLOTARR[I] = (void*)ASLOT;
       ASLOT->ISINUSE = RDI_F(2);
       ASLOT->DASH = RDI_F(4);
       ASLOT->LOGICALBLK = RDI_F(6);
       ASLOT->FIRSTSEG = RDI_F(3);
       ASLOT->NSEGS = RDI_F(3);
       ASLOT->DATASIZE = RDI_F(4);
       }
       RDL_R();
       goto next0002;
done0002:
       goto next0001;
done0001:
;      }
       CLOSE_R(1);
       OPENI_R(1, E_TXTLIT_F(_T("plblks.txt")));
       USE_R(1, 1);
       if (easlib->UIB_R->ROPENERR_V == 0) {
next0003:
       if ( !  ( easlib->UIB_R->EOF_V != 2 ) ) {
       goto done0003;
       }
       LBLK= c_LGBLKREP();
       if (EASserver->F_LBLKS == 0) {
       EASserver->F_LBLKS = (struct LGBLKREP*)LBLK;
       }
       else {
       EASserver->L_LBLKS->S_LBLKS = (struct LGBLKREP*)LBLK;
       }
       EASserver->L_LBLKS = (struct LGBLKREP*)LBLK;
       LBLK->BLKNUM = RDI_F(6);
       LBLK->BLKOFFSET = RDI_F(6);
       LBLK->N_FREESEGS = RDI_F(6);
       LBLK->F_FREESEGS = RDI_F(6);
       SEGARR = (int*)calloc(4 + 1, sizeof(int));
       SEGARR[0] = (int)(4);
       I = 1;
       goto test0004;
next0004:
       I = I+1;
test0004:
       if (I > 4) {
       goto done0004;
       }
       SEGARR[I] = (int)RDN_F();
       goto next0004;
done0004:
       LBLK->SEGARR_PTR = (void*)SEGARR;
       RDL_R();
       goto next0003;
done0003:
;      }
       CLOSE_R(1);
       OPENDATA_R(64*4);
       LISTENERINIT_F();
       WTX_R(E_TXTLIT_F(_T("Server shutting down; communication error")));
       WTL_R();
       CLOSE_R(6);
       return;
}
void CREETYPE(int ID1, int ID2, int& SLOTNUM, int& DASHNUM) {
struct PERSISTTYPE* PTYPE= 0;
struct SLOT* ASLOT= 0;
int I= 0;
int N= 0;
void** SLOTARR= 0;
void** NEWARR= 0;
       PTYPE = (struct PERSISTTYPE*)EASserver->F_PTYPES;
next0001:
       if ( !  ( PTYPE != 0 ) ) {
       goto done0001;
       }
       if (PTYPE->SSID == ID1 & PTYPE->ETYPEID == ID2) {
       goto done0001;
       }
       PTYPE = (struct PERSISTTYPE*)PTYPE->S_PTYPES;
       goto next0001;
done0001:
       if (PTYPE == 0) {
       WTX_R(E_TXTLIT_F(_T("No such entity type")));
       WTL_R();
       goto retlbl;
       }
next0002:
       if ( !  ( SLOTNUM == 0 ) ) {
       goto done0002;
       }
       SLOTARR = (void**)PTYPE->SLOTARR_PTR;
       N = PTYPE->NSLOTS;
       I = 1;
       goto test0003;
next0003:
       I = I+1;
test0003:
       if (I > N) {
       goto done0003;
       }
       if ( !  ( SLOTNUM == 0 ) ) {
       goto done0003;
       }
       if (SLOTARR[I] == 0) {
       ASLOT= c_SLOT();
       SLOTARR[I] = (void*)ASLOT;
       SLOTNUM = I;
       }
       else {
       ASLOT = (struct SLOT*)SLOTARR[I];
       if (ASLOT->ISINUSE == 0) {
       SLOTNUM = I;
       }
       }
       goto next0003;
done0003:
       if (SLOTNUM != 0) {
       ASLOT->ISINUSE = 1;
       ASLOT->DASH = ASLOT->DASH+1;
       DASHNUM = ASLOT->DASH;
       }
       else {
       NEWARR = (void**)calloc(N*2 + 1, sizeof(void*));
       NEWARR[0] = (void*)(N*2);
       I = 1;
       goto test0004;
next0004:
       I = I+1;
test0004:
       if (I > N) {
       goto done0004;
       }
       NEWARR[I] = (void*)SLOTARR[I];
       goto next0004;
done0004:
       PTYPE->NSLOTS = N*2;
       PTYPE->SLOTARR_PTR = (void*)NEWARR;
       }
       goto next0002;
done0002:
       WTX_R(E_TXTLIT_F(_T("New instance: ")));
       WTI_R(ID1, 5);
       WTI_R(ID2, 5);
       WTI_R(SLOTNUM, 5);
       WTI_R(DASHNUM, 5);
       WTL_R();
       goto retlbl;
retlbl:
       return;
}
int REGETYPE_F(int ID1, int ID2) {
struct PERSISTTYPE* PTYPE= 0;
int SUCCESS= 0;
void** SLOTARR= 0;
int rval = 0;
       PTYPE = (struct PERSISTTYPE*)EASserver->F_PTYPES;
next0001:
       if ( !  ( PTYPE != 0 ) ) {
       goto done0001;
       }
       if (PTYPE->SSID == ID1 & PTYPE->ETYPEID == ID2) {
       goto done0001;
       }
       PTYPE = (struct PERSISTTYPE*)PTYPE->S_PTYPES;
       goto next0001;
done0001:
       if (PTYPE == 0) {
       WTX_R(E_TXTLIT_F(_T("Registering new type: ")));
       WTI_R(ID1, 5);
       WTI_R(ID2, 5);
       WTL_R();
       PTYPE= c_PERSISTTYPE();
       PTYPE->SSID = ID1;
       PTYPE->ETYPEID = ID2;
       PTYPE->NSLOTS = 4;
       SLOTARR = (void**)calloc(PTYPE->NSLOTS + 1, sizeof(void*));
       SLOTARR[0] = (void*)(PTYPE->NSLOTS);
       PTYPE->SLOTARR_PTR = (void*)SLOTARR;
       PTYPE->S_PTYPES = (struct PERSISTTYPE*)EASserver->F_PTYPES;
       EASserver->F_PTYPES = (struct PERSISTTYPE*)PTYPE;
       }
       if (PTYPE != 0) {
       WTX_R(E_TXTLIT_F(_T("Catalogued/verified: ")));
       WTI_R(ID1, 5);
       WTI_R(ID2, 5);
       WTL_R();
       }
       else {
       SUCCESS = -1;
       }
       rval = (int)SUCCESS;
goto retlbl;
retlbl:
       return rval;
}

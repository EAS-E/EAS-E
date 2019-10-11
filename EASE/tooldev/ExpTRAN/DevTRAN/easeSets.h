#pragma once
#include "easlib.h"


#define _E_PSET
#define _E_SET
#define _E_PCARD
#define _E_CARD
#define _E_PINSTH
#define _E_INSTH
#define _eInstHdr
#define _Subprogram
#define _iRef
#define _Reference
#define _Text
#define _Real
#define _Integer
#define _UIB_W
#define _UIB_R
#define _E_PSET
#define _E_SET
#define _E_PCARD
#define _E_CARD
#define _E_PINSTH
#define _E_INSTH

struct E_PSET {
int SSID;
int ENTID;
void* DUMMY1;
void* DUMMY2;
struct E_PCARD* F_PMEMBERS;
struct E_PCARD* L_PMEMBERS;
int PMCOUNT;
Etxt* PSETNAME;
};
#define Z_E_PSET sizeof(E_PSET)
const int Y_E_PSET[ 10] = { sizeof(E_PSET),   8, 1, 1, 4, 5,  5,  5,  1,  3 };
struct E_SET {
int SSID;
int ENTID;
void* DUMMY1;
void* DUMMY2;
struct E_CARD* F_MEMBERS;
struct E_CARD* L_MEMBERS;
int MCOUNT;
Etxt* SETNAME;
};
#define Z_E_SET sizeof(E_SET)
struct E_PCARD {
int SSID;
int ENTID;
void* DUMMY1;
void* DUMMY2;
struct E_PCARD* P_PMEMBERS;
struct E_PCARD* S_PMEMBERS;
struct E_PCARD* S_PMSHIPS;
struct E_PINSTH* PMEMBER;
struct E_PSET* POWNRSET;
};
#define Z_E_PCARD sizeof(E_PCARD)
const int Y_E_PCARD[ 11] = { sizeof(E_PCARD),   9, 1, 1, 4, 5,  5,  5,  5,  5,  5 };
struct E_CARD {
int SSID;
int ENTID;
void* DUMMY1;
void* DUMMY2;
struct E_CARD* P_MEMBERS;
struct E_CARD* S_MEMBERS;
struct E_CARD* S_MSHIPS;
struct E_INSTH* MEMBER;
struct E_SET* OWNRSET;
};
#define Z_E_CARD sizeof(E_CARD)
struct E_PINSTH {
int SSID;
int ENTID;
struct E_CARD* F_XMSHIPS;
struct E_PCARD* F_PMSHIPS;
};
#define Z_E_PINSTH sizeof(E_PINSTH)
const int Y_E_PINSTH[  6] = { sizeof(E_PINSTH),   4, 1, 1, 4, 5 };
struct E_INSTH {
int SSID;
int ENTID;
struct E_CARD* F_MSHIPS;
struct E_PCARD* F_XPMSHIPS;
};
#define Z_E_INSTH sizeof(E_INSTH)
void d_E_INSTH(struct E_INSTH*& EPTR);
struct E_INSTH* c_E_INSTH();
void d_E_PINSTH(struct E_PINSTH*& EPTR);
struct iRef* c_E_PINSTH();
void d_E_CARD(struct E_CARD*& EPTR);
struct E_CARD* c_E_CARD();
void d_E_PCARD(struct E_PCARD*& EPTR);
struct iRef* c_E_PCARD();
void d_E_SET(struct E_SET*& EPTR);
struct E_SET* c_E_SET();
void d_E_PSET(struct E_PSET*& EPTR);
struct iRef* c_E_PSET();
void E_PRMVSPCFC_R(void* E1, void* E2);
void E_RMVSPCFC_R(void* E1, void* E2);
void* E_PRMVLAST_F(void* E1);
void* E_RMVLAST_F(void* E1);
void* E_PRMVFRST_F(void* E1);
void* E_RMVFRST_F(void* E1);
void* S_PEASSET_F(void* E, Etxt* SNAME);
void* S_EASSET_F(void* E, Etxt* SNAME);
void* P_PEASSET_F(void* E, Etxt* SNAME);
void* P_EASSET_F(void* E, Etxt* SNAME);
void* L_PEASSET_F(void* S);
void* L_EASSET_F(void* S);
void* F_PEASSET_F(void* S);
void* F_EASSET_F(void* S);
int N_PEASSET_F(void* S);
int N_EASSET_F(void* S);
int M_PEASSET_F(void* E, Etxt* SNAME);
int M_EASSET_F(void* E, Etxt* SNAME);
void E_PFAFTER_R(void* E1, void* E2, void* E3);
void E_FAFTER_R(void* E1, void* E2, void* E3);
void E_PFBEFOR_R(void* E1, void* E2, void* E3);
void E_FBEFOR_R(void* E1, void* E2, void* E3);
void E_PFLAST_R(void* E1, void* E2);
void E_FLAST_R(void* E1, void* E2);
void E_PFFIRST_R(void* E1, void* E2);
void E_FFIRST_R(void* E1, void* E2);

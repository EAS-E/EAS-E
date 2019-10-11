#pragma once
#include "easlib.h"
#include "easeApp1.h"

struct E_INSTH {
int SSID;
int ENTID;
 struct E_CARD* F_MSHIPS; 
 struct E_PCARD* F_XPMSHIPS; 
};
#define Z_E_INSTH sizeof(E_INSTH)
struct E_PINSTH {
int SSID;
int ENTID;
 struct E_CARD* F_XMSHIPS; 
 struct E_PCARD* F_PMSHIPS; 
};
#define Z_E_PINSTH sizeof(E_PINSTH)
const int Y_E_PINSTH[2] = {sizeof(E_PINSTH), 0};
struct E_CARD {
int SSID;
int ENTID;
void* DUMMY1;
void* DUMMY2;
 struct E_CARD* P_MEMBERS; 
 struct E_CARD* S_MEMBERS; 
 struct E_CARD* S_MSHIPS; 
 struct E_INSTH* MEMBER; 
 struct E_SETHDR* OWNRSET; 
};
#define Z_E_CARD sizeof(E_CARD)
struct E_PCARD {
int SSID;
int ENTID;
void* DUMMY1;
void* DUMMY2;
 struct E_PCARD* P_PMEMBERS; 
 struct E_PCARD* S_PMEMBERS; 
 struct E_PCARD* S_PMSHIPS; 
 struct E_PINSTH* PMEMBER; 
 struct E_PSETHDR* POWNRSET; 
};
#define Z_E_PCARD sizeof(E_PCARD)
const int Y_E_PCARD[7] = {sizeof(E_PCARD), 5, 5, 5, 5, 5, 5};
struct E_SETHDR {
int SSID;
int ENTID;
void* DUMMY1;
void* DUMMY2;
 struct E_CARD* F_MEMBERS; 
 struct E_CARD* L_MEMBERS; 
int MCOUNT;
Etxt* SETNAME;
};
#define Z_E_SETHDR sizeof(E_SETHDR)
struct E_PSETHDR {
int SSID;
int ENTID;
void* DUMMY1;
void* DUMMY2;
 struct E_PCARD* F_PMEMBERS; 
 struct E_PCARD* L_PMEMBERS; 
int PMCOUNT;
Etxt* PSETNAME;
};
#define Z_E_PSETHDR sizeof(E_PSETHDR)
const int Y_E_PSETHDR[6] = {sizeof(E_PSETHDR), 4, 5, 5, 1, 3};
void d_E_PSETHDR(struct E_PSETHDR* &EPTR); 
struct iRef* c_E_PSETHDR(); 
void d_E_SETHDR(struct E_SETHDR* &EPTR); 
struct E_SETHDR* c_E_SETHDR(); 
void d_E_PCARD(struct E_PCARD* &EPTR); 
struct iRef* c_E_PCARD(); 
void d_E_CARD(struct E_CARD* &EPTR); 
struct E_CARD* c_E_CARD(); 
void d_E_PINSTH(struct E_PINSTH* &EPTR); 
struct iRef* c_E_PINSTH(); 
void d_E_INSTH(struct E_INSTH* &EPTR); 
struct E_INSTH* c_E_INSTH(); 
void E_FFIRST_R(void* E1, void* E2); 
void E_PFFIRST_R(void* E1, void* E2); 
void E_FLAST_R(void* E1, void* E2); 
void E_PFLAST_R(void* E1, void* E2); 
void E_FBEFOR_R(void* E1, void* E2, void* E3); 
void E_PFBEFOR_R(void* E1, void* E2, void* E3); 
void E_FAFTER_R(void* E1, void* E2, void* E3); 
void E_PFAFTER_R(void* E1, void* E2, void* E3); 
int N_EASSET_F(void* S); 
int N_PEASSET_F(void* S); 
struct E_INSTH* F_EASSET_F(void* S); 
struct E_PINSTH* F_PEASSET_F(void* S); 
struct E_INSTH* P_EASSET_F(void* E, Etxt* SNAME); 
struct E_PINSTH* P_PEASSET_F(void* E, Etxt* SNAME); 
struct E_INSTH* S_EASSET_F(void* E, Etxt* SNAME); 
struct E_PINSTH* S_PEASSET_F(void* E, Etxt* SNAME); 
struct E_INSTH* E_RMVFRST_F(void* E1); 
struct E_PINSTH* E_PRMVFRST_F(void* E1); 
struct E_INSTH* E_RMVLAST_F(void* E1); 
struct E_PINSTH* E_PRMVLAST_F(void* E1); 
void E_RMVSPCFC_R(void* E1, void* E2); 
void E_PRMVSPCFC_R(void* E1, void* E2); 

#include "stdafx.h"
#include "malloc.h"
#include "libopts.h"
#include "math.h"
#include "easeSets.h"

void easeSets_addTypes() {
#ifdef _E_PSET
addEType(E_TXTLIT_F(_T("E_PSET")),    1,   13, Y_E_PSET);
#endif
#ifdef _E_SET
addEType(E_TXTLIT_F(_T("E_SET")),    1,   12, 0);
#endif
#ifdef _E_PCARD
addEType(E_TXTLIT_F(_T("E_PCARD")),    1,   11, Y_E_PCARD);
#endif
#ifdef _E_CARD
addEType(E_TXTLIT_F(_T("E_CARD")),    1,   10, 0);
#endif
#ifdef _E_PINSTH
addEType(E_TXTLIT_F(_T("E_PINSTH")),    1,    9, Y_E_PINSTH);
#endif
#ifdef _E_INSTH
addEType(E_TXTLIT_F(_T("E_INSTH")),    1,    8, 0);
#endif
}

void easeSets_init() {
easeSets_addTypes();
}
void d_E_INSTH(struct E_INSTH*& EPTR) {
       E_DESTROY_R(EPTR);
       EPTR = (struct E_INSTH*)0;
       return;
}
struct E_INSTH* c_E_INSTH() {
struct E_INSTH* EPTR= 0;
struct E_INSTH* rval = 0;
       EPTR = (struct E_INSTH*)E_CREATE_F(1, 8, Z_E_INSTH);
       rval = (struct E_INSTH*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void d_E_PINSTH(struct E_PINSTH*& EPTR) {
       E_PDESTROY_R(EPTR);
       easg((char*)&EPTR, (iRef*)0);
       eunasg((char*)&EPTR);
       return;
}
struct iRef* c_E_PINSTH() {
struct iRef* EPTR= 0;
struct iRef* rval = 0;
       EPTR = (struct iRef*)E_PCREATE_F(1, 9, Z_E_PINSTH);
       rval = (struct iRef*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void d_E_CARD(struct E_CARD*& EPTR) {
       E_DESTROY_R(EPTR);
       EPTR = (struct E_CARD*)0;
       return;
}
struct E_CARD* c_E_CARD() {
struct E_CARD* EPTR= 0;
struct E_CARD* rval = 0;
       EPTR = (struct E_CARD*)E_CREATE_F(1, 10, Z_E_CARD);
       rval = (struct E_CARD*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void d_E_PCARD(struct E_PCARD*& EPTR) {
       E_PDESTROY_R(EPTR);
       easg((char*)&EPTR, (iRef*)0);
       eunasg((char*)&EPTR);
       return;
}
struct iRef* c_E_PCARD() {
struct iRef* EPTR= 0;
struct iRef* rval = 0;
       EPTR = (struct iRef*)E_PCREATE_F(1, 11, Z_E_PCARD);
       rval = (struct iRef*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void d_E_SET(struct E_SET*& EPTR) {
       E_TXTASG_R(&EPTR->SETNAME, 0);
       E_DESTROY_R(EPTR);
       EPTR = (struct E_SET*)0;
       return;
}
struct E_SET* c_E_SET() {
struct E_SET* EPTR= 0;
struct E_SET* rval = 0;
       EPTR = (struct E_SET*)E_CREATE_F(1, 12, Z_E_SET);
       rval = (struct E_SET*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void d_E_PSET(struct E_PSET*& EPTR) {
       E_TXTASG_R(&(Etxt*)((struct E_PSET*)fetch((iRef*)EPTR))->PSETNAME, 0);
       E_PDESTROY_R(EPTR);
       easg((char*)&EPTR, (iRef*)0);
       eunasg((char*)&EPTR);
       return;
}
struct iRef* c_E_PSET() {
struct iRef* EPTR= 0;
struct iRef* rval = 0;
       EPTR = (struct iRef*)E_PCREATE_F(1, 13, Z_E_PSET);
       rval = (struct iRef*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void E_PRMVSPCFC_R(void* E1, void* E2) {
struct E_PCARD* MEMCARD= 0;
struct E_PCARD* ACARD= 0;
struct E_PSET* SET= 0;
struct E_PINSTH* ENTITY= 0;
       easg((char*)&SET, (iRef*)E1);
       easg((char*)&ENTITY, (iRef*)E2);
       if (ENTITY == 0 | SET == 0) {
       goto retlbl;
       }
       if (ENTITY == (struct E_PINSTH*)((struct E_PCARD*)fetch((iRef*)(struct E_PCARD*)((struct E_PSET*)fetch((iRef*)SET))->F_PMEMBERS))->PMEMBER) {
       easg((char*)&ENTITY, (iRef*)E_PRMVFRST_F(SET));
       goto retlbl;
       }
       if (ENTITY == (struct E_PINSTH*)((struct E_PCARD*)fetch((iRef*)(struct E_PCARD*)((struct E_PSET*)fetch((iRef*)SET))->L_PMEMBERS))->PMEMBER) {
       easg((char*)&ENTITY, (iRef*)E_PRMVLAST_F(SET));
       goto retlbl;
       }
       easg((char*)&MEMCARD, (iRef*)(struct E_PCARD*)((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS);
next0001:
       if ( !  ( MEMCARD != 0 ) ) {
       goto done0001;
       }
       if ((struct E_PSET*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->POWNRSET == SET) {
       goto done0001;
       }
       easg((char*)&ACARD, (iRef*)MEMCARD);
       easg((char*)&MEMCARD, (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMSHIPS);
       goto next0001;
done0001:
       if (MEMCARD == 0) {
       goto retlbl;
       }
       (*(int*)&((struct E_PSET*)fetch((iRef*)SET))->PMCOUNT) = (int)((struct E_PSET*)fetch((iRef*)SET))->PMCOUNT-1;
       if (ACARD == 0) {
       easg((char*)&(*(E_PCARD*)&((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS), (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMSHIPS);
       }
       else {
       easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)ACARD))->S_PMSHIPS), (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMSHIPS);
       }
       easg((char*)&ACARD, (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->P_PMEMBERS);
       easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)ACARD))->S_PMEMBERS), (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMEMBERS);
       easg((char*)&ACARD, (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMEMBERS);
       easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)ACARD))->P_PMEMBERS), (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->P_PMEMBERS);
       d_E_PCARD(MEMCARD);
retlbl:
eunasg((char*)&MEMCARD);
eunasg((char*)&ACARD);
eunasg((char*)&SET);
eunasg((char*)&ENTITY);
       return;
}
void E_RMVSPCFC_R(void* E1, void* E2) {
struct E_CARD* MEMCARD= 0;
struct E_CARD* ACARD= 0;
struct E_SET* SET= 0;
struct E_INSTH* ENTITY= 0;
       SET = (struct E_SET*)E1;
       ENTITY = (struct E_INSTH*)E2;
       if (ENTITY == 0 | SET == 0) {
       goto retlbl;
       }
       if (ENTITY == SET->F_MEMBERS->MEMBER) {
       ENTITY = (struct E_INSTH*)E_RMVFRST_F(SET);
       goto retlbl;
       }
       if (ENTITY == SET->L_MEMBERS->MEMBER) {
       ENTITY = (struct E_INSTH*)E_RMVLAST_F(SET);
       goto retlbl;
       }
       MEMCARD = (struct E_CARD*)ENTITY->F_MSHIPS;
next0001:
       if ( !  ( MEMCARD != 0 ) ) {
       goto done0001;
       }
       if (MEMCARD->OWNRSET == SET) {
       goto done0001;
       }
       ACARD = (struct E_CARD*)MEMCARD;
       MEMCARD = (struct E_CARD*)MEMCARD->S_MSHIPS;
       goto next0001;
done0001:
       if (MEMCARD == 0) {
       goto retlbl;
       }
       SET->MCOUNT = SET->MCOUNT-1;
       if (ACARD == 0) {
       ENTITY->F_MSHIPS = (struct E_CARD*)MEMCARD->S_MSHIPS;
       }
       else {
       ACARD->S_MSHIPS = (struct E_CARD*)MEMCARD->S_MSHIPS;
       }
       ACARD = (struct E_CARD*)MEMCARD->P_MEMBERS;
       ACARD->S_MEMBERS = (struct E_CARD*)MEMCARD->S_MEMBERS;
       ACARD = (struct E_CARD*)MEMCARD->S_MEMBERS;
       ACARD->P_MEMBERS = (struct E_CARD*)MEMCARD->P_MEMBERS;
       d_E_CARD(MEMCARD);
retlbl:
       return;
}
void* E_PRMVLAST_F(void* E1) {
struct E_PCARD* MEMCARD= 0;
struct E_PSET* SET= 0;
struct E_PINSTH* ENTITY= 0;
struct E_PCARD* ACARD= 0;
void* rval = 0;
       easg((char*)&SET, (iRef*)E1);
       if (SET == 0) {
       rval = (void*)0;
goto retlbl;
       }
       easg((char*)&MEMCARD, (iRef*)(struct E_PCARD*)((struct E_PSET*)fetch((iRef*)SET))->L_PMEMBERS);
       if (MEMCARD != 0) {
       (*(int*)&((struct E_PSET*)fetch((iRef*)SET))->PMCOUNT) = (int)((struct E_PSET*)fetch((iRef*)SET))->PMCOUNT-1;
       if ((struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->P_PMEMBERS == 0) {
       easg((char*)&(*(E_PCARD*)&((struct E_PSET*)fetch((iRef*)SET))->F_PMEMBERS), (iRef*)0);
       easg((char*)&(*(E_PCARD*)&((struct E_PSET*)fetch((iRef*)SET))->L_PMEMBERS), (iRef*)0);
       }
       else {
       easg((char*)&(*(E_PCARD*)&((struct E_PSET*)fetch((iRef*)SET))->L_PMEMBERS), (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->P_PMEMBERS);
       easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)(struct E_PCARD*)((struct E_PSET*)fetch((iRef*)SET))->L_PMEMBERS))->S_PMEMBERS), (iRef*)0);
       }
       easg((char*)&ENTITY, (iRef*)(struct E_PINSTH*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->PMEMBER);
       if (MEMCARD == (struct E_PCARD*)((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS) {
       easg((char*)&(*(E_PCARD*)&((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS), (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMSHIPS);
       }
       else {
       easg((char*)&ACARD, (iRef*)(struct E_PCARD*)((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS);
next0001:
       if ( !  ( (struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)ACARD))->S_PMSHIPS != MEMCARD ) ) {
       goto done0001;
       }
       easg((char*)&ACARD, (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)ACARD))->S_PMSHIPS);
       goto next0001;
done0001:
       easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)ACARD))->S_PMSHIPS), (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMSHIPS);
       }
       d_E_PCARD(MEMCARD);
       rval = (void*)ENTITY;
goto retlbl;
       }
       rval = (void*)0;
goto retlbl;
retlbl:
eunasg((char*)&MEMCARD);
eunasg((char*)&SET);
eunasg((char*)&ENTITY);
eunasg((char*)&ACARD);
       return rval;
}
void* E_RMVLAST_F(void* E1) {
struct E_CARD* MEMCARD= 0;
struct E_SET* SET= 0;
struct E_INSTH* ENTITY= 0;
struct E_CARD* ACARD= 0;
void* rval = 0;
       SET = (struct E_SET*)E1;
       if (SET == 0) {
       rval = (void*)0;
goto retlbl;
       }
       MEMCARD = (struct E_CARD*)SET->L_MEMBERS;
       if (MEMCARD != 0) {
       SET->MCOUNT = SET->MCOUNT-1;
       if (MEMCARD->P_MEMBERS == 0) {
       SET->F_MEMBERS = (struct E_CARD*)0;
       SET->L_MEMBERS = (struct E_CARD*)0;
       }
       else {
       SET->L_MEMBERS = (struct E_CARD*)MEMCARD->P_MEMBERS;
       SET->L_MEMBERS->S_MEMBERS = (struct E_CARD*)0;
       }
       ENTITY = (struct E_INSTH*)MEMCARD->MEMBER;
       if (MEMCARD == ENTITY->F_MSHIPS) {
       ENTITY->F_MSHIPS = (struct E_CARD*)MEMCARD->S_MSHIPS;
       }
       else {
       ACARD = (struct E_CARD*)ENTITY->F_MSHIPS;
next0001:
       if ( !  ( ACARD->S_MSHIPS != MEMCARD ) ) {
       goto done0001;
       }
       ACARD = (struct E_CARD*)ACARD->S_MSHIPS;
       goto next0001;
done0001:
       ACARD->S_MSHIPS = (struct E_CARD*)MEMCARD->S_MSHIPS;
       }
       d_E_CARD(MEMCARD);
       rval = (void*)ENTITY;
goto retlbl;
       }
       rval = (void*)0;
goto retlbl;
retlbl:
       return rval;
}
void* E_PRMVFRST_F(void* E1) {
struct E_PCARD* MEMCARD= 0;
struct E_PSET* SET= 0;
struct E_PINSTH* ENTITY= 0;
struct E_PCARD* ACARD= 0;
void* rval = 0;
       easg((char*)&SET, (iRef*)E1);
       if (SET == 0) {
       rval = (void*)0;
goto retlbl;
       }
       easg((char*)&MEMCARD, (iRef*)(struct E_PCARD*)((struct E_PSET*)fetch((iRef*)SET))->F_PMEMBERS);
       if (MEMCARD != 0) {
       (*(int*)&((struct E_PSET*)fetch((iRef*)SET))->PMCOUNT) = (int)((struct E_PSET*)fetch((iRef*)SET))->PMCOUNT-1;
       if ((struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMEMBERS == 0) {
       easg((char*)&(*(E_PCARD*)&((struct E_PSET*)fetch((iRef*)SET))->F_PMEMBERS), (iRef*)0);
       easg((char*)&(*(E_PCARD*)&((struct E_PSET*)fetch((iRef*)SET))->L_PMEMBERS), (iRef*)0);
       }
       else {
       easg((char*)&(*(E_PCARD*)&((struct E_PSET*)fetch((iRef*)SET))->F_PMEMBERS), (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMEMBERS);
       easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)(struct E_PCARD*)((struct E_PSET*)fetch((iRef*)SET))->F_PMEMBERS))->P_PMEMBERS), (iRef*)0);
       }
       easg((char*)&ENTITY, (iRef*)(struct E_PINSTH*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->PMEMBER);
       if (MEMCARD == (struct E_PCARD*)((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS) {
       easg((char*)&(*(E_PCARD*)&((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS), (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMSHIPS);
       }
       else {
       easg((char*)&ACARD, (iRef*)(struct E_PCARD*)((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS);
next0001:
       if ( !  ( (struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)ACARD))->S_PMSHIPS != MEMCARD ) ) {
       goto done0001;
       }
       easg((char*)&ACARD, (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)ACARD))->S_PMSHIPS);
       goto next0001;
done0001:
       easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)ACARD))->S_PMSHIPS), (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMSHIPS);
       }
       d_E_PCARD(MEMCARD);
       rval = (void*)ENTITY;
goto retlbl;
       }
       rval = (void*)0;
goto retlbl;
retlbl:
eunasg((char*)&MEMCARD);
eunasg((char*)&SET);
eunasg((char*)&ENTITY);
eunasg((char*)&ACARD);
       return rval;
}
void* E_RMVFRST_F(void* E1) {
struct E_CARD* MEMCARD= 0;
struct E_SET* SET= 0;
struct E_INSTH* ENTITY= 0;
struct E_CARD* ACARD= 0;
void* rval = 0;
       SET = (struct E_SET*)E1;
       if (SET == 0) {
       rval = (void*)0;
goto retlbl;
       }
       MEMCARD = (struct E_CARD*)SET->F_MEMBERS;
       if (MEMCARD != 0) {
       SET->MCOUNT = SET->MCOUNT-1;
       if (MEMCARD->S_MEMBERS == 0) {
       SET->F_MEMBERS = (struct E_CARD*)0;
       SET->L_MEMBERS = (struct E_CARD*)0;
       }
       else {
       SET->F_MEMBERS = (struct E_CARD*)MEMCARD->S_MEMBERS;
       SET->F_MEMBERS->P_MEMBERS = (struct E_CARD*)0;
       }
       ENTITY = (struct E_INSTH*)MEMCARD->MEMBER;
       if (MEMCARD == ENTITY->F_MSHIPS) {
       ENTITY->F_MSHIPS = (struct E_CARD*)MEMCARD->S_MSHIPS;
       }
       else {
       ACARD = (struct E_CARD*)ENTITY->F_MSHIPS;
next0001:
       if ( !  ( ACARD->S_MSHIPS != MEMCARD ) ) {
       goto done0001;
       }
       ACARD = (struct E_CARD*)ACARD->S_MSHIPS;
       goto next0001;
done0001:
       ACARD->S_MSHIPS = (struct E_CARD*)MEMCARD->S_MSHIPS;
       }
       d_E_CARD(MEMCARD);
       rval = (void*)ENTITY;
goto retlbl;
       }
       rval = (void*)0;
goto retlbl;
retlbl:
       return rval;
}
void* S_PEASSET_F(void* E, Etxt* SNAME) {
struct E_PINSTH* ENT= 0;
struct E_PCARD* MEMCARD= 0;
struct E_PCARD* ACARD= 0;
void* rval = 0;
E_TXTINC_R(SNAME);
       easg((char*)&ENT, (iRef*)E);
       if (ENT == 0) {
       rval = (void*)0;
goto retlbl;
       }
       easg((char*)&MEMCARD, (iRef*)(struct E_PCARD*)((struct E_PINSTH*)fetch((iRef*)ENT))->F_PMSHIPS);
next0001:
       if ( !  ( MEMCARD != 0 ) ) {
       goto done0001;
       }
       if (E_TXTEQL_F((Etxt*)((struct E_PSET*)fetch((iRef*)(struct E_PSET*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->POWNRSET))->PSETNAME, SNAME)) {
       goto done0001;
       easg((char*)&MEMCARD, (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMSHIPS);
       }
       goto next0001;
done0001:
       if (MEMCARD != 0) {
       easg((char*)&MEMCARD, (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMEMBERS);
       }
       if (MEMCARD != 0) {
       easg((char*)&ENT, (iRef*)(struct E_PINSTH*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->PMEMBER);
       rval = (void*)(struct E_PINSTH*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->PMEMBER;
goto retlbl;
       }
       else {
       rval = (void*)0;
goto retlbl;
       }
retlbl:
E_TXTDEL_R(SNAME);
eunasg((char*)&ENT);
eunasg((char*)&MEMCARD);
eunasg((char*)&ACARD);
       return rval;
}
void* S_EASSET_F(void* E, Etxt* SNAME) {
struct E_INSTH* ENT= 0;
struct E_CARD* MEMCARD= 0;
void* rval = 0;
E_TXTINC_R(SNAME);
       ENT = (struct E_INSTH*)E;
       if (ENT == 0) {
       rval = (void*)0;
goto retlbl;
       }
       MEMCARD = (struct E_CARD*)ENT->F_MSHIPS;
next0001:
       if ( !  ( MEMCARD != 0 ) ) {
       goto done0001;
       }
       if (E_TXTEQL_F(MEMCARD->OWNRSET->SETNAME, SNAME)) {
       goto done0001;
       MEMCARD = (struct E_CARD*)MEMCARD->S_MSHIPS;
       }
       goto next0001;
done0001:
       if (MEMCARD != 0) {
       MEMCARD = (struct E_CARD*)MEMCARD->S_MEMBERS;
       }
       if (MEMCARD != 0) {
       rval = (void*)MEMCARD->MEMBER;
goto retlbl;
       }
       else {
       rval = (void*)0;
goto retlbl;
       }
retlbl:
E_TXTDEL_R(SNAME);
       return rval;
}
void* P_PEASSET_F(void* E, Etxt* SNAME) {
struct E_PINSTH* ENT= 0;
struct E_PCARD* MEMCARD= 0;
void* rval = 0;
E_TXTINC_R(SNAME);
       easg((char*)&ENT, (iRef*)E);
       if (ENT == 0) {
       rval = (void*)0;
goto retlbl;
       }
       easg((char*)&MEMCARD, (iRef*)(struct E_PCARD*)((struct E_PINSTH*)fetch((iRef*)ENT))->F_PMSHIPS);
next0001:
       if ( !  ( MEMCARD != 0 ) ) {
       goto done0001;
       }
       if (E_TXTEQL_F((Etxt*)((struct E_PSET*)fetch((iRef*)(struct E_PSET*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->POWNRSET))->PSETNAME, SNAME)) {
       goto done0001;
       easg((char*)&MEMCARD, (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMSHIPS);
       }
       goto next0001;
done0001:
       easg((char*)&MEMCARD, (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->P_PMEMBERS);
       if (MEMCARD != 0) {
       rval = (void*)(struct E_PINSTH*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->PMEMBER;
goto retlbl;
       }
       else {
       rval = (void*)0;
goto retlbl;
       }
retlbl:
E_TXTDEL_R(SNAME);
eunasg((char*)&ENT);
eunasg((char*)&MEMCARD);
       return rval;
}
void* P_EASSET_F(void* E, Etxt* SNAME) {
struct E_INSTH* ENT= 0;
struct E_CARD* MEMCARD= 0;
void* rval = 0;
E_TXTINC_R(SNAME);
       ENT = (struct E_INSTH*)E;
       if (ENT == 0) {
       rval = (void*)0;
goto retlbl;
       }
       MEMCARD = (struct E_CARD*)ENT->F_MSHIPS;
next0001:
       if ( !  ( MEMCARD != 0 ) ) {
       goto done0001;
       }
       if (E_TXTEQL_F(MEMCARD->OWNRSET->SETNAME, SNAME)) {
       goto done0001;
       MEMCARD = (struct E_CARD*)MEMCARD->S_MSHIPS;
       }
       goto next0001;
done0001:
       MEMCARD = (struct E_CARD*)MEMCARD->P_MEMBERS;
       if (MEMCARD != 0) {
       rval = (void*)MEMCARD->MEMBER;
goto retlbl;
       }
       else {
       rval = (void*)0;
goto retlbl;
       }
retlbl:
E_TXTDEL_R(SNAME);
       return rval;
}
void* L_PEASSET_F(void* S) {
struct E_PSET* SET= 0;
struct E_PCARD* MEMCARD= 0;
void* rval = 0;
       easg((char*)&SET, (iRef*)S);
       if (S != 0) {
       easg((char*)&MEMCARD, (iRef*)(struct E_PCARD*)((struct E_PSET*)fetch((iRef*)SET))->L_PMEMBERS);
       }
       if (MEMCARD != 0) {
       rval = (void*)(struct E_PINSTH*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->PMEMBER;
goto retlbl;
       }
       rval = (void*)0;
goto retlbl;
retlbl:
eunasg((char*)&SET);
eunasg((char*)&MEMCARD);
       return rval;
}
void* L_EASSET_F(void* S) {
struct E_SET* SET= 0;
struct E_CARD* MEMCARD= 0;
void* rval = 0;
       SET = (struct E_SET*)S;
       if (S != 0) {
       MEMCARD = (struct E_CARD*)SET->L_MEMBERS;
       }
       if (MEMCARD != 0) {
       rval = (void*)MEMCARD->MEMBER;
goto retlbl;
       }
       rval = (void*)0;
goto retlbl;
retlbl:
       return rval;
}
void* F_PEASSET_F(void* S) {
struct E_PSET* SET= 0;
struct E_PCARD* MEMCARD= 0;
void* rval = 0;
       easg((char*)&SET, (iRef*)S);
       if (S != 0) {
       easg((char*)&MEMCARD, (iRef*)(struct E_PCARD*)((struct E_PSET*)fetch((iRef*)SET))->F_PMEMBERS);
       }
       if (MEMCARD != 0) {
       rval = (void*)(struct E_PINSTH*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->PMEMBER;
goto retlbl;
       }
       rval = (void*)0;
goto retlbl;
retlbl:
eunasg((char*)&SET);
eunasg((char*)&MEMCARD);
       return rval;
}
void* F_EASSET_F(void* S) {
struct E_SET* SET= 0;
struct E_CARD* MEMCARD= 0;
void* rval = 0;
       SET = (struct E_SET*)S;
       if (S != 0) {
       MEMCARD = (struct E_CARD*)SET->F_MEMBERS;
       }
       if (MEMCARD != 0) {
       rval = (void*)MEMCARD->MEMBER;
goto retlbl;
       }
       rval = (void*)0;
goto retlbl;
retlbl:
       return rval;
}
int N_PEASSET_F(void* S) {
struct E_PSET* SET= 0;
int rval = 0;
       easg((char*)&SET, (iRef*)S);
       if (SET != 0) {
       rval = (int)(int)((struct E_PSET*)fetch((iRef*)SET))->PMCOUNT;
goto retlbl;
       }
       rval = (int)0;
goto retlbl;
retlbl:
eunasg((char*)&SET);
       return rval;
}
int N_EASSET_F(void* S) {
struct E_SET* SET= 0;
int rval = 0;
       SET = (struct E_SET*)S;
       if (SET != 0) {
       rval = (int)SET->MCOUNT;
goto retlbl;
       }
       rval = (int)0;
goto retlbl;
retlbl:
       return rval;
}
int M_PEASSET_F(void* E, Etxt* SNAME) {
struct E_PINSTH* ENT= 0;
struct E_PCARD* MEMCARD= 0;
int rval = 0;
E_TXTINC_R(SNAME);
       easg((char*)&ENT, (iRef*)E);
       if (ENT == 0) {
       rval = (int)0;
goto retlbl;
       }
       easg((char*)&MEMCARD, (iRef*)(struct E_PCARD*)((struct E_PINSTH*)fetch((iRef*)ENT))->F_PMSHIPS);
next0001:
       if ( !  ( MEMCARD != 0 ) ) {
       goto done0001;
       }
       if (E_TXTEQL_F((Etxt*)((struct E_PSET*)fetch((iRef*)(struct E_PSET*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->POWNRSET))->PSETNAME, SNAME)) {
       goto done0001;
       easg((char*)&MEMCARD, (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMSHIPS);
       }
       goto next0001;
done0001:
       if (MEMCARD != 0) {
       rval = (int)1;
goto retlbl;
       }
       else {
       rval = (int)0;
goto retlbl;
       }
retlbl:
E_TXTDEL_R(SNAME);
eunasg((char*)&ENT);
eunasg((char*)&MEMCARD);
       return rval;
}
int M_EASSET_F(void* E, Etxt* SNAME) {
struct E_INSTH* ENT= 0;
struct E_CARD* MEMCARD= 0;
int rval = 0;
E_TXTINC_R(SNAME);
       ENT = (struct E_INSTH*)E;
       if (ENT == 0) {
       rval = (int)0;
goto retlbl;
       }
       MEMCARD = (struct E_CARD*)ENT->F_MSHIPS;
next0001:
       if ( !  ( MEMCARD != 0 ) ) {
       goto done0001;
       }
       if (E_TXTEQL_F(MEMCARD->OWNRSET->SETNAME, SNAME)) {
       goto done0001;
       MEMCARD = (struct E_CARD*)MEMCARD->S_MSHIPS;
       }
       goto next0001;
done0001:
       if (MEMCARD != 0) {
       rval = (int)1;
goto retlbl;
       }
       else {
       rval = (int)0;
goto retlbl;
       }
retlbl:
E_TXTDEL_R(SNAME);
       return rval;
}
void E_PFAFTER_R(void* E1, void* E2, void* E3) {
struct E_PCARD* MEMCARD= 0;
struct E_PSET* SET= 0;
struct E_PINSTH* ENTITY= 0;
struct E_PINSTH* TARGET= 0;
struct E_PCARD* ACARD= 0;
       easg((char*)&SET, (iRef*)E1);
       easg((char*)&ENTITY, (iRef*)E2);
       if (SET == 0 | ENTITY == 0) {
       goto retlbl;
       }
       easg((char*)&TARGET, (iRef*)E3);
       if (TARGET == 0) {
       goto retlbl;
       }
       if (TARGET == (struct E_PINSTH*)((struct E_PCARD*)fetch((iRef*)(struct E_PCARD*)((struct E_PSET*)fetch((iRef*)SET))->L_PMEMBERS))->PMEMBER) {
       E_PFLAST_R(SET, ENTITY);
       goto retlbl;
       }
       (*(int*)&((struct E_PSET*)fetch((iRef*)SET))->PMCOUNT) = (int)((struct E_PSET*)fetch((iRef*)SET))->PMCOUNT+1;
       easg((char*)&MEMCARD, c_E_PCARD());
       easg((char*)&(*(E_PINSTH*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->PMEMBER), (iRef*)ENTITY);
       easg((char*)&(*(E_PSET*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->POWNRSET), (iRef*)SET);
       easg((char*)&ACARD, (iRef*)(struct E_PCARD*)((struct E_PINSTH*)fetch((iRef*)TARGET))->F_PMSHIPS);
next0001:
       if ( !  ( ACARD != 0 ) ) {
       goto done0001;
       }
       if ((struct E_PSET*)((struct E_PCARD*)fetch((iRef*)ACARD))->POWNRSET == SET) {
       goto done0001;
       }
       easg((char*)&ACARD, (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)ACARD))->S_PMSHIPS);
       goto next0001;
done0001:
       easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)ACARD))->S_PMEMBERS))->P_PMEMBERS), (iRef*)MEMCARD);
       easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMEMBERS), (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)ACARD))->S_PMEMBERS);
       easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->P_PMEMBERS), (iRef*)ACARD);
       easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)ACARD))->S_PMEMBERS), (iRef*)MEMCARD);
       easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMSHIPS), (iRef*)(struct E_PCARD*)((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS);
       easg((char*)&(*(E_PCARD*)&((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS), (iRef*)MEMCARD);
retlbl:
eunasg((char*)&MEMCARD);
eunasg((char*)&SET);
eunasg((char*)&ENTITY);
eunasg((char*)&TARGET);
eunasg((char*)&ACARD);
       return;
}
void E_FAFTER_R(void* E1, void* E2, void* E3) {
struct E_CARD* MEMCARD= 0;
struct E_SET* SET= 0;
struct E_INSTH* ENTITY= 0;
struct E_INSTH* TARGET= 0;
struct E_CARD* ACARD= 0;
       SET = (struct E_SET*)E1;
       ENTITY = (struct E_INSTH*)E2;
       if (SET == 0 | ENTITY == 0) {
       goto retlbl;
       }
       TARGET = (struct E_INSTH*)E3;
       if (TARGET == 0) {
       goto retlbl;
       }
       if (TARGET == SET->L_MEMBERS->MEMBER) {
       E_FLAST_R(SET, ENTITY);
       goto retlbl;
       }
       SET->MCOUNT = SET->MCOUNT+1;
       MEMCARD= c_E_CARD();
       MEMCARD->MEMBER = (struct E_INSTH*)ENTITY;
       MEMCARD->OWNRSET = (struct E_SET*)SET;
       ACARD = (struct E_CARD*)TARGET->F_MSHIPS;
next0001:
       if ( !  ( ACARD != 0 ) ) {
       goto done0001;
       }
       if (ACARD->OWNRSET == SET) {
       goto done0001;
       }
       ACARD = (struct E_CARD*)ACARD->S_MSHIPS;
       goto next0001;
done0001:
       ACARD->S_MEMBERS->P_MEMBERS = (struct E_CARD*)MEMCARD;
       MEMCARD->S_MEMBERS = (struct E_CARD*)ACARD->S_MEMBERS;
       MEMCARD->P_MEMBERS = (struct E_CARD*)ACARD;
       ACARD->S_MEMBERS = (struct E_CARD*)MEMCARD;
       MEMCARD->S_MSHIPS = (struct E_CARD*)ENTITY->F_MSHIPS;
       ENTITY->F_MSHIPS = (struct E_CARD*)MEMCARD;
retlbl:
       return;
}
void E_PFBEFOR_R(void* E1, void* E2, void* E3) {
struct E_PCARD* MEMCARD= 0;
struct E_PSET* SET= 0;
struct E_PINSTH* ENTITY= 0;
struct E_PINSTH* TARGET= 0;
struct E_PCARD* ACARD= 0;
       easg((char*)&SET, (iRef*)E1);
       easg((char*)&ENTITY, (iRef*)E2);
       if (SET == 0 | ENTITY == 0) {
       goto retlbl;
       }
       easg((char*)&TARGET, (iRef*)E3);
       if (TARGET == 0) {
       goto retlbl;
       }
       if (TARGET == (struct E_PINSTH*)((struct E_PCARD*)fetch((iRef*)(struct E_PCARD*)((struct E_PSET*)fetch((iRef*)SET))->F_PMEMBERS))->PMEMBER) {
       E_PFFIRST_R(SET, ENTITY);
       goto retlbl;
       }
       (*(int*)&((struct E_PSET*)fetch((iRef*)SET))->PMCOUNT) = (int)((struct E_PSET*)fetch((iRef*)SET))->PMCOUNT+1;
       easg((char*)&MEMCARD, c_E_PCARD());
       easg((char*)&(*(E_PINSTH*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->PMEMBER), (iRef*)ENTITY);
       easg((char*)&(*(E_PSET*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->POWNRSET), (iRef*)SET);
       easg((char*)&ACARD, (iRef*)(struct E_PCARD*)((struct E_PINSTH*)fetch((iRef*)TARGET))->F_PMSHIPS);
next0001:
       if ( !  ( ACARD != 0 ) ) {
       goto done0001;
       }
       if ((struct E_PSET*)((struct E_PCARD*)fetch((iRef*)ACARD))->POWNRSET == SET) {
       goto done0001;
       }
       easg((char*)&ACARD, (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)ACARD))->S_PMSHIPS);
       goto next0001;
done0001:
       easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)ACARD))->P_PMEMBERS))->S_PMEMBERS), (iRef*)MEMCARD);
       easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->P_PMEMBERS), (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)ACARD))->P_PMEMBERS);
       easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMEMBERS), (iRef*)ACARD);
       easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)ACARD))->P_PMEMBERS), (iRef*)MEMCARD);
       easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMSHIPS), (iRef*)(struct E_PCARD*)((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS);
       easg((char*)&(*(E_PCARD*)&((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS), (iRef*)MEMCARD);
retlbl:
eunasg((char*)&MEMCARD);
eunasg((char*)&SET);
eunasg((char*)&ENTITY);
eunasg((char*)&TARGET);
eunasg((char*)&ACARD);
       return;
}
void E_FBEFOR_R(void* E1, void* E2, void* E3) {
struct E_CARD* MEMCARD= 0;
struct E_SET* SET= 0;
struct E_INSTH* ENTITY= 0;
struct E_INSTH* TARGET= 0;
struct E_CARD* ACARD= 0;
       SET = (struct E_SET*)E1;
       ENTITY = (struct E_INSTH*)E2;
       if (SET == 0 | ENTITY == 0) {
       goto retlbl;
       }
       TARGET = (struct E_INSTH*)E3;
       if (TARGET == 0) {
       goto retlbl;
       }
       if (TARGET == SET->F_MEMBERS->MEMBER) {
       E_FFIRST_R(SET, ENTITY);
       goto retlbl;
       }
       SET->MCOUNT = SET->MCOUNT+1;
       MEMCARD= c_E_CARD();
       MEMCARD->MEMBER = (struct E_INSTH*)ENTITY;
       MEMCARD->OWNRSET = (struct E_SET*)SET;
       ACARD = (struct E_CARD*)TARGET->F_MSHIPS;
next0001:
       if ( !  ( ACARD != 0 ) ) {
       goto done0001;
       }
       if (ACARD->OWNRSET == SET) {
       goto done0001;
       }
       ACARD = (struct E_CARD*)ACARD->S_MSHIPS;
       goto next0001;
done0001:
       ACARD->P_MEMBERS->S_MEMBERS = (struct E_CARD*)MEMCARD;
       MEMCARD->S_MEMBERS = (struct E_CARD*)ACARD;
       ACARD->P_MEMBERS = (struct E_CARD*)MEMCARD;
       MEMCARD->S_MSHIPS = (struct E_CARD*)ENTITY->F_MSHIPS;
       ENTITY->F_MSHIPS = (struct E_CARD*)MEMCARD;
retlbl:
       return;
}
void E_PFLAST_R(void* E1, void* E2) {
struct E_PCARD* MEMCARD= 0;
struct E_PSET* SET= 0;
struct E_PINSTH* ENTITY= 0;
       easg((char*)&SET, (iRef*)E1);
       easg((char*)&ENTITY, (iRef*)E2);
       if (SET == 0 | ENTITY == 0) {
       goto retlbl;
       }
       (*(int*)&((struct E_PSET*)fetch((iRef*)SET))->PMCOUNT) = (int)((struct E_PSET*)fetch((iRef*)SET))->PMCOUNT+1;
       easg((char*)&MEMCARD, c_E_PCARD());
       easg((char*)&(*(E_PINSTH*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->PMEMBER), (iRef*)ENTITY);
       easg((char*)&(*(E_PSET*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->POWNRSET), (iRef*)SET);
       if ((struct E_PCARD*)((struct E_PSET*)fetch((iRef*)SET))->L_PMEMBERS != 0) {
       easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)(struct E_PCARD*)((struct E_PSET*)fetch((iRef*)SET))->L_PMEMBERS))->S_PMEMBERS), (iRef*)MEMCARD);
       easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->P_PMEMBERS), (iRef*)(struct E_PCARD*)((struct E_PSET*)fetch((iRef*)SET))->L_PMEMBERS);
       }
       else {
       easg((char*)&(*(E_PCARD*)&((struct E_PSET*)fetch((iRef*)SET))->F_PMEMBERS), (iRef*)MEMCARD);
       }
       easg((char*)&(*(E_PCARD*)&((struct E_PSET*)fetch((iRef*)SET))->L_PMEMBERS), (iRef*)MEMCARD);
       easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMSHIPS), (iRef*)(struct E_PCARD*)((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS);
       easg((char*)&(*(E_PCARD*)&((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS), (iRef*)MEMCARD);
retlbl:
eunasg((char*)&MEMCARD);
eunasg((char*)&SET);
eunasg((char*)&ENTITY);
       return;
}
void E_FLAST_R(void* E1, void* E2) {
struct E_CARD* MEMCARD= 0;
struct E_SET* SET= 0;
struct E_INSTH* ENTITY= 0;
       SET = (struct E_SET*)E1;
       ENTITY = (struct E_INSTH*)E2;
       if (SET == 0 | ENTITY == 0) {
       goto retlbl;
       }
       SET->MCOUNT = SET->MCOUNT+1;
       MEMCARD= c_E_CARD();
       MEMCARD->MEMBER = (struct E_INSTH*)ENTITY;
       MEMCARD->OWNRSET = (struct E_SET*)SET;
       if (SET->L_MEMBERS != 0) {
       SET->L_MEMBERS->S_MEMBERS = (struct E_CARD*)MEMCARD;
       MEMCARD->P_MEMBERS = (struct E_CARD*)SET->L_MEMBERS;
       }
       else {
       SET->F_MEMBERS = (struct E_CARD*)MEMCARD;
       }
       SET->L_MEMBERS = (struct E_CARD*)MEMCARD;
       MEMCARD->S_MSHIPS = (struct E_CARD*)ENTITY->F_MSHIPS;
       ENTITY->F_MSHIPS = (struct E_CARD*)MEMCARD;
retlbl:
       return;
}
void E_PFFIRST_R(void* E1, void* E2) {
struct E_PCARD* MEMCARD= 0;
struct E_PSET* SET= 0;
struct E_PINSTH* ENTITY= 0;
struct E_PCARD* ACARD= 0;
       easg((char*)&SET, (iRef*)E1);
       easg((char*)&ENTITY, (iRef*)E2);
       if (SET == 0 | ENTITY == 0) {
       goto retlbl;
       }
       (*(int*)&((struct E_PSET*)fetch((iRef*)SET))->PMCOUNT) = (int)((struct E_PSET*)fetch((iRef*)SET))->PMCOUNT+1;
       easg((char*)&MEMCARD, c_E_PCARD());
       easg((char*)&(*(E_PSET*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->POWNRSET), (iRef*)SET);
       easg((char*)&(*(E_PINSTH*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->PMEMBER), (iRef*)ENTITY);
       easg((char*)&ACARD, (iRef*)(struct E_PCARD*)((struct E_PSET*)fetch((iRef*)SET))->F_PMEMBERS);
       if ((struct E_PCARD*)((struct E_PSET*)fetch((iRef*)SET))->F_PMEMBERS != 0) {
       easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)ACARD))->P_PMEMBERS), (iRef*)MEMCARD);
       easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMEMBERS), (iRef*)(struct E_PCARD*)((struct E_PSET*)fetch((iRef*)SET))->F_PMEMBERS);
       }
       else {
       easg((char*)&(*(E_PCARD*)&((struct E_PSET*)fetch((iRef*)SET))->L_PMEMBERS), (iRef*)MEMCARD);
       }
       easg((char*)&(*(E_PCARD*)&((struct E_PSET*)fetch((iRef*)SET))->F_PMEMBERS), (iRef*)MEMCARD);
       easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMSHIPS), (iRef*)(struct E_PCARD*)((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS);
       easg((char*)&(*(E_PCARD*)&((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS), (iRef*)MEMCARD);
retlbl:
eunasg((char*)&MEMCARD);
eunasg((char*)&SET);
eunasg((char*)&ENTITY);
eunasg((char*)&ACARD);
       return;
}
void E_FFIRST_R(void* E1, void* E2) {
struct E_CARD* MEMCARD= 0;
struct E_SET* SET= 0;
struct E_INSTH* ENTITY= 0;
       SET = (struct E_SET*)E1;
       if (SET == 0) {
       goto retlbl;
       }
       ENTITY = (struct E_INSTH*)E2;
       if (ENTITY == 0) {
       goto retlbl;
       }
       SET->MCOUNT = SET->MCOUNT+1;
       MEMCARD= c_E_CARD();
       MEMCARD->OWNRSET = (struct E_SET*)SET;
       MEMCARD->MEMBER = (struct E_INSTH*)ENTITY;
       if (SET->F_MEMBERS != 0) {
       SET->F_MEMBERS->P_MEMBERS = (struct E_CARD*)MEMCARD;
       MEMCARD->S_MEMBERS = (struct E_CARD*)SET->F_MEMBERS;
       }
       else {
       SET->L_MEMBERS = (struct E_CARD*)MEMCARD;
       }
       SET->F_MEMBERS = (struct E_CARD*)MEMCARD;
       MEMCARD->S_MSHIPS = (struct E_CARD*)ENTITY->F_MSHIPS;
       ENTITY->F_MSHIPS = (struct E_CARD*)MEMCARD;
retlbl:
       return;
}

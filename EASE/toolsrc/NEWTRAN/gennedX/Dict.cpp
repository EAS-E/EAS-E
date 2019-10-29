#include "stdafx.h"
#include "malloc.h"
#include "libopts.h"
#include "math.h"
#include "Dict.h"

void Dict_addTypes() {
#ifdef _DICTUSE
addEType(E_TXTLIT_F(_T("DICTUSE")), 3003,    2, 0);
#endif
#ifdef _DICTENTRY
addEType(E_TXTLIT_F(_T("DICTENTRY")), 3003,    1, 0);
#endif
}
Dict_sys* Dict;

void Dict_init() {
Dict = (Dict_sys*)E_CREATE_F( 0,3003, sizeof(Dict_sys));
Dict_sets();
Dict_addTypes();
}
void Dict_sets() {
       return;
}
void d_DICTENTRY(struct DICTENTRY*& EPTR) {
       E_TXTASG_R(&EPTR->LEXEME, 0);
       E_DESTROY_R(EPTR);
       EPTR = (struct DICTENTRY*)0;
       return;
}
struct DICTENTRY* c_DICTENTRY() {
struct DICTENTRY* EPTR= 0;
struct DICTENTRY* rval = 0;
       EPTR = (struct DICTENTRY*)E_CREATE_F(3003, 1, Z_DICTENTRY);
       rval = (struct DICTENTRY*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void d_DICTUSE(struct DICTUSE*& EPTR) {
       E_DESTROY_R(EPTR);
       EPTR = (struct DICTUSE*)0;
       return;
}
struct DICTUSE* c_DICTUSE() {
struct DICTUSE* EPTR= 0;
struct DICTUSE* rval = 0;
       EPTR = (struct DICTUSE*)E_CREATE_F(3003, 2, Z_DICTUSE);
       rval = (struct DICTUSE*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
struct DICTENTRY* FINDDICTENTRY_F(Etxt* INLEX) {
int INDEX= 0;
struct DICTENTRY* ENTRY= 0;
struct DICTENTRY* rval = 0;
E_TXTINC_R(INLEX);
       INDEX = ACHAR_F(INLEX, 1);
       ENTRY = (struct DICTENTRY*)Dict->F_DICT[INDEX];
next0001:
       if ( !  ( ENTRY != 0 ) ) {
       goto done0001;
       }
       if (E_TXTEQL_F(ENTRY->LEXEME, INLEX)) {
       goto done0001;
       }
       ENTRY = (struct DICTENTRY*)ENTRY->S_DICT;
       goto next0001;
done0001:
       if (ENTRY == 0) {
       ENTRY= c_DICTENTRY();
       E_TXTASG_R(&ENTRY->LEXEME, INLEX);
       ENTRY->S_DICT = (struct DICTENTRY*)Dict->F_DICT[INDEX];
       Dict->F_DICT[INDEX] = (struct DICTENTRY*)ENTRY;
       }
       rval = (struct DICTENTRY*)ENTRY;
goto retlbl;
retlbl:
E_TXTDEL_R(INLEX);
       return rval;
}
void DESTROYUSE(struct DICTUSE* AUSE) {
struct DICTENTRY* REF= 0;
struct DICTUSE* DUSE= 0;
struct DICTUSE* LUSE= 0;
       REF = (struct DICTENTRY*)AUSE->USEREF;
       DUSE = (struct DICTUSE*)REF->F_USAGE;
next0001:
       if ( !  ( DUSE != 0 ) ) {
       goto done0001;
       }
       if (DUSE == AUSE) {
       if (LUSE != 0) {
       LUSE->S_USAGE = (struct DICTUSE*)DUSE->S_USAGE;
       }
       else {
       REF->F_USAGE = (struct DICTUSE*)DUSE->S_USAGE;
       }
       d_DICTUSE(AUSE);
       goto done0001;
       }
       LUSE = (struct DICTUSE*)DUSE;
       DUSE = (struct DICTUSE*)DUSE->S_USAGE;
       goto next0001;
done0001:
       goto retlbl;
retlbl:
       return;
}
struct DICTUSE* FINDPREFUSE_F(struct TOKEN* TKN, int MUSTHAVE) {
struct DICTENTRY* DREF= 0;
struct DICTUSE* DUSE= 0;
struct DICTUSE* rval = 0;
       DREF = (struct DICTENTRY*)TKN->DICTREF;
       DUSE = (struct DICTUSE*)FINDSPECUSE_F(DREF, 1);
       if (DUSE == 0) {
       DUSE = (struct DICTUSE*)DREF->F_USAGE;
next0001:
       if ( !  ( DUSE != 0 ) ) {
       goto done0001;
       }
       if (DUSE->USETYPE < 7) {
       goto done0001;
       }
       DUSE = (struct DICTUSE*)DUSE->S_USAGE;
       goto next0001;
done0001:
;      }
       if (DUSE == 0 & MUSTHAVE != 0) {
       if (TKN->SCRIPTED == 0) {
       EASERR(1002, TKN->LEXEME);
       }
       DUSE = (struct DICTUSE*)MAKEUSE_F(DREF, 1);
       DUSE->USEMODE = 1;
       DUSE->USEENTITY = (struct ENTITYTYPE*)FINDETYPEBYNAME_F(E_TXTLIT_F(_T("Integer")), 1);
       }
       rval = (struct DICTUSE*)DUSE;
goto retlbl;
retlbl:
       return rval;
}
struct DICTUSE* FINDSPECUSE_F(struct DICTENTRY* DREF, int TYPE) {
struct DICTUSE* DUSE= 0;
struct DICTUSE* rval = 0;
       DUSE = (struct DICTUSE*)DREF->F_USAGE;
next0001:
       if ( !  ( DUSE != 0 ) ) {
       goto done0001;
       }
       if (DUSE->USETYPE == TYPE) {
       goto done0001;
       }
       DUSE = (struct DICTUSE*)DUSE->S_USAGE;
       goto next0001;
done0001:
       rval = (struct DICTUSE*)DUSE;
goto retlbl;
retlbl:
       return rval;
}
struct DICTUSE* MAKEUSE_F(struct DICTENTRY* DREF, int TYPE) {
struct DICTUSE* DUSE= 0;
struct DICTUSE* rval = 0;
       if (TYPE == 2 | TYPE == 3) {
       DUSE = (struct DICTUSE*)FINDSPECUSE_F(DREF, TYPE);
       if (DUSE != 0) {
       EASERR(-1020, DREF->LEXEME);
       rval = (struct DICTUSE*)DUSE;
goto retlbl;
       }
       }
       DUSE= c_DICTUSE();
       DUSE->USETYPE = TYPE;
       DUSE->S_USAGE = (struct DICTUSE*)DREF->F_USAGE;
       DREF->F_USAGE = (struct DICTUSE*)DUSE;
       DUSE->USEREF = (struct DICTENTRY*)DREF;
       rval = (struct DICTUSE*)DUSE;
goto retlbl;
retlbl:
       return rval;
}

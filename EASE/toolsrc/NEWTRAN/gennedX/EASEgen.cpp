#include "stdafx.h"
#include "malloc.h"
#include "libopts.h"
#include "math.h"
#include "EASEgen.h"

void EASEgen_addTypes() {
}
EASEgen_sys* EASEgen;

void EASEgen_init() {
EASEgen = (EASEgen_sys*)E_CREATE_F( 0,3008, sizeof(EASEgen_sys));
EASEgen_sets();
EASEgen_addTypes();
}
void EASEgen_sets() {
       return;
}
int GENPATTR(struct DICTUSE* AUSE, struct TOKEN* VARTOKEN, struct NODE* SUBNODE, int ISPUT) {
int MODE= 0;
struct DICTUSE* SUSE= 0;
struct DICTENTRY* AREF= 0;
int rval = 0;
       if (ISPUT != 0) {
       if (AUSE->USEMODE == 4 & AUSE->USEENTITY->ISPERSISTENT != 0) {
       WTX_R(E_TXTLIT_F(_T("easg((char*)&")));
       }
       WTX_R(E_TXTLIT_F(_T("(*")));
       GENSTARCAST(AUSE->USEENTITY);
       WTX_R(E_TXTLIT_F(_T("&")));
       }
       else {
       GENCAST(AUSE->USEENTITY);
       }
       WTX_R(E_TXTLIT_F(_T("(")));
       GENCAST(AUSE->USEOWNER);
       WTX_R(E_TXTLIT_F(_T("fetch((iRef*)")));
       if (SUBNODE != 0 & AUSE->USESUBS == 0) {
       MODE = GENEXP(SUBNODE);
       SUBNODE = (struct NODE*)0;
       }
       else {
       AREF = (struct DICTENTRY*)FINDDICTENTRY_F(AUSE->USEOWNER->ETYPENAME);
       if (FINDSPECUSE_F(AREF, 1) == 0) {
       SUSE = (struct DICTUSE*)FINDSPECUSE_F(AREF, 4);
       if (SUSE == 0) {
       EASERR(1018, AREF->LEXEME);
       }
       else {
       WTX_R(SUSE->USEOWNER->ETYPENAME);
       WTX_R(E_TXTLIT_F(_T("->")));
       }
       }
       WTX_R(AREF->LEXEME);
       }
       WTX_R(E_TXTLIT_F(_T("))->")));
       WTX_R(VARTOKEN->DICTREF->LEXEME);
       if (SUBNODE != 0) {
       MODE = GENEXP(SUBNODE);
       }
       if (ISPUT != 0) {
       WTX_R(E_TXTLIT_F(_T(")")));
       }
       rval = (int)AUSE->USEMODE;
goto retlbl;
retlbl:
       return rval;
}
int GENPENTREF(struct DICTUSE* AUSE, struct TOKEN* VARTOKEN, struct NODE* SUBNODE, int ISPUT) {
int MODE= 0;
int rval = 0;
       if (ISPUT != 0) {
       WTX_R(E_TXTLIT_F(_T("easg((char*)&")));
       }
       else {
       GENCAST(AUSE->USEENTITY);
       }
       if (SUBNODE != 0 & AUSE->USESUBS == 0) {
       MODE = GENEXP(SUBNODE);
       SUBNODE = (struct NODE*)0;
       }
       else {
       WTX_R(AUSE->USEOWNER->ETYPENAME);
       }
       WTX_R(E_TXTLIT_F(_T("->")));
       WTX_R(VARTOKEN->DICTREF->LEXEME);
       if (SUBNODE != 0) {
       MODE = GENEXP(SUBNODE);
       }
       rval = (int)4;
goto retlbl;
retlbl:
       return rval;
}
void GENSTARCAST(struct ENTITYTYPE* ETYPE) {
       WTX_R(E_TXTLIT_F(_T("(")));
       if (E_TXTNEQ_F(ETYPE->TARGETNAME, E_TXTLIT_F(_T("""")))) {
       WTX_R(ETYPE->TARGETNAME);
       }
       else {
       WTX_R(ETYPE->ETYPENAME);
       }
       WTX_R(E_TXTLIT_F(_T("*)")));
       goto retlbl;
retlbl:
       return;
}
void GENCAST(struct ENTITYTYPE* ETYPE) {
       WTX_R(E_TXTLIT_F(_T("(")));
       if (E_TXTNEQ_F(ETYPE->TARGETNAME, E_TXTLIT_F(_T("""")))) {
       WTX_R(ETYPE->TARGETNAME);
       }
       else {
       WTX_R(E_TXTLIT_F(_T("struct ")));
       WTX_R(ETYPE->ETYPENAME);
       WTX_R(E_TXTLIT_F(_T("*")));
       }
       WTX_R(E_TXTLIT_F(_T(")")));
       goto retlbl;
retlbl:
       return;
}
Etxt* QUOTE_F(Etxt* TXT) {
int L= 0;
Etxt* rval = 0;
E_TXTINC_R(TXT);
       E_TXTASG_R(&TXT, CONCAT_F(E_TXTLIT_F(_T(" ")), TXT));
       E_TXTASG_R(&TXT, CONCAT_F(TXT, E_TXTLIT_F(_T(" "))));
       QACHAR_F(TXT, 1, 34);
       L = LENGTH_F(TXT);
       QACHAR_F(TXT, L, 34);
       E_TXTASG_R(&rval, TXT);
goto retlbl;
retlbl:
E_TXTDEL_R(TXT);
       return rval;
}
void GENHEADER(struct SCHEMA* ASCHEMA) {
struct SCHEMA* ISCHEMA= 0;
Etxt* TXT= 0;
struct ENTITYTYPE* ETYPE= 0;
struct ENTITYTYPE* SYSENT= 0;
struct ATTRDEF* ATT= 0;
       WTX_R(E_TXTLIT_F(_T("#pragma once\n\#include \"easlib.h\"\n")));
       WTL_R();
       ISCHEMA = (struct SCHEMA*)EASEents->F_SCHEMAS;
next0001:
       if ( !  ( ISCHEMA != 0 ) ) {
       goto done0001;
       }
       if (ISCHEMA != ASCHEMA & ISCHEMA->NOGEN == 0) {
       E_TXTASG_R(&TXT, CONCAT_F(ISCHEMA->GENNAME, E_TXTLIT_F(_T(".h"))));
       WTX_R(E_TXTLIT_F(_T("#include ")));
       WTX_R(QUOTE_F(TXT));
       WTL_R();
       }
       ISCHEMA = (struct SCHEMA*)ISCHEMA->S_SCHEMAS;
       goto next0001;
done0001:
       WTL_R();
       ETYPE = (struct ENTITYTYPE*)ASCHEMA->F_ETYPES;
next0002:
       if ( !  ( ETYPE != 0 ) ) {
       goto done0002;
       }
       if (ETYPE->ISPROC == 0) {
       WTX_R(E_TXTLIT_F(_T("#define _")));
       WTX_R(ETYPE->ETYPENAME);
       WTL_R();
       }
       ETYPE = (struct ENTITYTYPE*)ETYPE->S_ETYPES;
       goto next0002;
done0002:
       WTL_R();
       ETYPE = (struct ENTITYTYPE*)ASCHEMA->F_ETYPES;
next0003:
       if ( !  ( ETYPE != 0 ) ) {
       goto done0003;
       }
       if (ETYPE->ISPROC == 0) {
       WTX_R(E_TXTLIT_F(_T("struct ")));
       WTX_R(ETYPE->ETYPENAME);
       WTX_R(E_TXTLIT_F(_T(" {")));
       WTL_R();
       if (ASCHEMA->NOHDR == 0) {
       WTX_R(E_TXTLIT_F(_T("struct eInstHdr hdr;")));
       WTL_R();
       }
       ATT = (struct ATTRDEF*)ETYPE->F_ATTRDEFS;
next0004:
       if ( !  ( ATT != 0 ) ) {
       goto done0004;
       }
       WTX_R(MAKEATTRTYPE_F(ATT));
       WTS_R(1);
       WTX_R(ATT->ATTRNAME);
       WTX_R(E_TXTLIT_F(_T(";")));
       WTL_R();
       ATT = (struct ATTRDEF*)ATT->S_ATTRDEFS;
       goto next0004;
done0004:
       WTX_R(E_TXTLIT_F(_T("};")));
       WTL_R();
       WTX_R(E_TXTLIT_F(_T("#define Z_")));
       WTX_R(ETYPE->ETYPENAME);
       WTX_R(E_TXTLIT_F(_T(" sizeof(")));
       WTX_R(ETYPE->ETYPENAME);
       WTX_R(E_TXTLIT_F(_T(")")));
       WTL_R();
       if (ETYPE->ISPERSISTENT != 0) {
       GENMAP(ETYPE);
       }
       }
       ETYPE = (struct ENTITYTYPE*)ETYPE->S_ETYPES;
       goto next0003;
done0003:
       ETYPE = (struct ENTITYTYPE*)ASCHEMA->F_ETYPES;
next0005:
       if ( !  ( ETYPE != 0 ) ) {
       goto done0005;
       }
       if (ETYPE->ISPROC != 0) {
       if (E_TXTNEQ_F(ETYPE->ETYPENAME, E_TXTLIT_F(_T("MAIN")))) {
       ATT = (struct ATTRDEF*)ETYPE->F_ATTRDEFS;
next0006:
       if ( !  ( ATT != 0 ) ) {
       goto done0006;
       }
       if (ATT->ISRETTYPE != 0) {
       goto done0006;
       }
       ATT = (struct ATTRDEF*)ATT->S_ATTRDEFS;
       goto next0006;
done0006:
       if (ATT != 0) {
       WTX_R(MAKEATTRTYPE_F(ATT));
       }
       else {
       WTX_R(E_TXTLIT_F(_T("void")));
       }
       WTS_R(1);
       WTX_R(ETYPE->ETYPENAME);
       GENARGLIST(ETYPE);
       WTX_R(E_TXTLIT_F(_T(";")));
       WTL_R();
       }
       }
       ETYPE = (struct ENTITYTYPE*)ETYPE->S_ETYPES;
       goto next0005;
done0005:
       ETYPE = (struct ENTITYTYPE*)ASCHEMA->THESYSTEM;
       if (ETYPE != 0) {
       WTL_R();
       WTX_R(E_TXTLIT_F(_T("struct ")));
       WTX_R(ETYPE->ETYPENAME);
       WTX_R(E_TXTLIT_F(_T("_sys {")));
       WTL_R();
       WTX_R(E_TXTLIT_F(_T("struct eInstHdr hdr;")));
       WTL_R();
       ATT = (struct ATTRDEF*)ETYPE->F_ATTRDEFS;
next0007:
       if ( !  ( ATT != 0 ) ) {
       goto done0007;
       }
       WTX_R(MAKEATTRTYPE_F(ATT));
       WTS_R(1);
       WTX_R(ATT->ATTRNAME);
       WTX_R(E_TXTLIT_F(_T(";")));
       WTL_R();
       ATT = (struct ATTRDEF*)ATT->S_ATTRDEFS;
       goto next0007;
done0007:
       WTX_R(E_TXTLIT_F(_T("};")));
       WTL_R();
       WTX_R(E_TXTLIT_F(_T("extern ")));
       WTX_R(ASCHEMA->GENNAME);
       WTX_R(E_TXTLIT_F(_T("_sys* ")));
       WTX_R(ASCHEMA->GENNAME);
       WTX_R(E_TXTLIT_F(_T(";")));
       WTL_R();
       }
       WTX_R(E_TXTLIT_F(_T("void ")));
       WTX_R(ASCHEMA->GENNAME);
       WTX_R(E_TXTLIT_F(_T("_init();")));
       WTL_R();
       goto retlbl;
retlbl:
E_TXTDEL_R(TXT);
       return;
}
void GENCOMP(struct NODE* ANODE) {
struct NODE* FINDER= 0;
struct DICTUSE* AUSE= 0;
int MODE1= 0;
int MODE2= 0;
int OPMATCH= 0;
       OPMATCH = ANODE->S_NODES->MATCHNUM;
       FINDER = (struct NODE*)ANODE->F_SUBNODES;
next0001:
       if ( !  ( FINDER->F_SUBNODES != 0 ) ) {
       goto done0001;
       }
       FINDER = (struct NODE*)FINDER->F_SUBNODES;
       goto next0001;
done0001:
       AUSE = (struct DICTUSE*)FINDPREFUSE_F(FINDER->START, 1);
       if (AUSE->USEMODE == 3) {
       if (OPMATCH == 1) {
       WTX_R(E_TXTLIT_F(_T("E_TXTEQL_F(")));
       }
       else {
       WTX_R(E_TXTLIT_F(_T("E_TXTNEQ_F(")));
       }
       MODE1 = GENEXP(ANODE);
       WTX_R(E_TXTLIT_F(_T(", ")));
       MODE2 = GENEXP(ANODE->S_NODES->S_NODES);
       WTX_R(E_TXTLIT_F(_T(")")));
       goto retlbl;
       }
       MODE1 = GENEXP(ANODE);
       ANODE = (struct NODE*)ANODE->S_NODES;
       WTX_R(EASEgen->LOGICOPS[OPMATCH]);
       ANODE = (struct NODE*)ANODE->S_NODES;
       MODE2 = GENEXP(ANODE);
       goto retlbl;
retlbl:
       return;
}
void GENLOGICL(struct NODE* ANODE) {
struct NODE* SUBNODE= 0;
       SUBNODE = (struct NODE*)ANODE->F_SUBNODES;
       if (SUBNODE->S_NODES != 0) {
       if (SUBNODE->S_NODES->F_SUBNODES->MATCHNUM == 2) {
       WTX_R(E_TXTLIT_F(_T(" ! ")));
       }
       }
       if (SUBNODE->MATCHNUM == 1) {
       WTX_R(E_TXTLIT_F(_T(" ( ")));
       GENLOGICL(SUBNODE->F_SUBNODES->S_NODES);
       WTX_R(E_TXTLIT_F(_T(" ) ")));
       }
       else {
       GENCOMP(SUBNODE->F_SUBNODES);
       }
       ANODE = (struct NODE*)ANODE->S_NODES;
       if (ANODE != 0) {
       SUBNODE = (struct NODE*)ANODE->F_SUBNODES;
       if (SUBNODE->MATCHNUM == 1) {
       WTX_R(E_TXTLIT_F(_T(" & ")));
       }
       else {
       WTX_R(E_TXTLIT_F(_T(" | ")));
       }
       ANODE = (struct NODE*)SUBNODE->S_NODES;
       GENLOGICL(ANODE);
       }
       goto retlbl;
retlbl:
       return;
}
void GENARRSUBS(struct NODE* ANODE) {
int EMODE= 0;
next0001:
       if ( !  ( ANODE != 0 ) ) {
       goto done0001;
       }
       if (ANODE->MATCHNUM != 1) {
       goto retlbl;
       }
       WTX_R(E_TXTLIT_F(_T("[")));
       EMODE = GENEXP(ANODE);
       WTX_R(E_TXTLIT_F(_T("]")));
       ANODE = (struct NODE*)ANODE->S_NODES;
       goto next0001;
done0001:
       goto retlbl;
retlbl:
       return;
}
int GENPOWER(struct NODE* ANODE) {
int MODE= 0;
struct NODE* EXPNODE= 0;
struct NODE* SUBNODE= 0;
int MATCH= 0;
int rval = 0;
       SUBNODE = (struct NODE*)ANODE->F_SUBNODES;
       EXPNODE = (struct NODE*)SUBNODE->S_NODES;
       SUBNODE->S_NODES = (struct NODE*)0;
       WTX_R(E_TXTLIT_F(_T(" pow(")));
       MODE = GENEXP(ANODE);
       WTX_R(E_TXTLIT_F(_T(", ")));
       ANODE = (struct NODE*)EXPNODE->F_SUBNODES->S_NODES;
       ANODE->F_SUBNODES->S_NODES = (struct NODE*)0;
       MODE = GENEXP(ANODE);
       WTX_R(E_TXTLIT_F(_T(")")));
       rval = (int)MODE;
goto retlbl;
retlbl:
       return rval;
}
int GENEXP(struct NODE* ANODE) {
int MODE= 0;
struct NODE* SUBNODE= 0;
int MATCH= 0;
int rval = 0;
       SUBNODE = (struct NODE*)ANODE->F_SUBNODES->S_NODES;
       if (SUBNODE != 0) {
       SUBNODE = (struct NODE*)SUBNODE->F_SUBNODES;
       if (SUBNODE->MATCHNUM == 1) {
       SUBNODE = (struct NODE*)SUBNODE->S_NODES->F_SUBNODES->S_NODES;
       MODE = GENPOWER(ANODE);
       if (SUBNODE != 0) {
       ANODE = (struct NODE*)SUBNODE->F_SUBNODES;
       WTX_R(ANODE->START->DICTREF->LEXEME);
       ANODE = (struct NODE*)ANODE->S_NODES;
       if (ANODE != 0) {
       MODE = GENEXP(ANODE);
       }
       }
       rval = (int)MODE;
goto retlbl;
       }
       }
       ANODE = (struct NODE*)ANODE->F_SUBNODES;
       SUBNODE = (struct NODE*)ANODE->F_SUBNODES;
       if (SUBNODE->S_NODES == ANODE->L_SUBNODES) {
       if (SUBNODE->MATCHNUM == 2) {
       WTX_R(SUBNODE->START->DICTREF->LEXEME);
       }
       SUBNODE = (struct NODE*)SUBNODE->S_NODES;
       }
       MATCH = SUBNODE->MATCHNUM;
       if (MATCH == 1) {
       WTX_R(SUBNODE->START->DICTREF->LEXEME);
       MODE = 1;
       }
       if (MATCH == 2) {
       WTX_R(SUBNODE->START->DICTREF->LEXEME);
       MODE = 2;
       }
       if (MATCH == 3) {
       WTX_R(E_TXTLIT_F(_T("E_TXTLIT_F(_T(")));
       WTX_R(QUOTE_F(SUBNODE->START->DICTREF->LEXEME));
       WTX_R(E_TXTLIT_F(_T("))")));
       MODE = 3;
       }
       if (MATCH == 4) {
       MODE = GENVAR(SUBNODE, 0);
       }
       if (MATCH == 5) {
       WTX_R(E_TXTLIT_F(_T("(")));
       MODE = GENEXP(SUBNODE->F_SUBNODES);
       WTX_R(E_TXTLIT_F(_T(")")));
       }
       if (MATCH == 6) {
       WTX_R(SUBNODE->F_SUBNODES->START->DICTREF->LEXEME);
       MODE = 0;
       }
       if (ANODE->S_NODES != 0) {
       ANODE = (struct NODE*)ANODE->S_NODES->F_SUBNODES;
       WTX_R(ANODE->START->DICTREF->LEXEME);
       ANODE = (struct NODE*)ANODE->S_NODES;
       if (ANODE != 0) {
       MODE = GENEXP(ANODE);
       }
       }
       rval = (int)MODE;
goto retlbl;
retlbl:
       return rval;
}
int GENVAR(struct NODE* ANODE, int ISPUT) {
int MODE= 0;
struct TOKEN* VARTOKEN= 0;
struct NODE* SUBNODE= 0;
struct DICTUSE* AUSE= 0;
struct DICTUSE* SUSE= 0;
struct DICTENTRY* DREF= 0;
struct DICTENTRY* AREF= 0;
int EMODE= 0;
struct ENTITYTYPE* ETYPE= 0;
struct SETMMBRREF* MREF= 0;
struct SETDEF* SDEF= 0;
struct ATTRDEF* ATT= 0;
int SAVP= 0;
int rval = 0;
       VARTOKEN = (struct TOKEN*)ANODE->START;
       if (ANODE->F_SUBNODES != 0) {
       if (ANODE->F_SUBNODES->S_NODES != 0) {
       SUBNODE = (struct NODE*)ANODE->F_SUBNODES->S_NODES->F_SUBNODES;
       }
       }
       DREF = (struct DICTENTRY*)VARTOKEN->DICTREF;
       AUSE = (struct DICTUSE*)FINDSPECUSE_F(DREF, 1);
       if (AUSE != 0) {
       if (AUSE->USEENTITY->ISPERSISTENT != 0) {
       if (ISPUT != 0) {
       WTX_R(E_TXTLIT_F(_T("easg((char*)&")));
       }
       }
       WTX_R(DREF->LEXEME);
       if (SUBNODE != 0) {
       GENARRSUBS(SUBNODE);
       }
       rval = (int)AUSE->USEMODE;
goto retlbl;
       }
       AUSE = (struct DICTUSE*)FINDSPECUSE_F(DREF, 4);
       if (AUSE != 0) {
       if (AUSE->ISCOMMONATT != 0 & SUBNODE == 0) {
       EASERR(1015, VARTOKEN->LEXEME);
       rval = (int)AUSE->USEMODE;
goto retlbl;
       }
       if (AUSE->USEOWNER->ISPERSISTENT != 0) {
       rval = (int)GENPATTR(AUSE, VARTOKEN, SUBNODE, ISPUT);
goto retlbl;
       }
       else {
       if (AUSE->USEENTITY->ISPERSISTENT != 0) {
       rval = (int)GENPENTREF(AUSE, VARTOKEN, SUBNODE, ISPUT);
goto retlbl;
       }
       }
       AREF = (struct DICTENTRY*)FINDDICTENTRY_F(AUSE->USEOWNER->ETYPENAME);
       if (SUBNODE != 0 & AUSE->USESUBS == 0) {
       EMODE = GENEXP(SUBNODE);
       SUBNODE = (struct NODE*)0;
       }
       else {
       if (FINDSPECUSE_F(AREF, 1) == 0) {
       SUSE = (struct DICTUSE*)FINDSPECUSE_F(AREF, 2);
       if (SUSE != 0) {
       SUSE = (struct DICTUSE*)FINDSPECUSE_F(AREF, 4);
       WTX_R(SUSE->USEOWNER->ETYPENAME);
       WTX_R(E_TXTLIT_F(_T("->")));
       }
       }
       WTX_R(AREF->LEXEME);
       }
       WTX_R(E_TXTLIT_F(_T("->")));
       WTX_R(DREF->LEXEME);
       if (SUBNODE != 0) {
       GENARRSUBS(SUBNODE);
       }
       rval = (int)AUSE->USEMODE;
goto retlbl;
       }
       AUSE = (struct DICTUSE*)FINDSPECUSE_F(DREF, 5);
       if (AUSE != 0) {
       if (AUSE->ISCOMMONATT != 0 & SUBNODE == 0) {
       EASERR(1015, VARTOKEN->LEXEME);
       rval = (int)AUSE->USEMODE;
goto retlbl;
       }
       ATT = (struct ATTRDEF*)AUSE->USESETREFATT;
       SDEF = (struct SETDEF*)ATT->SETATTRSETDEF;
       MREF = (struct SETMMBRREF*)SDEF->F_SETMMBRREFS;
       AREF = (struct DICTENTRY*)FINDDICTENTRY_F(AUSE->USEOWNER->ETYPENAME);
       SUSE = (struct DICTUSE*)FINDSPECUSE_F(AREF, 2);
       if (SUSE != 0) {
       if (SUSE->USEENTITY->ISPERSISTENT != 0) {
       SAVP = 1;
       }
       }
       if (AUSE->USEMODE == 4 & SAVP == 0) {
       WTX_R(E_TXTLIT_F(_T("(")));
       GENCAST(MREF->MMBRENT);
       }
       WTX_R(SUBSTR_F(DREF->LEXEME, 1, 2));
       if (ATT->ATTRTYPE->ISPERSISTENT != 0) {
       WTX_R(E_TXTLIT_F(_T("P")));
       }
       else {
       if (SAVP != 0) {
       WTX_R(E_TXTLIT_F(_T("X")));
       }
       }
       WTX_R(E_TXTLIT_F(_T("EASSET_F(")));
       if (SAVP != 0) {
       WTX_R(E_TXTLIT_F(_T("(")));
       GENCAST(AUSE->USEOWNER);
       WTX_R(E_TXTLIT_F(_T("fetch((iRef*)")));
       }
       if (SUBNODE != 0 & AUSE->USESUBS == 0) {
       MODE = GENEXP(SUBNODE);
       SUBNODE = (struct NODE*)0;
       }
       else {
       if (FINDSPECUSE_F(AREF, 1) == 0) {
       if (SUSE == 0 & AUSE->USEOWNER->ETYPEID != 0) {
       EASERR(1015, VARTOKEN->LEXEME);
       }
       SUSE = (struct DICTUSE*)FINDSPECUSE_F(AREF, 4);
       if (SUSE == 0 & AUSE->USEOWNER->ETYPEID != 0) {
       EASERR(1018, AREF->LEXEME);
       }
       else {
       if (SUSE != 0) {
       WTX_R(SUSE->USEOWNER->ETYPENAME);
       WTX_R(E_TXTLIT_F(_T("->")));
       }
       }
       }
       WTX_R(AREF->LEXEME);
       }
       if (SAVP != 0) {
       WTX_R(E_TXTLIT_F(_T("))")));
       }
       WTX_R(E_TXTLIT_F(_T("->")));
       WTX_R(AUSE->USESETREFATT->ATTRNAME);
       if (SUBNODE != 0) {
       GENARRSUBS(SUBNODE);
       }
       WTX_R(E_TXTLIT_F(_T(")")));
       if (AUSE->USEMODE == 4 & SAVP == 0) {
       WTX_R(E_TXTLIT_F(_T(")")));
       }
       rval = (int)AUSE->USEMODE;
goto retlbl;
       }
       AUSE = (struct DICTUSE*)FINDSPECUSE_F(DREF, 6);
       if (AUSE != 0) {
       if (AUSE->ISCOMMONATT != 0 & SUBNODE == 0) {
       EASERR(1015, VARTOKEN->LEXEME);
       rval = (int)AUSE->USEMODE;
goto retlbl;
       }
       SDEF = (struct SETDEF*)AUSE->USESETDEF;
       MREF = (struct SETMMBRREF*)SDEF->F_SETMMBRREFS;
       AREF = (struct DICTENTRY*)FINDDICTENTRY_F(MREF->MMBRENT->ETYPENAME);
       SUSE = (struct DICTUSE*)FINDSPECUSE_F(AREF, 2);
       if (SDEF->ISPERSISTENT != 0) {
       SAVP = 1;
       }
       if (AUSE->USEMODE == 4 & SAVP == 0) {
       WTX_R(E_TXTLIT_F(_T("(")));
       GENCAST(MREF->MMBRENT);
       }
       WTX_R(SUBSTR_F(DREF->LEXEME, 1, 2));
       if (SAVP != 0) {
       WTX_R(E_TXTLIT_F(_T("P")));
       }
       else {
       if (SUSE->USEENTITY->ISPERSISTENT != 0) {
       WTX_R(E_TXTLIT_F(_T("X")));
       }
       }
       WTX_R(E_TXTLIT_F(_T("EASSET_F(")));
       if (SUSE->USEENTITY->ISPERSISTENT != 0) {
       WTX_R(E_TXTLIT_F(_T("(iRef*)")));
       }
       if (SUBNODE != 0 & AUSE->USESUBS == 0) {
       MODE = GENEXP(SUBNODE);
       SUBNODE = (struct NODE*)0;
       }
       else {
       if (FINDSPECUSE_F(AREF, 1) == 0) {
       if (SUSE == 0) {
       EASERR(1015, VARTOKEN->LEXEME);
       }
       SUSE = (struct DICTUSE*)FINDSPECUSE_F(AREF, 4);
       if (SUSE == 0) {
       EASERR(1018, AREF->LEXEME);
       }
       else {
       WTX_R(SUSE->USEOWNER->ETYPENAME);
       WTX_R(E_TXTLIT_F(_T("->")));
       }
       }
       WTX_R(AREF->LEXEME);
       }
       if (SUBNODE != 0) {
       GENARRSUBS(SUBNODE);
       }
       WTX_R(E_TXTLIT_F(_T(", E_TXTLIT_F(_T(")));
       WTX_R(QUOTE_F(SDEF->SETNAME));
       WTX_R(E_TXTLIT_F(_T(")))")));
       if (AUSE->USEMODE == 4 & SAVP == 0) {
       WTX_R(E_TXTLIT_F(_T(")")));
       }
       rval = (int)AUSE->USEMODE;
goto retlbl;
       }
       AUSE = (struct DICTUSE*)FINDSPECUSE_F(DREF, 3);
       if (AUSE != 0) {
       GENFUNC(ANODE->F_SUBNODES);
       MODE = AUSE->USEMODE;
       }
       else {
       AUSE = (struct DICTUSE*)FINDPREFUSE_F(VARTOKEN, 1);
       WTX_R(VARTOKEN->LEXEME);
       }
       rval = (int)MODE;
goto retlbl;
retlbl:
       return rval;
}
Etxt* ARRTYPE_F(struct ENTITYTYPE* ETYPE, int STARS) {
Etxt* TXT= 0;
Etxt* rval = 0;
       if (E_TXTNEQ_F(ETYPE->TARGETNAME, 0)) {
       E_TXTASG_R(&TXT, ETYPE->TARGETNAME);
       }
       else {
       E_TXTASG_R(&TXT, CONCAT_F(ETYPE->ETYPENAME, E_TXTLIT_F(_T("*"))));
       }
       E_TXTASG_R(&TXT, CONCAT_F(E_TXTLIT_F(_T("(")), TXT));
next0001:
       if ( !  ( STARS > 0 ) ) {
       goto done0001;
       }
       E_TXTASG_R(&TXT, CONCAT_F(TXT, E_TXTLIT_F(_T("*"))));
       STARS = STARS-1;
       goto next0001;
done0001:
       E_TXTASG_R(&TXT, CONCAT_F(TXT, E_TXTLIT_F(_T(")"))));
       E_TXTASG_R(&rval, TXT);
goto retlbl;
retlbl:
E_TXTDEL_R(TXT);
       return rval;
}
void GENRESERVE(struct NODE* ANODE) {
int ARRMODE= 0;
struct DICTUSE* AUSE= 0;
struct NODE* SUBNODE= 0;
int I= 0;
int MODE= 0;
struct ENTITYTYPE* ETYPE= 0;
       AUSE = (struct DICTUSE*)FINDPREFUSE_F(ANODE->START, 1);
       I = AUSE->USESUBS;
       if (I == 0) {
       EASERR(1003, ANODE->START->LEXEME);
       goto retlbl;
       }
       ETYPE = (struct ENTITYTYPE*)AUSE->USEENTITY;
       ARRMODE = GENVAR(ANODE, 1);
       WTX_R(E_TXTLIT_F(_T(" = ")));
       I = AUSE->USESUBS;
       SUBNODE = (struct NODE*)ANODE->F_SUBNODES->S_NODES;
       if (SUBNODE != 0) {
       if (SUBNODE->F_SUBNODES->MATCHNUM == 1) {
       I = I-1;
       }
       }
       WTX_R(ARRTYPE_F(ETYPE, I));
       WTX_R(E_TXTLIT_F(_T("calloc(")));
       MODE = GENEXP(ANODE->S_NODES);
       I = I-1;
       WTX_R(E_TXTLIT_F(_T(" + 1, sizeof")));
       WTX_R(ARRTYPE_F(ETYPE, I));
       WTX_R(E_TXTLIT_F(_T(");")));
       WTL_R();
       WTB_R(8);
       MODE = GENVAR(ANODE, 1);
       WTX_R(E_TXTLIT_F(_T("[0] = ")));
       WTX_R(ARRTYPE_F(ETYPE, I));
       WTX_R(E_TXTLIT_F(_T("(")));
       MODE = GENEXP(ANODE->S_NODES);
       WTX_R(E_TXTLIT_F(_T(");")));
       WTL_R();
       goto retlbl;
retlbl:
       return;
}
void GENCALL(struct NODE* ANODE) {
struct NODE* SUBNODE= 0;
int EMODE= 0;
struct DICTUSE* AUSE= 0;
int FIRST= 0;
int YLD= 0;
       WTX_R(ANODE->START->DICTREF->LEXEME);
       WTX_R(E_TXTLIT_F(_T("(")));
       FIRST = 1;
       ANODE = (struct NODE*)ANODE->S_NODES;
next0001:
       if ( !  ( ANODE != 0 ) ) {
       goto done0001;
       }
       SUBNODE = (struct NODE*)ANODE->F_SUBNODES;
       if (SUBNODE->SCRIPTCODE != 0) {
       YLD = 1;
       }
next0002:
       if ( !  ( SUBNODE != 0 ) ) {
       goto done0002;
       }
       if (FIRST == 0) {
       WTX_R(E_TXTLIT_F(_T(", ")));
       }
       else {
       FIRST = 0;
       }
       if (YLD == 0) {
       EMODE = GENEXP(SUBNODE->F_SUBNODES);
       }
       else {
       EMODE = GENVAR(SUBNODE->F_SUBNODES, 1);
       }
       SUBNODE = (struct NODE*)SUBNODE->S_NODES;
       goto next0002;
done0002:
       ANODE = (struct NODE*)ANODE->S_NODES;
       goto next0001;
done0001:
       WTX_R(E_TXTLIT_F(_T(")")));
       goto retlbl;
retlbl:
       return;
}
void GENFUNC(struct NODE* ANODE) {
int EMODE= 0;
struct DICTUSE* AUSE= 0;
int FIRST= 0;
       WTX_R(ANODE->START->DICTREF->LEXEME);
       WTX_R(E_TXTLIT_F(_T("(")));
       if (ANODE->S_NODES != 0) {
       FIRST = 1;
       ANODE = (struct NODE*)ANODE->S_NODES->F_SUBNODES;
next0001:
       if ( !  ( ANODE != 0 ) ) {
       goto done0001;
       }
       if (FIRST == 0) {
       WTX_R(E_TXTLIT_F(_T(", ")));
       }
       EMODE = GENEXP(ANODE);
       FIRST = 0;
       ANODE = (struct NODE*)ANODE->S_NODES;
       goto next0001;
done0001:
;      }
       WTX_R(E_TXTLIT_F(_T(")")));
       goto retlbl;
retlbl:
       return;
}
void GENSTMT(struct EASEPROC* APROC, struct STMT* ASTMT) {
struct ENTITYTYPE* ETYPE= 0;
Etxt* RNAME= 0;
struct NODE* ANODE= 0;
struct NODE* VARNODE= 0;
struct NODE* EXPNODE= 0;
struct NODE* SUBNODE= 0;
struct DICTUSE* AUSE= 0;
struct DICTUSE* AUSE2= 0;
int MODE= 0;
int EMODE= 0;
int COUNT= 0;
       EASEmain->CURRLINE = ASTMT->STMTLINE;
       E_TXTASG_R(&RNAME, ASTMT->STMTRULE->RULENAME);
       ANODE = (struct NODE*)ASTMT->F_PARSENODES;
       WTB_R(8);
       if (E_TXTEQL_F(RNAME, E_TXTLIT_F(_T("CREATE")))) {
       AUSE = (struct DICTUSE*)FINDSPECUSE_F(ANODE->START->DICTREF, 2);
       if (AUSE == 0) {
       EASERR(1011, ANODE->START->LEXEME);
       goto retlbl;
       }
       AUSE->USEENTITY->ISUSEDTYPE = 1;
       if (ANODE->S_NODES != 0) {
       ANODE = (struct NODE*)ANODE->S_NODES;
       }
       MODE = GENVAR(ANODE, 1);
       if (AUSE->USEENTITY->ISPERSISTENT != 0) {
       WTX_R(E_TXTLIT_F(_T(", c_")));
       WTX_R(AUSE->USEENTITY->ETYPENAME);
       WTX_R(E_TXTLIT_F(_T("());")));
       EASEgen->USEPERSIST = 1;
       }
       else {
       WTX_R(E_TXTLIT_F(_T("= c_")));
       WTX_R(AUSE->USEENTITY->ETYPENAME);
       WTX_R(E_TXTLIT_F(_T("();")));
       }
       WTL_R();
       goto retlbl;
       }
       if (E_TXTEQL_F(RNAME, E_TXTLIT_F(_T("DESTROY")))) {
       AUSE = (struct DICTUSE*)FINDSPECUSE_F(ANODE->START->DICTREF, 2);
       if (AUSE == 0) {
       EASERR(1011, ANODE->START->LEXEME);
       goto retlbl;
       }
       if (ANODE->S_NODES != 0) {
       ANODE = (struct NODE*)ANODE->S_NODES;
       }
       WTX_R(CONCAT_F(E_TXTLIT_F(_T("d_")), AUSE->USEENTITY->ETYPENAME));
       WTX_R(E_TXTLIT_F(_T("(")));
       MODE = GENVAR(ANODE, 0);
       WTX_R(E_TXTLIT_F(_T(");")));
       WTL_R();
       goto retlbl;
       }
       if (E_TXTEQL_F(RNAME, E_TXTLIT_F(_T("ASSIGN")))) {
       VARNODE = (struct NODE*)ANODE;
       EXPNODE = (struct NODE*)VARNODE->S_NODES;
       AUSE = (struct DICTUSE*)FINDPREFUSE_F(VARNODE->START, 1);
       if (AUSE->USEMODE == 3) {
       WTX_R(E_TXTLIT_F(_T("E_TXTASG_R(&")));
       MODE = GENVAR(VARNODE, 0);
       WTX_R(E_TXTLIT_F(_T(", ")));
       MODE = GENEXP(EXPNODE);
       WTX_R(E_TXTLIT_F(_T(");")));
       WTL_R();
       goto retlbl;
       }
       if (AUSE->USETYPE == 3) {
       ANODE = (struct NODE*)VARNODE->F_SUBNODES;
       WTX_R(E_TXTLIT_F(_T("Q")));
       WTX_R(ANODE->START->DICTREF->LEXEME);
       WTX_R(E_TXTLIT_F(_T("(")));
       ANODE = (struct NODE*)ANODE->S_NODES->F_SUBNODES;
next0001:
       if ( !  ( ANODE != 0 ) ) {
       goto done0001;
       }
       MODE = GENEXP(ANODE);
       WTX_R(E_TXTLIT_F(_T(", ")));
       ANODE = (struct NODE*)ANODE->S_NODES;
       goto next0001;
done0001:
       MODE = GENEXP(EXPNODE);
       WTX_R(E_TXTLIT_F(_T(");")));
       WTL_R();
       goto retlbl;
       }
       if (AUSE->USETYPE == 5 | AUSE->USETYPE == 6) {
       EASERR(1017, ANODE->START->LEXEME);
       goto retlbl;
       }
       if (AUSE->USEENTITY->ISPERSISTENT != 0) {
       MODE = GENVAR(VARNODE, 1);
       WTX_R(E_TXTLIT_F(_T(", (iRef*)")));
       MODE = GENEXP(EXPNODE);
       WTX_R(E_TXTLIT_F(_T(");")));
       WTL_R();
       goto retlbl;
       }
       MODE = GENVAR(VARNODE, 1);
       WTX_R(E_TXTLIT_F(_T(" = ")));
       if (AUSE->USESUBS != 0) {
       COUNT = 0;
       ANODE = (struct NODE*)VARNODE->F_SUBNODES->S_NODES;
       if (ANODE != 0) {
       ANODE = (struct NODE*)ANODE->F_SUBNODES;
next0002:
       if ( !  ( ANODE != 0 ) ) {
       goto done0002;
       }
       if (ANODE->MATCHNUM == 1) {
       COUNT = COUNT+1;
       }
       ANODE = (struct NODE*)ANODE->S_NODES;
       goto next0002;
done0002:
       COUNT = AUSE->USESUBS-COUNT;
       }
       }
       if (MODE == 4 | AUSE->USESUBS != 0) {
       WTX_R(E_TXTLIT_F(_T("(")));
       WTX_R(MAKETYPE_F(AUSE->USEENTITY, COUNT));
       WTX_R(E_TXTLIT_F(_T(")")));
       }
       EMODE = GENEXP(EXPNODE);
       WTX_R(E_TXTLIT_F(_T(";")));
       WTL_R();
       goto retlbl;
       }
       if (E_TXTEQL_F(RNAME, E_TXTLIT_F(_T("CALL")))) {
       AUSE = (struct DICTUSE*)FINDSPECUSE_F(ANODE->START->DICTREF, 3);
       if (AUSE == 0) {
       EASERR(1012, ANODE->START->LEXEME);
       goto retlbl;
       }
       GENCALL(ASTMT->F_PARSENODES);
       WTX_R(E_TXTLIT_F(_T(";")));
       WTL_R();
       goto retlbl;
       }
       if (E_TXTEQL_F(RNAME, E_TXTLIT_F(_T("GOTO")))) {
       WTX_R(E_TXTLIT_F(_T("goto ")));
       WTX_R(ANODE->START->DICTREF->LEXEME);
       WTX_R(E_TXTLIT_F(_T(";")));
       WTL_R();
       goto retlbl;
       }
       if (E_TXTEQL_F(RNAME, E_TXTLIT_F(_T("LBL")))) {
       WTB_R(1);
       WTX_R(ANODE->START->S_TOKENLIST->DICTREF->LEXEME);
       WTX_R(E_TXTLIT_F(_T(":")));
       WTL_R();
       ASTMT = (struct STMT*)ASTMT->S_STMTS;
       if (ASTMT != 0) {
       if (E_TXTEQL_F(ASTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("ENDIF"))) | E_TXTEQL_F(ASTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("ELSE")))) {
       WTX_R(E_TXTLIT_F(_T(";")));
       }
       }
       goto retlbl;
       }
       if (E_TXTEQL_F(RNAME, E_TXTLIT_F(_T("IF")))) {
       if (ANODE->MATCHNUM == 2) {
       goto retlbl;
       }
       WTX_R(E_TXTLIT_F(_T("if (")));
       GENLOGICL(ANODE);
       WTX_R(E_TXTLIT_F(_T(") {")));
       WTL_R();
       goto retlbl;
       }
       if (E_TXTEQL_F(RNAME, E_TXTLIT_F(_T("ELSE")))) {
       WTX_R(E_TXTLIT_F(_T("}")));
       WTL_R();
       WTB_R(8);
       WTX_R(E_TXTLIT_F(_T("else {")));
       WTL_R();
       goto retlbl;
       }
       if (E_TXTEQL_F(RNAME, E_TXTLIT_F(_T("ENDIF")))) {
       WTX_R(E_TXTLIT_F(_T("}")));
       WTL_R();
       goto retlbl;
       }
       if (E_TXTEQL_F(RNAME, E_TXTLIT_F(_T("RET")))) {
       EASEgen->GORETLBL = 1;
       ANODE = (struct NODE*)ANODE->S_NODES;
       if (ANODE != 0) {
       if (APROC->RETURNATT == 0) {
       EASERR(-1013, 0);
       }
       ANODE = (struct NODE*)ANODE->F_SUBNODES;
       if (E_TXTEQL_F(APROC->RETURNATT->ATTRTYPE->ETYPENAME, E_TXTLIT_F(_T("Text")))) {
       WTX_R(E_TXTLIT_F(_T("E_TXTASG_R(&rval, ")));
       MODE = GENEXP(ANODE);
       WTX_R(E_TXTLIT_F(_T(");")));
       WTL_R();
       }
       else {
       WTX_R(E_TXTLIT_F(_T("rval = (")));
       WTX_R(MAKEATTRTYPE_F(APROC->RETURNATT));
       WTX_R(E_TXTLIT_F(_T(")")));
       MODE = GENEXP(ANODE);
       WTX_R(E_TXTLIT_F(_T(";")));
       WTL_R();
       }
       }
       else {
       if (APROC->RETURNATT != 0) {
       EASERR(-1014, 0);
       }
       }
       WTX_R(E_TXTLIT_F(_T("goto retlbl;")));
       WTL_R();
       goto retlbl;
       }
       if (E_TXTEQL_F(RNAME, E_TXTLIT_F(_T("RESERVE")))) {
       if (ANODE->S_NODES->S_NODES != 0) {
       goto retlbl;
       }
       GENRESERVE(ANODE);
       }
       goto retlbl;
retlbl:
E_TXTDEL_R(RNAME);
       return;
}
void GENSIZES(struct SCHEMA* ASCHEMA) {
Etxt* TXT= 0;
struct ENTITYTYPE* ETYPE= 0;
       ETYPE = (struct ENTITYTYPE*)ASCHEMA->F_ETYPES;
next0001:
       if ( !  ( ETYPE != 0 ) ) {
       goto done0001;
       }
       if (ETYPE->ISPROC == 0) {
       E_TXTASG_R(&TXT, CONCAT_F(E_TXTLIT_F(_T("int Z_")), ETYPE->ETYPENAME));
       WTX_R(TXT);
       WTX_R(E_TXTLIT_F(_T(" = sizeof(")));
       WTX_R(ETYPE->ETYPENAME);
       WTX_R(E_TXTLIT_F(_T(");")));
       WTL_R();
       }
       if (ETYPE->ISPERSISTENT != 0) {
       GENMAP(ETYPE);
       }
       ETYPE = (struct ENTITYTYPE*)ETYPE->S_ETYPES;
       goto next0001;
done0001:
       WTL_R();
       goto retlbl;
retlbl:
E_TXTDEL_R(TXT);
       return;
}
void GENMAP(struct ENTITYTYPE* ETYPE) {
int N= 0;
int I= 0;
struct ATTRDEF* ATTR= 0;
       ATTR = (struct ATTRDEF*)ETYPE->F_ATTRDEFS;
next0001:
       if ( !  ( ATTR != 0 ) ) {
       goto done0001;
       }
       N = N+1;
       ATTR = (struct ATTRDEF*)ATTR->S_ATTRDEFS;
       goto next0001;
done0001:
       ATTR = (struct ATTRDEF*)ETYPE->F_ATTRDEFS;
       if (ETYPE->SCHEMAREF->NOHDR == 0) {
       N = N+4;
       }
       else {
       I = 1;
       goto test0002;
next0002:
       I = I+1;
test0002:
       if (I > 4) {
       goto done0002;
       }
       ATTR = (struct ATTRDEF*)ATTR->S_ATTRDEFS;
       goto next0002;
done0002:
;      }
       WTX_R(E_TXTLIT_F(_T("const int Y_")));
       WTX_R(ETYPE->ETYPENAME);
       WTX_R(E_TXTLIT_F(_T("[")));
       WTI_R(N+2, 3);
       WTX_R(E_TXTLIT_F(_T("] = { sizeof(")));
       WTX_R(ETYPE->ETYPENAME);
       WTX_R(E_TXTLIT_F(_T("), ")));
       WTI_R(N, 3);
       WTX_R(E_TXTLIT_F(_T(", 1, 1, 4, 5")));
next0003:
       if ( !  ( ATTR != 0 ) ) {
       goto done0003;
       }
       ETYPE = (struct ENTITYTYPE*)ATTR->ATTRTYPE;
       N = 4;
       I = 1;
       goto test0004;
next0004:
       I = I+1;
test0004:
       if (I > 3) {
       goto done0004;
       }
       if (ETYPE == EASEents->E_BUILTINS[I]) {
       N = I;
       goto done0004;
       }
       goto next0004;
done0004:
       if (N == 4) {
       if (ETYPE->ISPERSISTENT != 0) {
       N = 5;
       }
       }
       WTX_R(E_TXTLIT_F(_T(", ")));
       WTI_R(N, 2);
       ATTR = (struct ATTRDEF*)ATTR->S_ATTRDEFS;
       goto next0003;
done0003:
       WTX_R(E_TXTLIT_F(_T(" };")));
       WTL_R();
       goto retlbl;
retlbl:
       return;
}
void GENPROCINCL(struct SCHEMA* ASCHEMA) {
Etxt* SYSNAME= 0;
Etxt* STYPENAME= 0;
Etxt* SREF= 0;
int ID= 0;
Etxt* TXT= 0;
       WTX_R(E_TXTLIT_F(_T("#include \"stdafx.h\"")));
       WTL_R();
       WTX_R(E_TXTLIT_F(_T("#include \"malloc.h\"")));
       WTL_R();
       if (EASEgen->USEPERSIST != 0) {
       WTX_R(E_TXTLIT_F(_T("	#define EASpersist")));
       WTL_R();
       }
       WTX_R(E_TXTLIT_F(_T("#include \"libopts.h\"")));
       WTL_R();
       WTX_R(E_TXTLIT_F(_T("#include \"math.h\"")));
       WTL_R();
       E_TXTASG_R(&TXT, CONCAT_F(ASCHEMA->GENNAME, E_TXTLIT_F(_T(".h"))));
       WTX_R(E_TXTLIT_F(_T("#include ")));
       WTX_R(QUOTE_F(TXT));
       WTL_R();
       WTL_R();
       GENADDTYPES(ASCHEMA);
       E_TXTASG_R(&SYSNAME, ASCHEMA->GENNAME);
       if (ASCHEMA->THESYSTEM != 0) {
       E_TXTASG_R(&STYPENAME, CONCAT_F(SYSNAME, E_TXTLIT_F(_T("_sys"))));
       E_TXTASG_R(&SREF, CONCAT_F(STYPENAME, E_TXTLIT_F(_T("*"))));
       WTX_R(SREF);
       WTS_R(1);
       WTX_R(SYSNAME);
       WTX_R(E_TXTLIT_F(_T(";")));
       WTL_R();
       }
       WTL_R();
       WTX_R(E_TXTLIT_F(_T("void ")));
       WTX_R(SYSNAME);
       WTX_R(E_TXTLIT_F(_T("_init() {")));
       WTL_R();
       if (ASCHEMA->THESYSTEM != 0) {
       ID = ASCHEMA->SCHEMAID;
       WTX_R(SYSNAME);
       WTX_R(E_TXTLIT_F(_T(" = (")));
       WTX_R(SREF);
       WTX_R(E_TXTLIT_F(_T(")E_CREATE_F( 0,")));
       WTI_R(ID, 4);
       WTX_R(E_TXTLIT_F(_T(", sizeof(")));
       WTX_R(STYPENAME);
       WTX_R(E_TXTLIT_F(_T("));")));
       WTL_R();
       WTX_R(CONCAT_F(SYSNAME, E_TXTLIT_F(_T("_sets();"))));
       WTL_R();
       }
       WTX_R(SYSNAME);
       WTX_R(E_TXTLIT_F(_T("_addTypes();")));
       WTL_R();
       WTX_R(E_TXTLIT_F(_T("}")));
       WTL_R();
       goto retlbl;
retlbl:
E_TXTDEL_R(SYSNAME);
E_TXTDEL_R(STYPENAME);
E_TXTDEL_R(SREF);
E_TXTDEL_R(TXT);
       return;
}
void GENINIT() {
struct ENTITYTYPE* SYSETYPE= 0;
Etxt* SYSNAME= 0;
Etxt* STYPENAME= 0;
Etxt* SREF= 0;
int ID= 0;
struct ATTRDEF* ATT= 0;
       WTL_R();
       WTX_R(E_TXTLIT_F(_T("void easinit() {")));
       WTL_R();
       SYSETYPE = (struct ENTITYTYPE*)EASEents->F_SYSTEMS;
next0001:
       if ( !  ( SYSETYPE != 0 ) ) {
       goto done0001;
       }
       E_TXTASG_R(&SYSNAME, SYSETYPE->SCHEMAREF->GENNAME);
       WTX_R(SYSNAME);
       WTX_R(E_TXTLIT_F(_T("_init();")));
       WTL_R();
       SYSETYPE = (struct ENTITYTYPE*)SYSETYPE->S_ETYPES;
       goto next0001;
done0001:
       WTX_R(E_TXTLIT_F(_T("#ifdef EASsets")));
       WTL_R();
       WTX_R(E_TXTLIT_F(_T("easeSets_init();")));
       WTL_R();
       WTX_R(E_TXTLIT_F(_T("#endif")));
       WTL_R();
       WTX_R(E_TXTLIT_F(_T("}")));
       WTL_R();
       goto retlbl;
retlbl:
E_TXTDEL_R(SYSNAME);
E_TXTDEL_R(STYPENAME);
E_TXTDEL_R(SREF);
       return;
}
void GENADDTYPES(struct SCHEMA* ASCHEMA) {
struct ENTITYTYPE* ETYPE= 0;
       WTX_R(E_TXTLIT_F(_T("void ")));
       WTX_R(ASCHEMA->GENNAME);
       WTX_R(E_TXTLIT_F(_T("_addTypes() {")));
       WTL_R();
       ETYPE = (struct ENTITYTYPE*)ASCHEMA->F_ETYPES;
next0001:
       if ( !  ( ETYPE != 0 ) ) {
       goto done0001;
       }
       if (ETYPE->ISPROC == 0) {
       WTX_R(E_TXTLIT_F(_T("#ifdef _")));
       WTX_R(ETYPE->ETYPENAME);
       WTL_R();
       WTX_R(E_TXTLIT_F(_T("addEType(E_TXTLIT_F(_T(")));
       WTX_R(QUOTE_F(ETYPE->ETYPENAME));
       WTX_R(E_TXTLIT_F(_T(")), ")));
       WTI_R(ASCHEMA->SCHEMAID, 4);
       WTX_R(E_TXTLIT_F(_T(", ")));
       WTI_R(ETYPE->ETYPEID, 4);
       WTX_R(E_TXTLIT_F(_T(", ")));
       if (ETYPE->ISPERSISTENT != 0) {
       WTX_R(CONCAT_F(E_TXTLIT_F(_T("Y_")), ETYPE->ETYPENAME));
       }
       else {
       WTX_R(E_TXTLIT_F(_T("0")));
       }
       WTX_R(E_TXTLIT_F(_T(");")));
       WTL_R();
       WTX_R(E_TXTLIT_F(_T("#endif")));
       WTL_R();
       }
       ETYPE = (struct ENTITYTYPE*)ETYPE->S_ETYPES;
       goto next0001;
done0001:
       WTX_R(E_TXTLIT_F(_T("}")));
       WTL_R();
       goto retlbl;
retlbl:
       return;
}
void GENPROC(struct EASEPROC* APROC) {
struct DICTUSE* AUSE= 0;
struct ENTITYTYPE* ETYPE= 0;
struct STMT* ASTMT= 0;
struct DICTENTRY* AREF= 0;
struct ATTRDEF* ATT= 0;
int FIRST= 0;
       EASEgen->GORETLBL = 0;
       AUSE = (struct DICTUSE*)FINDSPECUSE_F(APROC->PDICTREF, 3);
       if (APROC->RETURNATT == 0) {
       WTX_R(E_TXTLIT_F(_T("void ")));
       }
       else {
       WTX_R(MAKEATTRTYPE_F(APROC->RETURNATT));
       WTS_R(1);
       }
       ETYPE = (struct ENTITYTYPE*)AUSE->USEENTITY;
       if (E_TXTEQL_F(ETYPE->ETYPENAME, E_TXTLIT_F(_T("MAIN")))) {
       WTX_R(E_TXTLIT_F(_T("main")));
       }
       else {
       WTX_R(APROC->PDICTREF->LEXEME);
       }
       GENARGLIST(ETYPE);
       WTX_R(E_TXTLIT_F(_T(" {")));
       WTL_R();
       ATT = (struct ATTRDEF*)ETYPE->F_ATTRDEFS;
next0001:
       if ( !  ( ATT != 0 ) ) {
       goto done0001;
       }
       if (ATT->ISPARAM == 0 & ATT != APROC->RETURNATT) {
       WTX_R(MAKEATTRTYPE_F(ATT));
       WTS_R(1);
       WTX_R(ATT->ATTRNAME);
       WTX_R(E_TXTLIT_F(_T("= 0;")));
       WTL_R();
       }
       ATT = (struct ATTRDEF*)ATT->S_ATTRDEFS;
       goto next0001;
done0001:
       if (APROC->RETURNATT != 0) {
       WTX_R(MAKEATTRTYPE_F(APROC->RETURNATT));
       WTS_R(1);
       WTX_R(E_TXTLIT_F(_T("rval")));
       WTX_R(E_TXTLIT_F(_T(" = 0;")));
       WTL_R();
       }
       ATT = (struct ATTRDEF*)ETYPE->F_ATTRDEFS;
next0002:
       if ( !  ( ATT != 0 ) ) {
       goto done0002;
       }
       if (ATT->ISPARAM != 0) {
       if (E_TXTEQL_F(ATT->ATTRTYPE->ETYPENAME, E_TXTLIT_F(_T("Text")))) {
       WTX_R(E_TXTLIT_F(_T("E_TXTINC_R(")));
       WTX_R(ATT->ATTRNAME);
       WTX_R(E_TXTLIT_F(_T(");")));
       WTL_R();
       }
       }
       ATT = (struct ATTRDEF*)ATT->S_ATTRDEFS;
       goto next0002;
done0002:
       if (E_TXTEQL_F(ETYPE->ETYPENAME, E_TXTLIT_F(_T("MAIN")))) {
       WTB_R(8);
       WTX_R(E_TXTLIT_F(_T("easinit();")));
       WTL_R();
       }
       ASTMT = (struct STMT*)APROC->F_STMTS;
next0003:
       if ( !  ( ASTMT != 0 ) ) {
       goto done0003;
       }
       GENSTMT(APROC, ASTMT);
       ASTMT = (struct STMT*)ASTMT->S_STMTS;
       goto next0003;
done0003:
       if (EASEgen->GORETLBL != 0) {
       WTB_R(1);
       WTX_R(E_TXTLIT_F(_T("retlbl:")));
       WTL_R();
       }
       ATT = (struct ATTRDEF*)ETYPE->F_ATTRDEFS;
next0004:
       if ( !  ( ATT != 0 ) ) {
       goto done0004;
       }
       AREF = (struct DICTENTRY*)FINDDICTENTRY_F(ATT->ATTRNAME);
       AUSE = (struct DICTUSE*)FINDSPECUSE_F(AREF, 1);
       if (ATT != APROC->RETURNATT) {
       if (E_TXTEQL_F(ATT->ATTRTYPE->ETYPENAME, E_TXTLIT_F(_T("Text")))) {
       WTX_R(E_TXTLIT_F(_T("E_TXTDEL_R(")));
       WTX_R(ATT->ATTRNAME);
       WTX_R(E_TXTLIT_F(_T(");")));
       WTL_R();
       }
       if (AUSE->USEMODE == 4 & ATT->ATTRTYPE->ISPERSISTENT != 0) {
       WTX_R(E_TXTLIT_F(_T("eunasg((char*)&")));
       WTX_R(ATT->ATTRNAME);
       WTX_R(E_TXTLIT_F(_T(");")));
       WTL_R();
       }
       }
       DESTROYUSE(AUSE);
       ATT = (struct ATTRDEF*)ATT->S_ATTRDEFS;
       goto next0004;
done0004:
       WTB_R(8);
       WTX_R(E_TXTLIT_F(_T("return")));
       if (APROC->RETURNATT != 0) {
       WTX_R(E_TXTLIT_F(_T(" rval")));
       }
       WTX_R(E_TXTLIT_F(_T(";")));
       WTL_R();
       WTX_R(E_TXTLIT_F(_T("}")));
       WTL_R();
       goto retlbl;
retlbl:
       return;
}
void GENARGLIST(struct ENTITYTYPE* ETYPE) {
int FIRST= 0;
struct ATTRDEF* ATT= 0;
       FIRST = 1;
       WTX_R(E_TXTLIT_F(_T("(")));
       ATT = (struct ATTRDEF*)ETYPE->F_ATTRDEFS;
next0001:
       if ( !  ( ATT != 0 ) ) {
       goto done0001;
       }
       if (ATT->ISPARAM != 0) {
       if (FIRST == 0) {
       WTX_R(E_TXTLIT_F(_T(", ")));
       }
       FIRST = 0;
       WTX_R(MAKEATTRTYPE_F(ATT));
       if (ATT->ISYIELD != 0) {
       WTX_R(E_TXTLIT_F(_T("&")));
       }
       WTS_R(1);
       WTX_R(ATT->ATTRNAME);
       }
       ATT = (struct ATTRDEF*)ATT->S_ATTRDEFS;
       goto next0001;
done0001:
       WTX_R(E_TXTLIT_F(_T(")")));
       goto retlbl;
retlbl:
       return;
}
Etxt* MAKEATTRTYPE_F(struct ATTRDEF* ATT) {
Etxt* TXT= 0;
struct ENTITYTYPE* ETYPE= 0;
int STARS= 0;
Etxt* rval = 0;
       ETYPE = (struct ENTITYTYPE*)ATT->ATTRTYPE;
       STARS = ATT->SUBSCRIPTS;
       E_TXTASG_R(&TXT, MAKETYPE_F(ETYPE, STARS));
       E_TXTASG_R(&rval, TXT);
goto retlbl;
retlbl:
E_TXTDEL_R(TXT);
       return rval;
}
Etxt* MAKETYPE_F(struct ENTITYTYPE* ETYPE, int STARS) {
Etxt* TXT= 0;
Etxt* rval = 0;
       if (E_TXTNEQ_F(ETYPE->TARGETNAME, 0)) {
       E_TXTASG_R(&TXT, ETYPE->TARGETNAME);
       }
       else {
       E_TXTASG_R(&TXT, CONCAT_F(E_TXTLIT_F(_T("struct ")), ETYPE->ETYPENAME));
       E_TXTASG_R(&TXT, CONCAT_F(TXT, E_TXTLIT_F(_T("*"))));
       }
next0001:
       if ( !  ( STARS > 0 ) ) {
       goto done0001;
       }
       E_TXTASG_R(&TXT, CONCAT_F(TXT, E_TXTLIT_F(_T("*"))));
       STARS = STARS-1;
       goto next0001;
done0001:
       E_TXTASG_R(&rval, TXT);
goto retlbl;
retlbl:
E_TXTDEL_R(TXT);
       return rval;
}

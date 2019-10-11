#include "stdafx.h"
#include "malloc.h"
#include "libopts.h"
#include "math.h"
#include "Script.h"

void Script_addTypes() {
#ifdef _SCRIPTELEM
addEType(E_TXTLIT_F(_T("SCRIPTELEM")), 3006,    1, 0);
#endif
}
Script_sys* Script;

void Script_init() {
Script = (Script_sys*)E_CREATE_F( 0,3006, sizeof(Script_sys));
Script_sets();
Script_addTypes();
}
void Script_sets() {
       return;
}
void d_SCRIPTELEM(struct SCRIPTELEM*& EPTR) {
       E_DESTROY_R(EPTR);
       EPTR = (struct SCRIPTELEM*)0;
       return;
}
struct SCRIPTELEM* c_SCRIPTELEM() {
struct SCRIPTELEM* EPTR= 0;
struct SCRIPTELEM* rval = 0;
       EPTR = (struct SCRIPTELEM*)E_CREATE_F(3006, 1, Z_SCRIPTELEM);
       rval = (struct SCRIPTELEM*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void SCRIPTREAD(struct STMT* ASTMT) {
struct NODE* ANODE= 0;
struct NODE* EXPNODE= 0;
struct NODE* FMTNODE= 0;
int SCRIPTNUM= 0;
int MATCH= 0;
struct DICTUSE* AUSE= 0;
int AMODE= 0;
struct LCLDEF* ALCL= 0;
int HASUSING= 0;
       ANODE = (struct NODE*)ASTMT->F_PARSENODES;
       if (ANODE->S_NODES != 0) {
       HASUSING = 1;
       SCRIPT(61);
       Script->IPTRS[1] = (int)1;
       SCRIPT(60);
       }
       if (ANODE->MATCHNUM == 3) {
       ANODE = (struct NODE*)ANODE->F_SUBNODES;
next0001:
       if ( !  ( ANODE != 0 ) ) {
       goto done0001;
       }
       AUSE = (struct DICTUSE*)FINDPREFUSE_F(ANODE->START, 0);
       if (AUSE != 0) {
       AMODE = AUSE->USEMODE;
       }
       else {
       ALCL = (struct LCLDEF*)EASEmain->CURRPROC->F_LCLDEFS;
next0002:
       if ( !  ( ALCL != 0 ) ) {
       goto done0002;
       }
       if (E_TXTEQL_F(ALCL->LDEFNAME, ANODE->START->LEXEME)) {
       goto done0002;
       }
       ALCL = (struct LCLDEF*)ALCL->S_LCLDEFS;
       goto next0002;
done0002:
       if (ALCL == 0) {
       EASERR(1002, ANODE->START->LEXEME);
       }
       AMODE = FINDMODE_F(ALCL->LDEFTYPE);
       }
       Script->NODEPTRS[1] = (struct NODE*)ANODE->F_SUBNODES;
       if (AMODE == 1) {
       SCRIPT(40);
       }
       if (AMODE == 3) {
       SCRIPT(70);
       }
       if (AMODE == 2) {
       SCRIPT(75);
       }
       ANODE = (struct NODE*)ANODE->S_NODES;
       goto next0001;
done0001:
       if (HASUSING != 0) {
       SCRIPT(62);
       }
       goto retlbl;
       }
       if (ANODE->MATCHNUM == 2) {
       ANODE = (struct NODE*)ANODE->F_SUBNODES;
       EXPNODE = (struct NODE*)ANODE->F_SUBNODES;
       FMTNODE = (struct NODE*)ANODE->S_NODES;
       }
       else {
       FMTNODE = (struct NODE*)ANODE->F_SUBNODES;
       }
       FMTNODE = (struct NODE*)FMTNODE->F_SUBNODES;
next0003:
       if ( !  ( FMTNODE != 0 ) ) {
       goto done0003;
       }
       ANODE = (struct NODE*)FMTNODE->F_SUBNODES;
       if (ANODE->MATCHNUM == 1) {
       ANODE = (struct NODE*)ANODE->F_SUBNODES;
       MATCH = ANODE->MATCHNUM;
       if (MATCH == 1) {
       SCRIPTNUM = 21;
       Script->NODEPTRS[1] = (struct NODE*)ANODE->F_SUBNODES;
       }
       if (MATCH == 2) {
       SCRIPTNUM = 22;
       }
       if (MATCH == 3) {
       SCRIPTNUM = 23;
       Script->NODEPTRS[1] = (struct NODE*)ANODE->F_SUBNODES;
       }
       if (MATCH == 4) {
       SCRIPTNUM = 24;
       Script->NODEPTRS[1] = (struct NODE*)ANODE;
       }
       }
       else {
       Script->NODEPTRS[1] = (struct NODE*)EXPNODE->F_SUBNODES;
       ANODE = (struct NODE*)(FMTNODE)->F_SUBNODES->F_SUBNODES;
       if (ANODE->MATCHNUM == 1) {
       SCRIPTNUM = 37;
       Script->NODEPTRS[2] = (struct NODE*)ANODE->F_SUBNODES;
       }
       if (ANODE->MATCHNUM == 2) {
       ANODE = (struct NODE*)ANODE->F_SUBNODES;
       if (ANODE->MATCHNUM == 1) {
       SCRIPTNUM = 38;
       Script->NODEPTRS[2] = (struct NODE*)ANODE->F_SUBNODES;
       }
       else {
       SCRIPTNUM = 24;
       }
       }
       if (ANODE->MATCHNUM == 3) {
       SCRIPTNUM = 69;
       }
       if (ANODE->MATCHNUM == 4) {
       Script->NODEPTRS[2] = (struct NODE*)ANODE->F_SUBNODES;
       Script->NODEPTRS[3] = (struct NODE*)ANODE->F_SUBNODES->S_NODES;
       SCRIPTNUM = 71;
       }
       EXPNODE = (struct NODE*)EXPNODE->S_NODES;
       }
       FMTNODE = (struct NODE*)FMTNODE->S_NODES;
       SCRIPT(SCRIPTNUM);
       goto next0003;
done0003:
       if (HASUSING != 0) {
       SCRIPT(62);
       }
       goto retlbl;
retlbl:
       return;
}
void SCRIPTWRITE(struct STMT* ASTMT) {
struct NODE* ANODE= 0;
struct NODE* EXPNODE= 0;
struct NODE* FMTNODE= 0;
int SCRIPTNUM= 0;
int MATCH= 0;
int HASUSING= 0;
       ANODE = (struct NODE*)ASTMT->F_PARSENODES;
       if (ANODE->S_NODES != 0) {
       HASUSING = 1;
       SCRIPT(63);
       Script->IPTRS[1] = (int)2;
       SCRIPT(60);
       }
       if (ANODE->MATCHNUM == 2) {
       ANODE = (struct NODE*)ANODE->F_SUBNODES;
       EXPNODE = (struct NODE*)ANODE->F_SUBNODES;
       FMTNODE = (struct NODE*)ANODE->S_NODES->F_SUBNODES;
       }
       else {
       FMTNODE = (struct NODE*)ANODE->F_SUBNODES->F_SUBNODES;
       }
next0001:
       if ( !  ( FMTNODE != 0 ) ) {
       goto done0001;
       }
       ANODE = (struct NODE*)FMTNODE->F_SUBNODES;
       if (ANODE->MATCHNUM == 1) {
       ANODE = (struct NODE*)ANODE->F_SUBNODES;
       MATCH = ANODE->MATCHNUM;
       if (MATCH == 1) {
       SCRIPTNUM = 15;
       Script->NODEPTRS[1] = (struct NODE*)ANODE->F_SUBNODES;
       }
       if (MATCH == 2) {
       SCRIPTNUM = 16;
       }
       if (MATCH == 3) {
       SCRIPTNUM = 17;
       Script->NODEPTRS[1] = (struct NODE*)ANODE->F_SUBNODES;
       }
       if (MATCH == 4) {
       SCRIPTNUM = 9;
       Script->NODEPTRS[1] = (struct NODE*)ANODE;
       }
       }
       else {
       Script->NODEPTRS[1] = (struct NODE*)EXPNODE->F_SUBNODES;
       ANODE = (struct NODE*)(FMTNODE)->F_SUBNODES->F_SUBNODES;
       if (ANODE->MATCHNUM == 1) {
       SCRIPTNUM = 10;
       Script->NODEPTRS[2] = (struct NODE*)ANODE->F_SUBNODES;
       }
       if (ANODE->MATCHNUM == 2) {
       ANODE = (struct NODE*)ANODE->F_SUBNODES;
       if (ANODE->MATCHNUM == 1) {
       SCRIPTNUM = 19;
       Script->NODEPTRS[2] = (struct NODE*)ANODE->F_SUBNODES;
       }
       else {
       SCRIPTNUM = 9;
       }
       }
       if (ANODE->MATCHNUM == 3) {
       SCRIPTNUM = 68;
       }
       if (ANODE->MATCHNUM == 4) {
       Script->NODEPTRS[2] = (struct NODE*)ANODE->F_SUBNODES;
       Script->NODEPTRS[3] = (struct NODE*)ANODE->F_SUBNODES->S_NODES;
       SCRIPTNUM = 74;
       }
       EXPNODE = (struct NODE*)EXPNODE->S_NODES;
       }
       FMTNODE = (struct NODE*)FMTNODE->S_NODES;
       SCRIPT(SCRIPTNUM);
       goto next0001;
done0001:
       if (HASUSING != 0) {
       SCRIPT(64);
       }
       goto retlbl;
retlbl:
       return;
}
void STMTSCRIPT(struct STMT* ASTMT) {
struct NODE* ANODE= 0;
struct STMT* PSTMT= 0;
int I= 0;
int SCRIPTNO= 0;
struct DICTUSE* AUSE= 0;
struct SRCLINE* PRTLINE= 0;
struct LCLDEF* ALCL= 0;
       Script->SCRIPTLEVEL = ASTMT->SCRIPTDEPTH+1;
       I = 1;
       goto test0001;
next0001:
       I = I+1;
test0001:
       if (I > 9) {
       goto done0001;
       }
       Script->NODEPTRS[I] = (struct NODE*)0;
       goto next0001;
done0001:
       ANODE = (struct NODE*)ASTMT->F_PARSENODES;
       SETNODEPTRS(ANODE);
       if (E_TXTEQL_F(ASTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("FOR")))) {
       Script->LBL = Script->LBL+1;
       ASTMT->LBLNUM = Script->LBL;
       if (Script->LASTCTLSTMT != 0) {
       ASTMT->P_CTRLSTMT = (struct STMT*)Script->LASTCTLSTMT;
       }
       Script->LASTCTLSTMT = (struct STMT*)ASTMT;
       E_TXTASG_R(&Script->STRPTRS[2], SCRIPTLBL(E_TXTLIT_F(_T("next")), Script->LBL));
       if (ASTMT->P_CTRLSTMT == 0) {
       E_TXTASG_R(&Script->STRPTRS[3], SCRIPTLBL(E_TXTLIT_F(_T("done")), Script->LBL));
       }
       else {
       E_TXTASG_R(&Script->STRPTRS[3], SCRIPTLBL(E_TXTLIT_F(_T("next")), ASTMT->P_CTRLSTMT->LBLNUM));
       }
       E_TXTASG_R(&Script->STRPTRS[6], SCRIPTLBL(E_TXTLIT_F(_T("test")), Script->LBL));
       if (ANODE->MATCHNUM == 1) {
       Script->LV = Script->LV+1;
       E_TXTASG_R(&Script->STRPTRS[4], SCRIPTLBL(E_TXTLIT_F(_T("E_")), Script->LV));
       AUSE = (struct DICTUSE*)FINDPREFUSE_F(Script->NODEPTRS[1]->START, 0);
       if (AUSE != 0) {
       E_TXTASG_R(&Script->STRPTRS[5], AUSE->USEENTITY->ETYPENAME);
       }
       else {
       ALCL = (struct LCLDEF*)EASEmain->CURRPROC->F_LCLDEFS;
next0002:
       if ( !  ( ALCL != 0 ) ) {
       goto done0002;
       }
       if (E_TXTEQL_F(ALCL->LDEFNAME, Script->NODEPTRS[1]->START->LEXEME)) {
       goto done0002;
       }
       ALCL = (struct LCLDEF*)ALCL->S_LCLDEFS;
       goto next0002;
done0002:
       if (ALCL == 0) {
       EASERR(1002, Script->NODEPTRS[1]->START->LEXEME);
       }
       E_TXTASG_R(&Script->STRPTRS[5], ALCL->LDEFTYPE->ETYPENAME);
       }
       SCRIPT(41);
       SCRIPTNO = 2;
       }
       else {
       SCRIPTNO = 3;
       }
       SCRIPT(SCRIPTNO);
       goto retlbl;
       }
       if (E_TXTEQL_F(ASTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("WHILE")))) {
       I = 0;
       PSTMT = (struct STMT*)Script->LASTCTLSTMT;
next0003:
       if ( !  ( PSTMT != 0 ) ) {
       goto done0003;
       }
       I = PSTMT->LBLNUM;
       PSTMT = (struct STMT*)PSTMT->P_CTRLSTMT;
       goto next0003;
done0003:
       if (I == 0) {
       Script->LASTCTLSTMT = (struct STMT*)ASTMT;
       Script->LBL = Script->LBL+1;
       ASTMT->LBLNUM = Script->LBL;
       E_TXTASG_R(&Script->STRPTRS[1], SCRIPTLBL(E_TXTLIT_F(_T("next")), Script->LBL));
       SCRIPT(7);
       E_TXTASG_R(&Script->STRPTRS[3], SCRIPTLBL(E_TXTLIT_F(_T("done")), Script->LBL));
       }
       else {
       ASTMT->LBLNUM = I;
       E_TXTASG_R(&Script->STRPTRS[3], SCRIPTLBL(E_TXTLIT_F(_T("done")), I));
       }
       SCRIPT(8);
       goto retlbl;
       }
       if (E_TXTEQL_F(ASTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("UNTIL")))) {
       if (Script->LASTCTLSTMT == 0) {
       EASERR(1004, 0);
       goto retlbl;
       }
       PSTMT = (struct STMT*)Script->LASTCTLSTMT;
next0004:
       if ( !  ( PSTMT->P_CTRLSTMT != 0 ) ) {
       goto done0004;
       }
       PSTMT = (struct STMT*)PSTMT->P_CTRLSTMT;
       goto next0004;
done0004:
       E_TXTASG_R(&Script->STRPTRS[3], SCRIPTLBL(E_TXTLIT_F(_T("done")), PSTMT->LBLNUM));
       SCRIPT(14);
       goto retlbl;
       }
       if (E_TXTEQL_F(ASTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("WITH")))) {
       if (Script->LASTCTLSTMT == 0) {
       EASERR(1005, 0);
       goto retlbl;
       }
       E_TXTASG_R(&Script->STRPTRS[3], SCRIPTLBL(E_TXTLIT_F(_T("next")), Script->LASTCTLSTMT->LBLNUM));
       SCRIPT(8);
       goto retlbl;
       }
       if (E_TXTEQL_F(ASTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("FIND")))) {
       if (Script->LASTCTLSTMT == 0) {
       EASERR(1006, 0);
       goto retlbl;
       }
       if (ANODE->MATCHNUM == 1) {
       Script->NODEPTRS[1] = (struct NODE*)ANODE->F_SUBNODES;
       Script->NODEPTRS[2] = (struct NODE*)Script->NODEPTRS[1]->S_NODES;
       SCRIPT(4);
       }
       PSTMT = (struct STMT*)Script->LASTCTLSTMT;
       Script->LASTCTLSTMT = (struct STMT*)0;
next0005:
       if ( !  ( PSTMT != 0 ) ) {
       goto done0005;
       }
       I = PSTMT->LBLNUM;
       PSTMT = (struct STMT*)PSTMT->P_CTRLSTMT;
       goto next0005;
done0005:
       E_TXTASG_R(&Script->STRPTRS[1], SCRIPTLBL(E_TXTLIT_F(_T("skip")), I));
       E_TXTASG_R(&Script->STRPTRS[2], SCRIPTLBL(E_TXTLIT_F(_T("done")), I));
       SCRIPT(53);
       if (ANODE->S_NODES != 0) {
       if (ANODE->S_NODES->MATCHNUM == 1) {
       SCRIPT(54);
       }
       else {
       SCRIPT(55);
       }
       }
       goto retlbl;
       }
       if (E_TXTEQL_F(ASTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("DO")))) {
       if (Script->LASTCTLSTMT == 0) {
       EASERR(1007, 0);
       goto retlbl;
       }
       ASTMT->P_CTRLSTMT = (struct STMT*)Script->LASTCTLSTMT;
       if (Script->LASTDOSTMT != 0) {
       ASTMT->P_DOSTMT = (struct STMT*)Script->LASTDOSTMT;
       }
       Script->LASTDOSTMT = (struct STMT*)ASTMT;
       Script->LASTCTLSTMT = (struct STMT*)0;
       Script->CURRLOOPDEPTH = Script->CURRLOOPDEPTH+1;
       goto retlbl;
       }
       if (E_TXTEQL_F(ASTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("LOOP")))) {
       if (Script->LASTDOSTMT == 0) {
       EASERR(1008, 0);
       goto retlbl;
       }
       Script->CURRLOOPDEPTH = Script->CURRLOOPDEPTH-1;
       PSTMT = (struct STMT*)Script->LASTDOSTMT->P_CTRLSTMT;
       E_TXTASG_R(&Script->STRPTRS[2], SCRIPTLBL(E_TXTLIT_F(_T("next")), PSTMT->LBLNUM));
next0006:
       if ( !  ( PSTMT->P_CTRLSTMT != 0 ) ) {
       goto done0006;
       }
       PSTMT = (struct STMT*)PSTMT->P_CTRLSTMT;
       goto next0006;
done0006:
       E_TXTASG_R(&Script->STRPTRS[3], SCRIPTLBL(E_TXTLIT_F(_T("done")), PSTMT->LBLNUM));
       SCRIPT(13);
       Script->LASTDOSTMT = (struct STMT*)Script->LASTDOSTMT->P_DOSTMT;
       goto retlbl;
       }
       if (E_TXTEQL_F(ASTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("LEAVE")))) {
       if (Script->LASTDOSTMT == 0) {
       EASERR(1009, 0);
       goto retlbl;
       }
       PSTMT = (struct STMT*)Script->LASTDOSTMT->P_CTRLSTMT;
       if (PSTMT->P_CTRLSTMT == 0) {
       E_TXTASG_R(&Script->STRPTRS[3], SCRIPTLBL(E_TXTLIT_F(_T("done")), PSTMT->LBLNUM));
       }
       else {
       E_TXTASG_R(&Script->STRPTRS[3], SCRIPTLBL(E_TXTLIT_F(_T("next")), PSTMT->P_CTRLSTMT->LBLNUM));
       }
       SCRIPT(18);
       goto retlbl;
       }
       if (E_TXTEQL_F(ASTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("CYCLE")))) {
       if (Script->LASTDOSTMT == 0) {
       EASERR(1009, 0);
       goto retlbl;
       }
       PSTMT = (struct STMT*)Script->LASTDOSTMT->P_CTRLSTMT;
       E_TXTASG_R(&Script->STRPTRS[3], SCRIPTLBL(E_TXTLIT_F(_T("next")), PSTMT->LBLNUM));
       SCRIPT(18);
       goto retlbl;
       }
       if (E_TXTEQL_F(ASTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("FILE")))) {
       ANODE = (struct NODE*)ASTMT->F_PARSENODES->S_NODES;
       I = 0;
       if (ANODE->SCRIPTCODE == 0) {
       I = ANODE->MATCHNUM;
       ANODE = (struct NODE*)ANODE->S_NODES;
       }
       AUSE = (struct DICTUSE*)FINDSPECUSE_F(ANODE->START->DICTREF, 4);
       if (AUSE == 0) {
       EASERR(1010, ANODE->START->LEXEME);
       goto retlbl;
       }
       if (AUSE->USEENTITY->ISSETTYPE == 0) {
       EASERR(1010, ANODE->START->LEXEME);
       goto retlbl;
       }
       if (AUSE->USESETREFATT->SETATTRSETDEF->SETDISCIPLINE == 0) {
       if (I != 0) {
       EASERR(1016, ANODE->START->LEXEME);
       goto retlbl;
       }
       E_TXTASG_R(&Script->STRPTRS[1], Script->NODEPTRS[2]->F_SUBNODES->START->LEXEME);
       if (AUSE->USEENTITY->ISPERSISTENT != 0) {
       SCRIPTNO = 57;
       }
       else {
       SCRIPTNO = 42;
       }
       }
       else {
       SCRIPTNO = 6;
       if (I == 0) {
       if (AUSE->USESETREFATT->SETATTRSETDEF->SETDISCIPLINE == 1) {
       SCRIPTNO = 5;
       }
       }
       else {
       if (I == 1) {
       SCRIPTNO = 5;
       }
       }
       if (AUSE->USEENTITY->ISPERSISTENT != 0) {
       SCRIPTNO = SCRIPTNO+43;
       }
       }
       if (SCRIPTNO != 0) {
       SCRIPT(SCRIPTNO);
       }
       goto retlbl;
       }
       if (E_TXTEQL_F(ASTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("REMOV")))) {
       ANODE = (struct NODE*)ASTMT->F_PARSENODES;
       SCRIPTNO = 0;
       if (ANODE->SCRIPTCODE == 0) {
       SCRIPTNO = 34;
       if (ANODE->MATCHNUM == 2) {
       SCRIPTNO = 35;
       }
       if (ANODE->MATCHNUM == 3) {
       SCRIPTNO = 36;
       }
       ANODE = (struct NODE*)ANODE->S_NODES;
       }
       AUSE = (struct DICTUSE*)FINDSPECUSE_F(ANODE->START->DICTREF, 4);
       if (AUSE == 0) {
       EASERR(1010, ANODE->START->LEXEME);
       goto retlbl;
       }
       if (AUSE->USEENTITY->ISSETTYPE == 0) {
       EASERR(1010, ANODE->START->LEXEME);
       goto retlbl;
       }
       if (SCRIPTNO == 0) {
       SCRIPTNO = 34;
       if (AUSE->USESETREFATT->SETATTRSETDEF->SETDISCIPLINE == 1) {
       SCRIPTNO = 35;
       }
       }
       if (AUSE->USEENTITY->ISPERSISTENT != 0) {
       SCRIPTNO = SCRIPTNO+16;
       }
       SCRIPT(SCRIPTNO);
       goto retlbl;
       }
       if (E_TXTEQL_F(ASTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("OPEN")))) {
       if (ANODE->S_NODES->MATCHNUM == 1) {
       SCRIPTNO = 11;
       }
       else {
       SCRIPTNO = 12;
       }
       SCRIPT(SCRIPTNO);
       goto retlbl;
       }
       if (E_TXTEQL_F(ASTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("CLOSE")))) {
       SCRIPT(20);
       goto retlbl;
       }
       if (E_TXTEQL_F(ASTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("WRITE")))) {
       SCRIPTWRITE(ASTMT);
       goto retlbl;
       }
       if (E_TXTEQL_F(ASTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("READ")))) {
       SCRIPTREAD(ASTMT);
       goto retlbl;
       }
       if (E_TXTEQL_F(ASTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("USE")))) {
       Script->IPTRS[1] = (int)ANODE->S_NODES->MATCHNUM;
       SCRIPT(60);
       goto retlbl;
       }
       if (E_TXTEQL_F(ASTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("RESERVE")))) {
       if (ANODE->S_NODES->S_NODES != 0) {
       ANODE->END = (struct TOKEN*)ANODE->START;
       ANODE = (struct NODE*)ANODE->S_NODES;
       Script->NODEPTRS[2] = (struct NODE*)ANODE;
       Script->LV = Script->LV+1;
       E_TXTASG_R(&Script->STRPTRS[1], SCRIPTLBL(E_TXTLIT_F(_T("I_")), Script->LV));
       SCRIPT(25);
       Script->NODEPTRS[3] = (struct NODE*)ANODE->S_NODES;
       Script->LV = Script->LV+1;
       E_TXTASG_R(&Script->STRPTRS[2], SCRIPTLBL(E_TXTLIT_F(_T("I_")), Script->LV));
       Script->LV = Script->LV+1;
       E_TXTASG_R(&Script->STRPTRS[3], SCRIPTLBL(E_TXTLIT_F(_T("I_")), Script->LV));
       SCRIPT(26);
       }
       goto retlbl;
       }
       if (E_TXTEQL_F(ASTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("PRINTN")))) {
       PRTLINE = (struct SRCLINE*)ASTMT->F_FMTLINES;
next0007:
       if ( !  ( PRTLINE != 0 ) ) {
       goto done0007;
       }
       E_TXTASG_R(&Script->STRPTRS[1], PRTLINE->LTXT);
       SCRIPT(39);
       PRTLINE = (struct SRCLINE*)PRTLINE->S_SRCLINES;
       goto next0007;
done0007:
       goto retlbl;
       }
       if (E_TXTEQL_F(ASTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("ERASE")))) {
       SCRIPT(27);
       goto retlbl;
       }
       if (E_TXTEQL_F(ASTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("PSERVER")))) {
       if (ANODE->MATCHNUM == 1) {
       SCRIPT(65);
       }
       else {
       SCRIPT(66);
       }
       goto retlbl;
       }
       if (E_TXTEQL_F(ASTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("RECUNL")))) {
       if (ANODE->MATCHNUM == 1) {
       SCRIPT(58);
       }
       goto retlbl;
       }
       if (E_TXTEQL_F(ASTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("IF")))) {
       if (ANODE->MATCHNUM == 2) {
       E_TXTASG_R(&Script->STRPTRS[2], ANODE->END->DICTREF->LEXEME);
       SCRIPT(67);
       }
       goto retlbl;
       }
       goto retlbl;
retlbl:
       return;
}
void SCRIPTLOOP() {
int I= 0;
int J= 0;
struct STMT* PSTMT= 0;
       if (Script->LASTCTLSTMT == 0) {
       EASERR(1007, 0);
       }
       else {
       PSTMT = (struct STMT*)Script->LASTCTLSTMT;
       Script->LASTCTLSTMT = (struct STMT*)0;
next0001:
       if ( !  ( PSTMT != 0 ) ) {
       goto done0001;
       }
       if (E_TXTEQL_F(PSTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("FOR"))) | E_TXTEQL_F(PSTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("WHILE"))) | E_TXTEQL_F(PSTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("UNTIL")))) {
       E_TXTASG_R(&Script->STRPTRS[2], SCRIPTLBL(E_TXTLIT_F(_T("next")), PSTMT->LBLNUM));
       E_TXTASG_R(&Script->STRPTRS[3], SCRIPTLBL(E_TXTLIT_F(_T("done")), PSTMT->LBLNUM));
       SCRIPT(13);
       }
       PSTMT = (struct STMT*)PSTMT->P_CTRLSTMT;
       goto next0001;
done0001:
;      }
       goto retlbl;
retlbl:
       return;
}
Etxt* SCRIPTLBL(Etxt* PREFIX, int NUM) {
int I= 0;
int J= 0;
Etxt* ALBL= 0;
Etxt* rval = 0;
E_TXTINC_R(PREFIX);
       E_TXTASG_R(&ALBL, CONCAT_F(PREFIX, E_TXTLIT_F(_T("0000"))));
       I = LENGTH_F(PREFIX);
       J = I+4;
next0001:
       if ( !  ( NUM > 9 ) ) {
       goto done0001;
       }
       I = NUM;
       NUM = NUM/10;
       I = I-NUM*10;
       QACHAR_F(ALBL, J, I+48);
       J = J-1;
       goto next0001;
done0001:
       QACHAR_F(ALBL, J, NUM+48);
       E_TXTASG_R(&rval, ALBL);
goto retlbl;
retlbl:
E_TXTDEL_R(PREFIX);
E_TXTDEL_R(ALBL);
       return rval;
}
void SETNODEPTRS(struct NODE* ANODE) {
next0001:
       if ( !  ( ANODE != 0 ) ) {
       goto done0001;
       }
       if (ANODE->SCRIPTCODE != 0) {
       Script->NODEPTRS[ANODE->SCRIPTCODE] = (struct NODE*)ANODE;
       }
       if (ANODE->F_SUBNODES != 0) {
       SETNODEPTRS(ANODE->F_SUBNODES);
       }
       ANODE = (struct NODE*)ANODE->S_NODES;
       goto next0001;
done0001:
       goto retlbl;
retlbl:
       return;
}
void SCRIPT(int SCRIPTNO) {
struct SCRIPTELEM* AELEM= 0;
struct NODE* ANODE= 0;
struct TOKEN* ATOKEN= 0;
struct TOKEN* TKN= 0;
Etxt* TMPTXT= 0;
int I= 0;
       AELEM = (struct SCRIPTELEM*)Script->SCRIPTS[SCRIPTNO];
       if (AELEM == 0) {
       goto retlbl;
       }
next0001:
       if ( !  ( AELEM != 0 ) ) {
       goto done0001;
       }
       if (AELEM->SCRIPTCODE == 0) {
       ATOKEN= c_TOKEN();
       ATOKEN->SCRIPTED = Script->SCRIPTLEVEL;
       ATOKEN->DICTREF = (struct DICTENTRY*)AELEM->DICTREF;
       E_TXTASG_R(&ATOKEN->LEXEME, AELEM->DICTREF->LEXEME);
       ATOKEN->TOKENTYPE = AELEM->TKNFORM;
       FILETOKEN(ATOKEN);
       }
       else {
       if (AELEM->SCRIPTACTION == 1) {
       ANODE = (struct NODE*)Script->NODEPTRS[AELEM->SCRIPTCODE];
       if (ANODE != 0) {
       TKN = (struct TOKEN*)ANODE->START;
next0002:
       if ( !  ( TKN != ANODE->END->S_TOKENLIST ) ) {
       goto done0002;
       }
       ATOKEN= c_TOKEN();
       ATOKEN->SCRIPTED = Script->SCRIPTLEVEL;
       ATOKEN->DICTREF = (struct DICTENTRY*)TKN->DICTREF;
       E_TXTASG_R(&ATOKEN->LEXEME, TKN->DICTREF->LEXEME);
       ATOKEN->TOKENTYPE = TKN->TOKENTYPE;
       FILETOKEN(ATOKEN);
       TKN = (struct TOKEN*)TKN->S_TOKENLIST;
       goto next0002;
done0002:
;      }
       }
       if (AELEM->SCRIPTACTION == 2) {
       ATOKEN= c_TOKEN();
       ATOKEN->SCRIPTED = Script->SCRIPTLEVEL;
       E_TXTASG_R(&ATOKEN->LEXEME, Script->STRPTRS[AELEM->SCRIPTCODE]);
       ATOKEN->TOKENTYPE = AELEM->TKNFORM;
       ATOKEN->DICTREF = (struct DICTENTRY*)FINDDICTENTRY_F(ATOKEN->LEXEME);
       FILETOKEN(ATOKEN);
       }
       if (AELEM->SCRIPTACTION == 3) {
       ATOKEN= c_TOKEN();
       ATOKEN->SCRIPTED = Script->SCRIPTLEVEL;
       E_TXTASG_R(&TMPTXT, E_TXTLIT_F(_T("__")));
       QACHAR_F(TMPTXT, 1, AELEM->SCRIPTPREFIX);
       E_TXTASG_R(&ATOKEN->LEXEME, CONCAT_F(TMPTXT, Script->STRPTRS[AELEM->SCRIPTCODE]));
       ATOKEN->TOKENTYPE = AELEM->TKNFORM;
       ATOKEN->DICTREF = (struct DICTENTRY*)FINDDICTENTRY_F(ATOKEN->LEXEME);
       FILETOKEN(ATOKEN);
       }
       if (AELEM->SCRIPTACTION == 4) {
       ANODE = (struct NODE*)Script->NODEPTRS[AELEM->SCRIPTCODE];
       ATOKEN= c_TOKEN();
       ATOKEN->SCRIPTED = Script->SCRIPTLEVEL;
       E_TXTASG_R(&TMPTXT, E_TXTLIT_F(_T("__")));
       QACHAR_F(TMPTXT, 1, AELEM->SCRIPTPREFIX);
       E_TXTASG_R(&ATOKEN->LEXEME, CONCAT_F(TMPTXT, ANODE->START->LEXEME));
       ATOKEN->TOKENTYPE = AELEM->TKNFORM;
       ATOKEN->DICTREF = (struct DICTENTRY*)FINDDICTENTRY_F(ATOKEN->LEXEME);
       FILETOKEN(ATOKEN);
       }
       if (AELEM->SCRIPTACTION == 5) {
       ATOKEN= c_TOKEN();
       ATOKEN->SCRIPTED = Script->SCRIPTLEVEL;
       E_TXTASG_R(&ATOKEN->LEXEME, ITOT_F(Script->IPTRS[AELEM->SCRIPTCODE]));
       easlib->E_SAVE_V = easlib->WRITE_V;
       USE_R(97, 2);
       WTX_R(ATOKEN->LEXEME);
       WTS_R(2);
       USE_R(easlib->E_SAVE_V, 2);
       ATOKEN->TOKENTYPE = AELEM->TKNFORM;
       ATOKEN->DICTREF = (struct DICTENTRY*)FINDDICTENTRY_F(ATOKEN->LEXEME);
       FILETOKEN(ATOKEN);
       }
       }
       AELEM = (struct SCRIPTELEM*)AELEM->S_SCRIPTELEMS;
       goto next0001;
done0001:
       easlib->E_SAVE_V = easlib->WRITE_V;
       USE_R(97, 2);
       WTL_R();
       USE_R(easlib->E_SAVE_V, 2);
       goto retlbl;
retlbl:
E_TXTDEL_R(TMPTXT);
       return;
}
void READSCRIPT(int SCRIPTNO) {
struct TOKEN* ATOKEN= 0;
struct SCRIPTELEM* AELEM= 0;
struct SCRIPTELEM* LASTELEM= 0;
struct TOKEN* LAST= 0;
struct TOKEN* CLEAN= 0;
       ATOKEN = (struct TOKEN*)EASElex->F_TOKENLIST;
next0001:
       if ( !  ( E_TXTNEQ_F(ATOKEN->LEXEME, E_TXTLIT_F(_T("!"))) ) ) {
       goto done0001;
       }
       AELEM= c_SCRIPTELEM();
       if (E_TXTEQL_F(ATOKEN->LEXEME, E_TXTLIT_F(_T("#")))) {
       ATOKEN = (struct TOKEN*)ATOKEN->S_TOKENLIST;
       AELEM->SCRIPTACTION = 1;
       AELEM->SCRIPTCODE = ACHAR_F(ATOKEN->LEXEME, 1)-48;
       if (E_TXTEQL_F(ATOKEN->S_TOKENLIST->DICTREF->LEXEME, E_TXTLIT_F(_T("|")))) {
       ATOKEN = (struct TOKEN*)ATOKEN->S_TOKENLIST;
       }
       }
       if (E_TXTEQL_F(ATOKEN->LEXEME, E_TXTLIT_F(_T("%")))) {
       ATOKEN = (struct TOKEN*)ATOKEN->S_TOKENLIST;
       AELEM->TKNFORM = 3;
       if (E_TXTEQL_F(ATOKEN->LEXEME, E_TXTLIT_F(_T("%")))) {
       AELEM->TKNFORM = 2;
       ATOKEN = (struct TOKEN*)ATOKEN->S_TOKENLIST;
       }
       if (E_TXTEQL_F(ATOKEN->LEXEME, E_TXTLIT_F(_T("^")))) {
       AELEM->TKNFORM = 4;
       ATOKEN = (struct TOKEN*)ATOKEN->S_TOKENLIST;
       }
       AELEM->SCRIPTACTION = 2;
       AELEM->SCRIPTCODE = ACHAR_F(ATOKEN->LEXEME, 1)-48;
       }
       if (E_TXTEQL_F(ATOKEN->LEXEME, E_TXTLIT_F(_T("@")))) {
       ATOKEN = (struct TOKEN*)ATOKEN->S_TOKENLIST;
       AELEM->SCRIPTPREFIX = ACHAR_F(ATOKEN->LEXEME, 1);
       ATOKEN = (struct TOKEN*)ATOKEN->S_TOKENLIST;
       AELEM->SCRIPTACTION = 3;
       if (E_TXTEQL_F(ATOKEN->LEXEME, E_TXTLIT_F(_T("#")))) {
       AELEM->SCRIPTACTION = 4;
       }
       ATOKEN = (struct TOKEN*)ATOKEN->S_TOKENLIST;
       AELEM->TKNFORM = 3;
       AELEM->SCRIPTCODE = ACHAR_F(ATOKEN->LEXEME, 1)-48;
       }
       if (E_TXTEQL_F(ATOKEN->LEXEME, E_TXTLIT_F(_T("~")))) {
       ATOKEN = (struct TOKEN*)ATOKEN->S_TOKENLIST;
       AELEM->TKNFORM = 2;
       AELEM->SCRIPTCODE = ACHAR_F(ATOKEN->LEXEME, 1)-48;
       AELEM->SCRIPTACTION = 5;
       }
       if (AELEM->SCRIPTCODE == 0) {
       AELEM->DICTREF = (struct DICTENTRY*)ATOKEN->DICTREF;
       AELEM->TKNFORM = ATOKEN->TOKENTYPE;
       }
       if (Script->SCRIPTS[SCRIPTNO] == 0) {
       Script->SCRIPTS[SCRIPTNO] = (struct SCRIPTELEM*)AELEM;
       }
       else {
       LASTELEM->S_SCRIPTELEMS = (struct SCRIPTELEM*)AELEM;
       }
       LASTELEM = (struct SCRIPTELEM*)AELEM;
       ATOKEN = (struct TOKEN*)ATOKEN->S_TOKENLIST;
       goto next0001;
done0001:
       ATOKEN = (struct TOKEN*)ATOKEN->S_TOKENLIST;
       LAST = (struct TOKEN*)EASElex->F_TOKENLIST;
       EASElex->F_TOKENLIST = (struct TOKEN*)ATOKEN;
next0002:
       if ( !  ( LAST != EASElex->F_TOKENLIST ) ) {
       goto done0002;
       }
       CLEAN = (struct TOKEN*)LAST;
       LAST = (struct TOKEN*)LAST->S_TOKENLIST;
       E_TXTASG_R(&CLEAN->LEXEME, E_TXTLIT_F(_T("""")));
       d_TOKEN(CLEAN);
       goto next0002;
done0002:
       goto retlbl;
retlbl:
       return;
}
void READSCRIPTS(Etxt* FILENAME) {
int SCRIPTNO= 0;
Etxt* ALINE= 0;
int LEN= 0;
E_TXTINC_R(FILENAME);
       Script->SCRIPTS = (SCRIPTELEM**)calloc(128 + 1, sizeof(SCRIPTELEM*));
       Script->SCRIPTS[0] = (SCRIPTELEM*)(128);
       SCRIPTNO = 1;
       OPENI_R(5, FILENAME);
       USE_R(5, 1);
       easlib->UIB_R->EOF_V = 1;
next0001:
       if ( !  ( easlib->UIB_R->EOF_V != 2 ) ) {
       goto done0001;
       }
       E_TXTASG_R(&ALINE, RDT_F(easlib->UIB_R->RRECLEN_V));
       LEN = LENGTH_F(ALINE);
       ANALYZE(ALINE, LEN, 1);
       READSCRIPT(SCRIPTNO);
       SCRIPTNO = SCRIPTNO+1;
       RDL_R();
       goto next0001;
done0001:
       CLOSE_R(5);
       Script->NODEPTRS = (NODE**)calloc(9 + 1, sizeof(NODE*));
       Script->NODEPTRS[0] = (NODE*)(9);
       Script->STRPTRS = (Etxt**)calloc(9 + 1, sizeof(Etxt*));
       Script->STRPTRS[0] = (Etxt*)(9);
       Script->IPTRS = (int*)calloc(9 + 1, sizeof(int));
       Script->IPTRS[0] = (int)(9);
       goto retlbl;
retlbl:
E_TXTDEL_R(FILENAME);
E_TXTDEL_R(ALINE);
       return;
}

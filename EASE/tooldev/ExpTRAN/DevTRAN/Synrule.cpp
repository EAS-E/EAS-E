#include "stdafx.h"
#include "malloc.h"
#include "libopts.h"
#include "math.h"
#include "Synrule.h"

void Synrule_addTypes() {
#ifdef _ALTREF
addEType(E_TXTLIT_F(_T("ALTREF")), 3004,    9, 0);
#endif
#ifdef _RULFIXUP
addEType(E_TXTLIT_F(_T("RULFIXUP")), 3004,    8, 0);
#endif
#ifdef _ALTPART
addEType(E_TXTLIT_F(_T("ALTPART")), 3004,    3, 0);
#endif
#ifdef _RULEPART
addEType(E_TXTLIT_F(_T("RULEPART")), 3004,    2, 0);
#endif
#ifdef _SYNRULE
addEType(E_TXTLIT_F(_T("SYNRULE")), 3004,    1, 0);
#endif
}
Synrule_sys* Synrule;

void Synrule_init() {
Synrule = (Synrule_sys*)E_CREATE_F( 0,3004, sizeof(Synrule_sys));
Synrule_sets();
Synrule_addTypes();
}
void Synrule_sets() {
       return;
}
void d_SYNRULE(struct SYNRULE*& EPTR) {
       E_TXTASG_R(&EPTR->RULENAME, 0);
       E_DESTROY_R(EPTR);
       EPTR = (struct SYNRULE*)0;
       return;
}
struct SYNRULE* c_SYNRULE() {
struct SYNRULE* EPTR= 0;
struct SYNRULE* rval = 0;
       EPTR = (struct SYNRULE*)E_CREATE_F(3004, 1, Z_SYNRULE);
       rval = (struct SYNRULE*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void d_RULEPART(struct RULEPART*& EPTR) {
       E_DESTROY_R(EPTR);
       EPTR = (struct RULEPART*)0;
       return;
}
struct RULEPART* c_RULEPART() {
struct RULEPART* EPTR= 0;
struct RULEPART* rval = 0;
       EPTR = (struct RULEPART*)E_CREATE_F(3004, 2, Z_RULEPART);
       rval = (struct RULEPART*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void d_ALTPART(struct ALTPART*& EPTR) {
       E_DESTROY_R(EPTR);
       EPTR = (struct ALTPART*)0;
       return;
}
struct ALTPART* c_ALTPART() {
struct ALTPART* EPTR= 0;
struct ALTPART* rval = 0;
       EPTR = (struct ALTPART*)E_CREATE_F(3004, 3, Z_ALTPART);
       rval = (struct ALTPART*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void d_RULFIXUP(struct RULFIXUP*& EPTR) {
       E_TXTASG_R(&EPTR->RULENAME, 0);
       E_DESTROY_R(EPTR);
       EPTR = (struct RULFIXUP*)0;
       return;
}
struct RULFIXUP* c_RULFIXUP() {
struct RULFIXUP* EPTR= 0;
struct RULFIXUP* rval = 0;
       EPTR = (struct RULFIXUP*)E_CREATE_F(3004, 8, Z_RULFIXUP);
       rval = (struct RULFIXUP*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void d_ALTREF(struct ALTREF*& EPTR) {
       E_DESTROY_R(EPTR);
       EPTR = (struct ALTREF*)0;
       return;
}
struct ALTREF* c_ALTREF() {
struct ALTREF* EPTR= 0;
struct ALTREF* rval = 0;
       EPTR = (struct ALTREF*)E_CREATE_F(3004, 9, Z_ALTREF);
       rval = (struct ALTREF*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
struct RULEPART* READPART() {
struct RULEPART* APART= 0;
struct RULEPART* rval = 0;
       APART= c_RULEPART();
       if (E_TXTEQL_F(Synrule->CURRTOKEN->LEXEME, E_TXTLIT_F(_T("<"))) & Synrule->CURRTOKEN->TOKENTYPE == 0) {
       APART->REQUIRED = 1;
       Synrule->CURRTOKEN = (struct TOKEN*)Synrule->CURRTOKEN->S_TOKENLIST;
next0001:
       if ( !  ( E_TXTNEQ_F(Synrule->CURRTOKEN->LEXEME, E_TXTLIT_F(_T(">"))) | Synrule->CURRTOKEN->TOKENTYPE != 0 ) ) {
       goto done0001;
       }
       READALT(APART);
       goto next0001;
done0001:
;      }
       else {
       if (E_TXTEQL_F(Synrule->CURRTOKEN->LEXEME, E_TXTLIT_F(_T("(")))) {
       Synrule->CURRTOKEN = (struct TOKEN*)Synrule->CURRTOKEN->S_TOKENLIST;
next0002:
       if ( !  ( E_TXTNEQ_F(Synrule->CURRTOKEN->LEXEME, E_TXTLIT_F(_T(")"))) ) ) {
       goto done0002;
       }
       READALT(APART);
       goto next0002;
done0002:
;      }
       }
       Synrule->CURRTOKEN = (struct TOKEN*)Synrule->CURRTOKEN->S_TOKENLIST;
       if (E_TXTEQL_F(Synrule->CURRTOKEN->LEXEME, E_TXTLIT_F(_T("*")))) {
       APART->REPEATS = 1;
       Synrule->CURRTOKEN = (struct TOKEN*)Synrule->CURRTOKEN->S_TOKENLIST;
       }
       rval = (struct RULEPART*)APART;
goto retlbl;
retlbl:
       return rval;
}
void LINKSUBTOROOTENTRY(struct SYNRULE* ARULE) {
struct RULEPART* APART= 0;
struct ALTPART* AALT= 0;
struct RULEPART* SPART= 0;
struct SYNRULE* LRULE= 0;
struct DICTENTRY* AENTRY= 0;
       APART = (struct RULEPART*)ARULE->F_PARTS;
next0001:
       if ( !  ( APART != 0 ) ) {
       goto done0001;
       }
       AALT = (struct ALTPART*)APART->F_ALTS;
next0002:
       if ( !  ( AALT != 0 ) ) {
       goto done0002;
       }
       if (AALT->TERMINALTYPE == 5) {
       AENTRY = (struct DICTENTRY*)AALT->DICTENT;
       }
       else {
       SPART = (struct RULEPART*)AALT->SUBRULE->F_PARTS;
       AENTRY = (struct DICTENTRY*)SPART->F_ALTS->DICTENT;
       }
       if (AENTRY->F_ENTRULES == 0) {
       AENTRY->F_ENTRULES = (struct SYNRULE*)ARULE;
       }
       else {
       LRULE = (struct SYNRULE*)AENTRY->F_ENTRULES;
next0003:
       if ( !  ( LRULE->S_ENTRULES != 0 ) ) {
       goto done0003;
       }
       LRULE = (struct SYNRULE*)LRULE->S_ENTRULES;
       goto next0003;
done0003:
       LRULE->S_ENTRULES = (struct SYNRULE*)ARULE;
       }
       AALT = (struct ALTPART*)AALT->S_ALTS;
       goto next0002;
done0002:
       if (APART->REQUIRED != 0) {
       APART = (struct RULEPART*)0;
       }
       else {
       APART = (struct RULEPART*)APART->S_PARTS;
       }
       goto next0001;
done0001:
       goto retlbl;
retlbl:
       return;
}
void FIXUPSUBRULES() {
struct ALTREF* AREF= 0;
struct SYNRULE* ARULE= 0;
struct RULFIXUP* AFIX= 0;
       AFIX = (struct RULFIXUP*)Synrule->F_RULFIXUPS;
next0001:
       if ( !  ( AFIX != 0 ) ) {
       goto done0001;
       }
       AREF = (struct ALTREF*)AFIX->F_ALTREFS;
next0002:
       if ( !  ( AREF != 0 ) ) {
       goto done0002;
       }
       AREF->ALTSUBRULE->SUBRULE = (struct SYNRULE*)AFIX->THERULE;
       AREF = (struct ALTREF*)AREF->S_ALTREFS;
       goto next0002;
done0002:
       AFIX = (struct RULFIXUP*)AFIX->S_RULFIXUPS;
       goto next0001;
done0001:
       ARULE = (struct SYNRULE*)Synrule->F_SYNRULES;
next0003:
       if ( !  ( ARULE != 0 ) ) {
       goto done0003;
       }
       LINKSUBTOROOTENTRY(ARULE);
       ARULE = (struct SYNRULE*)ARULE->S_SYNRULES;
       goto next0003;
done0003:
       goto retlbl;
retlbl:
       return;
}
void READALT(struct RULEPART* PART) {
struct ALTPART* ALT= 0;
struct ALTPART* LAST= 0;
struct ALTREF* AREF= 0;
struct RULFIXUP* AFIX= 0;
       ALT= c_ALTPART();
       if (Synrule->CURRTOKEN->TOKENTYPE == 4) {
       ALT->DICTENT = (struct DICTENTRY*)FINDDICTENTRY_F(Synrule->CURRTOKEN->LEXEME);
       ALT->TERMINALTYPE = 5;
       if (E_TXTEQL_F(Synrule->CURRTOKEN->S_TOKENLIST->LEXEME, E_TXTLIT_F(_T("&")))) {
       ALT->DISCARD = 1;
       Synrule->CURRTOKEN = (struct TOKEN*)Synrule->CURRTOKEN->S_TOKENLIST;
       }
       }
       else {
       if (E_TXTEQL_F(Synrule->CURRTOKEN->LEXEME, E_TXTLIT_F(_T("@")))) {
       Synrule->CURRTOKEN = (struct TOKEN*)Synrule->CURRTOKEN->S_TOKENLIST;
       if (E_TXTEQL_F(Synrule->CURRTOKEN->LEXEME, E_TXTLIT_F(_T("IDENT")))) {
       ALT->TERMINALTYPE = 3;
       }
       if (E_TXTEQL_F(Synrule->CURRTOKEN->LEXEME, E_TXTLIT_F(_T("FLOAT")))) {
       ALT->TERMINALTYPE = 2;
       }
       if (E_TXTEQL_F(Synrule->CURRTOKEN->LEXEME, E_TXTLIT_F(_T("INT")))) {
       ALT->TERMINALTYPE = 1;
       }
       if (E_TXTEQL_F(Synrule->CURRTOKEN->LEXEME, E_TXTLIT_F(_T("STR")))) {
       ALT->TERMINALTYPE = 4;
       }
       }
       else {
       AREF= c_ALTREF();
       AREF->ALTSUBRULE = (struct ALTPART*)ALT;
       AFIX = (struct RULFIXUP*)Synrule->F_RULFIXUPS;
next0001:
       if ( !  ( AFIX != 0 ) ) {
       goto done0001;
       }
       if (E_TXTEQL_F(Synrule->CURRTOKEN->LEXEME, AFIX->RULENAME)) {
       goto done0001;
       }
       AFIX = (struct RULFIXUP*)AFIX->S_RULFIXUPS;
       goto next0001;
done0001:
       if (AFIX == 0) {
       AFIX= c_RULFIXUP();
       E_TXTASG_R(&AFIX->RULENAME, Synrule->CURRTOKEN->LEXEME);
       AFIX->S_RULFIXUPS = (struct RULFIXUP*)Synrule->F_RULFIXUPS;
       Synrule->F_RULFIXUPS = (struct RULFIXUP*)AFIX;
       }
       else {
       AREF->S_ALTREFS = (struct ALTREF*)AFIX->F_ALTREFS;
       }
       AFIX->F_ALTREFS = (struct ALTREF*)AREF;
       if (E_TXTEQL_F(Synrule->CURRTOKEN->S_TOKENLIST->LEXEME, E_TXTLIT_F(_T("&")))) {
       ALT->DISCARD = 1;
       Synrule->CURRTOKEN = (struct TOKEN*)Synrule->CURRTOKEN->S_TOKENLIST;
       }
       }
       }
       Synrule->CURRTOKEN = (struct TOKEN*)Synrule->CURRTOKEN->S_TOKENLIST;
       if (E_TXTEQL_F(Synrule->CURRTOKEN->LEXEME, E_TXTLIT_F(_T("#")))) {
       Synrule->CURRTOKEN = (struct TOKEN*)Synrule->CURRTOKEN->S_TOKENLIST;
       ALT->SCRIPTREF = ACHAR_F(Synrule->CURRTOKEN->LEXEME, 1)-48;
       Synrule->CURRTOKEN = (struct TOKEN*)Synrule->CURRTOKEN->S_TOKENLIST;
       }
       if (PART->F_ALTS == 0) {
       PART->F_ALTS = (struct ALTPART*)ALT;
       ALT->SEQNUM = 1;
       }
       else {
       LAST = (struct ALTPART*)PART->F_ALTS;
next0002:
       if ( !  ( LAST->S_ALTS != 0 ) ) {
       goto done0002;
       }
       LAST = (struct ALTPART*)LAST->S_ALTS;
       goto next0002;
done0002:
       LAST->S_ALTS = (struct ALTPART*)ALT;
       ALT->SEQNUM = LAST->SEQNUM+1;
       }
       goto retlbl;
retlbl:
       return;
}
void READRULE() {
struct SYNRULE* ARULE= 0;
struct RULEPART* APART= 0;
struct RULFIXUP* AFIX= 0;
struct RULEPART* LASTPART= 0;
struct TOKEN* LAST= 0;
struct TOKEN* CLEAN= 0;
       ARULE= c_SYNRULE();
       E_TXTASG_R(&ARULE->RULENAME, Synrule->CURRTOKEN->LEXEME);
       Synrule->CURRTOKEN = (struct TOKEN*)Synrule->CURRTOKEN->S_TOKENLIST;
       if (E_TXTEQL_F(Synrule->CURRTOKEN->LEXEME, E_TXTLIT_F(_T("~")))) {
       Synrule->CURRTOKEN = (struct TOKEN*)Synrule->CURRTOKEN->S_TOKENLIST;
       ARULE->KEYRULE = 0;
       AFIX = (struct RULFIXUP*)Synrule->F_RULFIXUPS;
next0001:
       if ( !  ( AFIX != 0 ) ) {
       goto done0001;
       }
       if (E_TXTEQL_F(ARULE->RULENAME, AFIX->RULENAME)) {
       goto done0001;
       }
       else {
       AFIX = (struct RULFIXUP*)AFIX->S_RULFIXUPS;
       }
       goto next0001;
done0001:
       if (AFIX == 0) {
       AFIX= c_RULFIXUP();
       E_TXTASG_R(&AFIX->RULENAME, ARULE->RULENAME);
       AFIX->S_RULFIXUPS = (struct RULFIXUP*)Synrule->F_RULFIXUPS;
       Synrule->F_RULFIXUPS = (struct RULFIXUP*)AFIX;
       }
       AFIX->THERULE = (struct SYNRULE*)ARULE;
       }
       else {
       ARULE->KEYRULE = 1;
       ARULE->S_SYNRULES = (struct SYNRULE*)Synrule->F_SYNRULES;
       Synrule->F_SYNRULES = (struct SYNRULE*)ARULE;
       ARULE->RULETYPE = 1;
       if (Synrule->CURRTOKEN->TOKENTYPE == 1) {
       ARULE->RULETYPE = ACHAR_F(Synrule->CURRTOKEN->LEXEME, 1)-48;
       Synrule->CURRTOKEN = (struct TOKEN*)Synrule->CURRTOKEN->S_TOKENLIST;
       }
       }
next0002:
       if ( !  ( E_TXTNEQ_F(Synrule->CURRTOKEN->LEXEME, E_TXTLIT_F(_T("!"))) ) ) {
       goto done0002;
       }
       APART = (struct RULEPART*)READPART();
       if (ARULE->F_PARTS == 0) {
       ARULE->F_PARTS = (struct RULEPART*)APART;
       }
       else {
       LASTPART = (struct RULEPART*)ARULE->F_PARTS;
next0003:
       if ( !  ( LASTPART->S_PARTS != 0 ) ) {
       goto done0003;
       }
       LASTPART = (struct RULEPART*)LASTPART->S_PARTS;
       goto next0003;
done0003:
       LASTPART->S_PARTS = (struct RULEPART*)APART;
       }
       goto next0002;
done0002:
       Synrule->CURRTOKEN = (struct TOKEN*)Synrule->CURRTOKEN->S_TOKENLIST;
       if (Synrule->CURRTOKEN != 0) {
       if (E_TXTEQL_F(Synrule->CURRTOKEN->LEXEME, E_TXTLIT_F(_T("!")))) {
       Synrule->CURRTOKEN = (struct TOKEN*)Synrule->CURRTOKEN->S_TOKENLIST;
       FIXUPSUBRULES();
       }
       }
       LAST = (struct TOKEN*)EASElex->F_TOKENLIST;
       EASElex->F_TOKENLIST = (struct TOKEN*)Synrule->CURRTOKEN;
next0004:
       if ( !  ( LAST != EASElex->F_TOKENLIST ) ) {
       goto done0004;
       }
       CLEAN = (struct TOKEN*)LAST;
       LAST = (struct TOKEN*)LAST->S_TOKENLIST;
       E_TXTASG_R(&CLEAN->LEXEME, E_TXTLIT_F(_T("""")));
       d_TOKEN(CLEAN);
       goto next0004;
done0004:
       goto retlbl;
retlbl:
       return;
}
void READSYNTAX(Etxt* FILENAME) {
Etxt* RULELINE= 0;
int LEN= 0;
struct EASEPROC* APROC= 0;
E_TXTINC_R(FILENAME);
       OPENI_R(5, FILENAME);
       USE_R(5, 1);
       easlib->UIB_R->EOF_V = 1;
next0001:
       if ( !  ( easlib->UIB_R->EOF_V != 2 ) ) {
       goto done0001;
       }
       E_TXTASG_R(&RULELINE, RDT_F(easlib->UIB_R->RRECLEN_V));
       LEN = LENGTH_F(RULELINE);
       ANALYZE(RULELINE, LEN, 0);
       if (EASElex->F_TOKENLIST != 0) {
       Synrule->CURRTOKEN = (struct TOKEN*)EASElex->F_TOKENLIST;
       READRULE();
       }
       RDL_R();
       goto next0001;
done0001:
       CLOSE_R(5);
E_TXTDEL_R(FILENAME);
E_TXTDEL_R(RULELINE);
       return;
}

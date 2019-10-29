#include "stdafx.h"
#include "malloc.h"
#include "libopts.h"
#include "math.h"
#include "EASEpars.h"

void EASEpars_addTypes() {
#ifdef _SRCLINE
addEType(E_TXTLIT_F(_T("SRCLINE")), 3005,  105, 0);
#endif
#ifdef _LCLDEF
addEType(E_TXTLIT_F(_T("LCLDEF")), 3005,  104, 0);
#endif
#ifdef _EASEPROC
addEType(E_TXTLIT_F(_T("EASEPROC")), 3005,  103, 0);
#endif
#ifdef _STMT
addEType(E_TXTLIT_F(_T("STMT")), 3005,  102, 0);
#endif
#ifdef _NODE
addEType(E_TXTLIT_F(_T("NODE")), 3005,  101, 0);
#endif
}
EASEpars_sys* EASEpars;

void EASEpars_init() {
EASEpars = (EASEpars_sys*)E_CREATE_F( 0,3005, sizeof(EASEpars_sys));
EASEpars_sets();
EASEpars_addTypes();
}
void EASEpars_sets() {
       return;
}
void d_NODE(struct NODE*& EPTR) {
       E_TXTASG_R(&EPTR->NODENAME, 0);
       E_DESTROY_R(EPTR);
       EPTR = (struct NODE*)0;
       return;
}
struct NODE* c_NODE() {
struct NODE* EPTR= 0;
struct NODE* rval = 0;
       EPTR = (struct NODE*)E_CREATE_F(3005, 101, Z_NODE);
       rval = (struct NODE*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void d_STMT(struct STMT*& EPTR) {
       E_DESTROY_R(EPTR);
       EPTR = (struct STMT*)0;
       return;
}
struct STMT* c_STMT() {
struct STMT* EPTR= 0;
struct STMT* rval = 0;
       EPTR = (struct STMT*)E_CREATE_F(3005, 102, Z_STMT);
       rval = (struct STMT*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void d_EASEPROC(struct EASEPROC*& EPTR) {
       E_DESTROY_R(EPTR);
       EPTR = (struct EASEPROC*)0;
       return;
}
struct EASEPROC* c_EASEPROC() {
struct EASEPROC* EPTR= 0;
struct EASEPROC* rval = 0;
       EPTR = (struct EASEPROC*)E_CREATE_F(3005, 103, Z_EASEPROC);
       rval = (struct EASEPROC*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void d_LCLDEF(struct LCLDEF*& EPTR) {
       E_TXTASG_R(&EPTR->LDEFNAME, 0);
       E_DESTROY_R(EPTR);
       EPTR = (struct LCLDEF*)0;
       return;
}
struct LCLDEF* c_LCLDEF() {
struct LCLDEF* EPTR= 0;
struct LCLDEF* rval = 0;
       EPTR = (struct LCLDEF*)E_CREATE_F(3005, 104, Z_LCLDEF);
       rval = (struct LCLDEF*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void d_SRCLINE(struct SRCLINE*& EPTR) {
       E_TXTASG_R(&EPTR->LTXT, 0);
       E_DESTROY_R(EPTR);
       EPTR = (struct SRCLINE*)0;
       return;
}
struct SRCLINE* c_SRCLINE() {
struct SRCLINE* EPTR= 0;
struct SRCLINE* rval = 0;
       EPTR = (struct SRCLINE*)E_CREATE_F(3005, 105, Z_SRCLINE);
       rval = (struct SRCLINE*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
struct LCLDEF* FINDLCLDEF(Etxt* VARNAME) {
struct LCLDEF* ALCL= 0;
struct LCLDEF* LAST= 0;
struct LCLDEF* rval = 0;
E_TXTINC_R(VARNAME);
       ALCL = (struct LCLDEF*)EASEmain->CURRPROC->F_LCLDEFS;
next0001:
       if ( !  ( ALCL != 0 ) ) {
       goto done0001;
       }
       if (E_TXTEQL_F(ALCL->LDEFNAME, VARNAME)) {
       goto done0001;
       }
       LAST = (struct LCLDEF*)ALCL;
       ALCL = (struct LCLDEF*)ALCL->S_LCLDEFS;
       goto next0001;
done0001:
       if (ALCL == 0) {
       ALCL= c_LCLDEF();
       if (LAST != 0) {
       LAST->S_LCLDEFS = (struct LCLDEF*)ALCL;
       }
       else {
       EASEmain->CURRPROC->F_LCLDEFS = (struct LCLDEF*)ALCL;
       }
       E_TXTASG_R(&ALCL->LDEFNAME, VARNAME);
       }
       rval = (struct LCLDEF*)ALCL;
goto retlbl;
retlbl:
E_TXTDEL_R(VARNAME);
       return rval;
}
void UPDATELCL(struct LCLDEF* ALCL, struct NODE* MODENODE, struct NODE* DIMNODE) {
struct DICTUSE* AUSE= 0;
       if (ALCL->LDEFTYPE != 0) {
       EASERR(1019, ALCL->LDEFNAME);
       goto retlbl;
       }
       if (MODENODE != 0) {
       if (MODENODE->MATCHNUM == 4 & MODENODE->F_SUBNODES != 0) {
       AUSE = (struct DICTUSE*)FINDSPECUSE_F(MODENODE->START->DICTREF, 2);
       if (AUSE == 0) {
       EASERR(1002, MODENODE->START->LEXEME);
       }
       else {
       ALCL->LDEFTYPE = (struct ENTITYTYPE*)AUSE->USEENTITY;
       }
       }
       else {
       ALCL->LDEFTYPE = (struct ENTITYTYPE*)EASEents->E_BUILTINS[MODENODE->MATCHNUM];
       }
       }
       if (ALCL->LDEFTYPE == 0) {
       EASERR(-1002, ALCL->LDEFNAME);
       ALCL->LDEFTYPE = (struct ENTITYTYPE*)EASEents->E_BUILTINS[1];
       }
       if (DIMNODE != 0) {
       ALCL->LDEFDIM = ACHAR_F(DIMNODE->START->LEXEME, 1)-48;
       }
       goto retlbl;
retlbl:
       return;
}
void STMTDEFFUNC(struct STMT* ASTMT) {
struct NODE* ANODE= 0;
struct LCLDEF* ALCL= 0;
struct NODE* VARNODE= 0;
struct DICTENTRY* DREF= 0;
struct DICTUSE* AUSE= 0;
struct ENTITYTYPE* RTYPE= 0;
       ANODE = (struct NODE*)ASTMT->F_PARSENODES;
       ANODE = (struct NODE*)ANODE->S_NODES;
       if (ANODE != ASTMT->L_PARSENODES) {
       VARNODE = (struct NODE*)ANODE->F_SUBNODES;
       }
next0001:
       if ( !  ( VARNODE != 0 ) ) {
       goto done0001;
       }
       ALCL = (struct LCLDEF*)FINDLCLDEF(VARNODE->F_SUBNODES->START->LEXEME);
       ALCL->LPARAM = 1;
       VARNODE = (struct NODE*)VARNODE->S_NODES;
       goto next0001;
done0001:
       ALCL = (struct LCLDEF*)FINDLCLDEF(E_TXTLIT_F(_T("rval")));
       ANODE = (struct NODE*)ASTMT->L_PARSENODES->F_SUBNODES->F_SUBNODES;
       if (ANODE->MATCHNUM == 4 & ANODE->F_SUBNODES != 0) {
       DREF = (struct DICTENTRY*)FINDDICTENTRY_F(ANODE->START->LEXEME);
       AUSE = (struct DICTUSE*)FINDSPECUSE_F(DREF, 2);
       if (AUSE != 0) {
       RTYPE = (struct ENTITYTYPE*)AUSE->USEENTITY;
       }
       }
       else {
       RTYPE = (struct ENTITYTYPE*)EASEents->E_BUILTINS[ANODE->MATCHNUM];
       }
       if (RTYPE == 0) {
       EASERR(1002, ANODE->START->LEXEME);
       RTYPE = (struct ENTITYTYPE*)EASEents->E_BUILTINS[1];
       }
       ALCL->LDEFTYPE = (struct ENTITYTYPE*)RTYPE;
       ALCL->LRET = 1;
       goto retlbl;
retlbl:
       return;
}
void STMTDEFRTN(struct STMT* ASTMT) {
struct NODE* ANODE= 0;
struct LCLDEF* ALCL= 0;
struct NODE* VARNODE= 0;
int YLD= 0;
       ANODE = (struct NODE*)ASTMT->F_PARSENODES;
       ANODE = (struct NODE*)ANODE->S_NODES;
next0001:
       if ( !  ( ANODE != 0 ) ) {
       goto done0001;
       }
       VARNODE = (struct NODE*)ANODE->F_SUBNODES;
       if (VARNODE->SCRIPTCODE != 0) {
       YLD = 1;
       }
next0002:
       if ( !  ( VARNODE != 0 ) ) {
       goto done0002;
       }
       ALCL = (struct LCLDEF*)FINDLCLDEF(VARNODE->F_SUBNODES->START->LEXEME);
       ALCL->LPARAM = 1;
       ALCL->LYLD = YLD;
       VARNODE = (struct NODE*)VARNODE->S_NODES;
       goto next0002;
done0002:
       ANODE = (struct NODE*)ANODE->S_NODES;
       goto next0001;
done0001:
       goto retlbl;
retlbl:
       return;
}
void STMTDEFVAR(struct STMT* ASTMT) {
struct NODE* ANODE= 0;
struct LCLDEF* ALCL= 0;
struct NODE* VARNODE= 0;
struct NODE* MODENODE= 0;
struct NODE* DIMNODE= 0;
       ANODE = (struct NODE*)ASTMT->F_PARSENODES;
       VARNODE = (struct NODE*)ANODE->F_SUBNODES;
       ANODE = (struct NODE*)ANODE->S_NODES;
next0001:
       if ( !  ( ANODE != 0 ) ) {
       goto done0001;
       }
       if (ANODE->MATCHNUM == 1) {
       DIMNODE = (struct NODE*)ANODE;
       }
       else {
       MODENODE = (struct NODE*)ANODE->F_SUBNODES;
       }
       ANODE = (struct NODE*)ANODE->S_NODES;
       goto next0001;
done0001:
next0002:
       if ( !  ( VARNODE != 0 ) ) {
       goto done0002;
       }
       ALCL = (struct LCLDEF*)FINDLCLDEF(VARNODE->START->LEXEME);
       UPDATELCL(ALCL, MODENODE, DIMNODE);
       if (ASTMT->L_PARSENODES->SCRIPTCODE != 0) {
       ALCL->ISSUBPROG = 1;
       }
       VARNODE = (struct NODE*)VARNODE->S_NODES;
       goto next0002;
done0002:
       goto retlbl;
retlbl:
       return;
}
void DESTROYNODES(struct NODE* ANODE) {
struct NODE* LASTNODE= 0;
       if (ANODE == EASEpars->F_NODES) {
       EASEpars->F_NODES = (struct NODE*)0;
       LASTNODE = (struct NODE*)ANODE;
       }
next0001:
       if ( !  ( ANODE != 0 ) ) {
       goto done0001;
       }
       if (ANODE->F_SUBNODES != 0) {
       DESTROYNODES(ANODE->F_SUBNODES);
       }
       LASTNODE = (struct NODE*)ANODE;
       ANODE = (struct NODE*)ANODE->S_NODES;
       d_NODE(LASTNODE);
       goto next0001;
done0001:
       goto retlbl;
retlbl:
       return;
}
void SUBSTITUT(struct TOKEN* ATOKEN) {
struct TOKEN* STOKEN= 0;
struct DICTENTRY* DREF= 0;
next0001:
       if ( !  ( ATOKEN != 0 ) ) {
       goto done0001;
       }
       if (ATOKEN->TOKENTYPE == 3) {
       DREF = (struct DICTENTRY*)ATOKEN->DICTREF;
       if (DREF->F_SUBST != 0) {
       if (DREF->F_SUBST == DREF->L_SUBST) {
       STOKEN = (struct TOKEN*)DREF->F_SUBST;
       ATOKEN->DICTREF = (struct DICTENTRY*)STOKEN->DICTREF;
       ATOKEN->TOKENTYPE = STOKEN->TOKENTYPE;
       E_TXTASG_R(&ATOKEN->LEXEME, STOKEN->LEXEME);
       }
       }
       }
       ATOKEN = (struct TOKEN*)ATOKEN->S_TOKENLIST;
       goto next0001;
done0001:
       goto retlbl;
retlbl:
       return;
}
void NAMECHECK(struct EASEPROC* APROC, struct STMT* ASTMT) {
struct DICTUSE* AUSE= 0;
struct ENTITYTYPE* ETYPE= 0;
Etxt* PROCNAME= 0;
       E_TXTASG_R(&PROCNAME, ASTMT->F_PARSENODES->START->LEXEME);
       if (ASTMT->STMTNUM != 1) {
       EASERR(1021, PROCNAME);
       }
       AUSE = (struct DICTUSE*)FINDSPECUSE_F(FINDDICTENTRY_F(PROCNAME), 3);
       if (AUSE != 0) {
       goto retlbl;
       }
       EASERR(-1019, PROCNAME);
       AUSE = (struct DICTUSE*)FINDSPECUSE_F(APROC->PDICTREF, 3);
       ETYPE = (struct ENTITYTYPE*)AUSE->USEENTITY;
       APROC->PDICTREF = (struct DICTENTRY*)FINDDICTENTRY_F(PROCNAME);
       if (FINDSPECUSE_F(APROC->PDICTREF, 3) == 0) {
       AUSE = (struct DICTUSE*)MAKEUSE_F(APROC->PDICTREF, 3);
       AUSE->USEENTITY = (struct ENTITYTYPE*)ETYPE;
       }
       goto retlbl;
retlbl:
E_TXTDEL_R(PROCNAME);
       return;
}
void FILENODE(struct NODE* ANODE) {
       if (EASEpars->F_NODES == 0) {
       EASEpars->F_NODES = (struct NODE*)ANODE;
       }
       else {
       EASEpars->L_NODES->S_NODES = (struct NODE*)ANODE;
       }
       EASEpars->L_NODES = (struct NODE*)ANODE;
       goto retlbl;
retlbl:
       return;
}
void PARSE(struct EASEPROC* APROC) {
Etxt* LINE= 0;
struct TOKEN* ATOKEN= 0;
struct TOKEN* SAVEF= 0;
struct TOKEN* SAVEL= 0;
struct STMT* ASTMT= 0;
int N= 0;
struct SRCLINE* PFMT= 0;
struct SRCLINE* LFMT= 0;
struct SYNRULE* ARULE= 0;
       Script->SCRIPTLEVEL = 0;
       EASEpars->STMTSTATE = 1;
next0001:
       if ( !  ( EASElex->F_TOKENLIST == 0 ) ) {
       goto done0001;
       }
       E_TXTASG_R(&LINE, NEXTLINE_F());
       if (E_TXTEQL_F(LINE, 0)) {
       goto retlbl;
       }
       ANALYZE(LINE, LENGTH_F(LINE), 1);
       SUBSTITUT(EASElex->F_TOKENLIST);
       goto next0001;
done0001:
next0002:
       if ( !  ( EASElex->F_TOKENLIST != 0 ) ) {
       goto done0002;
       }
       ATOKEN = (struct TOKEN*)EASElex->F_TOKENLIST;
       ASTMT = (struct STMT*)PARSESTMT_F();
       if (ASTMT != 0) {
       ASTMT->F_TOKENS = (struct TOKEN*)ATOKEN;
       ASTMT->SCRIPTDEPTH = ATOKEN->SCRIPTED;
next0003:
       if ( !  ( ATOKEN != 0 ) ) {
       goto done0003;
       }
       if (ATOKEN->PARSED == 0) {
       goto done0003;
       }
       EASEpars->LASTPARSED = (struct TOKEN*)ATOKEN;
       ATOKEN = (struct TOKEN*)ATOKEN->S_TOKENLIST;
       goto next0003;
done0003:
       ASTMT->L_TOKENS = (struct TOKEN*)EASEpars->LASTPARSED;
       if (ASTMT->SCRIPTDEPTH == 0) {
       EASEpars->STMTSTATE = EASEpars->CTLSTATES[EASEpars->STMTSTATE][ASTMT->STMTRULE->RULETYPE];
       }
       if (APROC->F_STMTS == 0) {
       APROC->F_STMTS = (struct STMT*)ASTMT;
       ASTMT->STMTNUM = 1;
       }
       else {
       APROC->L_STMTS->S_STMTS = (struct STMT*)ASTMT;
       ASTMT->STMTNUM = APROC->L_STMTS->STMTNUM+1;
       }
       ASTMT->P_STMTS = (struct STMT*)APROC->L_STMTS;
       APROC->L_STMTS = (struct STMT*)ASTMT;
       if (E_TXTEQL_F(ASTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("MAIN")))) {
       NAMECHECK(APROC, ASTMT);
       STMTDEFRTN(ASTMT);
       }
       if (E_TXTEQL_F(ASTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("DCLRTN")))) {
       NAMECHECK(APROC, ASTMT);
       STMTDEFRTN(ASTMT);
       }
       if (E_TXTEQL_F(ASTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("DCLFUNC")))) {
       NAMECHECK(APROC, ASTMT);
       STMTDEFFUNC(ASTMT);
       }
       if (E_TXTEQL_F(ASTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("DEFVAR")))) {
       STMTDEFVAR(ASTMT);
       }
       if (E_TXTEQL_F(ASTMT->STMTRULE->RULENAME, E_TXTLIT_F(_T("PRINTN")))) {
       if (ASTMT->F_PARSENODES->MATCHNUM == 2) {
       N = 1;
       }
       else {
       N = ACHAR_F(ASTMT->F_PARSENODES->START->LEXEME, 1)-48;
       }
next0004:
       if ( !  ( N > 0 ) ) {
       goto done0004;
       }
       N = N-1;
       PFMT= c_SRCLINE();
       E_TXTASG_R(&PFMT->LTXT, NEXTLINE_F());
       if (ASTMT->F_FMTLINES == 0) {
       ASTMT->F_FMTLINES = (struct SRCLINE*)PFMT;
       }
       else {
       LFMT = (struct SRCLINE*)ASTMT->F_FMTLINES;
next0005:
       if ( !  ( LFMT->S_SRCLINES != 0 ) ) {
       goto done0005;
       }
       LFMT = (struct SRCLINE*)LFMT->S_SRCLINES;
       goto next0005;
done0005:
       LFMT->S_SRCLINES = (struct SRCLINE*)PFMT;
       }
       goto next0004;
done0004:
;      }
       EASElex->F_TOKENLIST = (struct TOKEN*)EASEpars->LASTPARSED->S_TOKENLIST;
       EASEpars->LASTPARSED->S_TOKENLIST = (struct TOKEN*)0;
       if (EASElex->F_TOKENLIST == 0) {
       EASElex->L_TOKENLIST = (struct TOKEN*)0;
       }
       if (ASTMT->F_PARSENODES != 0) {
       SAVEF = (struct TOKEN*)EASElex->F_TOKENLIST;
       EASElex->F_TOKENLIST = (struct TOKEN*)0;
       SAVEL = (struct TOKEN*)EASElex->L_TOKENLIST;
       EASElex->L_TOKENLIST = (struct TOKEN*)0;
       STMTSCRIPT(ASTMT);
       if (EASEpars->STMTSTATE == 4) {
       SCRIPTLOOP();
       }
       if (EASElex->L_TOKENLIST != 0) {
       EASElex->L_TOKENLIST->S_TOKENLIST = (struct TOKEN*)SAVEF;
       }
       else {
       EASElex->F_TOKENLIST = (struct TOKEN*)SAVEF;
       }
       if (SAVEL != 0) {
       EASElex->L_TOKENLIST = (struct TOKEN*)SAVEL;
       }
       }
       if (EASEpars->STMTSTATE > 2) {
       EASEpars->STMTSTATE = 1;
       }
       }
       else {
       EASERR(1001, EASElex->F_TOKENLIST->LEXEME);
       ARULE = (struct SYNRULE*)0;
next0006:
       if ( !  ( ARULE == 0 ) ) {
       goto done0006;
       }
       EASElex->F_TOKENLIST = (struct TOKEN*)EASElex->F_TOKENLIST->S_TOKENLIST;
next0007:
       if ( !  ( EASElex->F_TOKENLIST == 0 ) ) {
       goto done0007;
       }
       E_TXTASG_R(&LINE, NEXTLINE_F());
       if (E_TXTEQL_F(LINE, 0)) {
       goto done0007;
       }
       ANALYZE(LINE, LENGTH_F(LINE), 1);
       SUBSTITUT(EASElex->F_TOKENLIST);
       goto next0007;
done0007:
       if (EASElex->F_TOKENLIST == 0) {
       goto done0006;
       }
       ARULE = (struct SYNRULE*)EASElex->F_TOKENLIST->DICTREF->F_ENTRULES;
       goto next0006;
done0006:
;      }
next0008:
       if ( !  ( EASElex->F_TOKENLIST == 0 ) ) {
       goto done0008;
       }
       E_TXTASG_R(&LINE, NEXTLINE_F());
       if (E_TXTEQL_F(LINE, 0)) {
       goto done0008;
       }
       ANALYZE(LINE, LENGTH_F(LINE), 1);
       SUBSTITUT(EASElex->F_TOKENLIST);
       goto next0008;
done0008:
       if (EASElex->F_TOKENLIST == 0) {
       EASElex->L_TOKENLIST = (struct TOKEN*)0;
       }
       goto next0002;
done0002:
       goto retlbl;
retlbl:
E_TXTDEL_R(LINE);
       return;
}
struct STMT* PARSESTMT_F() {
struct TOKEN* ATOKEN= 0;
struct DICTENTRY* AENTRY= 0;
struct SYNRULE* ARULE= 0;
struct RULEPART* APART= 0;
Etxt* LINE= 0;
struct STMT* ASTMT= 0;
int SUCCESS= 0;
struct TOKEN* LASTCHANCE= 0;
struct STMT* rval = 0;
       EASEpars->PARSETOKEN = (struct TOKEN*)EASElex->F_TOKENLIST;
       AENTRY = (struct DICTENTRY*)EASEpars->PARSETOKEN->DICTREF;
       ARULE = (struct SYNRULE*)AENTRY->F_ENTRULES;
       if (ARULE == 0 & EASEpars->PARSETOKEN->TOKENTYPE == 3) {
       LASTCHANCE = (struct TOKEN*)EASElex->F_TOKENLIST;
       AENTRY = (struct DICTENTRY*)FINDDICTENTRY_F(E_TXTLIT_F(_T("LET")));
       EASEpars->PARSETOKEN= c_TOKEN();
       EASEpars->PARSETOKEN->DICTREF = (struct DICTENTRY*)AENTRY;
       EASEpars->PARSETOKEN->S_TOKENLIST = (struct TOKEN*)EASElex->F_TOKENLIST;
       EASElex->F_TOKENLIST = (struct TOKEN*)EASEpars->PARSETOKEN;
       ARULE = (struct SYNRULE*)AENTRY->F_ENTRULES;
       }
next0001:
       if ( !  ( ARULE != 0 ) ) {
       goto done0001;
       }
       SUCCESS = MATCHRULE_F(ARULE);
       if (SUCCESS == 0) {
       DESTROYNODES(EASEpars->F_NODES);
       if (LASTCHANCE != 0) {
       EASElex->F_TOKENLIST = (struct TOKEN*)LASTCHANCE->S_TOKENLIST;
       rval = (struct STMT*)0;
goto retlbl;
       }
       EASEpars->PARSETOKEN = (struct TOKEN*)EASElex->F_TOKENLIST;
       ARULE = (struct SYNRULE*)ARULE->S_ENTRULES;
       }
       else {
       ASTMT= c_STMT();
       ASTMT->STMTRULE = (struct SYNRULE*)ARULE;
       ASTMT->STMTLINE = EASEmain->CURRLINE;
       if (EASEpars->F_NODES != 0) {
       ASTMT->F_PARSENODES = (struct NODE*)EASEpars->F_NODES;
       ASTMT->L_PARSENODES = (struct NODE*)EASEpars->L_NODES;
       EASEpars->F_NODES = (struct NODE*)0;
       EASEpars->L_NODES = (struct NODE*)0;
       }
       rval = (struct STMT*)ASTMT;
goto retlbl;
       }
       goto next0001;
done0001:
       rval = (struct STMT*)0;
goto retlbl;
retlbl:
E_TXTDEL_R(LINE);
       return rval;
}
int MATCHRULE_F(struct SYNRULE* ARULE) {
struct RULEPART* APART= 0;
int SUCCESS= 0;
int FOUNDPART= 0;
int rval = 0;
       APART = (struct RULEPART*)ARULE->F_PARTS;
next0001:
       if ( !  ( APART != 0 ) ) {
       goto done0001;
       }
       SUCCESS = MATCHRULEPART_F(APART);
       if (SUCCESS == 0) {
       if (APART->REQUIRED != 0) {
       goto done0001;
       }
       else {
       if (FOUNDPART != 0) {
       SUCCESS = 1;
       }
       }
       }
       else {
       FOUNDPART = 1;
       }
       APART = (struct RULEPART*)APART->S_PARTS;
       goto next0001;
done0001:
       rval = (int)SUCCESS;
goto retlbl;
retlbl:
       return rval;
}
int MATCHRULEPART_F(struct RULEPART* APART) {
struct ALTPART* AALT= 0;
int SUCCESS= 0;
int FOUND1= 0;
int rval = 0;
       AALT = (struct ALTPART*)APART->F_ALTS;
next0001:
       if ( !  ( AALT != 0 ) ) {
       goto done0001;
       }
       SUCCESS = MATCHPARTALT_F(AALT);
       if (SUCCESS != 0) {
       if (APART->REPEATS != 0) {
       FOUND1 = 1;
next0002:
       if ( !  ( SUCCESS != 0 ) ) {
       goto done0002;
       }
       SUCCESS = MATCHPARTALT_F(AALT);
       goto next0002;
done0002:
       SUCCESS = FOUND1;
       }
       AALT = (struct ALTPART*)0;
       }
       else {
       AALT = (struct ALTPART*)AALT->S_ALTS;
       }
       goto next0001;
done0001:
       rval = (int)SUCCESS;
goto retlbl;
retlbl:
       return rval;
}
int MATCHPARTALT_F(struct ALTPART* AALT) {
struct TOKEN* ATOKEN= 0;
Etxt* LINE= 0;
struct NODE* ANODE= 0;
struct NODE* LASTNODE= 0;
struct DICTENTRY* AENTRY= 0;
int TTYPE= 0;
int SUCCESS= 0;
int FOUND1= 0;
int rval = 0;
       SUCCESS = 0;
       if (EASEpars->PARSETOKEN == 0) {
       ATOKEN = (struct TOKEN*)EASElex->L_TOKENLIST;
next0001:
       if ( !  ( ATOKEN->S_TOKENLIST == 0 ) ) {
       goto done0001;
       }
       E_TXTASG_R(&LINE, NEXTLINE_F());
       if (E_TXTEQL_F(LINE, 0)) {
       rval = (int)SUCCESS;
goto retlbl;
       }
       ANALYZE(LINE, LENGTH_F(LINE), 1);
       SUBSTITUT(EASElex->F_TOKENLIST);
       goto next0001;
done0001:
       EASEpars->PARSETOKEN = (struct TOKEN*)ATOKEN->S_TOKENLIST;
       }
       if (AALT->SUBRULE != 0) {
       LASTNODE = (struct NODE*)EASEpars->L_NODES;
       ATOKEN = (struct TOKEN*)EASEpars->PARSETOKEN;
       SUCCESS = MATCHRULE_F(AALT->SUBRULE);
       if (SUCCESS == 0) {
       EASEpars->PARSETOKEN = (struct TOKEN*)ATOKEN;
next0002:
       if ( !  ( ATOKEN != 0 ) ) {
       goto done0002;
       }
       if (ATOKEN->PARSED == 0) {
       goto done0002;
       }
       ATOKEN->PARSED = 0;
       ATOKEN = (struct TOKEN*)ATOKEN->S_TOKENLIST;
       goto next0002;
done0002:
       if (LASTNODE != 0) {
       if (EASEpars->L_NODES != LASTNODE) {
       EASEpars->L_NODES = (struct NODE*)LASTNODE;
       ANODE = (struct NODE*)EASEpars->L_NODES->S_NODES;
       EASEpars->L_NODES->S_NODES = (struct NODE*)0;
       DESTROYNODES(ANODE);
       }
       }
       else {
       if (EASEpars->F_NODES != 0) {
       DESTROYNODES(EASEpars->F_NODES);
       EASEpars->F_NODES = (struct NODE*)0;
       EASEpars->L_NODES = (struct NODE*)0;
       }
       }
       }
       else {
       if (AALT->DISCARD == 0) {
       ANODE= c_NODE();
       ANODE->START = (struct TOKEN*)ATOKEN;
next0003:
       if ( !  ( ATOKEN != 0 ) ) {
       goto done0003;
       }
       if (ATOKEN->PARSED == 0) {
       goto done0003;
       }
       else {
       ANODE->END = (struct TOKEN*)ATOKEN;
       ATOKEN = (struct TOKEN*)ATOKEN->S_TOKENLIST;
       }
       goto next0003;
done0003:
       ANODE->MATCHNUM = AALT->SEQNUM;
       ANODE->SCRIPTCODE = AALT->SCRIPTREF;
       E_TXTASG_R(&ANODE->NODENAME, AALT->SUBRULE->RULENAME);
       STRUCTNODES(ANODE, LASTNODE);
       FILENODE(ANODE);
       }
       }
       }
       else {
       AENTRY = (struct DICTENTRY*)EASEpars->PARSETOKEN->DICTREF;
       TTYPE = AALT->TERMINALTYPE;
       if (TTYPE == 0) {
       if (AALT->DICTENT == AENTRY) {
       goto MATCHED;
       }
       }
       if (TTYPE == 1) {
       if (EASEpars->PARSETOKEN->TOKENTYPE == 1) {
       goto MATCHED;
       }
       }
       if (TTYPE == 2) {
       if (EASEpars->PARSETOKEN->TOKENTYPE == 1 | EASEpars->PARSETOKEN->TOKENTYPE == 2) {
       goto MATCHED;
       }
       }
       if (TTYPE == 3) {
       if (EASEpars->PARSETOKEN->TOKENTYPE == 3) {
       goto MATCHED;
       }
       }
       if (TTYPE == 4) {
       if (EASEpars->PARSETOKEN->TOKENTYPE == 4) {
       goto MATCHED;
       }
       }
       if (TTYPE == 5) {
       if (AALT->DICTENT == AENTRY) {
       goto MATCHED;
       }
       }
       rval = (int)0;
goto retlbl;
MATCHED:
       SUCCESS = 1;
       EASEpars->PARSETOKEN->PARSED = 1;
       if (AALT->DISCARD == 0) {
       ANODE= c_NODE();
       ANODE->START = (struct TOKEN*)EASEpars->PARSETOKEN;
       ANODE->END = (struct TOKEN*)EASEpars->PARSETOKEN;
       ANODE->MATCHNUM = AALT->SEQNUM;
       ANODE->SCRIPTCODE = AALT->SCRIPTREF;
       FILENODE(ANODE);
       }
       EASEpars->PARSETOKEN = (struct TOKEN*)EASEpars->PARSETOKEN->S_TOKENLIST;
       }
       rval = (int)SUCCESS;
goto retlbl;
retlbl:
E_TXTDEL_R(LINE);
       return rval;
}
void STRUCTNODES(struct NODE* ANODE, struct NODE* LASTNODE) {
       if (EASEpars->L_NODES != LASTNODE) {
       if (LASTNODE == 0) {
       ANODE->F_SUBNODES = (struct NODE*)EASEpars->F_NODES;
       ANODE->L_SUBNODES = (struct NODE*)EASEpars->L_NODES;
       EASEpars->F_NODES = (struct NODE*)0;
       EASEpars->L_NODES = (struct NODE*)0;
       }
       else {
       ANODE->F_SUBNODES = (struct NODE*)LASTNODE->S_NODES;
       LASTNODE->S_NODES = (struct NODE*)ANODE;
       ANODE->L_SUBNODES = (struct NODE*)EASEpars->L_NODES;
       EASEpars->L_NODES = (struct NODE*)LASTNODE;
       }
       }
       return;
}
Etxt* NEXTLINE_F() {
struct SRCLINE* LAST= 0;
Etxt* rval = 0;
       if (EASEpars->CURRENTLINE == 0) {
       EASEpars->CURRENTLINE = (struct SRCLINE*)EASEpars->F_SRCLINES;
       EASEmain->CURRLINE = 1;
       }
       else {
       EASEpars->CURRENTLINE = (struct SRCLINE*)EASEpars->CURRENTLINE->S_SRCLINES;
       EASEmain->CURRLINE = EASEmain->CURRLINE+1;
       }
       if (EASEpars->CURRENTLINE == 0) {
       EASEmain->CURRLINE = 0;
       CLEARSRCLINES();
       E_TXTASG_R(&rval, E_TXTLIT_F(_T("""")));
goto retlbl;
       }
       else {
       easlib->E_SAVE_V = easlib->WRITE_V;
       USE_R(98, 2);
       WTX_R(EASEpars->CURRENTLINE->LTXT);
       WTL_R();
       USE_R(easlib->E_SAVE_V, 2);
       E_TXTASG_R(&rval, EASEpars->CURRENTLINE->LTXT);
goto retlbl;
       }
retlbl:
       return rval;
}
void CLEARSRCLINES() {
struct SRCLINE* LAST= 0;
       EASEpars->CURRENTLINE = (struct SRCLINE*)EASEpars->F_SRCLINES;
       EASEpars->F_SRCLINES = (struct SRCLINE*)0;
next0001:
       if ( !  ( EASEpars->CURRENTLINE != 0 ) ) {
       goto done0001;
       }
       LAST = (struct SRCLINE*)EASEpars->CURRENTLINE;
       EASEpars->CURRENTLINE = (struct SRCLINE*)EASEpars->CURRENTLINE->S_SRCLINES;
       E_TXTASG_R(&LAST->LTXT, 0);
       d_SRCLINE(LAST);
       goto next0001;
done0001:
       return;
}
void BUILDSOURCE(Etxt* BODYTEXT) {
struct SRCLINE* ALINE= 0;
struct SRCLINE* LASTLINE= 0;
int TOTLEN= 0;
int LINELEN= 0;
int I= 0;
int START= 0;
E_TXTINC_R(BODYTEXT);
       CLEARSRCLINES();
       TOTLEN = LENGTH_F(BODYTEXT);
       START = 1;
       I = 1;
       goto test0001;
next0001:
       I = I+1;
test0001:
       if (I > TOTLEN) {
       goto done0001;
       }
       if (ACHAR_F(BODYTEXT, I) == 13) {
       LINELEN = I-START;
       if (LINELEN != 0) {
       ALINE= c_SRCLINE();
       E_TXTASG_R(&ALINE->LTXT, SUBSTR_F(BODYTEXT, START, LINELEN));
       if (EASEpars->F_SRCLINES == 0) {
       EASEpars->F_SRCLINES = (struct SRCLINE*)ALINE;
       }
       else {
       LASTLINE->S_SRCLINES = (struct SRCLINE*)ALINE;
       }
       LASTLINE = (struct SRCLINE*)ALINE;
       EASEmain->TOTLINES = EASEmain->TOTLINES+1;
       }
       START = I+2;
       }
       goto next0001;
done0001:
       goto retlbl;
retlbl:
E_TXTDEL_R(BODYTEXT);
       return;
}

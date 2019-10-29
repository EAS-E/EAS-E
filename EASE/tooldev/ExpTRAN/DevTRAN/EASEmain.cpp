#include "stdafx.h"
#include "malloc.h"
#include "libopts.h"
#include "math.h"
#include "EASEmain.h"

void EASEmain_addTypes() {
}
EASEmain_sys* EASEmain;

void EASEmain_init() {
EASEmain = (EASEmain_sys*)E_CREATE_F( 0,3001, sizeof(EASEmain_sys));
EASEmain_sets();
EASEmain_addTypes();
}
void EASEmain_sets() {
       return;
}

void easinit() {
EASEgen_init();
Script_init();
EASEpars_init();
Dict_init();
Synrule_init();
EASElex_init();
EASEents_init();
EASEmain_init();
easlib_init();
}
void main() {
       easinit();
       goto retlbl;
retlbl:
       return;
}
int INITERRS(Etxt* SYSDIR) {
int N= 0;
int I= 0;
int rval = 0;
E_TXTINC_R(SYSDIR);
       OPENI_R(1, CONCAT_F(SYSDIR, E_TXTLIT_F(_T("\\easeerrs.txt"))));
       USE_R(1, 1);
       if (easlib->UIB_R->ROPENERR_V != 0) {
       easlib->E_SAVE_V = easlib->WRITE_V;
       USE_R(97, 2);
       WTX_R(E_TXTLIT_F(_T("Open failed")));
       WTL_R();
       USE_R(easlib->E_SAVE_V, 2);
       rval = (int)1;
goto retlbl;
       }
       easlib->UIB_R->EOF_V = 1;
       N = RDN_F();
       RDL_R();
       EASEmain->ERRMSGS = (Etxt**)calloc(N + 1, sizeof(Etxt*));
       EASEmain->ERRMSGS[0] = (Etxt*)(N);
       I = 1;
       goto test0001;
next0001:
       I = I+1;
test0001:
       if (I > N) {
       goto done0001;
       }
       if ( !  ( easlib->UIB_R->EOF_V != 2 ) ) {
       goto done0001;
       }
       E_TXTASG_R(&EASEmain->ERRMSGS[I], RDT_F(easlib->UIB_R->RRECLEN_V));
       RDL_R();
       goto next0001;
done0001:
       CLOSE_R(1);
       rval = (int)0;
goto retlbl;
retlbl:
E_TXTDEL_R(SYSDIR);
       return rval;
}
void EASERR(int ERRNO, Etxt* TERM) {
E_TXTINC_R(TERM);
       EASEents->ERRORREC= c_ERRORREC();
       EASEents->ERRORREC->ERRNUM = ERRNO;
       EASEents->ERRORREC->INPROC = (struct EASEPROC*)EASEmain->CURRPROC;
       EASEents->ERRORREC->LINENUM = EASEmain->CURRLINE;
       if (EASEents->F_ERRORRECS == 0) {
       EASEents->F_ERRORRECS = (struct ERRORREC*)EASEents->ERRORREC;
       }
       else {
       EASEents->L_ERRORRECS->S_ERRORRECS = (struct ERRORREC*)EASEents->ERRORREC;
       }
       EASEents->L_ERRORRECS = (struct ERRORREC*)EASEents->ERRORREC;
       if (ERRNO > 0) {
       EASEmain->CURRPROC->ERRCOUNT = EASEmain->CURRPROC->ERRCOUNT+1;
       easlib->E_SAVE_V = easlib->WRITE_V;
       USE_R(98, 2);
       WTX_R(E_TXTLIT_F(_T("!!! Error ")));
       USE_R(easlib->E_SAVE_V, 2);
       }
       else {
       ERRNO = -ERRNO;
       easlib->E_SAVE_V = easlib->WRITE_V;
       USE_R(98, 2);
       WTX_R(E_TXTLIT_F(_T("--- Warning ")));
       USE_R(easlib->E_SAVE_V, 2);
       }
       easlib->E_SAVE_V = easlib->WRITE_V;
       USE_R(98, 2);
       WTI_R(ERRNO, 4);
       USE_R(easlib->E_SAVE_V, 2);
       if (E_TXTNEQ_F(TERM, E_TXTLIT_F(_T("""")))) {
       easlib->E_SAVE_V = easlib->WRITE_V;
       USE_R(98, 2);
       WTX_R(E_TXTLIT_F(_T(" involving ")));
       WTX_R(TERM);
       WTS_R(2);
       USE_R(easlib->E_SAVE_V, 2);
       }
       if (EASEmain->CURRPROC != 0) {
       easlib->E_SAVE_V = easlib->WRITE_V;
       USE_R(98, 2);
       WTX_R(E_TXTLIT_F(_T(" in ")));
       WTX_R(EASEmain->CURRPROC->PDICTREF->LEXEME);
       WTX_R(E_TXTLIT_F(_T(" at line ")));
       WTI_R(EASEmain->CURRLINE, 4);
       WTS_R(2);
       USE_R(easlib->E_SAVE_V, 2);
       }
       easlib->E_SAVE_V = easlib->WRITE_V;
       USE_R(98, 2);
       WTX_R(EASEmain->ERRMSGS[ERRNO-1000]);
       WTL_R();
       USE_R(easlib->E_SAVE_V, 2);
       goto retlbl;
retlbl:
E_TXTDEL_R(TERM);
       return;
}
void TRANSLATEPROCS() {
struct SCHEMA* ASCHEMA= 0;
Etxt* FILENAME= 0;
struct EASEPROC* APROC= 0;
struct DICTUSE* AUSE= 0;
Etxt* BODYTEXT= 0;
struct ENTITYTYPE* PROCENT= 0;
int INIT= 0;
       ASCHEMA = (struct SCHEMA*)EASEents->F_SCHEMAS;
next0001:
       if ( !  ( ASCHEMA != 0 ) ) {
       goto done0001;
       }
       if (ASCHEMA->NOGEN == 0) {
       E_TXTASG_R(&FILENAME, CONCAT_F(ASCHEMA->GENNAME, E_TXTLIT_F(_T(".cpp"))));
       E_TXTASG_R(&FILENAME, CONCAT_F(EASEmain->GENDIR, FILENAME));
       OPENO_R(6, FILENAME);
       USE_R(6, 2);
       GENPROCINCL(ASCHEMA);
       APROC = (struct EASEPROC*)ASCHEMA->F_PROCS;
next0002:
       if ( !  ( APROC != 0 ) ) {
       goto done0002;
       }
       EASEmain->CURRPROC = (struct EASEPROC*)APROC;
       AUSE = (struct DICTUSE*)FINDSPECUSE_F(APROC->PDICTREF, 3);
       PROCENT = (struct ENTITYTYPE*)AUSE->USEENTITY;
       E_TXTASG_R(&BODYTEXT, PROCENT->PROCBODY);
       if (E_TXTNEQ_F(BODYTEXT, E_TXTLIT_F(_T("""")))) {
       PROCTITLE(APROC);
       BUILDSOURCE(BODYTEXT);
       }
       else {
       CLEARSRCLINES();
       EASElex->F_TOKENLIST = (struct TOKEN*)APROC->F_SCRIPTTOKENS;
       EASElex->L_TOKENLIST = (struct TOKEN*)APROC->L_SCRIPTTOKENS;
       }
       Script->CURRLOOPDEPTH = 0;
       Script->LBL = 0;
       Script->LV = 0;
       MAKELCLSFROMXML(APROC);
       PARSE(APROC);
       if (E_TXTEQL_F(APROC->PDICTREF->LEXEME, E_TXTLIT_F(_T("MAIN")))) {
       GENINIT();
       }
       if (APROC->ERRCOUNT == 0) {
       MAKELCLS(APROC);
       GENPROC(APROC);
       DESTROYLCLS(PROCENT);
       }
       APROC = (struct EASEPROC*)APROC->S_PROCS;
       goto next0002;
done0002:
       CLOSE_R(6);
       }
       ASCHEMA = (struct SCHEMA*)ASCHEMA->S_SCHEMAS;
       goto next0001;
done0001:
       ASCHEMA = (struct SCHEMA*)EASEents->F_SCHEMAS;
next0003:
       if ( !  ( ASCHEMA != 0 ) ) {
       goto done0003;
       }
       if (ASCHEMA->NOGEN == 0) {
       E_TXTASG_R(&FILENAME, CONCAT_F(ASCHEMA->GENNAME, E_TXTLIT_F(_T(".h"))));
       OPENO_R(6, CONCAT_F(EASEmain->GENDIR, FILENAME));
       USE_R(6, 2);
       GENHEADER(ASCHEMA);
       CLOSE_R(6);
       }
       ASCHEMA = (struct SCHEMA*)ASCHEMA->S_SCHEMAS;
       goto next0003;
done0003:
       goto retlbl;
retlbl:
E_TXTDEL_R(FILENAME);
E_TXTDEL_R(BODYTEXT);
       return;
}
void PROCTITLE(struct EASEPROC* APROC) {
int SAVW= 0;
struct DICTUSE* AUSE= 0;
struct ATTRDEF* ATT= 0;
       SAVW = easlib->WRITE_V;
       USE_R(98, 2);
       if (APROC->RETURNATT != 0) {
       WTX_R(E_TXTLIT_F(_T("Function ")));
       }
       else {
       WTX_R(E_TXTLIT_F(_T("Routine ")));
       }
       WTX_R(APROC->PDICTREF->LEXEME);
       AUSE = (struct DICTUSE*)FINDSPECUSE_F(APROC->PDICTREF, 3);
       ATT = (struct ATTRDEF*)AUSE->USEENTITY->F_ATTRDEFS;
next0001:
       if ( !  ( ATT != 0 ) ) {
       goto done0001;
       }
       WTS_R(1);
       WTX_R(ATT->ATTRNAME);
       ATT = (struct ATTRDEF*)ATT->S_ATTRDEFS;
       goto next0001;
done0001:
       WTL_R();
       USE_R(SAVW, 2);
       goto retlbl;
retlbl:
       return;
}
void LISTING() {
struct SCHEMA* ASCHEMA= 0;
struct EASEPROC* APROC= 0;
       OPENO_R(6, CONCAT_F(EASEmain->GENDIR, E_TXTLIT_F(_T("proj.lst"))));
       USE_R(6, 2);
       ASCHEMA = (struct SCHEMA*)EASEents->F_SCHEMAS;
next0001:
       if ( !  ( ASCHEMA != 0 ) ) {
       goto done0001;
       }
       APROC = (struct EASEPROC*)ASCHEMA->F_PROCS;
next0002:
       if ( !  ( APROC != 0 ) ) {
       goto done0002;
       }
       PRINTSTARS(APROC);
       APROC = (struct EASEPROC*)APROC->S_PROCS;
       goto next0002;
done0002:
       ASCHEMA = (struct SCHEMA*)ASCHEMA->S_SCHEMAS;
       goto next0001;
done0001:
       WTX_R(E_TXTLIT_F(_T(" DONE: LINES = ")));
       WTI_R(EASEmain->TOTLINES, 6);
       WTL_R();
       CLOSE_R(6);
       goto retlbl;
retlbl:
       return;
}
void PRINTPROC(struct EASEPROC* APROC) {
struct NODE* ANODE= 0;
struct TOKEN* ATOKEN= 0;
struct STMT* ASTMT= 0;
int I= 0;
       WTX_R(E_TXTLIT_F(_T("Procedure ")));
       WTX_R(APROC->PDICTREF->LEXEME);
       WTL_R();
       ASTMT = (struct STMT*)APROC->F_STMTS;
next0001:
       if ( !  ( ASTMT != 0 ) ) {
       goto done0001;
       }
       ATOKEN = (struct TOKEN*)ASTMT->F_TOKENS;
       I = ASTMT->SCRIPTDEPTH;
       if (I == 0) {
       WTB_R(4);
next0002:
       if ( !  ( ATOKEN != 0 ) ) {
       goto done0002;
       }
       WTX_R(ATOKEN->DICTREF->LEXEME);
       WTS_R(1);
       ATOKEN = (struct TOKEN*)ATOKEN->S_TOKENLIST;
       goto next0002;
done0002:
       WTL_R();
       }
       ASTMT = (struct STMT*)ASTMT->S_STMTS;
       goto next0001;
done0001:
       WTL_R();
       goto retlbl;
retlbl:
       return;
}
void PRINTSTARS(struct EASEPROC* APROC) {
struct NODE* ANODE= 0;
struct TOKEN* ATOKEN= 0;
struct STMT* ASTMT= 0;
int I= 0;
       WTL_R();
       WTX_R(E_TXTLIT_F(_T("Procedure ")));
       WTX_R(APROC->PDICTREF->LEXEME);
       WTL_R();
       ASTMT = (struct STMT*)APROC->F_STMTS;
next0001:
       if ( !  ( ASTMT != 0 ) ) {
       goto done0001;
       }
       ATOKEN = (struct TOKEN*)ASTMT->F_TOKENS;
       I = ASTMT->SCRIPTDEPTH;
next0002:
       if ( !  ( I > 0 ) ) {
       goto done0002;
       }
       WTT_R(E_TXTLIT_F(_T("*")), 1);
       I = I-1;
       goto next0002;
done0002:
       WTB_R(4);
next0003:
       if ( !  ( ATOKEN != 0 ) ) {
       goto done0003;
       }
       WTX_R(ATOKEN->DICTREF->LEXEME);
       WTS_R(1);
       ATOKEN = (struct TOKEN*)ATOKEN->S_TOKENLIST;
       goto next0003;
done0003:
       WTL_R();
       ASTMT = (struct STMT*)ASTMT->S_STMTS;
       goto next0001;
done0001:
       goto retlbl;
retlbl:
       return;
}
void DESTROYLCLS(struct ENTITYTYPE* PROCENT) {
struct DICTENTRY* DREF= 0;
struct DICTUSE* AUSE= 0;
struct DICTUSE* DUSE= 0;
struct DICTUSE* LUSE= 0;
struct ATTRDEF* ATT= 0;
       ATT = (struct ATTRDEF*)PROCENT->F_ATTRDEFS;
next0001:
       if ( !  ( ATT != 0 ) ) {
       goto done0001;
       }
       DREF = (struct DICTENTRY*)FINDDICTENTRY_F(ATT->ATTRNAME);
       DUSE = (struct DICTUSE*)FINDSPECUSE_F(DREF, 1);
       AUSE = (struct DICTUSE*)DREF->F_USAGE;
next0002:
       if ( !  ( AUSE != 0 ) ) {
       goto done0002;
       }
       if (AUSE == DUSE) {
       if (LUSE != 0) {
       LUSE->S_USAGE = (struct DICTUSE*)AUSE->S_USAGE;
       }
       else {
       DREF->F_USAGE = (struct DICTUSE*)AUSE->S_USAGE;
       }
       d_DICTUSE(DUSE);
       AUSE = (struct DICTUSE*)0;
       }
       else {
       LUSE = (struct DICTUSE*)AUSE;
       AUSE = (struct DICTUSE*)AUSE->S_USAGE;
       }
       goto next0002;
done0002:
       ATT = (struct ATTRDEF*)ATT->S_ATTRDEFS;
       goto next0001;
done0001:
       return;
}
void MAKELCLS(struct EASEPROC* APROC) {
struct ENTITYTYPE* PROCENT= 0;
struct DICTENTRY* DREF= 0;
struct DICTUSE* AUSE= 0;
struct ATTRDEF* ATT= 0;
struct ATTRDEF* NEWATT= 0;
struct LCLDEF* ALCL= 0;
       AUSE = (struct DICTUSE*)FINDSPECUSE_F(APROC->PDICTREF, 3);
       PROCENT = (struct ENTITYTYPE*)AUSE->USEENTITY;
       ATT = (struct ATTRDEF*)PROCENT->F_ATTRDEFS;
       if (APROC->F_LCLDEFS != 0) {
       if (ATT != 0) {
next0001:
       if ( !  ( ATT->S_ATTRDEFS != 0 ) ) {
       goto done0001;
       }
       ATT = (struct ATTRDEF*)ATT->S_ATTRDEFS;
       goto next0001;
done0001:
;      }
       ALCL = (struct LCLDEF*)APROC->F_LCLDEFS;
next0002:
       if ( !  ( ALCL != 0 ) ) {
       goto done0002;
       }
       NEWATT= c_ATTRDEF();
       if (ATT != 0) {
       ATT->S_ATTRDEFS = (struct ATTRDEF*)NEWATT;
       }
       else {
       PROCENT->F_ATTRDEFS = (struct ATTRDEF*)NEWATT;
       }
       ATT = (struct ATTRDEF*)NEWATT;
       E_TXTASG_R(&NEWATT->ATTRNAME, ALCL->LDEFNAME);
       NEWATT->ATTRTYPE = (struct ENTITYTYPE*)ALCL->LDEFTYPE;
       if (NEWATT->ATTRTYPE == 0) {
       EASERR(-1002, NEWATT->ATTRNAME);
       NEWATT->ATTRTYPE = (struct ENTITYTYPE*)EASEents->E_BUILTINS[1];
       }
       NEWATT->ISPARAM = ALCL->LPARAM;
       NEWATT->ISYIELD = ALCL->LYLD;
       NEWATT->SUBSCRIPTS = ALCL->LDEFDIM;
       NEWATT->ISRETTYPE = ALCL->LRET;
       if (ALCL->LRET != 0) {
       NEWATT->ISRETTYPE = ALCL->LRET;
       APROC->RETURNATT = (struct ATTRDEF*)NEWATT;
       }
       DREF = (struct DICTENTRY*)FINDDICTENTRY_F(NEWATT->ATTRNAME);
       AUSE = (struct DICTUSE*)MAKEUSE_F(DREF, 1);
       AUSE->USEENTITY = (struct ENTITYTYPE*)NEWATT->ATTRTYPE;
       AUSE->USEMODE = FINDMODE_F(NEWATT->ATTRTYPE);
       AUSE->USESUBS = NEWATT->SUBSCRIPTS;
       ALCL = (struct LCLDEF*)ALCL->S_LCLDEFS;
       goto next0002;
done0002:
;      }
       goto retlbl;
retlbl:
       return;
}
void MAKELCLSFROMXML(struct EASEPROC* APROC) {
struct ENTITYTYPE* PROCENT= 0;
struct DICTENTRY* DREF= 0;
struct DICTUSE* AUSE= 0;
struct ATTRDEF* ATT= 0;
       AUSE = (struct DICTUSE*)FINDSPECUSE_F(APROC->PDICTREF, 3);
       PROCENT = (struct ENTITYTYPE*)AUSE->USEENTITY;
       ATT = (struct ATTRDEF*)PROCENT->F_ATTRDEFS;
next0001:
       if ( !  ( ATT != 0 ) ) {
       goto done0001;
       }
       DREF = (struct DICTENTRY*)FINDDICTENTRY_F(ATT->ATTRNAME);
       AUSE = (struct DICTUSE*)MAKEUSE_F(DREF, 1);
       if (ATT->ATTRTYPE == 0) {
       EASERR(-1002, ATT->ATTRNAME);
       ATT->ATTRTYPE = (struct ENTITYTYPE*)EASEents->E_BUILTINS[1];
       }
       AUSE->USEENTITY = (struct ENTITYTYPE*)ATT->ATTRTYPE;
       AUSE->USEMODE = FINDMODE_F(ATT->ATTRTYPE);
       AUSE->USESUBS = ATT->SUBSCRIPTS;
       ATT = (struct ATTRDEF*)ATT->S_ATTRDEFS;
       goto next0001;
done0001:
       goto retlbl;
retlbl:
       return;
}
void READSOURCE() {
Etxt* ALINE= 0;
struct SRCLINE* LASTLINE= 0;
       OPENI_R(5, E_TXTLIT_F(_T("source.txt")));
       USE_R(5, 1);
       easlib->UIB_R->EOF_V = 1;
next0001:
       if ( !  ( easlib->UIB_R->EOF_V != 2 ) ) {
       goto done0001;
       }
       E_TXTASG_R(&ALINE, RDT_F(easlib->UIB_R->RRECLEN_V));
       EASEpars->SRCLINE= c_SRCLINE();
       if (EASEpars->F_SRCLINES == 0) {
       EASEpars->F_SRCLINES = (struct SRCLINE*)EASEpars->SRCLINE;
       }
       else {
       LASTLINE->S_SRCLINES = (struct SRCLINE*)EASEpars->SRCLINE;
       }
       LASTLINE = (struct SRCLINE*)EASEpars->SRCLINE;
       E_TXTASG_R(&EASEpars->SRCLINE->LTXT, ALINE);
       RDL_R();
       goto next0001;
done0001:
       CLOSE_R(5);
E_TXTDEL_R(ALINE);
       return;
}
void LISTSYNTAX() {
int I= 0;
struct DICTENTRY* ENTRY= 0;
struct SYNRULE* RULE= 0;
       OPENO_R(6, E_TXTLIT_F(_T("listrules.txt")));
       USE_R(6, 2);
       I = 1;
       goto test0001;
next0001:
       I = I+1;
test0001:
       if (I > 128) {
       goto done0001;
       }
       WTI_R(I, 3);
       if (Dict->F_DICT[I] != 0) {
       ENTRY = (struct DICTENTRY*)Dict->F_DICT[I];
next0002:
       if ( !  ( ENTRY != 0 ) ) {
       goto done0002;
       }
       WTB_R(6);
       WTX_R(ENTRY->LEXEME);
       RULE = (struct SYNRULE*)ENTRY->F_ENTRULES;
next0003:
       if ( !  ( RULE != 0 ) ) {
       goto done0003;
       }
       WTB_R(20);
       WTX_R(RULE->RULENAME);
       WTB_R(36);
       WTX_R(RULE->F_PARTS->F_ALTS->DICTENT->LEXEME);
       WTL_R();
       RULE = (struct SYNRULE*)RULE->S_ENTRULES;
       goto next0003;
done0003:
       WTL_R();
       ENTRY = (struct DICTENTRY*)ENTRY->S_DICT;
       goto next0002;
done0002:
;      }
       else {
       WTB_R(6);
       WTX_R(E_TXTLIT_F(_T("None")));
       WTL_R();
       }
       goto next0001;
done0001:
       return;
}
int EASECOMPILE(Etxt* PROJDIR, Etxt* SYSDIR) {
Etxt* ALINE= 0;
struct EASEPROC* APROC= 0;
struct ERRORREC* ANERR= 0;
int ERR= 0;
int I_0001= 0;
int I_0002= 0;
int I_0003= 0;
int rval = 0;
E_TXTINC_R(PROJDIR);
E_TXTINC_R(SYSDIR);
       if (INITERRS(SYSDIR) != 0) {
       rval = (int)-1;
goto retlbl;
       }
       EASEgen->LOGICOPS = (Etxt**)calloc(6 + 1, sizeof(Etxt*));
       EASEgen->LOGICOPS[0] = (Etxt*)(6);
       E_TXTASG_R(&EASEgen->LOGICOPS[1], E_TXTLIT_F(_T(" == ")));
       E_TXTASG_R(&EASEgen->LOGICOPS[2], E_TXTLIT_F(_T(" != ")));
       E_TXTASG_R(&EASEgen->LOGICOPS[3], E_TXTLIT_F(_T(" <= ")));
       E_TXTASG_R(&EASEgen->LOGICOPS[4], E_TXTLIT_F(_T(" >= ")));
       E_TXTASG_R(&EASEgen->LOGICOPS[5], E_TXTLIT_F(_T(" < ")));
       E_TXTASG_R(&EASEgen->LOGICOPS[6], E_TXTLIT_F(_T(" > ")));
       INITLEX(SYSDIR);
       I_0001 = 2;
       EASEpars->CTLSTATES = (int**)calloc(I_0001 + 1, sizeof(int*));
       EASEpars->CTLSTATES[0] = (int*)(I_0001);
       I_0003 = 4;
       I_0002 = 1;
       goto test0001;
next0001:
       I_0002 = I_0002+1;
test0001:
       if (I_0002 > I_0001) {
       goto done0001;
       }
       EASEpars->CTLSTATES[I_0002] = (int*)calloc(I_0003 + 1, sizeof(int));
       EASEpars->CTLSTATES[I_0002][0] = (int)(I_0003);
       goto next0001;
done0001:
       EASEpars->CTLSTATES[1][1] = (int)1;
       EASEpars->CTLSTATES[1][2] = (int)2;
       EASEpars->CTLSTATES[1][3] = (int)1;
       EASEpars->CTLSTATES[1][4] = (int)1;
       EASEpars->CTLSTATES[2][1] = (int)4;
       EASEpars->CTLSTATES[2][2] = (int)2;
       EASEpars->CTLSTATES[2][3] = (int)2;
       EASEpars->CTLSTATES[2][4] = (int)1;
       READSYNTAX(CONCAT_F(SYSDIR, E_TXTLIT_F(_T("\\syntaxrules.txt"))));
       READSCRIPTS(CONCAT_F(SYSDIR, E_TXTLIT_F(_T("\\scriptrules.txt"))));
       READXML(CONCAT_F(SYSDIR, E_TXTLIT_F(_T("\\easetypes.xml"))), 0);
       READXML(CONCAT_F(SYSDIR, E_TXTLIT_F(_T("\\easelibsys.xml"))), 0);
       OPENI_R(5, CONCAT_F(PROJDIR, E_TXTLIT_F(_T("\\project.eas"))));
       USE_R(5, 1);
       if (easlib->UIB_R->ROPENERR_V != 0) {
       rval = (int)-2;
goto retlbl;
       }
       easlib->UIB_R->EOF_V = 1;
       E_TXTASG_R(&EASEmain->GENDIR, RDT_F(easlib->UIB_R->RRECLEN_V));
       RDL_R();
       OPENO_R(98, CONCAT_F(EASEmain->GENDIR, E_TXTLIT_F(_T("XLISTING.txt"))));
next0002:
       if ( !  ( easlib->UIB_R->EOF_V != 2 ) ) {
       goto done0002;
       }
       E_TXTASG_R(&ALINE, RDX_F());
       RDL_R();
       if (E_TXTNEQ_F(ALINE, E_TXTLIT_F(_T("""")))) {
       READXML(PROJDIR, ALINE);
       }
       goto next0002;
done0002:
       CLOSE_R(5);
       FIXUPSCHEMAS();
       TRANSLATEPROCS();
       CLOSE_R(98);
       CLOSE_R(97);
       if (EASEents->F_ERRORRECS != 0) {
       OPENO_R(99, CONCAT_F(EASEmain->GENDIR, E_TXTLIT_F(_T("XERRORS.txt"))));
       USE_R(99, 2);
       ANERR = (struct ERRORREC*)EASEents->F_ERRORRECS;
next0003:
       if ( !  ( ANERR != 0 ) ) {
       goto done0003;
       }
       ERR = ANERR->ERRNUM;
       if (ERR > 0) {
       WTX_R(E_TXTLIT_F(_T("Error ")));
       }
       else {
       ERR = -ERR;
       WTX_R(E_TXTLIT_F(_T("Warning ")));
       }
       WTI_R(ERR, 5);
       if (ANERR->INPROC != 0) {
       WTX_R(E_TXTLIT_F(_T(" in procedure ")));
       WTX_R(ANERR->INPROC->PDICTREF->LEXEME);
       WTX_R(E_TXTLIT_F(_T(" line ")));
       WTI_R(ANERR->LINENUM, 4);
       }
       WTS_R(2);
       WTX_R(EASEmain->ERRMSGS[ERR-1000]);
       WTL_R();
       ANERR = (struct ERRORREC*)ANERR->S_ERRORRECS;
       goto next0003;
done0003:
       CLOSE_R(99);
       rval = (int)1;
goto retlbl;
       }
       rval = (int)0;
goto retlbl;
retlbl:
E_TXTDEL_R(PROJDIR);
E_TXTDEL_R(SYSDIR);
E_TXTDEL_R(ALINE);
       return rval;
}

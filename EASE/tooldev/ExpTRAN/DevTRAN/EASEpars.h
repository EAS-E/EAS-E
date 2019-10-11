#pragma once
#include "easlib.h"

#include "EASEmain.h"
#include "EASEents.h"
#include "EASElex.h"
#include "Synrule.h"
#include "Dict.h"
#include "Script.h"
#include "EASEgen.h"

#define _SRCLINE
#define _LCLDEF
#define _EASEPROC
#define _STMT
#define _NODE

struct SRCLINE {
struct eInstHdr hdr;
struct SRCLINE* S_SRCLINES;
Etxt* LTXT;
};
#define Z_SRCLINE sizeof(SRCLINE)
struct LCLDEF {
struct eInstHdr hdr;
struct LCLDEF* S_LCLDEFS;
Etxt* LDEFNAME;
struct ENTITYTYPE* LDEFTYPE;
int LDEFDIM;
int LPARAM;
int LYLD;
int LRET;
int ISSUBPROG;
};
#define Z_LCLDEF sizeof(LCLDEF)
struct EASEPROC {
struct eInstHdr hdr;
struct EASEPROC* S_PROCS;
struct DICTENTRY* PDICTREF;
struct STMT* F_STMTS;
struct STMT* L_STMTS;
struct TOKEN* F_SCRIPTTOKENS;
struct TOKEN* L_SCRIPTTOKENS;
int LASTLBLNUM;
struct ATTRDEF* RETURNATT;
int ERRCOUNT;
struct LCLDEF* F_LCLDEFS;
};
#define Z_EASEPROC sizeof(EASEPROC)
struct STMT {
struct eInstHdr hdr;
struct NODE* F_PARSENODES;
struct NODE* L_PARSENODES;
struct STMT* S_STMTS;
struct STMT* P_STMTS;
struct SYNRULE* STMTRULE;
int LBLNUM;
int STMTNUM;
int LOOPDEPTH;
int SCRIPTDEPTH;
struct SRCLINE* F_FMTLINES;
struct TOKEN* F_TOKENS;
struct TOKEN* L_TOKENS;
struct STMT* P_CTRLSTMT;
struct STMT* P_DOSTMT;
int STMTLINE;
};
#define Z_STMT sizeof(STMT)
struct NODE {
struct eInstHdr hdr;
struct NODE* S_NODES;
struct NODE* F_SUBNODES;
struct NODE* L_SUBNODES;
struct TOKEN* START;
struct TOKEN* END;
int MATCHNUM;
int SCRIPTCODE;
Etxt* NODENAME;
};
#define Z_NODE sizeof(NODE)
void EASEpars_sets();
void d_NODE(struct NODE*& EPTR);
struct NODE* c_NODE();
void d_STMT(struct STMT*& EPTR);
struct STMT* c_STMT();
void d_EASEPROC(struct EASEPROC*& EPTR);
struct EASEPROC* c_EASEPROC();
void d_LCLDEF(struct LCLDEF*& EPTR);
struct LCLDEF* c_LCLDEF();
void d_SRCLINE(struct SRCLINE*& EPTR);
struct SRCLINE* c_SRCLINE();
struct LCLDEF* FINDLCLDEF(Etxt* VARNAME);
void UPDATELCL(struct LCLDEF* ALCL, struct NODE* MODENODE, struct NODE* DIMNODE);
void STMTDEFFUNC(struct STMT* ASTMT);
void STMTDEFRTN(struct STMT* ASTMT);
void STMTDEFVAR(struct STMT* ASTMT);
void DESTROYNODES(struct NODE* ANODE);
void SUBSTITUT(struct TOKEN* ATOKEN);
void FILENODE(struct NODE* ANODE);
void PARSE(struct EASEPROC* APROC);
struct STMT* PARSESTMT_F();
int MATCHRULE_F(struct SYNRULE* ARULE);
int MATCHRULEPART_F(struct RULEPART* APART);
int MATCHPARTALT_F(struct ALTPART* AALT);
void STRUCTNODES(struct NODE* ANODE, struct NODE* LASTNODE);
Etxt* NEXTLINE_F();
void CLEARSRCLINES();
void BUILDSOURCE(Etxt* BODYTEXT);

struct EASEpars_sys {
struct eInstHdr hdr;
struct NODE* NODE;
struct STMT* STMT;
struct SRCLINE* SRCLINE;
struct EASEPROC* EASEPROC;
struct NODE* F_NODES;
struct NODE* L_NODES;
struct SRCLINE* F_SRCLINES;
struct SRCLINE* CURRENTLINE;
struct TOKEN* LASTPARSED;
struct TOKEN* PARSETOKEN;
int STMTSTATE;
int** CTLSTATES;
};
extern EASEpars_sys* EASEpars;
void EASEpars_init();

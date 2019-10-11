#pragma once
#include "easlib.h"

#include "EASEmain.h"
#include "EASEents.h"
#include "EASElex.h"
#include "Synrule.h"
#include "Dict.h"
#include "EASEpars.h"
#include "EASEgen.h"

#define _SCRIPTELEM

struct SCRIPTELEM {
struct eInstHdr hdr;
struct DICTENTRY* DICTREF;
int SCRIPTCODE;
int SCRIPTACTION;
int TKNFORM;
int SCRIPTPREFIX;
struct SCRIPTELEM* S_SCRIPTELEMS;
};
#define Z_SCRIPTELEM sizeof(SCRIPTELEM)
void Script_sets();
void d_SCRIPTELEM(struct SCRIPTELEM*& EPTR);
struct SCRIPTELEM* c_SCRIPTELEM();
void SCRIPTREAD(struct STMT* ASTMT);
void SCRIPTWRITE(struct STMT* ASTMT);
void STMTSCRIPT(struct STMT* ASTMT);
void SCRIPTLOOP();
Etxt* SCRIPTLBL(Etxt* PREFIX, int NUM);
void SETNODEPTRS(struct NODE* ANODE);
void SCRIPT(int SCRIPTNO);
void READSCRIPT(int SCRIPTNO);
void READSCRIPTS(Etxt* FILENAME);

struct Script_sys {
struct eInstHdr hdr;
struct SCRIPTELEM* SCRIPTELEM;
struct SCRIPTELEM** SCRIPTS;
struct NODE** NODEPTRS;
Etxt** STRPTRS;
int* IPTRS;
int LBL;
int LV;
int SCRIPTLEVEL;
int CURRLOOPDEPTH;
struct STMT* LASTCTLSTMT;
struct STMT* LASTDOSTMT;
};
extern Script_sys* Script;
void Script_init();

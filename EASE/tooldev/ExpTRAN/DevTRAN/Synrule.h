#pragma once
#include "easlib.h"

#include "EASEmain.h"
#include "EASEents.h"
#include "EASElex.h"
#include "Dict.h"
#include "EASEpars.h"
#include "Script.h"
#include "EASEgen.h"

#define _ALTREF
#define _RULFIXUP
#define _ALTPART
#define _RULEPART
#define _SYNRULE

struct ALTREF {
struct eInstHdr hdr;
struct ALTPART* ALTSUBRULE;
struct ALTREF* S_ALTREFS;
};
#define Z_ALTREF sizeof(ALTREF)
struct RULFIXUP {
struct eInstHdr hdr;
Etxt* RULENAME;
struct SYNRULE* THERULE;
struct RULFIXUP* S_RULFIXUPS;
struct ALTREF* F_ALTREFS;
};
#define Z_RULFIXUP sizeof(RULFIXUP)
struct ALTPART {
struct eInstHdr hdr;
struct DICTENTRY* DICTENT;
struct ALTPART* S_ALTS;
int SCRIPTREF;
struct SYNRULE* SUBRULE;
int TERMINALTYPE;
int SEQNUM;
int DISCARD;
};
#define Z_ALTPART sizeof(ALTPART)
struct RULEPART {
struct eInstHdr hdr;
struct RULEPART* S_PARTS;
int REPEATS;
int REQUIRED;
struct ALTPART* F_ALTS;
};
#define Z_RULEPART sizeof(RULEPART)
struct SYNRULE {
struct eInstHdr hdr;
Etxt* RULENAME;
int KEYRULE;
struct SYNRULE* S_SYNRULES;
struct SYNRULE* S_ENTRULES;
int RULETYPE;
struct RULEPART* F_PARTS;
};
#define Z_SYNRULE sizeof(SYNRULE)
void Synrule_sets();
void d_SYNRULE(struct SYNRULE*& EPTR);
struct SYNRULE* c_SYNRULE();
void d_RULEPART(struct RULEPART*& EPTR);
struct RULEPART* c_RULEPART();
void d_ALTPART(struct ALTPART*& EPTR);
struct ALTPART* c_ALTPART();
void d_RULFIXUP(struct RULFIXUP*& EPTR);
struct RULFIXUP* c_RULFIXUP();
void d_ALTREF(struct ALTREF*& EPTR);
struct ALTREF* c_ALTREF();
struct RULEPART* READPART();
void LINKSUBTOROOTENTRY(struct SYNRULE* ARULE);
void FIXUPSUBRULES();
void READALT(struct RULEPART* PART);
void READRULE();
void READSYNTAX(Etxt* FILENAME);

struct Synrule_sys {
struct eInstHdr hdr;
struct TOKEN* CURRTOKEN;
struct SYNRULE* F_SYNRULES;
struct RULFIXUP* F_RULFIXUPS;
};
extern Synrule_sys* Synrule;
void Synrule_init();

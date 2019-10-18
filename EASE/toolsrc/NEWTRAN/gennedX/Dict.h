#pragma once
#include "easlib.h"

#include "EASEmain.h"
#include "EASEents.h"
#include "EASElex.h"
#include "Synrule.h"
#include "EASEpars.h"
#include "Script.h"
#include "EASEgen.h"

#define _DICTUSE
#define _DICTENTRY

struct DICTUSE {
struct eInstHdr hdr;
struct DICTUSE* S_USAGE;
struct DICTENTRY* USEREF;
int USETYPE;
int USEMODE;
struct ENTITYTYPE* USEENTITY;
struct ENTITYTYPE* USEOWNER;
struct ATTRDEF* USESETREFATT;
struct SETDEF* USESETDEF;
int USESUBS;
int ISCOMMONATT;
};
#define Z_DICTUSE sizeof(DICTUSE)
struct DICTENTRY {
struct eInstHdr hdr;
struct DICTENTRY* S_DICT;
struct SYNRULE* F_ENTRULES;
Etxt* LEXEME;
struct DICTUSE* F_USAGE;
struct TOKEN* F_SUBST;
struct TOKEN* L_SUBST;
};
#define Z_DICTENTRY sizeof(DICTENTRY)
void Dict_sets();
void d_DICTENTRY(struct DICTENTRY*& EPTR);
struct DICTENTRY* c_DICTENTRY();
void d_DICTUSE(struct DICTUSE*& EPTR);
struct DICTUSE* c_DICTUSE();
struct DICTENTRY* FINDDICTENTRY_F(Etxt* INLEX);
void DESTROYUSE(struct DICTUSE* AUSE);
struct DICTUSE* FINDPREFUSE_F(struct TOKEN* TKN, int MUSTHAVE);
struct DICTUSE* FINDSPECUSE_F(struct DICTENTRY* DREF, int TYPE);
struct DICTUSE* MAKEUSE_F(struct DICTENTRY* DREF, int TYPE);

struct Dict_sys {
struct eInstHdr hdr;
struct DICTENTRY* DICTENTRY;
struct DICTENTRY** F_DICT;
};
extern Dict_sys* Dict;
void Dict_init();

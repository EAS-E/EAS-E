#pragma once
#include "easlib.h"

#include "EASEmain.h"
#include "EASEents.h"
#include "EASElex.h"
#include "Synrule.h"
#include "Dict.h"
#include "EASEpars.h"
#include "Script.h"


void EASEgen_sets();
int GENPATTR(struct DICTUSE* AUSE, struct TOKEN* VARTOKEN, struct NODE* SUBNODE, int ISPUT);
int GENPENTREF(struct DICTUSE* AUSE, struct TOKEN* VARTOKEN, struct NODE* SUBNODE, int ISPUT);
void GENSTARCAST(struct ENTITYTYPE* ETYPE);
void GENCAST(struct ENTITYTYPE* ETYPE);
Etxt* QUOTE_F(Etxt* TXT);
void GENHEADER(struct SCHEMA* ASCHEMA);
void GENCOMP(struct NODE* ANODE);
void GENLOGICL(struct NODE* ANODE);
void GENARRSUBS(struct NODE* ANODE);
int GENPOWER(struct NODE* ANODE);
int GENEXP(struct NODE* ANODE);
int GENVAR(struct NODE* ANODE, int ISPUT);
Etxt* ARRTYPE_F(struct ENTITYTYPE* ETYPE, int STARS);
void GENRESERVE(struct NODE* ANODE);
void GENCALL(struct NODE* ANODE);
void GENFUNC(struct NODE* ANODE);
void GENSTMT(struct EASEPROC* APROC, struct STMT* ASTMT);
void GENSIZES(struct SCHEMA* ASCHEMA);
void GENMAP(struct ENTITYTYPE* ETYPE);
void GENPROCINCL(struct SCHEMA* ASCHEMA);
void GENINIT();
void GENADDTYPES(struct SCHEMA* ASCHEMA);
void GENPROC(struct EASEPROC* APROC);
void GENARGLIST(struct ENTITYTYPE* ETYPE);
Etxt* MAKEATTRTYPE_F(struct ATTRDEF* ATT);
Etxt* MAKETYPE_F(struct ENTITYTYPE* ETYPE, int STARS);

struct EASEgen_sys {
struct eInstHdr hdr;
int GORETLBL;
Etxt** LOGICOPS;
int USEPERSIST;
};
extern EASEgen_sys* EASEgen;
void EASEgen_init();

#pragma once
#include "easlib.h"

#include "EASEents.h"
#include "EASElex.h"
#include "Synrule.h"
#include "Dict.h"
#include "EASEpars.h"
#include "Script.h"
#include "EASEgen.h"


void EASEmain_sets();
int INITERRS(Etxt* SYSDIR);
void EASERR(int ERRNO, Etxt* TERM);
void TRANSLATEPROCS();
void PROCTITLE(struct EASEPROC* APROC);
void LISTING();
void PRINTPROC(struct EASEPROC* APROC);
void PRINTSTARS(struct EASEPROC* APROC);
void DESTROYLCLS(struct ENTITYTYPE* PROCENT);
void MAKELCLS(struct EASEPROC* APROC);
void MAKELCLSFROMXML(struct EASEPROC* APROC);
void READSOURCE();
void LISTSYNTAX();
int EASECOMPILE(Etxt* PROJDIR, Etxt* SYSDIR);

struct EASEmain_sys {
struct eInstHdr hdr;
int TOTLINES;
Etxt* GENDIR;
int CURRLINE;
struct EASEPROC* CURRPROC;
Etxt** ERRMSGS;
Etxt* PROJECTDIR;
};
extern EASEmain_sys* EASEmain;
void EASEmain_init();

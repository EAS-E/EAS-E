#pragma once
#include "easlib.h"

#include "EASEmain.h"
#include "EASEents.h"
#include "Synrule.h"
#include "Dict.h"
#include "EASEpars.h"
#include "Script.h"
#include "EASEgen.h"

#define _TOKEN

struct TOKEN {
struct eInstHdr hdr;
int TOKENTYPE;
struct TOKEN* S_TOKENLIST;
Etxt* LEXEME;
int PARSED;
int SCRIPTED;
struct DICTENTRY* DICTREF;
};
#define Z_TOKEN sizeof(TOKEN)
void EASElex_sets();
void d_TOKEN(struct TOKEN*& EPTR);
struct TOKEN* c_TOKEN();
void INITLEX(Etxt* SYSDIR);
void ANALYZE(Etxt* BUFFER, int BUFFERLEN, int SEEKDICT);
void MAKETOKEN(Etxt* BUFF, int BEGIN, int END, int TTYPE, int SEEKDICT);
void FILETOKEN(struct TOKEN* ATOKEN);

struct EASElex_sys {
struct eInstHdr hdr;
struct TOKEN* TOKEN;
struct TOKEN* F_TOKENLIST;
struct TOKEN* L_TOKENLIST;
int* CHARTYPE;
int** NEXTSTATE;
int** ACTION;
int* TOKENFORM;
};
extern EASElex_sys* EASElex;
void EASElex_init();

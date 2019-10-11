#pragma once
#include "easlib.h"

#include "EASserver.h"


void LISTENERINIT_F();
int WRITEBLK_F();
void* READBLK_F();
void OPENDATA_R();
void* ALLOCNEWBLK_F();
int GETDATA_R();
void PUTDATA_R();
void plib_init();

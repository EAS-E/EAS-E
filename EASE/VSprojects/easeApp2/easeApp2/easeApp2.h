#pragma once
#include "easlib.h"

#include "pjobsdef.h"

#define _MACHINEGROUP

struct MACHINEGROUP {
struct eInstHdr hdr;
struct E_PSET* INBUFFER;
};
#define Z_MACHINEGROUP sizeof(MACHINEGROUP)
void easeApp2_sets();
void d_MACHINEGROUP(struct MACHINEGROUP*& EPTR);
struct MACHINEGROUP* c_MACHINEGROUP();
void TESTENTRY();

struct easeApp2_sys {
struct eInstHdr hdr;
struct MACHINEGROUP* MACHINEGROUP;
};
extern easeApp2_sys* easeApp2;
void easeApp2_init();

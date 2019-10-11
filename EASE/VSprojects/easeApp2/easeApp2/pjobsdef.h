#pragma once
#include "easlib.h"

#include "easeApp2.h"

#define _JOBSTEP
#define _JOB

struct JOBSTEP {
struct eInstHdr hdr;
Etxt* STEPNAME;
};
#define Z_JOBSTEP sizeof(JOBSTEP)
const int Y_JOBSTEP[  7] = { sizeof(JOBSTEP),   5, 1, 1, 4, 5,  3 };
struct JOB {
struct eInstHdr hdr;
Etxt* JOBNAME;
int PRIORITY;
int VALUE;
struct E_PSET* ROUTING;
};
#define Z_JOB sizeof(JOB)
const int Y_JOB[ 10] = { sizeof(JOB),   8, 1, 1, 4, 5,  3,  1,  1,  5 };
void pjobsdef_sets();
int X_INBUFFER(void* E1, void* E2);
void d_JOB(struct JOB*& EPTR);
struct iRef* c_JOB();
void d_JOBSTEP(struct JOBSTEP*& EPTR);
struct iRef* c_JOBSTEP();

struct pjobsdef_sys {
struct eInstHdr hdr;
struct JOB* JOB;
struct JOBSTEP* JOBSTEP;
};
extern pjobsdef_sys* pjobsdef;
void pjobsdef_init();

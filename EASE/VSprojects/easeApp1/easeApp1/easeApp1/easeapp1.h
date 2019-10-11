#pragma once
#include "easlib.h"
#include "easeSets.h"

struct MACHINEGROUP {
struct eInstHdr hdr;
void* INBUFFER;
};
#define Z_MACHINEGROUP sizeof(MACHINEGROUP)
struct JOB {
struct eInstHdr hdr;
Etxt* JOBNAME;
int PRIORITY;
int VALUE;
void* ROUTING;
};
#define Z_JOB sizeof(JOB)
const int Y_JOB[6] = {sizeof(JOB), 4, 3, 1, 1, 5};
struct JOBSTEP {
struct eInstHdr hdr;
Etxt* STEPNAME;
};
#define Z_JOBSTEP sizeof(JOBSTEP)
const int Y_JOBSTEP[3] = {sizeof(JOBSTEP), 1, 3};
void d_JOBSTEP(struct JOBSTEP* &EPTR); 
struct iRef* c_JOBSTEP(); 
void d_JOB(struct JOB* &EPTR); 
struct iRef* c_JOB(); 
int X_INBUFFER(void* E1, void* E2); 
void d_MACHINEGROUP(struct MACHINEGROUP* &EPTR); 
struct MACHINEGROUP* c_MACHINEGROUP(); 
void TESTENTRY(); 

struct easeApp1_sys {
 struct eInstHdr hdr;
 struct JOB* JOB;
 struct MACHINEGROUP* MACHINEGROUP;
 struct JOBSTEP* JOBSTEP;
};
extern easeApp1_sys* easeApp1;

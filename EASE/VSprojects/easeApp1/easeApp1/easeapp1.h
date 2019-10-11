#pragma once
#include "easlib.h"


#define _TASK
#define _JOBSTEP
#define _JOB
#define _MACHINEGROUP

struct TASK {
struct eInstHdr hdr;
Etxt* STEPNAME;
int DURATION;
};
#define Z_TASK sizeof(TASK)
struct JOBSTEP {
struct eInstHdr hdr;
Etxt* STEPNAME;
};
#define Z_JOBSTEP sizeof(JOBSTEP)
struct JOB {
struct eInstHdr hdr;
Etxt* JOBNAME;
int PRIORITY;
int VALUE;
struct E_SET* ROUTING;
};
#define Z_JOB sizeof(JOB)
struct MACHINEGROUP {
struct eInstHdr hdr;
void* SETUPARR_PTR;
struct E_SET* INBUFFER;
};
#define Z_MACHINEGROUP sizeof(MACHINEGROUP)
void easeApp1_sets();
int X_INBUFFER(void* E1, void* E2);
void d_MACHINEGROUP(struct MACHINEGROUP*& EPTR);
struct MACHINEGROUP* c_MACHINEGROUP();
void d_JOB(struct JOB*& EPTR);
struct JOB* c_JOB();
void d_JOBSTEP(struct JOBSTEP*& EPTR);
struct JOBSTEP* c_JOBSTEP();
void d_TASK(struct TASK*& EPTR);
struct TASK* c_TASK();
void MAKEJOB(Etxt* NAME, int IMPORTANCE, int PRICE, struct JOB*& AJOB);
struct MACHINEGROUP* GETMACHINE_F(int MACHTYPE);
void TESTENTRY();

struct easeApp1_sys {
struct eInstHdr hdr;
struct MACHINEGROUP** JOBSHOP;
struct MACHINEGROUP* MACHINEGROUP;
struct JOB* JOB;
struct JOBSTEP* JOBSTEP;
struct TASK* TASK;
};
extern easeApp1_sys* easeApp1;
void easeApp1_init();

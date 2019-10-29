#include "stdafx.h"
#include "malloc.h"
#include "libopts.h"
#include "math.h"
#include "easeApp1.h"

void easeApp1_addTypes() {
#ifdef _TASK
addEType(E_TXTLIT_F(_T("TASK")), 4000,    4, 0);
#endif
#ifdef _JOBSTEP
addEType(E_TXTLIT_F(_T("JOBSTEP")), 4000,    3, 0);
#endif
#ifdef _JOB
addEType(E_TXTLIT_F(_T("JOB")), 4000,    2, 0);
#endif
#ifdef _MACHINEGROUP
addEType(E_TXTLIT_F(_T("MACHINEGROUP")), 4000,    1, 0);
#endif
}
easeApp1_sys* easeApp1;

void easeApp1_init() {
easeApp1 = (easeApp1_sys*)E_CREATE_F( 0,4000, sizeof(easeApp1_sys));
easeApp1_sets();
easeApp1_addTypes();
}
void easeApp1_sets() {
       return;
}
int X_INBUFFER(void* E1, void* E2) {
struct JOB* ENT1= 0;
struct JOB* ENT2= 0;
int rval = 0;
       ENT1 = (struct JOB*)E1;
       ENT2 = (struct JOB*)E2;
       if (ENT1->PRIORITY > ENT2->PRIORITY) {
       rval = (int)1;
goto retlbl;
       }
       if (ENT1->PRIORITY < ENT2->PRIORITY) {
       rval = (int)-1;
goto retlbl;
       }
       if (ENT1->VALUE > ENT2->VALUE) {
       rval = (int)1;
goto retlbl;
       }
       if (ENT1->VALUE < ENT2->VALUE) {
       rval = (int)-1;
goto retlbl;
       }
       rval = (int)0;
goto retlbl;
retlbl:
       return rval;
}
void d_MACHINEGROUP(struct MACHINEGROUP*& EPTR) {
       d_E_SET(EPTR->INBUFFER);
       E_DESTROY_R(EPTR);
       EPTR = (struct MACHINEGROUP*)0;
       return;
}
struct MACHINEGROUP* c_MACHINEGROUP() {
struct MACHINEGROUP* EPTR= 0;
struct MACHINEGROUP* rval = 0;
       EPTR = (struct MACHINEGROUP*)E_CREATE_F(4000, 1, Z_MACHINEGROUP);
       EPTR->INBUFFER= c_E_SET();
       E_TXTASG_R(&EPTR->INBUFFER->SETNAME, E_TXTLIT_F(_T("INBUFFER")));
       rval = (struct MACHINEGROUP*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void d_JOB(struct JOB*& EPTR) {
       E_TXTASG_R(&EPTR->JOBNAME, 0);
       d_E_SET(EPTR->ROUTING);
       E_DESTROY_R(EPTR);
       EPTR = (struct JOB*)0;
       return;
}
struct JOB* c_JOB() {
struct JOB* EPTR= 0;
struct JOB* rval = 0;
       EPTR = (struct JOB*)E_CREATE_F(4000, 2, Z_JOB);
       EPTR->ROUTING= c_E_SET();
       E_TXTASG_R(&EPTR->ROUTING->SETNAME, E_TXTLIT_F(_T("ROUTING")));
       rval = (struct JOB*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void d_JOBSTEP(struct JOBSTEP*& EPTR) {
       E_TXTASG_R(&EPTR->STEPNAME, 0);
       E_DESTROY_R(EPTR);
       EPTR = (struct JOBSTEP*)0;
       return;
}
struct JOBSTEP* c_JOBSTEP() {
struct JOBSTEP* EPTR= 0;
struct JOBSTEP* rval = 0;
       EPTR = (struct JOBSTEP*)E_CREATE_F(4000, 3, Z_JOBSTEP);
       rval = (struct JOBSTEP*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void d_TASK(struct TASK*& EPTR) {
       E_TXTASG_R(&EPTR->STEPNAME, 0);
       E_DESTROY_R(EPTR);
       EPTR = (struct TASK*)0;
       return;
}
struct TASK* c_TASK() {
struct TASK* EPTR= 0;
struct TASK* rval = 0;
       EPTR = (struct TASK*)E_CREATE_F(4000, 4, Z_TASK);
       rval = (struct TASK*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void MAKEJOB(Etxt* NAME, int IMPORTANCE, int PRICE, struct JOB*& AJOB) {
E_TXTINC_R(NAME);
       AJOB= c_JOB();
       E_TXTASG_R(&AJOB->JOBNAME, NAME);
       AJOB->PRIORITY = IMPORTANCE;
       AJOB->VALUE = PRICE;
       goto retlbl;
retlbl:
E_TXTDEL_R(NAME);
       return;
}
struct MACHINEGROUP* GETMACHINES_F(int MACHTYPE, int NUMBER) {
struct MACHINEGROUP* rval = 0;
       easeApp1->MACHINEGROUP= c_MACHINEGROUP();
       easeApp1->MACHINEGROUP->COUNT = NUMBER;
       rval = (struct MACHINEGROUP*)easeApp1->MACHINEGROUP;
goto retlbl;
retlbl:
       return rval;
}

void easinit() {
easeApp1_init();
easlib_init();
#ifdef EASsets
easeSets_init();
#endif
}
void main() {
int N= 0;
       easinit();
       USE_R(1, 2);
       WTX_R(E_TXTLIT_F(_T("Testing console input/output: enter a (small) number")));
       WTL_R();
       USE_R(2, 1);
       N = RDN_F();
next0001:
       if ( !  ( N > 0 ) ) {
       goto done0001;
       }
       WTI_R(N, 6);
       WTL_R();
       N = N-1;
       goto next0001;
done0001:
       MYJOBSHOP();
       WTX_R(E_TXTLIT_F(_T("See the output file - jobs.txt - in the VSprojects/easeApp1/easeApp1 folder")));
       WTL_R();
       return;
}
void MYJOBSHOP() {
struct MACHINEGROUP* MG1= 0;
struct JOB* MYJOB= 0;
int I= 0;
int J= 0;
Etxt* NAME= 0;
struct JOB* E_0001= 0;
struct JOB* E_0002= 0;
struct JOBSTEP* E_0003= 0;
struct JOB* E_0004= 0;
       easeApp1->N_MACHINEGROUP = 5;
       easeApp1->JOBSHOP = (MACHINEGROUP**)calloc(easeApp1->N_MACHINEGROUP + 1, sizeof(MACHINEGROUP*));
       easeApp1->JOBSHOP[0] = (MACHINEGROUP*)(easeApp1->N_MACHINEGROUP);
       I = 1;
       goto test0001;
next0001:
       I = I+1;
test0001:
       if (I > easeApp1->N_MACHINEGROUP) {
       goto done0001;
       }
       easeApp1->JOBSHOP[1] = (struct MACHINEGROUP*)GETMACHINES_F(I, 3);
       goto next0001;
done0001:
       MG1 = (struct MACHINEGROUP*)easeApp1->JOBSHOP[1];
       OPENO_R(6, E_TXTLIT_F(_T("jobs.txt")));
       USE_R(6, 2);
       WTX_R(E_TXTLIT_F(_T("Testing RANKED set filing by PRIORITY, then VALUE")));
       WTL_R();
       OPENI_R(5, E_TXTLIT_F(_T("jobdata.txt")));
       USE_R(5, 1);
       if (easlib->UIB_R->ROPENERR_V == 0) {
       easlib->UIB_R->EOF_V = 1;
       }
next0002:
       if ( !  ( easlib->UIB_R->EOF_V != 2 ) ) {
       goto done0002;
       }
       E_TXTASG_R(&NAME, RDS_F());
       MAKEJOB(NAME, 0, 0, easeApp1->JOB);
       easeApp1->JOB->PRIORITY = RDN_F();
       easeApp1->JOB->VALUE = RDN_F();
       WTI_R(easeApp1->JOB->PRIORITY, 6);
       WTI_R(easeApp1->JOB->VALUE, 6);
       WTS_R(2);
       WTX_R(easeApp1->JOB->JOBNAME);
       WTL_R();
       J = RDN_F();
       I = 1;
       goto test0003;
next0003:
       I = I+1;
test0003:
       if (I > J) {
       goto done0003;
       }
       easeApp1->JOBSTEP= c_JOBSTEP();
       E_TXTASG_R(&easeApp1->JOBSTEP->STEPNAME, RDX_F());
       E_FFIRST_R(easeApp1->JOB->ROUTING, easeApp1->JOBSTEP);
       goto next0003;
done0003:
       E_FRANK_R(MG1->INBUFFER, easeApp1->JOB, X_INBUFFER);
       RDL_R();
       goto next0002;
done0002:
       CLOSE_R(5);
       WTX_R(E_TXTLIT_F(_T("Listing RANKED set contents:")));
       WTL_R();
       WTX_R(E_TXTLIT_F(_T("SEQ   PRI   VAL")));
       WTL_R();
       I = 1;
       easeApp1->JOB = (struct JOB*)((struct JOB*)F_EASSET_F(MG1->INBUFFER));
       goto test0004;
next0004:
       easeApp1->JOB = (struct JOB*)E_0001;
test0004:
       if (easeApp1->JOB == 0) {
       goto done0004;
       }
       E_0001 = (struct JOB*)((struct JOB*)S_EASSET_F(easeApp1->JOB, E_TXTLIT_F(_T("INBUFFER"))));
       if ( !  ( ((struct JOBSTEP*)F_EASSET_F(easeApp1->JOB->ROUTING)) != 0 ) ) {
       goto done0004;
       }
       easeApp1->TASK= c_TASK();
       easeApp1->TASK->DURATION = I*30;
       E_FLAST_R(easeApp1->JOB->ROUTING, easeApp1->TASK);
       WTI_R(I, 3);
       WTI_R(easeApp1->JOB->PRIORITY, 6);
       WTI_R(easeApp1->JOB->VALUE, 6);
       WTS_R(2);
       WTX_R(easeApp1->JOB->JOBNAME);
       WTL_R();
       I = I+1;
       goto next0004;
done0004:
       WTX_R(E_TXTLIT_F(_T("TOTAL JOBS: ")));
       WTI_R(N_EASSET_F(MG1->INBUFFER), 3);
       WTL_R();
       WTX_R(E_TXTLIT_F(_T("Testing FOR EACH in set ")));
       WTL_R();
       MYJOB = (struct JOB*)((struct JOB*)F_EASSET_F(MG1->INBUFFER));
       goto test0005;
next0005:
       MYJOB = (struct JOB*)E_0002;
test0005:
       if (MYJOB == 0) {
       goto done0005;
       }
       E_0002 = (struct JOB*)((struct JOB*)S_EASSET_F(MYJOB, E_TXTLIT_F(_T("INBUFFER"))));
       WTX_R(E_TXTLIT_F(_T("JOB: ")));
       WTX_R(MYJOB->JOBNAME);
       WTB_R(20);
       easeApp1->JOBSTEP = (struct JOBSTEP*)((struct JOBSTEP*)F_EASSET_F(MYJOB->ROUTING));
       goto test0006;
next0006:
       easeApp1->JOBSTEP = (struct JOBSTEP*)E_0003;
test0006:
       if (easeApp1->JOBSTEP == 0) {
       goto done0006;
       }
       E_0003 = (struct JOBSTEP*)((struct JOBSTEP*)S_EASSET_F(easeApp1->JOBSTEP, E_TXTLIT_F(_T("ROUTING"))));
       WTX_R(easeApp1->JOBSTEP->STEPNAME);
       WTS_R(2);
       goto next0006;
done0006:
       WTL_R();
       goto next0005;
done0005:
       WTX_R(E_TXTLIT_F(_T("Testing cascaded set attribute references: 1st & 2nd step names of 1st, then 1st of 2nd job")));
       WTL_R();
       WTX_R(((struct JOBSTEP*)F_EASSET_F(((struct JOB*)F_EASSET_F(MG1->INBUFFER))->ROUTING))->STEPNAME);
       WTL_R();
       WTX_R(((struct JOBSTEP*)S_EASSET_F(((struct JOBSTEP*)F_EASSET_F(((struct JOB*)F_EASSET_F(MG1->INBUFFER))->ROUTING)), E_TXTLIT_F(_T("ROUTING"))))->STEPNAME);
       WTL_R();
       WTX_R(((struct JOBSTEP*)F_EASSET_F(((struct JOB*)S_EASSET_F(((struct JOB*)F_EASSET_F(MG1->INBUFFER)), E_TXTLIT_F(_T("INBUFFER"))))->ROUTING))->STEPNAME);
       WTL_R();
       WTX_R(E_TXTLIT_F(_T("Testing FIND - look for PRIORITY > 2 ")));
       WTL_R();
       MYJOB = (struct JOB*)((struct JOB*)F_EASSET_F(MG1->INBUFFER));
       goto test0007;
next0007:
       MYJOB = (struct JOB*)E_0004;
test0007:
       if (MYJOB == 0) {
       goto done0007;
       }
       E_0004 = (struct JOB*)((struct JOB*)S_EASSET_F(MYJOB, E_TXTLIT_F(_T("INBUFFER"))));
       if ( !  ( MYJOB->PRIORITY > 2 ) ) {
       goto next0007;
       }
       easlib->E_FOUND_V = 1;
       goto skip0007;
done0007:
       easlib->E_FOUND_V = 0;
skip0007:
       if (easlib->E_FOUND_V != 0) {
       WTX_R(E_TXTLIT_F(_T("JOB: ")));
       WTX_R(MYJOB->JOBNAME);
       WTX_R(E_TXTLIT_F(_T(" has priority ")));
       WTI_R(MYJOB->PRIORITY, 2);
       WTX_R(E_TXTLIT_F(_T(" - REMOVE specific")));
       WTL_R();
       E_RMVSPCFC_R(MG1->INBUFFER, MYJOB);
       WTX_R(E_TXTLIT_F(_T(" removed - you won't see this name again")));
       WTL_R();
       if (((struct JOB*)S_EASSET_F(MYJOB, E_TXTLIT_F(_T("INBUFFER")))) == 0) {
       WTX_R(E_TXTLIT_F(_T("Testing for S.set - passed")));
       WTL_R();
       }
       d_JOB(MYJOB);
       }
       WTX_R(E_TXTLIT_F(_T("INBUFFER set count is now = ")));
       WTI_R(N_EASSET_F(MG1->INBUFFER), 4);
       WTL_R();
next0008:
       if ( !  ( N_EASSET_F(MG1->INBUFFER) != 0 ) ) {
       goto done0008;
       }
       MYJOB = (struct JOB*)E_RMVFRST_F(MG1->INBUFFER);
       WTX_R(E_TXTLIT_F(_T("Removed JOB called ")));
       WTX_R(MYJOB->JOBNAME);
       WTL_R();
next0009:
       if ( !  ( ((struct JOBSTEP*)F_EASSET_F(MYJOB->ROUTING)) != 0 ) ) {
       goto done0009;
       }
       if (E_TXTEQL_F(E_TYPENAME_F(((struct JOBSTEP*)F_EASSET_F(MYJOB->ROUTING))), E_TXTLIT_F(_T("TASK")))) {
       WTX_R(E_TXTLIT_F(_T("Removing a TASK: duration ")));
       WTI_R(easeApp1->TASK->DURATION, 4);
       WTL_R();
       easeApp1->TASK = (struct TASK*)E_RMVFRST_F(MYJOB->ROUTING);
       }
       else {
       easeApp1->JOBSTEP = (struct JOBSTEP*)E_RMVFRST_F(MYJOB->ROUTING);
       WTX_R(E_TXTLIT_F(_T("Cleared step ")));
       WTX_R(easeApp1->JOBSTEP->STEPNAME);
       WTL_R();
       d_JOBSTEP(easeApp1->JOBSTEP);
       }
       goto next0009;
done0009:
       d_JOB(MYJOB);
       goto next0008;
done0008:
       WTX_R(E_TXTLIT_F(_T("Testing PRINT THUS")));
       WTL_R();
       WTX_R(E_TXTLIT_F(_T("INBUFFER IS EMPTY - THERE ARE NO JOBS WAITING")));
       WTL_R();
       CLOSE_R(6);
       E_TXTDEL_R(NAME);
       return;
}

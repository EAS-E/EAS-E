#include "stdafx.h"
#include "malloc.h"
	#define EASpersist
#include "libopts.h"
#include "math.h"
#include "pjobsdef.h"

void pjobsdef_addTypes() {
#ifdef _JOBSTEP
addEType(E_TXTLIT_F(_T("JOBSTEP")), 2000,    3, Y_JOBSTEP);
#endif
#ifdef _JOB
addEType(E_TXTLIT_F(_T("JOB")), 2000,    2, Y_JOB);
#endif
}
pjobsdef_sys* pjobsdef;

void pjobsdef_init() {
pjobsdef = (pjobsdef_sys*)E_CREATE_F( 0,2000, sizeof(pjobsdef_sys));
pjobsdef_sets();
pjobsdef_addTypes();
}
void pjobsdef_sets() {
       return;
}
int X_INBUFFER(void* E1, void* E2) {
struct JOB* ENT1= 0;
struct JOB* ENT2= 0;
int rval = 0;
       easg((char*)&ENT1, (iRef*)E1);
       easg((char*)&ENT2, (iRef*)E2);
       if ((int)((struct JOB*)fetch((iRef*)ENT1))->PRIORITY > (int)((struct JOB*)fetch((iRef*)ENT2))->PRIORITY) {
       rval = (int)1;
goto retlbl;
       }
       if ((int)((struct JOB*)fetch((iRef*)ENT1))->PRIORITY < (int)((struct JOB*)fetch((iRef*)ENT2))->PRIORITY) {
       rval = (int)-1;
goto retlbl;
       }
       if ((int)((struct JOB*)fetch((iRef*)ENT1))->VALUE > (int)((struct JOB*)fetch((iRef*)ENT2))->VALUE) {
       rval = (int)1;
goto retlbl;
       }
       if ((int)((struct JOB*)fetch((iRef*)ENT1))->VALUE < (int)((struct JOB*)fetch((iRef*)ENT2))->VALUE) {
       rval = (int)-1;
goto retlbl;
       }
       rval = (int)0;
goto retlbl;
retlbl:
eunasg((char*)&ENT1);
eunasg((char*)&ENT2);
       return rval;
}
void d_JOB(struct JOB*& EPTR) {
       E_TXTASG_R(&(Etxt*)((struct JOB*)fetch((iRef*)EPTR))->JOBNAME, 0);
       d_E_PSET((struct E_PSET*)((struct JOB*)fetch((iRef*)EPTR))->ROUTING);
       E_PDESTROY_R(EPTR);
       easg((char*)&EPTR, (iRef*)0);
       eunasg((char*)&EPTR);
       return;
}
struct iRef* c_JOB() {
struct iRef* EPTR= 0;
struct iRef* rval = 0;
       EPTR = (struct iRef*)E_PCREATE_F(2000, 2, Z_JOB);
       easg((char*)&(*(E_PSET*)&((struct JOB*)fetch((iRef*)EPTR))->ROUTING), c_E_PSET());
       E_TXTASG_R(&(Etxt*)((struct E_PSET*)fetch((iRef*)(struct E_PSET*)((struct JOB*)fetch((iRef*)EPTR))->ROUTING))->PSETNAME, E_TXTLIT_F(_T("ROUTING")));
       rval = (struct iRef*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void d_JOBSTEP(struct JOBSTEP*& EPTR) {
       E_TXTASG_R(&(Etxt*)((struct JOBSTEP*)fetch((iRef*)EPTR))->STEPNAME, 0);
       E_PDESTROY_R(EPTR);
       easg((char*)&EPTR, (iRef*)0);
       eunasg((char*)&EPTR);
       return;
}
struct iRef* c_JOBSTEP() {
struct iRef* EPTR= 0;
struct iRef* rval = 0;
       EPTR = (struct iRef*)E_PCREATE_F(2000, 3, Z_JOBSTEP);
       rval = (struct iRef*)EPTR;
goto retlbl;
retlbl:
       return rval;
}

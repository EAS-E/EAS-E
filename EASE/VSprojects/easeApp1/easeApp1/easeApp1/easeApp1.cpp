#include "stdafx.h"
#include "malloc.h"
#include "easeApp1.h"

void addTypes() {
addPtype(4000, 2, Y_JOB);
addPtype(4000, 3, Y_JOBSTEP);
addPtype(2, 12, Y_E_PINSTH);
addPtype(2, 14, Y_E_PCARD);
addPtype(2, 16, Y_E_PSETHDR);
}
easeApp1_sys* easeApp1;
easlib_sys* easlib;

void easinit() {
easeApp1 = (easeApp1_sys*)E_CREATE_F(4000, 0, sizeof(easeApp1_sys));
easlib = (easlib_sys*)E_CREATE_F(2, 0, sizeof(easlib_sys));
addTypes();
}
void d_JOBSTEP(JOBSTEP* &EPTR) { 
    E_TXTASG_R(&(Etxt*)((struct JOBSTEP*)fetch((iRef*)EPTR))->STEPNAME, 0);
    E_PDESTROY_R(EPTR);
    easg((char*)&EPTR, (iRef*)0);
    eunasg((char*)&EPTR);
return;
}
iRef* c_JOBSTEP() { 
iRef* EPTR = 0;
iRef* rval = 0;
    EPTR = (struct iRef*)E_PCREATE_F(4000,3,Z_JOBSTEP);
    rval = (iRef*)EPTR;
goto ret;
ret:
return rval;
}
void d_JOB(JOB* &EPTR) { 
    E_TXTASG_R(&(Etxt*)((struct JOB*)fetch((iRef*)EPTR))->JOBNAME, 0);
    E_PDELSET_R((void*)((struct JOB*)fetch((iRef*)EPTR))->ROUTING);
    E_PDESTROY_R(EPTR);
    easg((char*)&EPTR, (iRef*)0);
    eunasg((char*)&EPTR);
return;
}
iRef* c_JOB() { 
iRef* EPTR = 0;
iRef* rval = 0;
    EPTR = (struct iRef*)E_PCREATE_F(4000,2,Z_JOB);
    easg((char*)&(*(void**)&((struct JOB*)fetch((iRef*)EPTR))->ROUTING), (iRef*)E_PINITSET_F(E_TXTLIT_F(_T("ROUTING")),2, 16));
    rval = (iRef*)EPTR;
goto ret;
ret:
return rval;
}
int X_INBUFFER(void* E1, void* E2) { 
int rval = 0;
struct JOB* ENT1 = 0;
struct JOB* ENT2 = 0;
    easg((char*)&ENT1, (iRef*)E1);
    easg((char*)&ENT2, (iRef*)E2);
    if ((int)((struct JOB*)fetch((iRef*)ENT1))->PRIORITY > (int)((struct JOB*)fetch((iRef*)ENT2))->PRIORITY ) { 
    rval = (int)1;
goto ret;
    } 
    if ((int)((struct JOB*)fetch((iRef*)ENT1))->PRIORITY < (int)((struct JOB*)fetch((iRef*)ENT2))->PRIORITY ) { 
    rval = (int)-1;
goto ret;
    } 
    if ((int)((struct JOB*)fetch((iRef*)ENT1))->VALUE > (int)((struct JOB*)fetch((iRef*)ENT2))->VALUE ) { 
    rval = (int)1;
goto ret;
    } 
    if ((int)((struct JOB*)fetch((iRef*)ENT1))->VALUE < (int)((struct JOB*)fetch((iRef*)ENT2))->VALUE ) { 
    rval = (int)-1;
goto ret;
    } 
    rval = (int)0;
goto ret;
ret:
return rval;
}
void d_MACHINEGROUP(MACHINEGROUP* &EPTR) { 
    E_PDELSET_R((void*)EPTR->INBUFFER);
    E_DESTROY_R(EPTR);
    EPTR = (struct MACHINEGROUP*)0;
return;
}
MACHINEGROUP* c_MACHINEGROUP() { 
MACHINEGROUP* EPTR = 0;
MACHINEGROUP* rval = 0;
    EPTR = (struct MACHINEGROUP*)E_CREATE_F(4000,1,Z_MACHINEGROUP);
    easg((char*)&EPTR->INBUFFER, (iRef*)E_PINITSET_F(E_TXTLIT_F(_T("INBUFFER")),2, 16));
    rval = (MACHINEGROUP*)EPTR;
goto ret;
ret:
return rval;
}
void main() { 
    easinit();
    TESTENTRY();
return;
}
void TESTENTRY() { 
MACHINEGROUP* MG1 = 0;
JOB* MYJOB = 0;
JOB* JOB = 0;
int I = 0;
int J = 0;
int K = 0;
MG1 = c_MACHINEGROUP();
    OPENI_R(5, E_TXTLIT_F(_T("C:\\EASEprojects\\jobdata.txt")));
    easlib->UIB_R->EOF_V = 1;
    I = 1;
    OPENO_R(6, E_TXTLIT_F(_T("C:\\EASEprojects\\jobs.txt")));
    WTX_R(E_TXTLIT_F(_T("Testing RANKED set filing by PRIORITY, then VALUE")));
    WTL_R();
next0006: 
    if ( !  ( easlib->UIB_R->EOF_V != 2 )  ) { 
    goto done0006; 
    } 
easg((char*)&JOB, c_JOB());
    E_TXTASG_R(&(Etxt*)((struct JOB*)fetch((iRef*)JOB))->JOBNAME, RDS_F());
    (*(int*)&((struct JOB*)fetch((iRef*)JOB))->PRIORITY) = RDN_F();
    (*(int*)&((struct JOB*)fetch((iRef*)JOB))->VALUE) = RDN_F();
    WTI_R((int)((struct JOB*)fetch((iRef*)JOB))->PRIORITY, 6);
    WTI_R((int)((struct JOB*)fetch((iRef*)JOB))->VALUE, 6);
    WTS_R(2);
    WTX_R((Etxt*)((struct JOB*)fetch((iRef*)JOB))->JOBNAME);
    WTL_R();
    J = RDN_F();
    I = 1;
    goto test0007; 
next0007: 
    I = I+1;
test0007: 
    if (I > J ) { 
    goto done0007; 
    } 
easg((char*)&easeApp1->JOBSTEP, c_JOBSTEP());
    E_TXTASG_R(&(Etxt*)((struct JOBSTEP*)fetch((iRef*)(struct JOBSTEP*)easeApp1->JOBSTEP))->STEPNAME, RDS_F());
    E_PFFIRST_R((void*)((struct JOB*)fetch((iRef*)JOB))->ROUTING, (struct JOBSTEP*)easeApp1->JOBSTEP);
    goto next0007; 
done0007: 
    E_PFRANK_R((void*)MG1->INBUFFER, JOB, X_INBUFFER);
    RDL_R();
    goto next0006; 
done0006: 
    CLOSE_R(5);
    WTX_R(E_TXTLIT_F(_T("Listing RANKED set contents:")));
    WTL_R();
    WTX_R(E_TXTLIT_F(_T("SEQ   PRI   VAL")));
    WTL_R();
    I = 1;
struct JOB* E_0001 = 0;
    easg((char*)&JOB, (iRef*)F_PEASSET_F(MG1->INBUFFER));
    goto test0008; 
next0008: 
    easg((char*)&JOB, (iRef*)E_0001);
test0008: 
    if (JOB == 0 ) { 
    goto done0008; 
    } 
    easg((char*)&E_0001, (iRef*)S_PEASSET_F((iRef*)JOB, E_TXTLIT_F(_T("INBUFFER"))));
    WTI_R(I, 3);
    WTI_R((int)((struct JOB*)fetch((iRef*)JOB))->PRIORITY, 6);
    WTI_R((int)((struct JOB*)fetch((iRef*)JOB))->VALUE, 6);
    WTS_R(2);
    WTX_R((Etxt*)((struct JOB*)fetch((iRef*)JOB))->JOBNAME);
    WTL_R();
    I = I+1;
struct JOBSTEP* E_0002 = 0;
    easg((char*)&easeApp1->JOBSTEP, (iRef*)F_PEASSET_F(((struct JOB*)fetch((iRef*)JOB))->ROUTING));
    goto test0009; 
next0009: 
    easg((char*)&easeApp1->JOBSTEP, (iRef*)E_0002);
test0009: 
    if ((struct JOBSTEP*)easeApp1->JOBSTEP == 0 ) { 
    goto done0009; 
    } 
    easg((char*)&E_0002, (iRef*)S_PEASSET_F((iRef*)(struct JOBSTEP*)easeApp1->JOBSTEP, E_TXTLIT_F(_T("ROUTING"))));
    WTX_R((Etxt*)((struct JOBSTEP*)fetch((iRef*)(struct JOBSTEP*)easeApp1->JOBSTEP))->STEPNAME);
    WTL_R();
    goto next0009; 
done0009: 
    goto next0008; 
done0008: 
    WTX_R(E_TXTLIT_F(_T("TOTAL JOBS: ")));
    WTI_R(N_PEASSET_F(MG1->INBUFFER), 3);
    WTL_R();
    WTX_R(E_TXTLIT_F(_T("Testing FOR EACH in set ")));
    WTL_R();
struct JOB* E_0003 = 0;
    easg((char*)&MYJOB, (iRef*)F_PEASSET_F(MG1->INBUFFER));
    goto test0010; 
next0010: 
    easg((char*)&MYJOB, (iRef*)E_0003);
test0010: 
    if (MYJOB == 0 ) { 
    goto done0010; 
    } 
    easg((char*)&E_0003, (iRef*)S_PEASSET_F((iRef*)MYJOB, E_TXTLIT_F(_T("INBUFFER"))));
    WTX_R(E_TXTLIT_F(_T("JOB: ")));
    WTX_R((Etxt*)((struct JOB*)fetch((iRef*)MYJOB))->JOBNAME);
    WTB_R(20);
struct JOBSTEP* E_0004 = 0;
    easg((char*)&easeApp1->JOBSTEP, (iRef*)F_PEASSET_F(((struct JOB*)fetch((iRef*)MYJOB))->ROUTING));
    goto test0011; 
next0011: 
    easg((char*)&easeApp1->JOBSTEP, (iRef*)E_0004);
test0011: 
    if ((struct JOBSTEP*)easeApp1->JOBSTEP == 0 ) { 
    goto done0011; 
    } 
    easg((char*)&E_0004, (iRef*)S_PEASSET_F((iRef*)(struct JOBSTEP*)easeApp1->JOBSTEP, E_TXTLIT_F(_T("ROUTING"))));
    WTX_R((Etxt*)((struct JOBSTEP*)fetch((iRef*)(struct JOBSTEP*)easeApp1->JOBSTEP))->STEPNAME);
    WTS_R(2);
    goto next0011; 
done0011: 
    WTL_R();
    goto next0010; 
done0010: 
    WTX_R(E_TXTLIT_F(_T("Implicit: JOBNAME.., FOR EACH JOBSTEP, STEPNAME")));
    WTL_R();
struct JOB* E_0005 = 0;
    easg((char*)&JOB, (iRef*)F_PEASSET_F(MG1->INBUFFER));
    goto test0012; 
next0012: 
    easg((char*)&JOB, (iRef*)E_0005);
test0012: 
    if (JOB == 0 ) { 
    goto done0012; 
    } 
    easg((char*)&E_0005, (iRef*)S_PEASSET_F((iRef*)JOB, E_TXTLIT_F(_T("INBUFFER"))));
    WTX_R((Etxt*)((struct JOB*)fetch((iRef*)JOB))->JOBNAME);
    WTS_R(3);
struct JOBSTEP* E_0006 = 0;
    easg((char*)&easeApp1->JOBSTEP, (iRef*)F_PEASSET_F(((struct JOB*)fetch((iRef*)JOB))->ROUTING));
    goto test0013; 
next0013: 
    easg((char*)&easeApp1->JOBSTEP, (iRef*)E_0006);
test0013: 
    if ((struct JOBSTEP*)easeApp1->JOBSTEP == 0 ) { 
    goto done0013; 
    } 
    easg((char*)&E_0006, (iRef*)S_PEASSET_F((iRef*)(struct JOBSTEP*)easeApp1->JOBSTEP, E_TXTLIT_F(_T("ROUTING"))));
    WTX_R((Etxt*)((struct JOBSTEP*)fetch((iRef*)easeApp1->JOBSTEP))->STEPNAME);
    WTS_R(2);
    goto next0013; 
done0013: 
    if (S_PEASSET_F((iRef*)JOB, E_TXTLIT_F(_T("INBUFFER"))) != 0 ) { 
    WTX_R(E_TXTLIT_F(_T("next job will be:  ")));
    WTX_R((Etxt*)((struct JOB*)fetch((iRef*)S_PEASSET_F((iRef*)JOB, E_TXTLIT_F(_T("INBUFFER")))))->JOBNAME);
    } 
    WTL_R();
    goto next0012; 
done0012: 
    WTX_R(E_TXTLIT_F(_T("Testing cascaded set attribute refs: 1st step name of 2nd job")));
    WTL_R();
    WTX_R((Etxt*)((struct JOBSTEP*)fetch((iRef*)F_PEASSET_F(((struct JOB*)fetch((iRef*)S_PEASSET_F((iRef*)F_PEASSET_F(MG1->INBUFFER), E_TXTLIT_F(_T("INBUFFER")))))->ROUTING)))->STEPNAME);
    WTL_R();
    WTX_R(E_TXTLIT_F(_T("Testing FIND - look for PRIORITY > 2 ")));
    WTL_R();
struct JOB* E_0007 = 0;
    easg((char*)&MYJOB, (iRef*)F_PEASSET_F(MG1->INBUFFER));
    goto test0014; 
next0014: 
    easg((char*)&MYJOB, (iRef*)E_0007);
test0014: 
    if (MYJOB == 0 ) { 
    goto done0014; 
    } 
    easg((char*)&E_0007, (iRef*)S_PEASSET_F((iRef*)MYJOB, E_TXTLIT_F(_T("INBUFFER"))));
    if ( !  ( (int)((struct JOB*)fetch((iRef*)MYJOB))->PRIORITY > 2 )  ) { 
    goto next0014; 
    } 
    easlib->E_FOUND_V = 1;
    goto skip0014; 
done0014: 
    easlib->E_FOUND_V = 0;
skip0014: 
    if (easlib->E_FOUND_V != 0 ) { 
    WTX_R(E_TXTLIT_F(_T("JOB: ")));
    WTX_R((Etxt*)((struct JOB*)fetch((iRef*)MYJOB))->JOBNAME);
    WTX_R(E_TXTLIT_F(_T(" has priority ")));
    WTI_R((int)((struct JOB*)fetch((iRef*)MYJOB))->PRIORITY, 2);
    WTX_R(E_TXTLIT_F(_T(" - REMOVE specific")));
    WTL_R();
    E_PRMVSPCFC_R((void*)MG1->INBUFFER, MYJOB);
    WTX_R(E_TXTLIT_F(_T(" removed - you won't see this name again")));
    WTL_R();
    } 
    E_RECORD_R();
    WTX_R(E_TXTLIT_F(_T("INBUFFER set count is now = ")));
    WTI_R(N_PEASSET_F(MG1->INBUFFER), 4);
    WTL_R();
next0015: 
    if ( !  ( N_PEASSET_F(MG1->INBUFFER) != 0 )  ) { 
    goto done0015; 
    } 
    easg((char*)&MYJOB, (iRef*)E_PRMVFRST_F((void*)MG1->INBUFFER));
    WTX_R(E_TXTLIT_F(_T("Removed JOB called ")));
    WTX_R((Etxt*)((struct JOB*)fetch((iRef*)MYJOB))->JOBNAME);
    WTL_R();
next0016: 
    if ( !  ( F_PEASSET_F(((struct JOB*)fetch((iRef*)MYJOB))->ROUTING) != 0 )  ) { 
    goto done0016; 
    } 
    easg((char*)&easeApp1->JOBSTEP, (iRef*)E_PRMVFRST_F((void*)((struct JOB*)fetch((iRef*)MYJOB))->ROUTING));
    WTX_R(E_TXTLIT_F(_T("Cleared step ")));
    WTX_R((Etxt*)((struct JOBSTEP*)fetch((iRef*)easeApp1->JOBSTEP))->STEPNAME);
    WTL_R();
    d_JOBSTEP((struct JOBSTEP*)easeApp1->JOBSTEP);
    goto next0016; 
done0016: 
    d_JOB(MYJOB);
    goto next0015; 
done0015: 
    WTX_R(E_TXTLIT_F(_T("Testing PRINT THUS")));
    WTL_R();
    WTX_R(E_TXTLIT_F(_T("INBUFFER IS EMPTY - THERE ARE NO JOBS WAITING")));
    WTL_R();
    CLOSE_R(6);
    eunasg((char*)&MYJOB);
    eunasg((char*)&JOB);
return;
}

#include "stdafx.h"
#include "malloc.h"
#include "libopts.h"
#include "math.h"
#include "easeApp2.h"

void easeApp2_addTypes() {
#ifdef _MACHINEGROUP
addEType(E_TXTLIT_F(_T("MACHINEGROUP")), 5000,    1, 0);
#endif
}
easeApp2_sys* easeApp2;

void easeApp2_init() {
easeApp2 = (easeApp2_sys*)E_CREATE_F( 0,5000, sizeof(easeApp2_sys));
easeApp2_sets();
easeApp2_addTypes();
}
void easeApp2_sets() {
       return;
}
void d_MACHINEGROUP(struct MACHINEGROUP*& EPTR) {
       d_E_PSET((struct E_PSET*)EPTR->INBUFFER);
       E_DESTROY_R(EPTR);
       EPTR = (struct MACHINEGROUP*)0;
       return;
}
struct MACHINEGROUP* c_MACHINEGROUP() {
struct MACHINEGROUP* EPTR= 0;
struct MACHINEGROUP* rval = 0;
       EPTR = (struct MACHINEGROUP*)E_CREATE_F(5000, 1, Z_MACHINEGROUP);
       easg((char*)&EPTR->INBUFFER, c_E_PSET());
       E_TXTASG_R(&(Etxt*)((struct E_PSET*)fetch((iRef*)(struct E_PSET*)EPTR->INBUFFER))->PSETNAME, E_TXTLIT_F(_T("INBUFFER")));
       rval = (struct MACHINEGROUP*)EPTR;
goto retlbl;
retlbl:
       return rval;
}

void easinit() {
pjobsdef_init();
easeApp2_init();
easlib_init();
#ifdef EASsets
easeSets_init();
#endif
}
void main() {
       easinit();
       TESTENTRY();
       return;
}
void TESTENTRY() {
struct MACHINEGROUP* MG1= 0;
struct JOB* JOB= 0;
struct JOB* MYJOB= 0;
int I= 0;
int J= 0;
Etxt* SERVERNAME= 0;
struct JOB* E_0001= 0;
struct JOBSTEP* E_0002= 0;
struct JOB* E_0003= 0;
struct JOBSTEP* E_0004= 0;
struct JOB* E_0005= 0;
struct JOBSTEP* E_0006= 0;
struct JOB* E_0007= 0;
       OPENO_R(6, E_TXTLIT_F(_T("jobs.txt")));
       USE_R(6, 2);
       OPENI_R(5, E_TXTLIT_F(_T("localdata.txt")));
       USE_R(5, 1);
       E_TXTASG_R(&SERVERNAME, RDX_F());
       E_PCONNECT_R(SERVERNAME);
       RDL_R();
       if (easlib->UIB_R->EOF_V != 2) {
       MG1= c_MACHINEGROUP();
       easg((char*)&MG1->INBUFFER, (iRef*)RDP_F());
       RDL_R();
       }
       CLOSE_R(5);
       if (MG1 == 0) {
       MG1= c_MACHINEGROUP();
       WTX_R(E_TXTLIT_F(_T("Testing RANKED set filing by PRIORITY, then VALUE")));
       WTL_R();
       WTX_R(E_TXTLIT_F(_T("Reading job data... ")));
       WTL_R();
       OPENI_R(5, E_TXTLIT_F(_T("jobdata.txt")));
       USE_R(5, 1);
       easlib->UIB_R->EOF_V = 1;
next0001:
       if ( !  ( easlib->UIB_R->EOF_V != 2 ) ) {
       goto done0001;
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
       goto test0002;
next0002:
       I = I+1;
test0002:
       if (I > J) {
       goto done0002;
       }
       easg((char*)&pjobsdef->JOBSTEP, c_JOBSTEP());
       E_TXTASG_R(&(Etxt*)((struct JOBSTEP*)fetch((iRef*)(struct JOBSTEP*)pjobsdef->JOBSTEP))->STEPNAME, RDS_F());
       E_PFFIRST_R((struct E_PSET*)((struct JOB*)fetch((iRef*)JOB))->ROUTING, (struct JOBSTEP*)pjobsdef->JOBSTEP);
       goto next0002;
done0002:
       E_PFRANK_R((struct E_PSET*)MG1->INBUFFER, JOB, X_INBUFFER);
       RDL_R();
       goto next0001;
done0001:
       CLOSE_R(5);
       E_RECORD_R();
       }
       WTX_R(E_TXTLIT_F(_T("Listing RANKED set contents:")));
       WTL_R();
       WTX_R(E_TXTLIT_F(_T("SEQ   PRI   VAL")));
       WTL_R();
       I = 1;
       easg((char*)&JOB, (iRef*)((struct JOB*)F_PEASSET_F(MG1->INBUFFER)));
       goto test0003;
next0003:
       easg((char*)&JOB, (iRef*)E_0001);
test0003:
       if (JOB == 0) {
       goto done0003;
       }
       easg((char*)&E_0001, (iRef*)S_PEASSET_F((iRef*)JOB, E_TXTLIT_F(_T("INBUFFER"))));
       WTI_R(I, 3);
       WTI_R((int)((struct JOB*)fetch((iRef*)JOB))->PRIORITY, 6);
       WTI_R((int)((struct JOB*)fetch((iRef*)JOB))->VALUE, 6);
       WTS_R(2);
       WTX_R((Etxt*)((struct JOB*)fetch((iRef*)JOB))->JOBNAME);
       WTL_R();
       I = I+1;
       easg((char*)&pjobsdef->JOBSTEP, (iRef*)F_PEASSET_F(((struct JOB*)fetch((iRef*)JOB))->ROUTING));
       goto test0004;
next0004:
       easg((char*)&pjobsdef->JOBSTEP, (iRef*)E_0002);
test0004:
       if ((struct JOBSTEP*)pjobsdef->JOBSTEP == 0) {
       goto done0004;
       }
       easg((char*)&E_0002, (iRef*)S_PEASSET_F((iRef*)(struct JOBSTEP*)pjobsdef->JOBSTEP, E_TXTLIT_F(_T("ROUTING"))));
       WTX_R((Etxt*)((struct JOBSTEP*)fetch((iRef*)(struct JOBSTEP*)pjobsdef->JOBSTEP))->STEPNAME);
       WTL_R();
       goto next0004;
done0004:
       goto next0003;
done0003:
       WTX_R(E_TXTLIT_F(_T("TOTAL JOBS: ")));
       WTI_R(N_PEASSET_F(MG1->INBUFFER), 3);
       WTL_R();
       WTX_R(E_TXTLIT_F(_T("Testing FOR EACH in set ")));
       WTL_R();
       easg((char*)&MYJOB, (iRef*)((struct JOB*)F_PEASSET_F(MG1->INBUFFER)));
       goto test0005;
next0005:
       easg((char*)&MYJOB, (iRef*)E_0003);
test0005:
       if (MYJOB == 0) {
       goto done0005;
       }
       easg((char*)&E_0003, (iRef*)S_PEASSET_F((iRef*)MYJOB, E_TXTLIT_F(_T("INBUFFER"))));
       WTX_R(E_TXTLIT_F(_T("JOB: ")));
       WTX_R((Etxt*)((struct JOB*)fetch((iRef*)MYJOB))->JOBNAME);
       WTB_R(20);
       easg((char*)&pjobsdef->JOBSTEP, (iRef*)F_PEASSET_F(((struct JOB*)fetch((iRef*)MYJOB))->ROUTING));
       goto test0006;
next0006:
       easg((char*)&pjobsdef->JOBSTEP, (iRef*)E_0004);
test0006:
       if ((struct JOBSTEP*)pjobsdef->JOBSTEP == 0) {
       goto done0006;
       }
       easg((char*)&E_0004, (iRef*)S_PEASSET_F((iRef*)(struct JOBSTEP*)pjobsdef->JOBSTEP, E_TXTLIT_F(_T("ROUTING"))));
       WTX_R((Etxt*)((struct JOBSTEP*)fetch((iRef*)(struct JOBSTEP*)pjobsdef->JOBSTEP))->STEPNAME);
       WTS_R(2);
       goto next0006;
done0006:
       WTL_R();
       goto next0005;
done0005:
       WTX_R(E_TXTLIT_F(_T("Implicit: JOBNAME.., FOR EACH JOBSTEP, STEPNAME")));
       WTL_R();
       easg((char*)&JOB, (iRef*)((struct JOB*)F_PEASSET_F(MG1->INBUFFER)));
       goto test0007;
next0007:
       easg((char*)&JOB, (iRef*)E_0005);
test0007:
       if (JOB == 0) {
       goto done0007;
       }
       easg((char*)&E_0005, (iRef*)S_PEASSET_F((iRef*)JOB, E_TXTLIT_F(_T("INBUFFER"))));
       WTX_R((Etxt*)((struct JOB*)fetch((iRef*)JOB))->JOBNAME);
       WTS_R(3);
       easg((char*)&pjobsdef->JOBSTEP, (iRef*)F_PEASSET_F(((struct JOB*)fetch((iRef*)JOB))->ROUTING));
       goto test0008;
next0008:
       easg((char*)&pjobsdef->JOBSTEP, (iRef*)E_0006);
test0008:
       if ((struct JOBSTEP*)pjobsdef->JOBSTEP == 0) {
       goto done0008;
       }
       easg((char*)&E_0006, (iRef*)S_PEASSET_F((iRef*)(struct JOBSTEP*)pjobsdef->JOBSTEP, E_TXTLIT_F(_T("ROUTING"))));
       WTX_R((Etxt*)((struct JOBSTEP*)fetch((iRef*)pjobsdef->JOBSTEP))->STEPNAME);
       WTS_R(2);
       goto next0008;
done0008:
       if (S_PEASSET_F((iRef*)JOB, E_TXTLIT_F(_T("INBUFFER"))) != 0) {
       WTX_R(E_TXTLIT_F(_T("next job will be:  ")));
       WTX_R((Etxt*)((struct JOB*)fetch((iRef*)S_PEASSET_F((iRef*)JOB, E_TXTLIT_F(_T("INBUFFER")))))->JOBNAME);
       }
       WTL_R();
       goto next0007;
done0007:
       WTX_R(E_TXTLIT_F(_T("Testing cascaded set attribute refs: 1st & 2nd step names of 1st, then 1st of 2nd job")));
       WTL_R();
       WTX_R((Etxt*)((struct JOBSTEP*)fetch((iRef*)F_PEASSET_F(((struct JOB*)fetch((iRef*)((struct JOB*)F_PEASSET_F(MG1->INBUFFER))))->ROUTING)))->STEPNAME);
       WTL_R();
/*       WTX_R((Etxt*)((struct JOBSTEP*)fetch((iRef*)S_PEASSET_F((iRef*)F_PEASSET_F(((struct JOB*)fetch((iRef*)((struct JOB*)F_PEASSET_F(MG1->INBUFFER))))->ROUTING), E_TXTLIT_F(_T("ROUTING")))))->STEPNAME);
       WTL_R();
       WTX_R((Etxt*)((struct JOBSTEP*)fetch((iRef*)F_PEASSET_F(((struct JOB*)fetch((iRef*)S_PEASSET_F((iRef*)((struct JOB*)F_PEASSET_F(MG1->INBUFFER)), E_TXTLIT_F(_T("INBUFFER")))))->ROUTING)))->STEPNAME);
       WTL_R(); */
       WTX_R(E_TXTLIT_F(_T("Testing FIND - look for PRIORITY > 2 ")));
       WTL_R();
       easg((char*)&MYJOB, (iRef*)((struct JOB*)F_PEASSET_F(MG1->INBUFFER)));
       goto test0009;
next0009:
       easg((char*)&MYJOB, (iRef*)E_0007);
test0009:
       if (MYJOB == 0) {
       goto done0009;
       }
       easg((char*)&E_0007, (iRef*)S_PEASSET_F((iRef*)MYJOB, E_TXTLIT_F(_T("INBUFFER"))));
       if ( !  ( (int)((struct JOB*)fetch((iRef*)MYJOB))->PRIORITY > 2 ) ) {
       goto next0009;
       }
       easlib->E_FOUND_V = 1;
       goto skip0009;
done0009:
       easlib->E_FOUND_V = 0;
skip0009:
       if (easlib->E_FOUND_V != 0) {
       WTX_R(E_TXTLIT_F(_T("JOB: ")));
       WTX_R((Etxt*)((struct JOB*)fetch((iRef*)MYJOB))->JOBNAME);
       WTX_R(E_TXTLIT_F(_T(" has priority ")));
       WTI_R((int)((struct JOB*)fetch((iRef*)MYJOB))->PRIORITY, 2);
       WTX_R(E_TXTLIT_F(_T(" - REMOVE specific")));
       WTL_R();
       E_PRMVSPCFC_R((struct E_PSET*)MG1->INBUFFER, MYJOB);
       WTX_R(E_TXTLIT_F(_T(" removed - you won't see this name again")));
       WTL_R();
       }
       WTX_R(E_TXTLIT_F(_T("INBUFFER set count is now = ")));
       WTI_R(N_PEASSET_F(MG1->INBUFFER), 4);
       WTL_R();
next0010:
       if ( !  ( N_PEASSET_F(MG1->INBUFFER) != 0 ) ) {
       goto done0010;
       }
       easg((char*)&MYJOB, (iRef*)E_PRMVFRST_F((struct E_PSET*)MG1->INBUFFER));
       WTX_R(E_TXTLIT_F(_T("Removed JOB called ")));
       WTX_R((Etxt*)((struct JOB*)fetch((iRef*)MYJOB))->JOBNAME);
       WTL_R();
next0011:
       if ( !  ( F_PEASSET_F(((struct JOB*)fetch((iRef*)MYJOB))->ROUTING) != 0 ) ) {
       goto done0011;
       }
       easg((char*)&pjobsdef->JOBSTEP, (iRef*)E_PRMVFRST_F((struct E_PSET*)((struct JOB*)fetch((iRef*)MYJOB))->ROUTING));
       WTX_R(E_TXTLIT_F(_T("Cleared step ")));
       WTX_R((Etxt*)((struct JOBSTEP*)fetch((iRef*)pjobsdef->JOBSTEP))->STEPNAME);
       WTL_R();
       d_JOBSTEP((struct JOBSTEP*)pjobsdef->JOBSTEP);
       goto next0011;
done0011:
       d_JOB(MYJOB);
       goto next0010;
done0010:
       WTX_R(E_TXTLIT_F(_T("Testing PRINT THUS")));
       WTL_R();
       WTX_R(E_TXTLIT_F(_T("INBUFFER IS EMPTY - THERE ARE NO JOBS WAITING")));
       WTL_R();
       E_PDISCONNECT_R(SERVERNAME);
       CLOSE_R(6);
       OPENO_R(6, E_TXTLIT_F(_T("localdata.txt")));
       USE_R(6, 2);
       WTX_R(SERVERNAME);
       WTL_R();
       WTP_R((struct E_PSET*)MG1->INBUFFER);
       WTL_R();
       CLOSE_R(6);
       eunasg((char*)&JOB);
eunasg((char*)&MYJOB);
E_TXTDEL_R(SERVERNAME);
eunasg((char*)&E_0001);
eunasg((char*)&E_0002);
eunasg((char*)&E_0003);
eunasg((char*)&E_0004);
eunasg((char*)&E_0005);
eunasg((char*)&E_0006);
eunasg((char*)&E_0007);
       return;
}

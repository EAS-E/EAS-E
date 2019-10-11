#include "stdafx.h"
#include "malloc.h"
#include "easeSets.h"

void d_E_PSETHDR(E_PSETHDR* &EPTR) { 
    E_TXTASG_R(&(Etxt*)((struct E_PSETHDR*)fetch((iRef*)EPTR))->PSETNAME, 0);
    E_PDESTROY_R(EPTR);
    easg((char*)&EPTR, (iRef*)0);
    eunasg((char*)&EPTR);
return;
}
iRef* c_E_PSETHDR() { 
iRef* EPTR = 0;
iRef* rval = 0;
    EPTR = (struct iRef*)E_PCREATE_F(2,16,Z_E_PSETHDR);
    rval = (iRef*)EPTR;
goto ret;
ret:
return rval;
}
void d_E_SETHDR(E_SETHDR* &EPTR) { 
    E_TXTASG_R(&EPTR->SETNAME, 0);
    E_DESTROY_R(EPTR);
    EPTR = (struct E_SETHDR*)0;
return;
}
E_SETHDR* c_E_SETHDR() { 
E_SETHDR* EPTR = 0;
E_SETHDR* rval = 0;
    EPTR = (struct E_SETHDR*)E_CREATE_F(2,15,Z_E_SETHDR);
    rval = (E_SETHDR*)EPTR;
goto ret;
ret:
return rval;
}
void d_E_PCARD(E_PCARD* &EPTR) { 
    E_PDESTROY_R(EPTR);
    easg((char*)&EPTR, (iRef*)0);
    eunasg((char*)&EPTR);
return;
}
iRef* c_E_PCARD() { 
iRef* EPTR = 0;
iRef* rval = 0;
    EPTR = (struct iRef*)E_PCREATE_F(2,14,Z_E_PCARD);
    rval = (iRef*)EPTR;
goto ret;
ret:
return rval;
}
void d_E_CARD(E_CARD* &EPTR) { 
    E_DESTROY_R(EPTR);
    EPTR = (struct E_CARD*)0;
return;
}
E_CARD* c_E_CARD() { 
E_CARD* EPTR = 0;
E_CARD* rval = 0;
    EPTR = (struct E_CARD*)E_CREATE_F(2,13,Z_E_CARD);
    rval = (E_CARD*)EPTR;
goto ret;
ret:
return rval;
}
void d_E_PINSTH(E_PINSTH* &EPTR) { 
    E_PDESTROY_R(EPTR);
    easg((char*)&EPTR, (iRef*)0);
    eunasg((char*)&EPTR);
return;
}
iRef* c_E_PINSTH() { 
iRef* EPTR = 0;
iRef* rval = 0;
    EPTR = (struct iRef*)E_PCREATE_F(2,12,Z_E_PINSTH);
    rval = (iRef*)EPTR;
goto ret;
ret:
return rval;
}
void d_E_INSTH(E_INSTH* &EPTR) { 
    E_DESTROY_R(EPTR);
    EPTR = (struct E_INSTH*)0;
return;
}
E_INSTH* c_E_INSTH() { 
E_INSTH* EPTR = 0;
E_INSTH* rval = 0;
    EPTR = (struct E_INSTH*)E_CREATE_F(2,11,Z_E_INSTH);
    rval = (E_INSTH*)EPTR;
goto ret;
ret:
return rval;
}
void E_PRMVSPCFC_R(void* E1, void* E2) { 
E_PCARD* MEMCARD = 0;
E_PCARD* ACARD = 0;
E_PSETHDR* SET = 0;
E_PINSTH* ENTITY = 0;
    easg((char*)&SET, (iRef*)E1);
    easg((char*)&ENTITY, (iRef*)E2);
    if (ENTITY == 0 | SET == 0 ) { 
goto ret;
    } 
    if (ENTITY == (struct E_PINSTH*)((struct E_PCARD*)fetch((iRef*)(struct E_PCARD*)((struct E_PSETHDR*)fetch((iRef*)SET))->F_PMEMBERS))->PMEMBER ) { 
    easg((char*)&ENTITY, (iRef*)E_PRMVFRST_F(SET));
goto ret;
    } 
    if (ENTITY == (struct E_PINSTH*)((struct E_PCARD*)fetch((iRef*)(struct E_PCARD*)((struct E_PSETHDR*)fetch((iRef*)SET))->L_PMEMBERS))->PMEMBER ) { 
    easg((char*)&ENTITY, (iRef*)E_PRMVLAST_F(SET));
goto ret;
    } 
    easg((char*)&MEMCARD, (iRef*)(struct E_PCARD*)((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS);
next0017: 
    if ( !  ( MEMCARD != 0 )  ) { 
    goto done0017; 
    } 
    if ((struct E_PSETHDR*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->POWNRSET == SET ) { 
    goto done0017; 
    } 
    easg((char*)&ACARD, (iRef*)MEMCARD);
    easg((char*)&MEMCARD, (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMSHIPS);
    goto next0017; 
done0017: 
    if (MEMCARD == 0 ) { 
goto ret;
    } 
    (*(int*)&((struct E_PSETHDR*)fetch((iRef*)SET))->PMCOUNT) = (int)((struct E_PSETHDR*)fetch((iRef*)SET))->PMCOUNT-1;
    if (ACARD == 0 ) { 
    easg((char*)&(*(E_PCARD*)&((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS), (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMSHIPS);
    } 
    else { 
    easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)ACARD))->S_PMSHIPS), (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMSHIPS);
    } 
    easg((char*)&ACARD, (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->P_PMEMBERS);
    easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)ACARD))->S_PMEMBERS), (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMEMBERS);
    easg((char*)&ACARD, (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMEMBERS);
    easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)ACARD))->P_PMEMBERS), (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->P_PMEMBERS);
    d_E_PCARD(MEMCARD);
ret:
    eunasg((char*)&MEMCARD);
    eunasg((char*)&ACARD);
    eunasg((char*)&SET);
    eunasg((char*)&ENTITY);
return;
}
void E_RMVSPCFC_R(void* E1, void* E2) { 
E_CARD* MEMCARD = 0;
E_CARD* ACARD = 0;
E_SETHDR* SET = 0;
E_INSTH* ENTITY = 0;
    SET = (struct E_SETHDR*)E1;
    ENTITY = (struct E_INSTH*)E2;
    if (ENTITY == 0 | SET == 0 ) { 
goto ret;
    } 
    if (ENTITY == SET->F_MEMBERS->MEMBER ) { 
    ENTITY = (struct E_INSTH*)E_RMVFRST_F(SET);
goto ret;
    } 
    if (ENTITY == SET->L_MEMBERS->MEMBER ) { 
    ENTITY = (struct E_INSTH*)E_RMVLAST_F(SET);
goto ret;
    } 
    MEMCARD = (struct E_CARD*)ENTITY->F_MSHIPS;
next0018: 
    if ( !  ( MEMCARD != 0 )  ) { 
    goto done0018; 
    } 
    if (MEMCARD->OWNRSET == SET ) { 
    goto done0018; 
    } 
    ACARD = (struct E_CARD*)MEMCARD;
    MEMCARD = (struct E_CARD*)MEMCARD->S_MSHIPS;
    goto next0018; 
done0018: 
    if (MEMCARD == 0 ) { 
goto ret;
    } 
    SET->MCOUNT = SET->MCOUNT-1;
    if (ACARD == 0 ) { 
    ENTITY->F_MSHIPS = (E_CARD*)MEMCARD->S_MSHIPS;
    } 
    else { 
    ACARD->S_MSHIPS = (E_CARD*)MEMCARD->S_MSHIPS;
    } 
    ACARD = (struct E_CARD*)MEMCARD->P_MEMBERS;
    ACARD->S_MEMBERS = (E_CARD*)MEMCARD->S_MEMBERS;
    ACARD = (struct E_CARD*)MEMCARD->S_MEMBERS;
    ACARD->P_MEMBERS = (E_CARD*)MEMCARD->P_MEMBERS;
    d_E_CARD(MEMCARD);
ret:
return;
}
E_PINSTH* E_PRMVLAST_F(void* E1) { 
E_PCARD* MEMCARD = 0;
E_PSETHDR* SET = 0;
E_PINSTH* ENTITY = 0;
E_PCARD* ACARD = 0;
E_PINSTH* rval = 0;
    easg((char*)&SET, (iRef*)E1);
    if (SET == 0 ) { 
    rval = (E_PINSTH*)0;
goto ret;
    } 
    easg((char*)&MEMCARD, (iRef*)(struct E_PCARD*)((struct E_PSETHDR*)fetch((iRef*)SET))->L_PMEMBERS);
    if (MEMCARD != 0 ) { 
    (*(int*)&((struct E_PSETHDR*)fetch((iRef*)SET))->PMCOUNT) = (int)((struct E_PSETHDR*)fetch((iRef*)SET))->PMCOUNT-1;
    if ((struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->P_PMEMBERS == 0 ) { 
    easg((char*)&(*(E_PCARD*)&((struct E_PSETHDR*)fetch((iRef*)SET))->F_PMEMBERS), (iRef*)0);
    easg((char*)&(*(E_PCARD*)&((struct E_PSETHDR*)fetch((iRef*)SET))->L_PMEMBERS), (iRef*)0);
    } 
    else { 
    easg((char*)&(*(E_PCARD*)&((struct E_PSETHDR*)fetch((iRef*)SET))->L_PMEMBERS), (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->P_PMEMBERS);
    easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)(struct E_PCARD*)((struct E_PSETHDR*)fetch((iRef*)SET))->L_PMEMBERS))->S_PMEMBERS), (iRef*)0);
    } 
    easg((char*)&ENTITY, (iRef*)(struct E_PINSTH*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->PMEMBER);
    if (MEMCARD == (struct E_PCARD*)((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS ) { 
    easg((char*)&(*(E_PCARD*)&((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS), (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMSHIPS);
    } 
    else { 
    easg((char*)&ACARD, (iRef*)(struct E_PCARD*)((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS);
next0019: 
    if ( !  ( (struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)ACARD))->S_PMSHIPS != MEMCARD )  ) { 
    goto done0019; 
    } 
    easg((char*)&ACARD, (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)ACARD))->S_PMSHIPS);
    goto next0019; 
done0019: 
    easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)ACARD))->S_PMSHIPS), (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMSHIPS);
    } 
    d_E_PCARD(MEMCARD);
    rval = (E_PINSTH*)ENTITY;
goto ret;
    } 
    rval = (E_PINSTH*)0;
goto ret;
ret:
    eunasg((char*)&MEMCARD);
    eunasg((char*)&SET);
    eunasg((char*)&ENTITY);
    eunasg((char*)&ACARD);
return rval;
}
E_INSTH* E_RMVLAST_F(void* E1) { 
E_CARD* MEMCARD = 0;
E_SETHDR* SET = 0;
E_INSTH* ENTITY = 0;
E_CARD* ACARD = 0;
E_INSTH* rval = 0;
    SET = (struct E_SETHDR*)E1;
    if (SET == 0 ) { 
    rval = (E_INSTH*)0;
goto ret;
    } 
    MEMCARD = (struct E_CARD*)SET->L_MEMBERS;
    if (MEMCARD != 0 ) { 
    SET->MCOUNT = SET->MCOUNT-1;
    if (MEMCARD->P_MEMBERS == 0 ) { 
    SET->F_MEMBERS = (E_CARD*)0;
    SET->L_MEMBERS = (E_CARD*)0;
    } 
    else { 
    SET->L_MEMBERS = (E_CARD*)MEMCARD->P_MEMBERS;
    SET->L_MEMBERS->S_MEMBERS = (E_CARD*)0;
    } 
    ENTITY = (struct E_INSTH*)MEMCARD->MEMBER;
    if (MEMCARD == ENTITY->F_MSHIPS ) { 
    ENTITY->F_MSHIPS = (E_CARD*)MEMCARD->S_MSHIPS;
    } 
    else { 
    ACARD = (struct E_CARD*)ENTITY->F_MSHIPS;
next0020: 
    if ( !  ( ACARD->S_MSHIPS != MEMCARD )  ) { 
    goto done0020; 
    } 
    ACARD = (struct E_CARD*)ACARD->S_MSHIPS;
    goto next0020; 
done0020: 
    ACARD->S_MSHIPS = (E_CARD*)MEMCARD->S_MSHIPS;
    } 
    d_E_CARD(MEMCARD);
    rval = (E_INSTH*)ENTITY;
goto ret;
    } 
    rval = (E_INSTH*)0;
goto ret;
ret:
return rval;
}
E_PINSTH* E_PRMVFRST_F(void* E1) { 
E_PCARD* MEMCARD = 0;
E_PSETHDR* SET = 0;
E_PINSTH* ENTITY = 0;
E_PCARD* ACARD = 0;
E_PINSTH* rval = 0;
    easg((char*)&SET, (iRef*)E1);
    if (SET == 0 ) { 
    rval = (E_PINSTH*)0;
goto ret;
    } 
    easg((char*)&MEMCARD, (iRef*)(struct E_PCARD*)((struct E_PSETHDR*)fetch((iRef*)SET))->F_PMEMBERS);
    if (MEMCARD != 0 ) { 
    (*(int*)&((struct E_PSETHDR*)fetch((iRef*)SET))->PMCOUNT) = (int)((struct E_PSETHDR*)fetch((iRef*)SET))->PMCOUNT-1;
    if ((struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMEMBERS == 0 ) { 
    easg((char*)&(*(E_PCARD*)&((struct E_PSETHDR*)fetch((iRef*)SET))->F_PMEMBERS), (iRef*)0);
    easg((char*)&(*(E_PCARD*)&((struct E_PSETHDR*)fetch((iRef*)SET))->L_PMEMBERS), (iRef*)0);
    } 
    else { 
    easg((char*)&(*(E_PCARD*)&((struct E_PSETHDR*)fetch((iRef*)SET))->F_PMEMBERS), (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMEMBERS);
    easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)(struct E_PCARD*)((struct E_PSETHDR*)fetch((iRef*)SET))->F_PMEMBERS))->P_PMEMBERS), (iRef*)0);
    } 
    easg((char*)&ENTITY, (iRef*)(struct E_PINSTH*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->PMEMBER);
    if (MEMCARD == (struct E_PCARD*)((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS ) { 
    easg((char*)&(*(E_PCARD*)&((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS), (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMSHIPS);
    } 
    else { 
    easg((char*)&ACARD, (iRef*)(struct E_PCARD*)((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS);
next0021: 
    if ( !  ( (struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)ACARD))->S_PMSHIPS != MEMCARD )  ) { 
    goto done0021; 
    } 
    easg((char*)&ACARD, (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)ACARD))->S_PMSHIPS);
    goto next0021; 
done0021: 
    easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)ACARD))->S_PMSHIPS), (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMSHIPS);
    } 
    d_E_PCARD(MEMCARD);
    rval = (E_PINSTH*)ENTITY;
goto ret;
    } 
    rval = (E_PINSTH*)0;
goto ret;
ret:
    eunasg((char*)&MEMCARD);
    eunasg((char*)&SET);
    eunasg((char*)&ENTITY);
    eunasg((char*)&ACARD);
return rval;
}
E_INSTH* E_RMVFRST_F(void* E1) { 
E_CARD* MEMCARD = 0;
E_SETHDR* SET = 0;
E_INSTH* ENTITY = 0;
E_CARD* ACARD = 0;
E_INSTH* rval = 0;
    SET = (struct E_SETHDR*)E1;
    if (SET == 0 ) { 
    rval = (E_INSTH*)0;
goto ret;
    } 
    MEMCARD = (struct E_CARD*)SET->F_MEMBERS;
    if (MEMCARD != 0 ) { 
    SET->MCOUNT = SET->MCOUNT-1;
    if (MEMCARD->S_MEMBERS == 0 ) { 
    SET->F_MEMBERS = (E_CARD*)0;
    SET->L_MEMBERS = (E_CARD*)0;
    } 
    else { 
    SET->F_MEMBERS = (E_CARD*)MEMCARD->S_MEMBERS;
    SET->F_MEMBERS->P_MEMBERS = (E_CARD*)0;
    } 
    ENTITY = (struct E_INSTH*)MEMCARD->MEMBER;
    if (MEMCARD == ENTITY->F_MSHIPS ) { 
    ENTITY->F_MSHIPS = (E_CARD*)MEMCARD->S_MSHIPS;
    } 
    else { 
    ACARD = (struct E_CARD*)ENTITY->F_MSHIPS;
next0022: 
    if ( !  ( ACARD->S_MSHIPS != MEMCARD )  ) { 
    goto done0022; 
    } 
    ACARD = (struct E_CARD*)ACARD->S_MSHIPS;
    goto next0022; 
done0022: 
    ACARD->S_MSHIPS = (E_CARD*)MEMCARD->S_MSHIPS;
    } 
    d_E_CARD(MEMCARD);
    rval = (E_INSTH*)ENTITY;
goto ret;
    } 
    rval = (E_INSTH*)0;
goto ret;
ret:
return rval;
}
E_PINSTH* S_PEASSET_F(void* E, Etxt* SNAME) { 
E_PINSTH* ENT = 0;
E_PCARD* MEMCARD = 0;
E_PCARD* ACARD = 0;
E_PINSTH* rval = 0;
    E_TXTINC_R(SNAME);
    easg((char*)&ENT, (iRef*)E);
    if (ENT == 0 ) { 
    rval = (E_PINSTH*)0;
goto ret;
    } 
    easg((char*)&MEMCARD, (iRef*)(struct E_PCARD*)((struct E_PINSTH*)fetch((iRef*)ENT))->F_PMSHIPS);
next0023: 
    if ( !  ( MEMCARD != 0 )  ) { 
    goto done0023; 
    } 
    if (E_TXTEQL_F((Etxt*)((struct E_PSETHDR*)fetch((iRef*)(struct E_PSETHDR*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->POWNRSET))->PSETNAME, SNAME) ) { 
    goto done0023; 
    easg((char*)&MEMCARD, (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMSHIPS);
    } 
    goto next0023; 
done0023: 
    if (MEMCARD != 0 ) { 
    easg((char*)&MEMCARD, (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMEMBERS);
    } 
    if (MEMCARD != 0 ) { 
    easg((char*)&ENT, (iRef*)(struct E_PINSTH*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->PMEMBER);
    rval = (E_PINSTH*)(struct E_PINSTH*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->PMEMBER;
goto ret;
    } 
    else { 
    rval = (E_PINSTH*)0;
goto ret;
    } 
ret:
    E_TXTDEL_R(SNAME);
    eunasg((char*)&ENT);
    eunasg((char*)&MEMCARD);
    eunasg((char*)&ACARD);
return rval;
}
E_INSTH* S_EASSET_F(void* E, Etxt* SNAME) { 
E_INSTH* ENT = 0;
E_CARD* MEMCARD = 0;
E_INSTH* rval = 0;
    E_TXTINC_R(SNAME);
    ENT = (struct E_INSTH*)E;
    if (ENT == 0 ) { 
    rval = (E_INSTH*)0;
goto ret;
    } 
    MEMCARD = (struct E_CARD*)ENT->F_MSHIPS;
next0024: 
    if ( !  ( MEMCARD != 0 )  ) { 
    goto done0024; 
    } 
    if (E_TXTEQL_F(MEMCARD->OWNRSET->SETNAME, SNAME) ) { 
    goto done0024; 
    MEMCARD = (struct E_CARD*)MEMCARD->S_MSHIPS;
    } 
    goto next0024; 
done0024: 
    if (MEMCARD != 0 ) { 
    MEMCARD = (struct E_CARD*)MEMCARD->S_MEMBERS;
    } 
    if (MEMCARD != 0 ) { 
    rval = (E_INSTH*)MEMCARD->MEMBER;
goto ret;
    } 
    else { 
    rval = (E_INSTH*)0;
goto ret;
    } 
ret:
    E_TXTDEL_R(SNAME);
return rval;
}
E_PINSTH* P_PEASSET_F(void* E, Etxt* SNAME) { 
E_PINSTH* ENT = 0;
E_PCARD* MEMCARD = 0;
E_PINSTH* rval = 0;
    E_TXTINC_R(SNAME);
    easg((char*)&ENT, (iRef*)E);
    if (ENT == 0 ) { 
    rval = (E_PINSTH*)0;
goto ret;
    } 
    easg((char*)&MEMCARD, (iRef*)(struct E_PCARD*)((struct E_PINSTH*)fetch((iRef*)ENT))->F_PMSHIPS);
next0025: 
    if ( !  ( MEMCARD != 0 )  ) { 
    goto done0025; 
    } 
    if (E_TXTEQL_F((Etxt*)((struct E_PSETHDR*)fetch((iRef*)(struct E_PSETHDR*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->POWNRSET))->PSETNAME, SNAME) ) { 
    goto done0025; 
    easg((char*)&MEMCARD, (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMSHIPS);
    } 
    goto next0025; 
done0025: 
    easg((char*)&MEMCARD, (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->P_PMEMBERS);
    if (MEMCARD != 0 ) { 
    rval = (E_PINSTH*)(struct E_PINSTH*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->PMEMBER;
goto ret;
    } 
    else { 
    rval = (E_PINSTH*)0;
goto ret;
    } 
ret:
    E_TXTDEL_R(SNAME);
    eunasg((char*)&ENT);
    eunasg((char*)&MEMCARD);
return rval;
}
E_INSTH* P_EASSET_F(void* E, Etxt* SNAME) { 
E_INSTH* ENT = 0;
E_CARD* MEMCARD = 0;
E_INSTH* rval = 0;
    E_TXTINC_R(SNAME);
    ENT = (struct E_INSTH*)E;
    if (ENT == 0 ) { 
    rval = (E_INSTH*)0;
goto ret;
    } 
    MEMCARD = (struct E_CARD*)ENT->F_MSHIPS;
next0026: 
    if ( !  ( MEMCARD != 0 )  ) { 
    goto done0026; 
    } 
    if (E_TXTEQL_F(MEMCARD->OWNRSET->SETNAME, SNAME) ) { 
    goto done0026; 
    MEMCARD = (struct E_CARD*)MEMCARD->S_MSHIPS;
    } 
    goto next0026; 
done0026: 
    MEMCARD = (struct E_CARD*)MEMCARD->P_MEMBERS;
    if (MEMCARD != 0 ) { 
    rval = (E_INSTH*)MEMCARD->MEMBER;
goto ret;
    } 
    else { 
    rval = (E_INSTH*)0;
goto ret;
    } 
ret:
    E_TXTDEL_R(SNAME);
return rval;
}
E_PINSTH* F_PEASSET_F(void* S) { 
E_PSETHDR* SET = 0;
E_PCARD* MEMCARD = 0;
E_PINSTH* rval = 0;
    easg((char*)&SET, (iRef*)S);
    if (S != 0 ) { 
    easg((char*)&MEMCARD, (iRef*)(struct E_PCARD*)((struct E_PSETHDR*)fetch((iRef*)SET))->F_PMEMBERS);
    } 
    if (MEMCARD != 0 ) { 
    rval = (E_PINSTH*)(struct E_PINSTH*)((struct E_PCARD*)fetch((iRef*)MEMCARD))->PMEMBER;
goto ret;
    } 
    rval = (E_PINSTH*)0;
goto ret;
ret:
    eunasg((char*)&SET);
    eunasg((char*)&MEMCARD);
return rval;
}
E_INSTH* F_EASSET_F(void* S) { 
E_SETHDR* SET = 0;
E_CARD* MEMCARD = 0;
E_INSTH* rval = 0;
    SET = (struct E_SETHDR*)S;
    if (S != 0 ) { 
    MEMCARD = (struct E_CARD*)SET->F_MEMBERS;
    } 
    if (MEMCARD != 0 ) { 
    rval = (E_INSTH*)MEMCARD->MEMBER;
goto ret;
    } 
    rval = (E_INSTH*)0;
goto ret;
ret:
return rval;
}
int N_PEASSET_F(void* S) { 
E_PSETHDR* SET = 0;
int rval = 0;
    easg((char*)&SET, (iRef*)S);
    if (SET != 0 ) { 
    rval = (int)(int)((struct E_PSETHDR*)fetch((iRef*)SET))->PMCOUNT;
goto ret;
    } 
    rval = (int)0;
goto ret;
ret:
    eunasg((char*)&SET);
return rval;
}
int N_EASSET_F(void* S) { 
E_SETHDR* SET = 0;
int rval = 0;
    SET = (struct E_SETHDR*)S;
    if (SET != 0 ) { 
    rval = (int)SET->MCOUNT;
goto ret;
    } 
    rval = (int)0;
goto ret;
ret:
return rval;
}
void E_PFAFTER_R(void* E1, void* E2, void* E3) { 
E_PCARD* MEMCARD = 0;
E_PSETHDR* SET = 0;
E_PINSTH* ENTITY = 0;
E_PINSTH* TARGET = 0;
E_PCARD* ACARD = 0;
    easg((char*)&SET, (iRef*)E1);
    easg((char*)&ENTITY, (iRef*)E2);
    if (SET == 0 | ENTITY == 0 ) { 
goto ret;
    } 
    easg((char*)&TARGET, (iRef*)E3);
    if (TARGET == 0 ) { 
goto ret;
    } 
    if (TARGET == (struct E_PINSTH*)((struct E_PCARD*)fetch((iRef*)(struct E_PCARD*)((struct E_PSETHDR*)fetch((iRef*)SET))->L_PMEMBERS))->PMEMBER ) { 
    E_PFLAST_R(SET, ENTITY);
goto ret;
    } 
    (*(int*)&((struct E_PSETHDR*)fetch((iRef*)SET))->PMCOUNT) = (int)((struct E_PSETHDR*)fetch((iRef*)SET))->PMCOUNT+1;
easg((char*)&MEMCARD, c_E_PCARD());
    easg((char*)&(*(E_PINSTH*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->PMEMBER), (iRef*)ENTITY);
    easg((char*)&(*(E_PSETHDR*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->POWNRSET), (iRef*)SET);
    easg((char*)&ACARD, (iRef*)(struct E_PCARD*)((struct E_PINSTH*)fetch((iRef*)TARGET))->F_PMSHIPS);
next0027: 
    if ( !  ( ACARD != 0 )  ) { 
    goto done0027; 
    } 
    if ((struct E_PSETHDR*)((struct E_PCARD*)fetch((iRef*)ACARD))->POWNRSET == SET ) { 
    goto done0027; 
    } 
    easg((char*)&ACARD, (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)ACARD))->S_PMSHIPS);
    goto next0027; 
done0027: 
    easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)ACARD))->S_PMEMBERS))->P_PMEMBERS), (iRef*)MEMCARD);
    easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->P_PMEMBERS), (iRef*)ACARD);
    easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)ACARD))->S_PMEMBERS), (iRef*)MEMCARD);
    easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMSHIPS), (iRef*)(struct E_PCARD*)((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS);
    easg((char*)&(*(E_PCARD*)&((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS), (iRef*)MEMCARD);
ret:
    eunasg((char*)&MEMCARD);
    eunasg((char*)&SET);
    eunasg((char*)&ENTITY);
    eunasg((char*)&TARGET);
    eunasg((char*)&ACARD);
return;
}
void E_FAFTER_R(void* E1, void* E2, void* E3) { 
E_CARD* MEMCARD = 0;
E_SETHDR* SET = 0;
E_INSTH* ENTITY = 0;
E_INSTH* TARGET = 0;
E_CARD* ACARD = 0;
    SET = (struct E_SETHDR*)E1;
    ENTITY = (struct E_INSTH*)E2;
    if (SET == 0 | ENTITY == 0 ) { 
goto ret;
    } 
    TARGET = (struct E_INSTH*)E3;
    if (TARGET == 0 ) { 
goto ret;
    } 
    if (TARGET == SET->L_MEMBERS->MEMBER ) { 
    E_FLAST_R(SET, ENTITY);
goto ret;
    } 
    SET->MCOUNT = SET->MCOUNT+1;
MEMCARD = c_E_CARD();
    MEMCARD->MEMBER = (E_INSTH*)ENTITY;
    MEMCARD->OWNRSET = (E_SETHDR*)SET;
    ACARD = (struct E_CARD*)TARGET->F_MSHIPS;
next0028: 
    if ( !  ( ACARD != 0 )  ) { 
    goto done0028; 
    } 
    if (ACARD->OWNRSET == SET ) { 
    goto done0028; 
    } 
    ACARD = (struct E_CARD*)ACARD->S_MSHIPS;
    goto next0028; 
done0028: 
    ACARD->S_MEMBERS->P_MEMBERS = (E_CARD*)MEMCARD;
    MEMCARD->P_MEMBERS = (E_CARD*)ACARD;
    ACARD->S_MEMBERS = (E_CARD*)MEMCARD;
    MEMCARD->S_MSHIPS = (E_CARD*)ENTITY->F_MSHIPS;
    ENTITY->F_MSHIPS = (E_CARD*)MEMCARD;
ret:
return;
}
void E_PFBEFOR_R(void* E1, void* E2, void* E3) { 
E_PCARD* MEMCARD = 0;
E_PSETHDR* SET = 0;
E_PINSTH* ENTITY = 0;
E_PINSTH* TARGET = 0;
E_PCARD* ACARD = 0;
    easg((char*)&SET, (iRef*)E1);
    easg((char*)&ENTITY, (iRef*)E2);
    if (SET == 0 | ENTITY == 0 ) { 
goto ret;
    } 
    easg((char*)&TARGET, (iRef*)E3);
    if (TARGET == 0 ) { 
goto ret;
    } 
    if (TARGET == (struct E_PINSTH*)((struct E_PCARD*)fetch((iRef*)(struct E_PCARD*)((struct E_PSETHDR*)fetch((iRef*)SET))->F_PMEMBERS))->PMEMBER ) { 
    E_PFFIRST_R(SET, ENTITY);
goto ret;
    } 
    (*(int*)&((struct E_PSETHDR*)fetch((iRef*)SET))->PMCOUNT) = (int)((struct E_PSETHDR*)fetch((iRef*)SET))->PMCOUNT+1;
easg((char*)&MEMCARD, c_E_PCARD());
    easg((char*)&(*(E_PINSTH*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->PMEMBER), (iRef*)ENTITY);
    easg((char*)&(*(E_PSETHDR*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->POWNRSET), (iRef*)SET);
    easg((char*)&ACARD, (iRef*)(struct E_PCARD*)((struct E_PINSTH*)fetch((iRef*)TARGET))->F_PMSHIPS);
next0029: 
    if ( !  ( ACARD != 0 )  ) { 
    goto done0029; 
    } 
    if ((struct E_PSETHDR*)((struct E_PCARD*)fetch((iRef*)ACARD))->POWNRSET == SET ) { 
    goto done0029; 
    } 
    easg((char*)&ACARD, (iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)ACARD))->S_PMSHIPS);
    goto next0029; 
done0029: 
    easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)(struct E_PCARD*)((struct E_PCARD*)fetch((iRef*)ACARD))->P_PMEMBERS))->S_PMEMBERS), (iRef*)MEMCARD);
    easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMEMBERS), (iRef*)ACARD);
    easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)ACARD))->P_PMEMBERS), (iRef*)MEMCARD);
    easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMSHIPS), (iRef*)(struct E_PCARD*)((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS);
    easg((char*)&(*(E_PCARD*)&((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS), (iRef*)MEMCARD);
ret:
    eunasg((char*)&MEMCARD);
    eunasg((char*)&SET);
    eunasg((char*)&ENTITY);
    eunasg((char*)&TARGET);
    eunasg((char*)&ACARD);
return;
}
void E_FBEFOR_R(void* E1, void* E2, void* E3) { 
E_CARD* MEMCARD = 0;
E_SETHDR* SET = 0;
E_INSTH* ENTITY = 0;
E_INSTH* TARGET = 0;
E_CARD* ACARD = 0;
    SET = (struct E_SETHDR*)E1;
    ENTITY = (struct E_INSTH*)E2;
    if (SET == 0 | ENTITY == 0 ) { 
goto ret;
    } 
    TARGET = (struct E_INSTH*)E3;
    if (TARGET == 0 ) { 
goto ret;
    } 
    if (TARGET == SET->F_MEMBERS->MEMBER ) { 
    E_FFIRST_R(SET, ENTITY);
goto ret;
    } 
    SET->MCOUNT = SET->MCOUNT+1;
MEMCARD = c_E_CARD();
    MEMCARD->MEMBER = (E_INSTH*)ENTITY;
    MEMCARD->OWNRSET = (E_SETHDR*)SET;
    ACARD = (struct E_CARD*)TARGET->F_MSHIPS;
next0030: 
    if ( !  ( ACARD != 0 )  ) { 
    goto done0030; 
    } 
    if (ACARD->OWNRSET == SET ) { 
    goto done0030; 
    } 
    ACARD = (struct E_CARD*)ACARD->S_MSHIPS;
    goto next0030; 
done0030: 
    ACARD->P_MEMBERS->S_MEMBERS = (E_CARD*)MEMCARD;
    MEMCARD->S_MEMBERS = (E_CARD*)ACARD;
    ACARD->P_MEMBERS = (E_CARD*)MEMCARD;
    MEMCARD->S_MSHIPS = (E_CARD*)ENTITY->F_MSHIPS;
    ENTITY->F_MSHIPS = (E_CARD*)MEMCARD;
ret:
return;
}
void E_PFLAST_R(void* E1, void* E2) { 
E_PCARD* MEMCARD = 0;
E_PSETHDR* SET = 0;
E_PINSTH* ENTITY = 0;
    easg((char*)&SET, (iRef*)E1);
    easg((char*)&ENTITY, (iRef*)E2);
    if (SET == 0 | ENTITY == 0 ) { 
goto ret;
    } 
    (*(int*)&((struct E_PSETHDR*)fetch((iRef*)SET))->PMCOUNT) = (int)((struct E_PSETHDR*)fetch((iRef*)SET))->PMCOUNT+1;
easg((char*)&MEMCARD, c_E_PCARD());
    easg((char*)&(*(E_PINSTH*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->PMEMBER), (iRef*)ENTITY);
    easg((char*)&(*(E_PSETHDR*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->POWNRSET), (iRef*)SET);
    if ((struct E_PCARD*)((struct E_PSETHDR*)fetch((iRef*)SET))->L_PMEMBERS != 0 ) { 
    easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)(struct E_PCARD*)((struct E_PSETHDR*)fetch((iRef*)SET))->L_PMEMBERS))->S_PMEMBERS), (iRef*)MEMCARD);
    easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->P_PMEMBERS), (iRef*)(struct E_PCARD*)((struct E_PSETHDR*)fetch((iRef*)SET))->L_PMEMBERS);
    } 
    else { 
    easg((char*)&(*(E_PCARD*)&((struct E_PSETHDR*)fetch((iRef*)SET))->F_PMEMBERS), (iRef*)MEMCARD);
    } 
    easg((char*)&(*(E_PCARD*)&((struct E_PSETHDR*)fetch((iRef*)SET))->L_PMEMBERS), (iRef*)MEMCARD);
    easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMSHIPS), (iRef*)(struct E_PCARD*)((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS);
    easg((char*)&(*(E_PCARD*)&((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS), (iRef*)MEMCARD);
ret:
    eunasg((char*)&MEMCARD);
    eunasg((char*)&SET);
    eunasg((char*)&ENTITY);
return;
}
void E_FLAST_R(void* E1, void* E2) { 
E_CARD* MEMCARD = 0;
E_SETHDR* SET = 0;
E_INSTH* ENTITY = 0;
    SET = (struct E_SETHDR*)E1;
    ENTITY = (struct E_INSTH*)E2;
    if (SET == 0 | ENTITY == 0 ) { 
goto ret;
    } 
    SET->MCOUNT = SET->MCOUNT+1;
MEMCARD = c_E_CARD();
    MEMCARD->MEMBER = (E_INSTH*)ENTITY;
    MEMCARD->OWNRSET = (E_SETHDR*)SET;
    if (SET->L_MEMBERS != 0 ) { 
    SET->L_MEMBERS->S_MEMBERS = (E_CARD*)MEMCARD;
    MEMCARD->P_MEMBERS = (E_CARD*)SET->L_MEMBERS;
    } 
    else { 
    SET->F_MEMBERS = (E_CARD*)MEMCARD;
    } 
    SET->L_MEMBERS = (E_CARD*)MEMCARD;
    MEMCARD->S_MSHIPS = (E_CARD*)ENTITY->F_MSHIPS;
    ENTITY->F_MSHIPS = (E_CARD*)MEMCARD;
ret:
return;
}
void E_PFFIRST_R(void* E1, void* E2) { 
E_PCARD* MEMCARD = 0;
E_PSETHDR* SET = 0;
E_PINSTH* ENTITY = 0;
E_PCARD* ACARD = 0;
    easg((char*)&SET, (iRef*)E1);
    easg((char*)&ENTITY, (iRef*)E2);
    if (SET == 0 | ENTITY == 0 ) { 
goto ret;
    } 
    (*(int*)&((struct E_PSETHDR*)fetch((iRef*)SET))->PMCOUNT) = (int)((struct E_PSETHDR*)fetch((iRef*)SET))->PMCOUNT+1;
easg((char*)&MEMCARD, c_E_PCARD());
    easg((char*)&(*(E_PSETHDR*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->POWNRSET), (iRef*)SET);
    easg((char*)&(*(E_PINSTH*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->PMEMBER), (iRef*)ENTITY);
    easg((char*)&ACARD, (iRef*)(struct E_PCARD*)((struct E_PSETHDR*)fetch((iRef*)SET))->F_PMEMBERS);
    if ((struct E_PCARD*)((struct E_PSETHDR*)fetch((iRef*)SET))->F_PMEMBERS != 0 ) { 
    easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)ACARD))->P_PMEMBERS), (iRef*)MEMCARD);
    easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMEMBERS), (iRef*)(struct E_PCARD*)((struct E_PSETHDR*)fetch((iRef*)SET))->F_PMEMBERS);
    } 
    else { 
    easg((char*)&(*(E_PCARD*)&((struct E_PSETHDR*)fetch((iRef*)SET))->L_PMEMBERS), (iRef*)MEMCARD);
    } 
    easg((char*)&(*(E_PCARD*)&((struct E_PSETHDR*)fetch((iRef*)SET))->F_PMEMBERS), (iRef*)MEMCARD);
    easg((char*)&(*(E_PCARD*)&((struct E_PCARD*)fetch((iRef*)MEMCARD))->S_PMSHIPS), (iRef*)(struct E_PCARD*)((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS);
    easg((char*)&(*(E_PCARD*)&((struct E_PINSTH*)fetch((iRef*)ENTITY))->F_PMSHIPS), (iRef*)MEMCARD);
ret:
    eunasg((char*)&MEMCARD);
    eunasg((char*)&SET);
    eunasg((char*)&ENTITY);
    eunasg((char*)&ACARD);
return;
}
void E_FFIRST_R(void* E1, void* E2) { 
E_CARD* MEMCARD = 0;
E_SETHDR* SET = 0;
E_INSTH* ENTITY = 0;
    SET = (struct E_SETHDR*)E1;
    if (SET == 0 ) { 
goto ret;
    } 
    ENTITY = (struct E_INSTH*)E2;
    if (ENTITY == 0 ) { 
goto ret;
    } 
    SET->MCOUNT = SET->MCOUNT+1;
MEMCARD = c_E_CARD();
    MEMCARD->OWNRSET = (E_SETHDR*)SET;
    MEMCARD->MEMBER = (E_INSTH*)ENTITY;
    if (SET->F_MEMBERS != 0 ) { 
    SET->F_MEMBERS->P_MEMBERS = (E_CARD*)MEMCARD;
    MEMCARD->S_MEMBERS = (E_CARD*)SET->F_MEMBERS;
    } 
    else { 
    SET->L_MEMBERS = (E_CARD*)MEMCARD;
    } 
    SET->F_MEMBERS = (E_CARD*)MEMCARD;
    MEMCARD->S_MSHIPS = (E_CARD*)ENTITY->F_MSHIPS;
    ENTITY->F_MSHIPS = (E_CARD*)MEMCARD;
ret:
return;
}

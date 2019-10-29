#include "stdafx.h"
#include "malloc.h"
#include "libopts.h"
#include "math.h"
#include "EASEents.h"

void EASEents_addTypes() {
#ifdef _ERRORREC
addEType(E_TXTLIT_F(_T("ERRORREC")), 3007,  110, 0);
#endif
#ifdef _RANKATTRDEF
addEType(E_TXTLIT_F(_T("RANKATTRDEF")), 3007,  109, 0);
#endif
#ifdef _FIXUP
addEType(E_TXTLIT_F(_T("FIXUP")), 3007,  104, 0);
#endif
#ifdef _SETDEF
addEType(E_TXTLIT_F(_T("SETDEF")), 3007,  108, 0);
#endif
#ifdef _SETATTDEFREF
addEType(E_TXTLIT_F(_T("SETATTDEFREF")), 3007,  107, 0);
#endif
#ifdef _SETMMBRREF
addEType(E_TXTLIT_F(_T("SETMMBRREF")), 3007,  106, 0);
#endif
#ifdef _ATTRDEF
addEType(E_TXTLIT_F(_T("ATTRDEF")), 3007,  103, 0);
#endif
#ifdef _ENTITYTYPE
addEType(E_TXTLIT_F(_T("ENTITYTYPE")), 3007,  102, 0);
#endif
#ifdef _SCHEMA
addEType(E_TXTLIT_F(_T("SCHEMA")), 3007,  101, 0);
#endif
}
EASEents_sys* EASEents;

void EASEents_init() {
EASEents = (EASEents_sys*)E_CREATE_F( 0,3007, sizeof(EASEents_sys));
EASEents_sets();
EASEents_addTypes();
}
void EASEents_sets() {
       return;
}
void d_SCHEMA(struct SCHEMA*& EPTR) {
       E_TXTASG_R(&EPTR->GENNAME, 0);
       E_DESTROY_R(EPTR);
       EPTR = (struct SCHEMA*)0;
       return;
}
struct SCHEMA* c_SCHEMA() {
struct SCHEMA* EPTR= 0;
struct SCHEMA* rval = 0;
       EPTR = (struct SCHEMA*)E_CREATE_F(3007, 101, Z_SCHEMA);
       rval = (struct SCHEMA*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void d_ENTITYTYPE(struct ENTITYTYPE*& EPTR) {
       E_TXTASG_R(&EPTR->ETYPENAME, 0);
       E_TXTASG_R(&EPTR->PROCBODY, 0);
       E_TXTASG_R(&EPTR->TARGETNAME, 0);
       E_DESTROY_R(EPTR);
       EPTR = (struct ENTITYTYPE*)0;
       return;
}
struct ENTITYTYPE* c_ENTITYTYPE() {
struct ENTITYTYPE* EPTR= 0;
struct ENTITYTYPE* rval = 0;
       EPTR = (struct ENTITYTYPE*)E_CREATE_F(3007, 102, Z_ENTITYTYPE);
       rval = (struct ENTITYTYPE*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void d_ATTRDEF(struct ATTRDEF*& EPTR) {
       E_TXTASG_R(&EPTR->ATTRNAME, 0);
       E_DESTROY_R(EPTR);
       EPTR = (struct ATTRDEF*)0;
       return;
}
struct ATTRDEF* c_ATTRDEF() {
struct ATTRDEF* EPTR= 0;
struct ATTRDEF* rval = 0;
       EPTR = (struct ATTRDEF*)E_CREATE_F(3007, 103, Z_ATTRDEF);
       rval = (struct ATTRDEF*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void d_SETMMBRREF(struct SETMMBRREF*& EPTR) {
       E_DESTROY_R(EPTR);
       EPTR = (struct SETMMBRREF*)0;
       return;
}
struct SETMMBRREF* c_SETMMBRREF() {
struct SETMMBRREF* EPTR= 0;
struct SETMMBRREF* rval = 0;
       EPTR = (struct SETMMBRREF*)E_CREATE_F(3007, 106, Z_SETMMBRREF);
       rval = (struct SETMMBRREF*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void d_SETATTDEFREF(struct SETATTDEFREF*& EPTR) {
       E_TXTASG_R(&EPTR->SETATTNAME, 0);
       E_DESTROY_R(EPTR);
       EPTR = (struct SETATTDEFREF*)0;
       return;
}
struct SETATTDEFREF* c_SETATTDEFREF() {
struct SETATTDEFREF* EPTR= 0;
struct SETATTDEFREF* rval = 0;
       EPTR = (struct SETATTDEFREF*)E_CREATE_F(3007, 107, Z_SETATTDEFREF);
       rval = (struct SETATTDEFREF*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void d_SETDEF(struct SETDEF*& EPTR) {
       E_TXTASG_R(&EPTR->SETNAME, 0);
       E_DESTROY_R(EPTR);
       EPTR = (struct SETDEF*)0;
       return;
}
struct SETDEF* c_SETDEF() {
struct SETDEF* EPTR= 0;
struct SETDEF* rval = 0;
       EPTR = (struct SETDEF*)E_CREATE_F(3007, 108, Z_SETDEF);
       rval = (struct SETDEF*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void d_FIXUP(struct FIXUP*& EPTR) {
       E_TXTASG_R(&EPTR->ENTREFNAME, 0);
       E_DESTROY_R(EPTR);
       EPTR = (struct FIXUP*)0;
       return;
}
struct FIXUP* c_FIXUP() {
struct FIXUP* EPTR= 0;
struct FIXUP* rval = 0;
       EPTR = (struct FIXUP*)E_CREATE_F(3007, 104, Z_FIXUP);
       rval = (struct FIXUP*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void d_RANKATTRDEF(struct RANKATTRDEF*& EPTR) {
       E_TXTASG_R(&EPTR->RATTRNAME, 0);
       E_DESTROY_R(EPTR);
       EPTR = (struct RANKATTRDEF*)0;
       return;
}
struct RANKATTRDEF* c_RANKATTRDEF() {
struct RANKATTRDEF* EPTR= 0;
struct RANKATTRDEF* rval = 0;
       EPTR = (struct RANKATTRDEF*)E_CREATE_F(3007, 109, Z_RANKATTRDEF);
       rval = (struct RANKATTRDEF*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void d_ERRORREC(struct ERRORREC*& EPTR) {
       E_DESTROY_R(EPTR);
       EPTR = (struct ERRORREC*)0;
       return;
}
struct ERRORREC* c_ERRORREC() {
struct ERRORREC* EPTR= 0;
struct ERRORREC* rval = 0;
       EPTR = (struct ERRORREC*)E_CREATE_F(3007, 110, Z_ERRORREC);
       rval = (struct ERRORREC*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
int FINDMODE_F(struct ENTITYTYPE* ETYPE) {
int rval = 0;
       if (E_TXTEQL_F(ETYPE->ETYPENAME, E_TXTLIT_F(_T("Integer")))) {
       rval = (int)1;
goto retlbl;
       }
       if (E_TXTEQL_F(ETYPE->ETYPENAME, E_TXTLIT_F(_T("Real")))) {
       rval = (int)2;
goto retlbl;
       }
       if (E_TXTEQL_F(ETYPE->ETYPENAME, E_TXTLIT_F(_T("Text")))) {
       rval = (int)3;
goto retlbl;
       }
       rval = (int)4;
goto retlbl;
retlbl:
       return rval;
}
void LISTENTITIES() {
struct ATTRDEF* DATTR= 0;
Etxt* ANAME= 0;
struct ENTITYTYPE* ETYPE= 0;
struct SCHEMA* ASCHEMA= 0;
       OPENO_R(7, E_TXTLIT_F(_T("C:\\EASEsysdata\\entitylist.txt")));
       USE_R(7, 2);
       WTX_R(E_TXTLIT_F(_T(" ****  Entity Definitions ****")));
       WTL_R();
       ASCHEMA = (struct SCHEMA*)EASEents->F_SCHEMAS;
next0001:
       if ( !  ( ASCHEMA != 0 ) ) {
       goto done0001;
       }
       WTL_R();
       WTX_R(E_TXTLIT_F(_T(" ** Schema name: ")));
       WTX_R(ASCHEMA->GENNAME);
       WTL_R();
       ETYPE = (struct ENTITYTYPE*)ASCHEMA->F_ETYPES;
next0002:
       if ( !  ( ETYPE != 0 ) ) {
       goto done0002;
       }
       WTB_R(2);
       WTX_R(ETYPE->ETYPENAME);
       WTL_R();
       DATTR = (struct ATTRDEF*)ETYPE->F_ATTRDEFS;
       if (ETYPE->ISPROC == 0) {
next0003:
       if ( !  ( DATTR != 0 ) ) {
       goto done0003;
       }
       WTB_R(6);
       WTX_R(DATTR->ATTRNAME);
       WTB_R(26);
       if (DATTR->ATTRTYPE != 0) {
       WTX_R(DATTR->ATTRTYPE->ETYPENAME);
       }
       else {
       WTX_R(E_TXTLIT_F(_T("Unknown - ")));
       }
       WTL_R();
       DATTR = (struct ATTRDEF*)DATTR->S_ATTRDEFS;
       goto next0003;
done0003:
;      }
       ETYPE = (struct ENTITYTYPE*)ETYPE->S_ETYPES;
       goto next0002;
done0002:
       ASCHEMA = (struct SCHEMA*)ASCHEMA->S_SCHEMAS;
       goto next0001;
done0001:
       CLOSE_R(7);
       goto retlbl;
retlbl:
E_TXTDEL_R(ANAME);
       return;
}
struct SETDEF* FINDSET_F(Etxt* ANAME, int SID) {
struct ENTITYTYPE* ETYPE= 0;
struct SETDEF* SDEF= 0;
struct SETDEF* rval = 0;
E_TXTINC_R(ANAME);
       SDEF = (struct SETDEF*)EASEents->F_SETDEFS;
next0001:
       if ( !  ( SDEF != 0 ) ) {
       goto done0001;
       }
       if (E_TXTEQL_F(SDEF->SETNAME, ANAME)) {
       rval = (struct SETDEF*)SDEF;
goto retlbl;
       }
       SDEF = (struct SETDEF*)SDEF->S_SETDEFS;
       goto next0001;
done0001:
       rval = (struct SETDEF*)0;
goto retlbl;
retlbl:
E_TXTDEL_R(ANAME);
       return rval;
}
struct ENTITYTYPE* FINDETYPEBYNAME_F(Etxt* ANAME, int SID) {
struct ENTITYTYPE* ETYPE= 0;
struct SCHEMA* ASCHEMA= 0;
struct ENTITYTYPE* FOUND= 0;
struct ENTITYTYPE* rval = 0;
E_TXTINC_R(ANAME);
       ASCHEMA = (struct SCHEMA*)EASEents->F_SCHEMAS;
next0001:
       if ( !  ( ASCHEMA != 0 ) ) {
       goto done0001;
       }
       ETYPE = (struct ENTITYTYPE*)ASCHEMA->F_ETYPES;
next0002:
       if ( !  ( ETYPE != 0 ) ) {
       goto done0002;
       }
       if (E_TXTEQL_F(ETYPE->ETYPENAME, ANAME)) {
       FOUND = (struct ENTITYTYPE*)ETYPE;
       if (ASCHEMA->SCHEMAID == SID) {
       rval = (struct ENTITYTYPE*)ETYPE;
goto retlbl;
       }
       }
       ETYPE = (struct ENTITYTYPE*)ETYPE->S_ETYPES;
       goto next0002;
done0002:
       ASCHEMA = (struct SCHEMA*)ASCHEMA->S_SCHEMAS;
       goto next0001;
done0001:
       rval = (struct ENTITYTYPE*)FOUND;
goto retlbl;
retlbl:
E_TXTDEL_R(ANAME);
       return rval;
}
void MAKESETMMBRATTR(Etxt* PREFIX, struct ENTITYTYPE* ETYPE, int MODE, struct SETDEF* SDEF) {
struct DICTENTRY* DREF= 0;
struct DICTUSE* DUSE= 0;
struct DICTUSE* AUSE= 0;
E_TXTINC_R(PREFIX);
       DREF = (struct DICTENTRY*)FINDDICTENTRY_F(CONCAT_F(PREFIX, SDEF->SETNAME));
       AUSE = (struct DICTUSE*)FINDSPECUSE_F(DREF, 6);
       DUSE = (struct DICTUSE*)MAKEUSE_F(DREF, 6);
       if (AUSE != 0) {
       AUSE->ISCOMMONATT = 1;
       DUSE->ISCOMMONATT = 1;
       }
       DUSE->USEOWNER = (struct ENTITYTYPE*)ETYPE;
       DUSE->USEMODE = MODE;
       DUSE->USESETDEF = (struct SETDEF*)SDEF;
       goto retlbl;
retlbl:
E_TXTDEL_R(PREFIX);
       return;
}
void MAKESETOWNRATTR(Etxt* PREFIX, struct ATTRDEF* ATTR, int MODE) {
struct DICTENTRY* DREF= 0;
struct DICTUSE* DUSE= 0;
struct DICTUSE* AUSE= 0;
E_TXTINC_R(PREFIX);
       DREF = (struct DICTENTRY*)FINDDICTENTRY_F(CONCAT_F(PREFIX, ATTR->ATTRNAME));
       AUSE = (struct DICTUSE*)FINDSPECUSE_F(DREF, 5);
       DUSE = (struct DICTUSE*)MAKEUSE_F(DREF, 5);
       if (AUSE != 0) {
       AUSE->ISCOMMONATT = 1;
       DUSE->ISCOMMONATT = 1;
       }
       DUSE->USEOWNER = (struct ENTITYTYPE*)ATTR->OWNERTYPE;
       DUSE->USEMODE = MODE;
       DUSE->USESETREFATT = (struct ATTRDEF*)ATTR;
       goto retlbl;
retlbl:
E_TXTDEL_R(PREFIX);
       return;
}
void SYSSETSINIT() {
struct ENTITYTYPE* SYSETYPE= 0;
Etxt* SYSNAME= 0;
struct ATTRDEF* ATT= 0;
struct EASEPROC* APROC= 0;
       SYSETYPE = (struct ENTITYTYPE*)EASEents->F_SYSTEMS;
next0001:
       if ( !  ( SYSETYPE != 0 ) ) {
       goto done0001;
       }
       Script->SCRIPTLEVEL = 1;
       E_TXTASG_R(&SYSNAME, SYSETYPE->SCHEMAREF->GENNAME);
       APROC = (struct EASEPROC*)MAKEPROC_F(CONCAT_F(SYSNAME, E_TXTLIT_F(_T("_sets"))), SYSETYPE->SCHEMAREF, 0);
       ATT = (struct ATTRDEF*)SYSETYPE->F_ATTRDEFS;
next0002:
       if ( !  ( ATT != 0 ) ) {
       goto done0002;
       }
       if (ATT->ATTRTYPE->ISSETTYPE != 0) {
       E_TXTASG_R(&Script->STRPTRS[2], ATT->ATTRNAME);
       if (ATT->ATTRTYPE->ISPERSISTENT != 0) {
       SCRIPT(73);
       }
       else {
       SCRIPT(72);
       }
       }
       ATT = (struct ATTRDEF*)ATT->S_ATTRDEFS;
       goto next0002;
done0002:
       APROC->F_SCRIPTTOKENS = (struct TOKEN*)EASElex->F_TOKENLIST;
       APROC->L_SCRIPTTOKENS = (struct TOKEN*)EASElex->L_TOKENLIST;
       EASElex->F_TOKENLIST = (struct TOKEN*)0;
       EASElex->L_TOKENLIST = (struct TOKEN*)0;
       Script->SCRIPTLEVEL = 0;
       SYSETYPE = (struct ENTITYTYPE*)SYSETYPE->S_ETYPES;
       goto next0001;
done0001:
       goto retlbl;
retlbl:
E_TXTDEL_R(SYSNAME);
       return;
}
void SETSWRAPUP() {
struct ENTITYTYPE* ETYPE= 0;
struct SETDEF* SDEF= 0;
struct SETMMBRREF* MREF= 0;
       SDEF = (struct SETDEF*)EASEents->F_SETDEFS;
next0001:
       if ( !  ( SDEF != 0 ) ) {
       goto done0001;
       }
       MREF = (struct SETMMBRREF*)SDEF->F_SETMMBRREFS;
next0002:
       if ( !  ( MREF != 0 ) ) {
       goto done0002;
       }
       ETYPE = (struct ENTITYTYPE*)MREF->MMBRENT;
       MAKESETMMBRATTR(E_TXTLIT_F(_T("P_")), ETYPE, 4, SDEF);
       MAKESETMMBRATTR(E_TXTLIT_F(_T("S_")), ETYPE, 4, SDEF);
       MAKESETMMBRATTR(E_TXTLIT_F(_T("M_")), ETYPE, 1, SDEF);
       MREF = (struct SETMMBRREF*)MREF->S_SETMMBRREFS;
       goto next0002;
done0002:
       if (SDEF->SETDISCIPLINE == 0) {
       ATTRRANKRTN(ETYPE, SDEF);
       }
       SDEF = (struct SETDEF*)SDEF->S_SETDEFS;
       goto next0001;
done0001:
       goto retlbl;
retlbl:
       return;
}
void ENTSWRAPUP() {
struct ENTITYTYPE* ETYPE= 0;
struct SCHEMA* ASCHEMA= 0;
       ASCHEMA = (struct SCHEMA*)EASEents->F_SCHEMAS;
next0001:
       if ( !  ( ASCHEMA != 0 ) ) {
       goto done0001;
       }
       if (ASCHEMA->NOGEN == 0) {
       ETYPE = (struct ENTITYTYPE*)ASCHEMA->F_ETYPES;
next0002:
       if ( !  ( ETYPE != 0 ) ) {
       goto done0002;
       }
       if (ETYPE->ISPROC == 0) {
       CRERTN(ETYPE);
       DESRTN(ETYPE);
       }
       ETYPE = (struct ENTITYTYPE*)ETYPE->S_ETYPES;
       goto next0002;
done0002:
;      }
       ASCHEMA = (struct SCHEMA*)ASCHEMA->S_SCHEMAS;
       goto next0001;
done0001:
       goto retlbl;
retlbl:
       return;
}
void DESRTN(struct ENTITYTYPE* ETYPE) {
struct EASEPROC* APROC= 0;
struct ATTRDEF* ATT= 0;
       Script->SCRIPTLEVEL = 1;
       APROC = (struct EASEPROC*)MAKEPROC_F(CONCAT_F(E_TXTLIT_F(_T("d_")), ETYPE->ETYPENAME), ETYPE->SCHEMAREF, 0);
       E_TXTASG_R(&Script->STRPTRS[1], E_TXTLIT_F(_T("EPTR")));
       ADDPARM(APROC, ETYPE, Script->STRPTRS[1], 0, 1);
       ATT = (struct ATTRDEF*)ETYPE->F_ATTRDEFS;
next0001:
       if ( !  ( ATT != 0 ) ) {
       goto done0001;
       }
       if (E_TXTEQL_F(ATT->ATTRTYPE->ETYPENAME, E_TXTLIT_F(_T("Text")))) {
       E_TXTASG_R(&Script->STRPTRS[2], ATT->ATTRNAME);
       SCRIPT(28);
       }
       if (ATT->ATTRTYPE->ISSETTYPE != 0 & ETYPE->ISHIDDEN == 0) {
       E_TXTASG_R(&Script->STRPTRS[2], ATT->ATTRNAME);
       if (ATT->ATTRTYPE->ISPERSISTENT != 0) {
       SCRIPT(59);
       }
       else {
       SCRIPT(33);
       }
       }
       ATT = (struct ATTRDEF*)ATT->S_ATTRDEFS;
       goto next0001;
done0001:
       if (ETYPE->ISPERSISTENT != 0) {
       SCRIPT(56);
       }
       else {
       SCRIPT(29);
       }
       APROC->F_SCRIPTTOKENS = (struct TOKEN*)EASElex->F_TOKENLIST;
       APROC->L_SCRIPTTOKENS = (struct TOKEN*)EASElex->L_TOKENLIST;
       EASElex->F_TOKENLIST = (struct TOKEN*)0;
       EASElex->L_TOKENLIST = (struct TOKEN*)0;
       Script->SCRIPTLEVEL = 0;
       goto retlbl;
retlbl:
       return;
}
void CRERTN(struct ENTITYTYPE* ETYPE) {
struct ENTITYTYPE* RTYPE= 0;
struct EASEPROC* APROC= 0;
struct ATTRDEF* ATT= 0;
       Script->SCRIPTLEVEL = 1;
       if (ETYPE->ISPERSISTENT != 0) {
       RTYPE = (struct ENTITYTYPE*)FINDETYPEBYNAME_F(E_TXTLIT_F(_T("iRef")), 1);
       }
       else {
       RTYPE = (struct ENTITYTYPE*)ETYPE;
       }
       APROC = (struct EASEPROC*)MAKEPROC_F(CONCAT_F(E_TXTLIT_F(_T("c_")), ETYPE->ETYPENAME), ETYPE->SCHEMAREF, RTYPE);
       ADDLCL(APROC, RTYPE, E_TXTLIT_F(_T("EPTR")), 0);
       E_TXTASG_R(&Script->STRPTRS[1], ETYPE->ETYPENAME);
       Script->IPTRS[1] = (int)ETYPE->SCHEMAREF->SCHEMAID;
       Script->IPTRS[2] = (int)ETYPE->ETYPEID;
       if (ETYPE->ISPERSISTENT != 0) {
       SCRIPT(46);
       }
       else {
       SCRIPT(30);
       }
       E_TXTASG_R(&Script->STRPTRS[1], E_TXTLIT_F(_T("EPTR")));
       if (ETYPE->ISHIDDEN == 0) {
       ATT = (struct ATTRDEF*)ETYPE->F_ATTRDEFS;
next0001:
       if ( !  ( ATT != 0 ) ) {
       goto done0001;
       }
       if (ATT->ATTRTYPE->ISSETTYPE != 0) {
       E_TXTASG_R(&Script->STRPTRS[2], ATT->ATTRNAME);
       Script->IPTRS[3] = (int)ATT->ATTRTYPE->SCHEMAREF->SCHEMAID;
       Script->IPTRS[4] = (int)ATT->ATTRTYPE->ETYPEID;
       if (ATT->ATTRTYPE->ISPERSISTENT != 0) {
       SCRIPT(47);
       }
       else {
       SCRIPT(31);
       }
       }
       ATT = (struct ATTRDEF*)ATT->S_ATTRDEFS;
       goto next0001;
done0001:
;      }
       SCRIPT(32);
       APROC->F_SCRIPTTOKENS = (struct TOKEN*)EASElex->F_TOKENLIST;
       APROC->L_SCRIPTTOKENS = (struct TOKEN*)EASElex->L_TOKENLIST;
       EASElex->F_TOKENLIST = (struct TOKEN*)0;
       EASElex->L_TOKENLIST = (struct TOKEN*)0;
       Script->SCRIPTLEVEL = 0;
       goto retlbl;
retlbl:
       return;
}
void ATTRRANKRTN(struct ENTITYTYPE* ETYPE, struct SETDEF* SDEF) {
struct ENTITYTYPE* PTYPE= 0;
struct ENTITYTYPE* STYPE= 0;
struct EASEPROC* APROC= 0;
struct RANKATTRDEF* RANKATTR= 0;
       Script->SCRIPTLEVEL = 1;
       PTYPE = (struct ENTITYTYPE*)FINDETYPEBYNAME_F(E_TXTLIT_F(_T("Integer")), 1);
       APROC = (struct EASEPROC*)MAKEPROC_F(CONCAT_F(E_TXTLIT_F(_T("X_")), SDEF->SETNAME), ETYPE->SCHEMAREF, PTYPE);
       E_TXTASG_R(&Script->STRPTRS[1], E_TXTLIT_F(_T("E1")));
       E_TXTASG_R(&Script->STRPTRS[2], E_TXTLIT_F(_T("E2")));
       PTYPE = (struct ENTITYTYPE*)FINDETYPEBYNAME_F(E_TXTLIT_F(_T("Reference")), 1);
       ADDPARM(APROC, PTYPE, Script->STRPTRS[2], 0, 0);
       ADDPARM(APROC, PTYPE, Script->STRPTRS[1], 0, 0);
       E_TXTASG_R(&Script->STRPTRS[3], ETYPE->ETYPENAME);
       SCRIPT(43);
       RANKATTR = (struct RANKATTRDEF*)SDEF->F_RANKATTRS;
next0001:
       if ( !  ( RANKATTR != 0 ) ) {
       goto done0001;
       }
       E_TXTASG_R(&Script->STRPTRS[4], RANKATTR->RATTRNAME);
       SCRIPT(44);
       RANKATTR = (struct RANKATTRDEF*)RANKATTR->S_RANKATTRS;
       goto next0001;
done0001:
       SCRIPT(45);
       APROC->F_SCRIPTTOKENS = (struct TOKEN*)EASElex->F_TOKENLIST;
       APROC->L_SCRIPTTOKENS = (struct TOKEN*)EASElex->L_TOKENLIST;
       EASElex->F_TOKENLIST = (struct TOKEN*)0;
       EASElex->L_TOKENLIST = (struct TOKEN*)0;
       Script->SCRIPTLEVEL = 0;
       goto retlbl;
retlbl:
       return;
}
void ADDLCL(struct EASEPROC* APROC, struct ENTITYTYPE* TYPE, Etxt* ANAME, int SUBS) {
struct ENTITYTYPE* RTN= 0;
struct DICTUSE* AUSE= 0;
struct ATTRDEF* ATT= 0;
E_TXTINC_R(ANAME);
       ATT= c_ATTRDEF();
       E_TXTASG_R(&ATT->ATTRNAME, ANAME);
       ATT->ATTRTYPE = (struct ENTITYTYPE*)TYPE;
       ATT->SUBSCRIPTS = SUBS;
       AUSE = (struct DICTUSE*)FINDSPECUSE_F(APROC->PDICTREF, 3);
       RTN = (struct ENTITYTYPE*)AUSE->USEENTITY;
       ATT->S_ATTRDEFS = (struct ATTRDEF*)RTN->F_ATTRDEFS;
       RTN->F_ATTRDEFS = (struct ATTRDEF*)ATT;
       goto retlbl;
retlbl:
E_TXTDEL_R(ANAME);
       return;
}
void ADDPARM(struct EASEPROC* APROC, struct ENTITYTYPE* TYPE, Etxt* PNAME, int SUBS, int YLD) {
struct ENTITYTYPE* RTN= 0;
struct DICTUSE* AUSE= 0;
struct ATTRDEF* PARM= 0;
E_TXTINC_R(PNAME);
       PARM= c_ATTRDEF();
       E_TXTASG_R(&PARM->ATTRNAME, PNAME);
       PARM->ATTRTYPE = (struct ENTITYTYPE*)TYPE;
       PARM->SUBSCRIPTS = SUBS;
       PARM->ISPARAM = 1;
       PARM->ISYIELD = YLD;
       AUSE = (struct DICTUSE*)FINDSPECUSE_F(APROC->PDICTREF, 3);
       RTN = (struct ENTITYTYPE*)AUSE->USEENTITY;
       PARM->S_ATTRDEFS = (struct ATTRDEF*)RTN->F_ATTRDEFS;
       RTN->F_ATTRDEFS = (struct ATTRDEF*)PARM;
       goto retlbl;
retlbl:
E_TXTDEL_R(PNAME);
       return;
}
struct EASEPROC* MAKEPROC_F(Etxt* RNAME, struct SCHEMA* ASCHEMA, struct ENTITYTYPE* RTYPE) {
struct ENTITYTYPE* RTN= 0;
struct EASEPROC* APROC= 0;
struct DICTUSE* AUSE= 0;
struct DICTENTRY* DREF= 0;
struct ATTRDEF* RATT= 0;
struct EASEPROC* rval = 0;
E_TXTINC_R(RNAME);
       RTN= c_ENTITYTYPE();
       RTN->S_ETYPES = (struct ENTITYTYPE*)ASCHEMA->F_ETYPES;
       ASCHEMA->F_ETYPES = (struct ENTITYTYPE*)RTN;
       RTN->SCHEMAREF = (struct SCHEMA*)ASCHEMA;
       RTN->ISPROC = 1;
       E_TXTASG_R(&RTN->ETYPENAME, RNAME);
       DREF = (struct DICTENTRY*)FINDDICTENTRY_F(RNAME);
       AUSE = (struct DICTUSE*)MAKEUSE_F(DREF, 3);
       AUSE->USEENTITY = (struct ENTITYTYPE*)RTN;
       APROC= c_EASEPROC();
       APROC->PDICTREF = (struct DICTENTRY*)DREF;
       APROC->S_PROCS = (struct EASEPROC*)ASCHEMA->F_PROCS;
       ASCHEMA->F_PROCS = (struct EASEPROC*)APROC;
       if (RTYPE != 0) {
       RATT= c_ATTRDEF();
       RATT->ISRETTYPE = 1;
       E_TXTASG_R(&RATT->ATTRNAME, E_TXTLIT_F(_T("rval")));
       RATT->ATTRTYPE = (struct ENTITYTYPE*)RTYPE;
       RTN->F_ATTRDEFS = (struct ATTRDEF*)RATT;
       APROC->RETURNATT = (struct ATTRDEF*)RATT;
       }
       rval = (struct EASEPROC*)APROC;
goto retlbl;
retlbl:
E_TXTDEL_R(RNAME);
       return rval;
}
void FIXUPSCHEMAS() {
struct FIXUP* AFIX= 0;
struct ATTRDEF* DATTR= 0;
struct ENTITYTYPE* ETYPE= 0;
struct DICTENTRY* DREF= 0;
struct DICTUSE* AUSE= 0;
struct DICTUSE* AUSE2= 0;
struct SETATTDEFREF* SETREF= 0;
struct SETMMBRREF* MREF= 0;
struct SETDEF* SDEF= 0;
struct FIXUP* DEAD= 0;
       EASEents->E_BUILTINS = (ENTITYTYPE**)calloc(13 + 1, sizeof(ENTITYTYPE*));
       EASEents->E_BUILTINS[0] = (ENTITYTYPE*)(13);
       EASEents->E_BUILTINS[1] = (struct ENTITYTYPE*)FINDETYPEBYNAME_F(E_TXTLIT_F(_T("Integer")), 1);
       EASEents->E_BUILTINS[2] = (struct ENTITYTYPE*)FINDETYPEBYNAME_F(E_TXTLIT_F(_T("Real")), 1);
       EASEents->E_BUILTINS[3] = (struct ENTITYTYPE*)FINDETYPEBYNAME_F(E_TXTLIT_F(_T("Text")), 1);
       EASEents->E_BUILTINS[4] = (struct ENTITYTYPE*)FINDETYPEBYNAME_F(E_TXTLIT_F(_T("Reference")), 1);
       EASEents->E_BUILTINS[5] = (struct ENTITYTYPE*)FINDETYPEBYNAME_F(E_TXTLIT_F(_T("iRef")), 1);
       EASEents->E_BUILTINS[6] = (struct ENTITYTYPE*)FINDETYPEBYNAME_F(E_TXTLIT_F(_T("Subprogram")), 1);
       EASEents->E_BUILTINS[12] = (struct ENTITYTYPE*)FINDETYPEBYNAME_F(E_TXTLIT_F(_T("E_SET")), 1);
       EASEents->E_BUILTINS[13] = (struct ENTITYTYPE*)FINDETYPEBYNAME_F(E_TXTLIT_F(_T("E_PSET")), 1);
       AFIX = (struct FIXUP*)EASEents->F_SETOWNRFIXUPS;
next0001:
       if ( !  ( AFIX != 0 ) ) {
       goto done0001;
       }
       SDEF = (struct SETDEF*)FINDSET_F(AFIX->ATTREF->ATTRNAME, AFIX->DBID);
       if (SDEF->ISPERSISTENT == 0) {
       E_TXTASG_R(&AFIX->ENTREFNAME, EASEents->E_BUILTINS[12]->ETYPENAME);
       }
       else {
       E_TXTASG_R(&AFIX->ENTREFNAME, EASEents->E_BUILTINS[13]->ETYPENAME);
       }
       AFIX->ATTREF->SETATTRSETDEF = (struct SETDEF*)SDEF;
       EASEents->FIXUP = (struct FIXUP*)AFIX;
       AFIX = (struct FIXUP*)AFIX->S_FIXUPS;
       EASEents->FIXUP->S_FIXUPS = (struct FIXUP*)EASEents->F_ATTRFIXUPS;
       EASEents->F_ATTRFIXUPS = (struct FIXUP*)EASEents->FIXUP;
       goto next0001;
done0001:
       AFIX = (struct FIXUP*)EASEents->F_ATTRFIXUPS;
next0002:
       if ( !  ( AFIX != 0 ) ) {
       goto done0002;
       }
       DATTR = (struct ATTRDEF*)AFIX->ATTREF;
       ETYPE = (struct ENTITYTYPE*)FINDETYPEBYNAME_F(AFIX->ENTREFNAME, AFIX->DBID);
       if (ETYPE == 0) {
       EASERR(-1002, AFIX->ENTREFNAME);
       ETYPE = (struct ENTITYTYPE*)EASEents->E_BUILTINS[1];
       }
       DATTR->ATTRTYPE = (struct ENTITYTYPE*)ETYPE;
       DREF = (struct DICTENTRY*)FINDDICTENTRY_F(DATTR->ATTRNAME);
       if (DATTR->OWNERTYPE->ISPROC == 0) {
       AUSE2 = (struct DICTUSE*)FINDSPECUSE_F(DREF, 4);
       AUSE = (struct DICTUSE*)MAKEUSE_F(DREF, 4);
       if (AUSE2 != 0) {
       AUSE->ISCOMMONATT = 1;
       AUSE2->ISCOMMONATT = 1;
       }
       AUSE->USEOWNER = (struct ENTITYTYPE*)DATTR->OWNERTYPE;
       AUSE->USEENTITY = (struct ENTITYTYPE*)ETYPE;
       AUSE->USESUBS = DATTR->SUBSCRIPTS;
       AUSE->USEMODE = FINDMODE_F(ETYPE);
       if (ETYPE->ISSETTYPE != 0) {
       AUSE->USESETREFATT = (struct ATTRDEF*)DATTR;
       MAKESETOWNRATTR(E_TXTLIT_F(_T("F_")), DATTR, 4);
       MAKESETOWNRATTR(E_TXTLIT_F(_T("L_")), DATTR, 4);
       MAKESETOWNRATTR(E_TXTLIT_F(_T("N_")), DATTR, 1);
       }
       }
       else {
       if (DATTR->ISRETTYPE != 0) {
       DREF = (struct DICTENTRY*)FINDDICTENTRY_F(DATTR->OWNERTYPE->ETYPENAME);
       AUSE = (struct DICTUSE*)FINDSPECUSE_F(DREF, 3);
       AUSE->USEMODE = FINDMODE_F(ETYPE);
       }
       }
       DEAD = (struct FIXUP*)AFIX;
       AFIX = (struct FIXUP*)AFIX->S_FIXUPS;
       d_FIXUP(DEAD);
       goto next0002;
done0002:
       EASEents->F_ATTRFIXUPS = (struct FIXUP*)0;
       AFIX = (struct FIXUP*)EASEents->F_SETMMBRFIXUPS;
next0003:
       if ( !  ( AFIX != 0 ) ) {
       goto done0003;
       }
       SETREF = (struct SETATTDEFREF*)AFIX->SETATTREF;
       SDEF = (struct SETDEF*)FINDSET_F(SETREF->SETATTNAME, SETREF->DBID);
       MREF= c_SETMMBRREF();
       MREF->S_SETMMBRREFS = (struct SETMMBRREF*)SDEF->F_SETMMBRREFS;
       SDEF->F_SETMMBRREFS = (struct SETMMBRREF*)MREF;
       MREF->MMBRENT = (struct ENTITYTYPE*)AFIX->FIXMMBRENTREF;
       DEAD = (struct FIXUP*)AFIX;
       AFIX = (struct FIXUP*)AFIX->S_FIXUPS;
       d_FIXUP(DEAD);
       goto next0003;
done0003:
       ENTSWRAPUP();
       SETSWRAPUP();
       SYSSETSINIT();
       goto retlbl;
retlbl:
       return;
}
Etxt* FIXNAME_F(Etxt* ATTNAME) {
int LEN= 0;
int I= 0;
Etxt* rval = 0;
E_TXTINC_R(ATTNAME);
       LEN = LENGTH_F(ATTNAME);
       I = 1;
       goto test0001;
next0001:
       I = I+1;
test0001:
       if (I > LEN) {
       goto done0001;
       }
       if (ACHAR_F(ATTNAME, I) == 46 | ACHAR_F(ATTNAME, I) == 32) {
       QACHAR_F(ATTNAME, I, 95);
       }
       goto next0001;
done0001:
       E_TXTASG_R(&rval, ATTNAME);
goto retlbl;
retlbl:
E_TXTDEL_R(ATTNAME);
       return rval;
}
struct ENTITYTYPE* READXMLENT_F(struct SCHEMA* ASCHEMA) {
int AINT= 0;
Etxt* ATXT= 0;
struct ENTITYTYPE* ETYPE= 0;
struct ATTRDEF* DATTR= 0;
struct ATTRDEF* LATTR= 0;
struct SETDEF* SDEF= 0;
struct SETATTDEFREF* SETREF= 0;
struct FIXUP* AFIX= 0;
struct RANKATTRDEF* RANKATTR= 0;
struct ENTITYTYPE* rval = 0;
       ETYPE= c_ENTITYTYPE();
       ETYPE->ETYPEID = XMLIATTR_F(E_TXTLIT_F(_T("ID")));
       if (XMLLATTR_F(E_TXTLIT_F(_T("isSystemDefined"))) != 0) {
       ETYPE->ISSETTYPE = XMLLATTR_F(E_TXTLIT_F(_T("isSetType")));
       ETYPE->ISHIDDEN = XMLLATTR_F(E_TXTLIT_F(_T("isHidden")));
       E_TXTASG_R(&ETYPE->TARGETNAME, XMLTATTR_F(E_TXTLIT_F(_T("targetName"))));
       }
       ETYPE->ISPROC = XMLLATTR_F(E_TXTLIT_F(_T("isProcedure")));
       ETYPE->ISPERSISTENT = XMLLATTR_F(E_TXTLIT_F(_T("isPersistent")));
       XMLINTO();
       if (XMLFINDELEM_F(E_TXTLIT_F(_T("entityTypeName"))) != 0) {
       E_TXTASG_R(&ETYPE->ETYPENAME, FIXNAME_F(XMLGETDATA_F()));
       }
       if (ETYPE->ISPROC != 0) {
       if (XMLFINDELEM_F(E_TXTLIT_F(_T("Body"))) != 0) {
       E_TXTASG_R(&ETYPE->PROCBODY, XMLGETDATA_F());
       }
       }
       LATTR = (struct ATTRDEF*)0;
next0001:
       if ( !  ( XMLFINDELEM_F(E_TXTLIT_F(_T("attrDef"))) != 0 ) ) {
       goto done0001;
       }
       DATTR= c_ATTRDEF();
       if (ETYPE->F_ATTRDEFS == 0) {
       ETYPE->F_ATTRDEFS = (struct ATTRDEF*)DATTR;
       }
       else {
       LATTR->S_ATTRDEFS = (struct ATTRDEF*)DATTR;
       }
       LATTR = (struct ATTRDEF*)DATTR;
       DATTR->OWNERTYPE = (struct ENTITYTYPE*)ETYPE;
       DATTR->ISEMBED = XMLLATTR_F(E_TXTLIT_F(_T("embedded")));
       DATTR->ISPARAM = XMLLATTR_F(E_TXTLIT_F(_T("parameter")));
       DATTR->ISYIELD = XMLLATTR_F(E_TXTLIT_F(_T("yielded")));
       DATTR->ISRETTYPE = XMLLATTR_F(E_TXTLIT_F(_T("returntype")));
       DATTR->SUBSCRIPTS = XMLIATTR_F(E_TXTLIT_F(_T("subscripts")));
       if (XMLFINDCHILD_F(E_TXTLIT_F(_T("attrName"))) != 0) {
       E_TXTASG_R(&DATTR->ATTRNAME, FIXNAME_F(XMLGETCHILDDATA_F()));
       }
       if (XMLFINDCHILD_F(E_TXTLIT_F(_T("attrTypeName"))) != 0) {
       AFIX= c_FIXUP();
       AFIX->ATTREF = (struct ATTRDEF*)DATTR;
       E_TXTASG_R(&AFIX->ENTREFNAME, FIXNAME_F(XMLGETCHILDDATA_F()));
       AFIX->DBID = ASCHEMA->SCHEMAID;
       AFIX->S_FIXUPS = (struct FIXUP*)EASEents->F_ATTRFIXUPS;
       EASEents->F_ATTRFIXUPS = (struct FIXUP*)AFIX;
       }
       goto next0001;
done0001:
next0002:
       if ( !  ( XMLFINDELEM_F(E_TXTLIT_F(_T("setOwnDef"))) != 0 ) ) {
       goto done0002;
       }
       DATTR= c_ATTRDEF();
       E_TXTASG_R(&DATTR->ATTRNAME, FIXNAME_F(XMLGETDATA_F()));
       if (ETYPE->F_ATTRDEFS == 0) {
       ETYPE->F_ATTRDEFS = (struct ATTRDEF*)DATTR;
       }
       else {
       LATTR->S_ATTRDEFS = (struct ATTRDEF*)DATTR;
       }
       LATTR = (struct ATTRDEF*)DATTR;
       DATTR->OWNERTYPE = (struct ENTITYTYPE*)ETYPE;
       AFIX= c_FIXUP();
       AFIX->ATTREF = (struct ATTRDEF*)DATTR;
       AFIX->DBID = XMLIATTR_F(E_TXTLIT_F(_T("dbId")));
       AFIX->S_FIXUPS = (struct FIXUP*)EASEents->F_SETOWNRFIXUPS;
       EASEents->F_SETOWNRFIXUPS = (struct FIXUP*)AFIX;
       goto next0002;
done0002:
next0003:
       if ( !  ( XMLFINDELEM_F(E_TXTLIT_F(_T("setBelongDef"))) != 0 ) ) {
       goto done0003;
       }
       SETREF= c_SETATTDEFREF();
       E_TXTASG_R(&SETREF->SETATTNAME, FIXNAME_F(XMLGETDATA_F()));
       SETREF->DBID = XMLIATTR_F(E_TXTLIT_F(_T("dbId")));
       AFIX= c_FIXUP();
       AFIX->SETATTREF = (struct SETATTDEFREF*)SETREF;
       AFIX->FIXMMBRENTREF = (struct ENTITYTYPE*)ETYPE;
       AFIX->S_FIXUPS = (struct FIXUP*)EASEents->F_SETMMBRFIXUPS;
       EASEents->F_SETMMBRFIXUPS = (struct FIXUP*)AFIX;
       goto next0003;
done0003:
       XMLOUTOF();
       rval = (struct ENTITYTYPE*)ETYPE;
goto retlbl;
retlbl:
E_TXTDEL_R(ATXT);
       return rval;
}
void READXML(Etxt* PATH, Etxt* FNAME) {
Etxt* XMLFILE= 0;
int AINT= 0;
int OK= 0;
Etxt* ATXT= 0;
struct SCHEMA* ASCHEMA= 0;
struct SCHEMA* LSCHEMA= 0;
struct ENTITYTYPE* ETYPE= 0;
struct EASEPROC* APROC= 0;
struct DICTENTRY* DREF= 0;
struct DICTUSE* AUSE= 0;
struct ATTRDEF* ATT= 0;
struct SETDEF* SDEF= 0;
struct RANKATTRDEF* RANKATTR= 0;
struct RANKATTRDEF* LRANKATTR= 0;
E_TXTINC_R(PATH);
E_TXTINC_R(FNAME);
       E_TXTASG_R(&XMLFILE, PATH);
       if (E_TXTNEQ_F(FNAME, 0)) {
       E_TXTASG_R(&XMLFILE, CONCAT_F(PATH, FNAME));
       E_TXTASG_R(&XMLFILE, CONCAT_F(XMLFILE, E_TXTLIT_F(_T(".xml"))));
       }
       OK = XMLOPEN_F(XMLFILE);
       OK = XMLFINDELEM_F(E_TXTLIT_F(_T("EASE-Database")));
       ASCHEMA= c_SCHEMA();
       E_TXTASG_R(&ASCHEMA->GENNAME, FNAME);
       if (EASEents->F_SCHEMAS == 0) {
       EASEents->F_SCHEMAS = (struct SCHEMA*)ASCHEMA;
       }
       else {
       LSCHEMA = (struct SCHEMA*)EASEents->F_SCHEMAS;
next0001:
       if ( !  ( LSCHEMA->S_SCHEMAS != 0 ) ) {
       goto done0001;
       }
       LSCHEMA = (struct SCHEMA*)LSCHEMA->S_SCHEMAS;
       goto next0001;
done0001:
       LSCHEMA->S_SCHEMAS = (struct SCHEMA*)ASCHEMA;
       }
       ASCHEMA->SCHEMAID = XMLIATTR_F(E_TXTLIT_F(_T("ID")));
       if (E_TXTNEQ_F(XMLTATTR_F(E_TXTLIT_F(_T("noGen"))), E_TXTLIT_F(_T("""")))) {
       ASCHEMA->NOGEN = 1;
       }
       if (E_TXTNEQ_F(XMLTATTR_F(E_TXTLIT_F(_T("noHdr"))), E_TXTLIT_F(_T("""")))) {
       ASCHEMA->NOHDR = 1;
       }
       E_TXTASG_R(&ATXT, XMLTATTR_F(E_TXTLIT_F(_T("genname"))));
       if (E_TXTNEQ_F(ATXT, 0)) {
       E_TXTASG_R(&ASCHEMA->GENNAME, ATXT);
       }
       XMLINTO();
       if (XMLFINDELEM_F(E_TXTLIT_F(_T("ENTITIES"))) != 0) {
       XMLINTO();
next0002:
       if ( !  ( XMLFINDELEM_F(E_TXTLIT_F(_T("entityType"))) != 0 ) ) {
       goto done0002;
       }
       ETYPE = (struct ENTITYTYPE*)READXMLENT_F(ASCHEMA);
       ETYPE->S_ETYPES = (struct ENTITYTYPE*)ASCHEMA->F_ETYPES;
       ASCHEMA->F_ETYPES = (struct ENTITYTYPE*)ETYPE;
       ETYPE->SCHEMAREF = (struct SCHEMA*)ASCHEMA;
       DREF = (struct DICTENTRY*)FINDDICTENTRY_F(ETYPE->ETYPENAME);
       if (ETYPE->ISPROC != 0) {
       APROC= c_EASEPROC();
       APROC->PDICTREF = (struct DICTENTRY*)DREF;
       APROC->S_PROCS = (struct EASEPROC*)ASCHEMA->F_PROCS;
       ASCHEMA->F_PROCS = (struct EASEPROC*)APROC;
       AUSE = (struct DICTUSE*)MAKEUSE_F(DREF, 3);
       ATT = (struct ATTRDEF*)ETYPE->F_ATTRDEFS;
next0003:
       if ( !  ( ATT != 0 ) ) {
       goto done0003;
       }
       if (ATT->ISRETTYPE != 0) {
       APROC->RETURNATT = (struct ATTRDEF*)ATT;
       goto done0003;
       }
       ATT = (struct ATTRDEF*)ATT->S_ATTRDEFS;
       goto next0003;
done0003:
;      }
       else {
       AUSE = (struct DICTUSE*)MAKEUSE_F(DREF, 2);
       AUSE->USEMODE = 4;
       }
       AUSE->USEENTITY = (struct ENTITYTYPE*)ETYPE;
       goto next0002;
done0002:
       XMLOUTOF();
       }
       if (XMLFINDELEM_F(E_TXTLIT_F(_T("SETS"))) != 0) {
       XMLINTO();
next0004:
       if ( !  ( XMLFINDELEM_F(E_TXTLIT_F(_T("setDef"))) != 0 ) ) {
       goto done0004;
       }
       SDEF= c_SETDEF();
       SDEF->S_SETDEFS = (struct SETDEF*)EASEents->F_SETDEFS;
       EASEents->F_SETDEFS = (struct SETDEF*)SDEF;
       E_TXTASG_R(&ATXT, XMLTATTR_F(E_TXTLIT_F(_T("discipline"))));
       if (E_TXTEQL_F(ATXT, E_TXTLIT_F(_T("F")))) {
       SDEF->SETDISCIPLINE = 1;
       }
       if (E_TXTEQL_F(ATXT, E_TXTLIT_F(_T("L")))) {
       SDEF->SETDISCIPLINE = 2;
       }
       if (E_TXTEQL_F(XMLTATTR_F(E_TXTLIT_F(_T("isPersistent"))), E_TXTLIT_F(_T("Y")))) {
       SDEF->ISPERSISTENT = 1;
       }
       XMLINTO();
       if (XMLFINDELEM_F(E_TXTLIT_F(_T("setName"))) != 0) {
       E_TXTASG_R(&SDEF->SETNAME, FIXNAME_F(XMLGETDATA_F()));
       }
next0005:
       if ( !  ( XMLFINDELEM_F(E_TXTLIT_F(_T("rankAttr"))) != 0 ) ) {
       goto done0005;
       }
       RANKATTR= c_RANKATTRDEF();
       if (SDEF->F_RANKATTRS == 0) {
       SDEF->F_RANKATTRS = (struct RANKATTRDEF*)RANKATTR;
       }
       else {
       LRANKATTR = (struct RANKATTRDEF*)SDEF->F_RANKATTRS;
next0006:
       if ( !  ( LRANKATTR->S_RANKATTRS != 0 ) ) {
       goto done0006;
       }
       LRANKATTR = (struct RANKATTRDEF*)LRANKATTR->S_RANKATTRS;
       goto next0006;
done0006:
       LRANKATTR->S_RANKATTRS = (struct RANKATTRDEF*)RANKATTR;
       }
       if (XMLIATTR_F(E_TXTLIT_F(_T("low"))) != 0) {
       RANKATTR->LO = 1;
       }
       E_TXTASG_R(&RANKATTR->RATTRNAME, FIXNAME_F(XMLGETDATA_F()));
       goto next0005;
done0005:
       XMLOUTOF();
       goto next0004;
done0004:
       XMLOUTOF();
       }
       if (XMLFINDELEM_F(E_TXTLIT_F(_T("SYSTEM"))) != 0) {
       XMLINTO();
       if (XMLFINDELEM_F(E_TXTLIT_F(_T("entityType"))) != 0) {
       ETYPE = (struct ENTITYTYPE*)READXMLENT_F(ASCHEMA);
       ETYPE->S_ETYPES = (struct ENTITYTYPE*)EASEents->F_SYSTEMS;
       EASEents->F_SYSTEMS = (struct ENTITYTYPE*)ETYPE;
       ETYPE->SCHEMAREF = (struct SCHEMA*)ASCHEMA;
       E_TXTASG_R(&ETYPE->ETYPENAME, ASCHEMA->GENNAME);
       ASCHEMA->THESYSTEM = (struct ENTITYTYPE*)ETYPE;
       }
       XMLOUTOF();
       }
       if (XMLFINDELEM_F(E_TXTLIT_F(_T("SUBST"))) != 0) {
       XMLINTO();
next0007:
       if ( !  ( XMLFINDELEM_F(E_TXTLIT_F(_T("d2m"))) != 0 ) ) {
       goto done0007;
       }
       E_TXTASG_R(&ATXT, XMLTATTR_F(E_TXTLIT_F(_T("term"))));
       DREF = (struct DICTENTRY*)FINDDICTENTRY_F(ATXT);
       if (XMLFINDCHILD_F(E_TXTLIT_F(_T("substxt"))) != 0) {
       E_TXTASG_R(&ATXT, FIXNAME_F(XMLGETCHILDDATA_F()));
       ANALYZE(ATXT, LENGTH_F(ATXT), 1);
       DREF->F_SUBST = (struct TOKEN*)EASElex->F_TOKENLIST;
       DREF->L_SUBST = (struct TOKEN*)EASElex->L_TOKENLIST;
       EASElex->F_TOKENLIST = (struct TOKEN*)0;
       EASElex->L_TOKENLIST = (struct TOKEN*)0;
       }
       goto next0007;
done0007:
       XMLOUTOF();
       }
E_TXTDEL_R(PATH);
E_TXTDEL_R(FNAME);
E_TXTDEL_R(XMLFILE);
E_TXTDEL_R(ATXT);
       return;
}

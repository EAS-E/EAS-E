#pragma once
#include "easlib.h"

#include "EASEmain.h"
#include "EASElex.h"
#include "Synrule.h"
#include "Dict.h"
#include "EASEpars.h"
#include "Script.h"
#include "EASEgen.h"

#define _ERRORREC
#define _RANKATTRDEF
#define _FIXUP
#define _SETDEF
#define _SETATTDEFREF
#define _SETMMBRREF
#define _ATTRDEF
#define _ENTITYTYPE
#define _SCHEMA

struct ERRORREC {
struct eInstHdr hdr;
struct ERRORREC* S_ERRORRECS;
int ERRNUM;
struct EASEPROC* INPROC;
int LINENUM;
};
#define Z_ERRORREC sizeof(ERRORREC)
struct RANKATTRDEF {
struct eInstHdr hdr;
struct RANKATTRDEF* S_RANKATTRS;
int LO;
Etxt* RATTRNAME;
};
#define Z_RANKATTRDEF sizeof(RANKATTRDEF)
struct FIXUP {
struct eInstHdr hdr;
Etxt* ENTREFNAME;
struct ATTRDEF* ATTREF;
struct ENTITYTYPE* FIXMMBRENTREF;
struct SETATTDEFREF* SETATTREF;
struct SETDEF* FIXSETDEF;
int DBID;
struct FIXUP* S_FIXUPS;
};
#define Z_FIXUP sizeof(FIXUP)
struct SETDEF {
struct eInstHdr hdr;
struct SETDEF* S_SETDEFS;
int SSID;
Etxt* SETNAME;
int SETDISCIPLINE;
int ISPERSISTENT;
struct RANKATTRDEF* F_RANKATTRS;
struct SETMMBRREF* F_SETMMBRREFS;
};
#define Z_SETDEF sizeof(SETDEF)
struct SETATTDEFREF {
struct eInstHdr hdr;
struct SETATTDEFREF* S_SETATTDEFREFS;
struct ATTRDEF* ATTREF;
int DBID;
Etxt* SETATTNAME;
};
#define Z_SETATTDEFREF sizeof(SETATTDEFREF)
struct SETMMBRREF {
struct eInstHdr hdr;
struct SETMMBRREF* S_SETMMBRREFS;
struct ENTITYTYPE* MMBRENT;
};
#define Z_SETMMBRREF sizeof(SETMMBRREF)
struct ATTRDEF {
struct eInstHdr hdr;
Etxt* ATTRNAME;
struct ATTRDEF* S_ATTRDEFS;
struct ENTITYTYPE* OWNERTYPE;
struct ENTITYTYPE* ATTRTYPE;
int ISEMBED;
int ISPARAM;
int ISYIELD;
int ISRETTYPE;
int SUBSCRIPTS;
struct SETMMBRREF* F_SETMMBRREFS;
struct SETDEF* SETATTRSETDEF;
};
#define Z_ATTRDEF sizeof(ATTRDEF)
struct ENTITYTYPE {
struct eInstHdr hdr;
int ETYPEID;
Etxt* ETYPENAME;
struct ENTITYTYPE* S_ETYPES;
struct ATTRDEF* F_ATTRDEFS;
struct SETATTDEFREF* F_OWNDSETREFS;
struct SETATTDEFREF* F_MMBRSETATTREFS;
Etxt* PROCBODY;
struct SCHEMA* SCHEMAREF;
int ISHIDDEN;
int ISSETTYPE;
int ISPROC;
int ISPERSISTENT;
int ISUSEDTYPE;
Etxt* TARGETNAME;
};
#define Z_ENTITYTYPE sizeof(ENTITYTYPE)
struct SCHEMA {
struct eInstHdr hdr;
Etxt* GENNAME;
struct ENTITYTYPE* F_ETYPES;
struct SCHEMA* S_SCHEMAS;
struct ENTITYTYPE* THESYSTEM;
struct EASEPROC* F_PROCS;
int SCHEMAID;
int LASTETYPEID;
int NOGEN;
int NOHDR;
};
#define Z_SCHEMA sizeof(SCHEMA)
void EASEents_sets();
void d_SCHEMA(struct SCHEMA*& EPTR);
struct SCHEMA* c_SCHEMA();
void d_ENTITYTYPE(struct ENTITYTYPE*& EPTR);
struct ENTITYTYPE* c_ENTITYTYPE();
void d_ATTRDEF(struct ATTRDEF*& EPTR);
struct ATTRDEF* c_ATTRDEF();
void d_SETMMBRREF(struct SETMMBRREF*& EPTR);
struct SETMMBRREF* c_SETMMBRREF();
void d_SETATTDEFREF(struct SETATTDEFREF*& EPTR);
struct SETATTDEFREF* c_SETATTDEFREF();
void d_SETDEF(struct SETDEF*& EPTR);
struct SETDEF* c_SETDEF();
void d_FIXUP(struct FIXUP*& EPTR);
struct FIXUP* c_FIXUP();
void d_RANKATTRDEF(struct RANKATTRDEF*& EPTR);
struct RANKATTRDEF* c_RANKATTRDEF();
void d_ERRORREC(struct ERRORREC*& EPTR);
struct ERRORREC* c_ERRORREC();
int FINDMODE_F(struct ENTITYTYPE* ETYPE);
void LISTENTITIES();
struct SETDEF* FINDSET_F(Etxt* ANAME, int SID);
struct ENTITYTYPE* FINDETYPEBYNAME_F(Etxt* ANAME, int SID);
void MAKESETMMBRATTR(Etxt* PREFIX, struct ENTITYTYPE* ETYPE, int MODE, struct SETDEF* SDEF);
void MAKESETOWNRATTR(Etxt* PREFIX, struct ATTRDEF* ATTR, int MODE);
void SYSSETSINIT();
void SETSWRAPUP();
void ENTSWRAPUP();
void DESRTN(struct ENTITYTYPE* ETYPE);
void CRERTN(struct ENTITYTYPE* ETYPE);
void ATTRRANKRTN(struct ENTITYTYPE* ETYPE, struct SETDEF* SDEF);
void ADDLCL(struct EASEPROC* APROC, struct ENTITYTYPE* TYPE, Etxt* ANAME, int SUBS);
void ADDPARM(struct EASEPROC* APROC, struct ENTITYTYPE* TYPE, Etxt* PNAME, int SUBS, int YLD);
struct EASEPROC* MAKEPROC_F(Etxt* RNAME, struct SCHEMA* ASCHEMA, struct ENTITYTYPE* RTYPE);
void FIXUPSCHEMAS();
Etxt* FIXNAME_F(Etxt* ATTNAME);
struct ENTITYTYPE* READXMLENT_F(struct SCHEMA* ASCHEMA);
void READXML(Etxt* PATH, Etxt* FNAME);

struct EASEents_sys {
struct eInstHdr hdr;
struct ENTITYTYPE* ENTITYTYPE;
struct SCHEMA* SCHEMA;
struct ATTRDEF* ATTRDEF;
struct FIXUP* FIXUP;
struct ERRORREC* ERRORREC;
struct FIXUP* F_ATTRFIXUPS;
struct FIXUP* F_SETOWNRFIXUPS;
struct FIXUP* F_SETMMBRFIXUPS;
struct SETDEF* F_SETDEFS;
struct SCHEMA* F_SCHEMAS;
struct ENTITYTYPE* F_SYSTEMS;
struct ERRORREC* F_ERRORRECS;
struct ERRORREC* L_ERRORRECS;
struct ENTITYTYPE** E_BUILTINS;
};
extern EASEents_sys* EASEents;
void EASEents_init();

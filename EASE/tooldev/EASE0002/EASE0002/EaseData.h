// Core data type declarations for EASE		Alasdar, Feb-May 2016

//Entity Type Definitions

#pragma once

struct EASdbSchema {						// schema definition
		TCHAR* dbName;
		int dbID;
		bool isImported;
		struct entityTypeDef* theSystem;
		struct entityTypeDef* f_eTypes;		// set of types defined in this schema
		struct substdef* f_substs;
		struct setDef* f_setDefs;
		int lastTypeID;
		BOOL noGen;
		BOOL noHdr;
		TCHAR* genname;
		TCHAR* schemaFilename;
		BOOL isHidden;
		BOOL isSystemDefined;
		EASdbSchema* s_dbSchemas;
};

struct entityTypeDef {						// entity type definition
		TCHAR* entityTypeName;				// declared name
		int entityTypeID;
		entityTypeDef* s_entityTypes;
		struct defRef* f_attrDefs;			// set(list) of attribute definition references
		struct entTypeRef* f_entTypeRefs;	// Compound entity 'component entities' * not yet implemented *
		struct defRef* f_owndSetRefs;		// set(list) of refs to sets this entity type owns
		struct defRef* f_mmbrSetRefs;		// set(list) of refs to sets this entity type may belong to
		struct defRef* f_sysAttrs;			// for THE SYSTEM - 'scripted' (system-generated) attributes
		EASdbSchema* dbRef;
		bool isSystemDefined;			// non-editable, system primitive(?)
		bool isSetType;					// a set-type entity
		bool isHidden;					// internally-used
		bool isProc;
		TCHAR* procBody;
		TCHAR* fileName;				// filename for procedural code (option - not implemented)
		struct setDefRef* f_setAttrRefs;	// set type definition keeps track of all attributes defined as that type
		int formatCode;					// used to select edit control type
		int valueSize;					// required storage allocation for value (not used...)
		TCHAR* targetName;				// type name in target language
		int lastInstanceID;				// last instance ID allocated
		int version;
		TCHAR* entDescription;
		bool isSys;						// a 'SYSTEM' entity
		bool isPersistent;
		bool deleted;
};

enum refType {ref_att, ref_set, ref_ent};

struct defRef {							// reference to attrDef/setDef/??
	union {
		struct attrDef* attRef;
		struct setDef* setRef;
		struct entityTypeDef* entRef;	// used for SYSTEM 'scripted' attributes
	};
	refType drType;
	TCHAR* refName;
	int dbId;
	defRef* s_defRefs;
};

struct entTypeRef {						// components of a compound entity / members of a set
	entityTypeDef* entType;
	TCHAR* entTypeName;
	int entDbId;
	entTypeRef* s_entTypeRefs;
};

struct attrDef {						// attribute specification
	TCHAR* attrDefName;					// attribute declared name
	entityTypeDef* attrDefType;			// reference to defining entity type
	bool embedded;						// if embedded as field(s); else a this attribute is a reference
	bool scripted;						// system-generated attribute
	bool param;
	bool yielded;
	bool returns;
	int subscripts;
	entityTypeDef* ownerType;			// owning entity
	TCHAR* attrDescription;
	attrDef* s_attrDefs;
};

struct fixup {							// for forward reference resolution by name + schema
	TCHAR* fixRefName;
	attrDef* attRef;
	setDefRef* sDefRef;
	defRef* fixRef;
	entityTypeDef* entRef;
	int dbId;
	fixup* s_fixups;
};

struct setDefRef {				// set membership reference (orig. by name) to SetDef
	struct setDef* dSet;
	TCHAR* dSetName;
	int dbId;
	setDefRef* s_setDefRef;
};

struct setDef {					// Set definition
	TCHAR* setName;
	int dbId;
	bool isPersistent;
	int setDiscipline;
	struct rankAttr* f_rankAttrs;
	entTypeRef* f_setMmbrs;
	TCHAR* setDescription;
	setDef* s_setDefs;
	bool deleted;
};

struct rankAttr {
	TCHAR* rattName;
	bool seqLow;	// default rank by high value
	rankAttr* s_rankAttrs;
};

struct substdef {		// text substitution definition (define to mean) - * no GUI yet!
	TCHAR* term;
	TCHAR* substxt;
	struct substdef* s_substs;
};

extern CString projectDir;
extern BOOL DBloaded;
extern EASdbSchema* f_dbSchemas;					// first of loaded schemas
extern entityTypeDef* f_systems;

void ReadEASEschema(CString path, CString fname, bool isImport);
void FixUpEASEschemas();
void WriteEASEschema(EASdbSchema* dbSchema);

entityTypeDef* FindETypeByName(LPCTSTR eTypeName, int dbId); 
entityTypeDef* FindETypeByTypeID(int eType, int dbId);
setDef* FindSetDefByName(LPCTSTR Name, int dbId);

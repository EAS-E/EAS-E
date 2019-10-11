#include "stdafx.h"
#include "EaseData.h"
#include "malloc.h"
#include "stdio.h"
#include "stdio.h"
#include "Markup.h"
#include "Strsafe.h"


entityTypeDef* f_systems;
//entityInstance* SYSTEM = NULL;
EASdbSchema* f_dbSchemas = NULL;
void ScriptSysAttributes(EASdbSchema* dbSchema);

CString projectDir;
CFile dbFile;						// the instance database file  - not xml definitions...
CFile dbText;
BOOL DBloaded;
fixup* f_attrFixups = NULL;
fixup* f_setFixups = NULL;

TCHAR modenames[10][8] = { _T("void   "),_T("int    "), _T("double "), _T("Etxt*  "), _T("void*  "), _T("void*  "), _T("void*  "), _T("void*  "), _T("void*  "), _T("void*  "), };


void ReadEASEschema(CString path, CString fname, bool isImport) {		// Initialise entity types

	CFile file;
	CString filename;
	CString csText;
	CMarkup xml;
	EASdbSchema* dbSchema;
	EASdbSchema* db;
	entityTypeDef*  eType;
	entityTypeDef* lastEType;
	attrDef* dAttr;
	attrDef* ldAttr;
	setDef* dSet;
	rankAttr* rankAtt;
	rankAttr* lrankAtt;
	fixup* fix;
	defRef* dRef;
	defRef* nRef;
	CString temp;
	int len;
	TCHAR* zero = 0;
	HRESULT res;
	substdef* aSubst;

	filename = path;
	if (fname != "")
		filename = path + fname + _T(".xml");

	dbSchema = f_dbSchemas;
	while (dbSchema) {
		if (_tcscmp(dbSchema->dbName, filename) == 0) {
			AfxMessageBox(_T("Already opened " + filename), MB_OK);
			return;
		}
		dbSchema = dbSchema->s_dbSchemas;
	}

	if (!file.Open((LPCTSTR)filename, CFile::modeRead)) {
		AfxMessageBox(_T("Cannot open " + filename), MB_OK);
		return;
	}

	int nFileLen = (int)file.GetLength();
	unsigned char* pBuffer = new unsigned char[nFileLen + 2];
	nFileLen = file.Read(pBuffer, nFileLen);
	file.Close();
	pBuffer[nFileLen] = '\0';
	pBuffer[nFileLen + 1] = '\0';

	// Windows Unicode file is detected if starts with FEFF
	if (pBuffer[0] == 0xff && pBuffer[1] == 0xfe)
	{
		// Contains byte order mark, so assume wide char content
		// non _UNICODE builds should perform UCS-2 (wide char) to UTF-8 conversion here
		csText = (LPCWSTR)(&pBuffer[2]);
		//		csNotes += _T("File starts with hex FFFE, assumed to be wide char format. ");
	}
	else
	{
		// _UNICODE builds should perform UTF-8 to UCS-2 (wide char) conversion here
		csText = (LPCSTR)pBuffer;
	}
	delete[] pBuffer;

	bool bResult = xml.SetDoc(csText);
	if (!xml.FindElem(_T("EASE-Database"))) {		// root - Database
		AfxMessageBox(_T("Not an EAS schema file"), MB_OK);
		return;
	}
	dbSchema = (EASdbSchema*)calloc(1, sizeof(EASdbSchema));
	if (f_dbSchemas == NULL)
		f_dbSchemas = dbSchema;
	else {
		db = f_dbSchemas;
		while (db->s_dbSchemas)
			db = db->s_dbSchemas;
		db->s_dbSchemas = dbSchema;
	}
	len = filename.GetLength();
	dbSchema->schemaFilename = new TCHAR[len + 1];
	res = StringCchCopy(dbSchema->schemaFilename, len + 1, (LPCTSTR)filename);
	len = fname.GetLength();
	dbSchema->dbName = new TCHAR[len + 1];
	res = StringCchCopy(dbSchema->dbName, len + 1, (LPCTSTR)fname);
	dbSchema->isImported = isImport;
	temp = xml.GetAttrib(_T("ID"));
	dbSchema->dbID = _tcstol(temp, &zero, 10);
	if (xml.GetAttrib("noGen") == "Y")
		dbSchema->noGen = TRUE;
	if (xml.GetAttrib("noHdr") == "Y")
		dbSchema->noHdr = TRUE;
	temp = xml.GetAttrib(_T("genname"));
	if (temp) {
		len = temp.GetLength();
		dbSchema->genname = new TCHAR[len + 1];
	}
	res = StringCchCopy(dbSchema->genname, len + 1, (LPCTSTR)temp);
	if (xml.GetAttrib("isSystemDefined") == "Y") 
		dbSchema->isSystemDefined = TRUE;
	if (xml.GetAttrib("isHidden") == "Y")
		dbSchema->isHidden = TRUE;

	xml.IntoElem();		// down 1 level
	xml.FindElem(_T("ENTITIES"));
	xml.IntoElem();
	lastEType = NULL;

	lastEType = dbSchema->f_eTypes;
	if (lastEType)
		while (lastEType->s_entityTypes)
			lastEType = lastEType->s_entityTypes;

	while (xml.FindElem(_T("entityType"))) {
		eType = (entityTypeDef*)calloc(1, sizeof(entityTypeDef));		// create new type definition
		eType->dbRef = dbSchema;
		if (dbSchema->f_eTypes == NULL)
			dbSchema->f_eTypes = eType;

		if (lastEType == NULL)
			dbSchema->f_eTypes = eType;	// remember the first one
		else
			lastEType->s_entityTypes = eType;
		lastEType = eType;
		eType->s_entityTypes = NULL;
		eType->entityTypeID = _tcstol(xml.GetAttrib(_T("ID")), &zero, 10);
		if (eType->entityTypeID > dbSchema->lastTypeID)
			dbSchema->lastTypeID = eType->entityTypeID;
		if (xml.GetAttrib("isProcedure") == "Y")
			eType->isProc = TRUE;
		if (xml.GetAttrib("isSystemDefined") == "Y") {
			eType->isSystemDefined = TRUE;									// a built-in type ?
			if (xml.GetAttrib("isSetType") == "Y")
				eType->isSetType = TRUE;
			if (xml.GetAttrib("isHidden") == "Y")
				eType->isHidden = TRUE;
			temp = xml.GetAttrib("valueSize");
			if (temp != "")
				eType->valueSize = _tcstol(temp, &zero, 10);
			temp = xml.GetAttrib("formatCode");
			if (temp != "")
				eType->formatCode = _tcstol(temp, &zero, 10);
			temp = xml.GetAttrib("targetName");
			if (temp != "") {
				len = temp.GetLength();
				eType->targetName = new TCHAR[len + 1];
				res = StringCchCopy(eType->targetName, len + 1, (LPCTSTR)temp);
			}
		}
		if (xml.GetAttrib("isPersistent") == "Y")
			eType->isPersistent = TRUE;

		xml.IntoElem();
		xml.FindElem(_T("entityTypeName"));
		temp = xml.GetData();
		len = temp.GetLength();
		eType->entityTypeName = new TCHAR[len + 1];
		res = StringCchCopy(eType->entityTypeName, len + 1, (LPCTSTR)temp);
		if (xml.FindElem(_T("Descr"))) {
			temp = xml.GetData();
			len = temp.GetLength();
			eType->entDescription = new TCHAR[len + 1];
			res = StringCchCopy(eType->entDescription, len + 1, (LPCTSTR)temp);
		}
		if (xml.FindElem(_T("Body"))) {
			temp = xml.GetData();
			len = temp.GetLength();
			eType->procBody = new TCHAR[len + 1];
			res = StringCchCopy(eType->procBody, len + 1, (LPCTSTR)temp);
		}
		eType->f_attrDefs = NULL;
		ldAttr = NULL;
		while (xml.FindElem(_T("attrDef"))) {
			dAttr = (attrDef*)calloc(1, sizeof(attrDef));
			nRef = (defRef*)calloc(1, sizeof(defRef));
			nRef->attRef = dAttr;
			nRef->drType = ref_att;
			dRef = eType->f_attrDefs;
			if (dRef) {
				while (dRef->s_defRefs)
					dRef = dRef->s_defRefs;
				dRef->s_defRefs = nRef;
			}
			else
				eType->f_attrDefs = nRef;

			dAttr->ownerType = eType;
			if (xml.GetAttrib(_T("embedded")) != "")
				dAttr->embedded = TRUE;
			if (xml.GetAttrib(_T("scripted")) != "")
				dAttr->scripted = TRUE;
			if (xml.GetAttrib(_T("parameter")) != "")
				dAttr->param = TRUE;
			if (xml.GetAttrib(_T("yielded")) != "")
				dAttr->yielded = TRUE;
			if (xml.GetAttrib(_T("returntype")) != "")
				dAttr->returns = TRUE;
			temp = xml.GetAttrib("subscripts");
			if (temp != "")
				dAttr->subscripts = _tcstol(temp, &zero, 10);

			if (xml.FindChildElem(_T("attrName"))) {
				temp = xml.GetChildData();
				len = temp.GetLength();
				dAttr->attrDefName = new TCHAR[len + 1];
				res = StringCchCopy(dAttr->attrDefName, len + 1, (LPCTSTR)temp);
			}
			xml.ResetChildPos();
			if (xml.FindChildElem(_T("attrTypeName"))) {
				temp = xml.GetChildData();
				fix = (fixup*)calloc(1, sizeof(fixup));
				len = temp.GetLength();
				fix->fixRefName = new TCHAR[len + 1];
				res = StringCchCopy(fix->fixRefName, len + 1, (LPCTSTR)temp);
				fix->attRef = dAttr;
				fix->s_fixups = f_attrFixups;
				f_attrFixups = fix;
			}
			if (xml.FindChildElem(_T("Descr"))) {
				temp = xml.GetChildData();
				len = temp.GetLength();
				dAttr->attrDescription = new TCHAR[len + 1];
				res = StringCchCopy(dAttr->attrDescription, len + 1, (LPCTSTR)temp);
			}
		}

		while (xml.FindElem(_T("setOwnDef"))) {					// set ownership information for this entity
			dRef = (defRef*)calloc(1, sizeof(defRef));
			dRef->s_defRefs = eType->f_owndSetRefs;
			eType->f_owndSetRefs = dRef;
			dRef->drType = ref_set;
			temp = xml.GetAttrib("dbId");
			dRef->dbId = _tcstol(temp, &zero, 10);
			temp = xml.GetData();
			len = temp.GetLength();
			dRef->refName = new TCHAR[len + 1];
			res = StringCchCopy(dRef->refName, len + 1, (LPCTSTR)temp);

			fix = (fixup*)calloc(1, sizeof(fixup));
			fix->fixRef = dRef;
			fix->s_fixups = f_setFixups;
			f_setFixups = fix;
		}

		while (xml.FindElem(_T("setBelongDef"))) {				// set membership information  for this entity 
			dRef = (defRef*)calloc(1, sizeof(defRef));
			dRef->s_defRefs = eType->f_mmbrSetRefs;
			eType->f_mmbrSetRefs = dRef;
			dRef->drType = ref_set;
			temp = xml.GetAttrib("dbId");
			dRef->dbId = _tcstol(temp, &zero, 10);
			temp = xml.GetData();
			len = temp.GetLength();
			dRef->refName = new TCHAR[len + 1];
			res = StringCchCopy(dRef->refName, len + 1, (LPCTSTR)temp);

			fix = (fixup*)calloc(1, sizeof(fixup));
			fix->fixRef = dRef;
			fix->s_fixups = f_setFixups;
			fix->entRef = eType;
			f_setFixups = fix;
		}

		xml.OutOfElem();
	}
	xml.OutOfElem();

	if (xml.FindElem(_T("SETS"))) {

		xml.IntoElem();
		while (xml.FindElem(_T("setDef"))) {

			dSet = (setDef*)calloc(1, sizeof(setDef));
			dSet->s_setDefs = dbSchema->f_setDefs;
			dbSchema->f_setDefs = dSet;
			temp = xml.GetAttrib(_T("discipline"));
			if (temp == "F")
				dSet->setDiscipline = 1;					// FIFO
			if (temp == "L")
				dSet->setDiscipline = 2;					// LIFO
			if (xml.GetAttrib(_T("isPersistent")) == "Y")
				dSet->isPersistent = TRUE;
			if (xml.FindChildElem(_T("setName"))) {
				temp = xml.GetChildData();
				len = temp.GetLength();
				dSet->setName = new TCHAR[len + 1];
				StringCchCopy(dSet->setName, len + 1, (LPCTSTR)temp);
			}
			if (dSet->setDiscipline == 0) {
				while (xml.FindChildElem(_T("rankAttr"))) {
					xml.IntoElem();
					rankAtt = (rankAttr*)calloc(1, sizeof(rankAttr));
					temp = xml.GetAttrib("low");
					if (xml.GetAttrib("low") == "Y")
						rankAtt->seqLow = true;
					temp = xml.GetData();
					len = temp.GetLength();
					rankAtt->rattName = new TCHAR[len + 1];
					StringCchCopy(rankAtt->rattName, len + 1, (LPCTSTR)temp);
					if (dSet->f_rankAttrs == NULL)
						dSet->f_rankAttrs = rankAtt;
					else {
						lrankAtt = dSet->f_rankAttrs;
						while (lrankAtt->s_rankAttrs != NULL)
							lrankAtt = lrankAtt->s_rankAttrs;
						lrankAtt->s_rankAttrs = rankAtt;
					}
					xml.OutOfElem();
				}
			}
			xml.ResetChildPos();
			if (xml.FindChildElem(_T("Descr"))) {
				temp = xml.GetChildData();
				len = temp.GetLength();
				dSet->setDescription = new TCHAR[len + 1];
				res = StringCchCopy(dSet->setDescription, len + 1, (LPCTSTR)temp);
			}
		}
		xml.OutOfElem();		// SETS
	}


	if (xml.FindElem(_T("SYSTEM"))) {
		eType = (entityTypeDef*)calloc(1, sizeof(entityTypeDef));		// create new type definition
		eType->dbRef = dbSchema;
		dbSchema->theSystem = eType;
		eType->isSys = TRUE;

		xml.IntoElem();
		if (xml.FindElem(_T("entityType"))) {
			eType->entityTypeID = _tcstol(xml.GetAttrib(_T("ID")), &zero, 10);
			// none of the following are applicable to system-type entity
			//if (xml.GetAttrib("isSystemDefined") == "Y") 
			//	eType->isSystemDefined = TRUE;							// a "primitive"
			//if (xml.GetAttrib("isSetType") == "Y") 
			//	eType->isSetType = TRUE;
			//if (xml.GetAttrib("isHidden") == "Y")
			//	eType->isHidden = TRUE;
			//temp = xml.GetAttrib("valueSize");
			//if (temp != "")
			//	eType->valueSize = _tcstol(temp, &zero, 10);
			//temp = xml.GetAttrib("formatCode");
			//if (temp != "")
			//	eType->formatCode = _tcstol(temp, &zero, 10);

			xml.IntoElem();
			xml.FindElem(_T("entityTypeName"));
			temp = xml.GetData();
			len = temp.GetLength();
			eType->entityTypeName = new TCHAR[len + 1];
			res = StringCchCopy(eType->entityTypeName, len + 1, (LPCTSTR)temp);

			if (xml.FindElem(_T("Descr"))) {
				temp = xml.GetData();
				len = temp.GetLength();
				eType->entDescription = new TCHAR[len + 1];
				res = StringCchCopy(eType->entDescription, len + 1, (LPCTSTR)temp);
			}

			eType->f_attrDefs = NULL;
			while (xml.FindElem(_T("attrDef"))) {
				if (xml.GetAttrib(_T("scripted")) == "") {
					dAttr = (attrDef*)calloc(1, sizeof(attrDef));
					nRef = (defRef*)calloc(1, sizeof(defRef));
					nRef->attRef = dAttr;
					nRef->drType = ref_att;
					dRef = eType->f_attrDefs;
					if (dRef) {
						while (dRef->s_defRefs)
							dRef = dRef->s_defRefs;
						dRef->s_defRefs = nRef;
					}
					else
						eType->f_attrDefs = nRef;

					if (xml.GetAttrib(_T("embedded")) != "")
						dAttr->embedded = TRUE;
					temp = xml.GetAttrib("subscripts");
					if (temp != "")
						dAttr->subscripts = _tcstol(temp, &zero, 10);

					if (xml.FindChildElem(_T("attrName"))) {
						temp = xml.GetChildData();
						len = temp.GetLength();
						dAttr->attrDefName = new TCHAR[len + 1];
						res = StringCchCopy(dAttr->attrDefName, len + 1, (LPCTSTR)temp);
					}
					xml.ResetChildPos();
					if (xml.FindChildElem(_T("attrTypeName"))) {
						temp = xml.GetChildData();
						fix = (fixup*)calloc(1, sizeof(fixup));
						len = temp.GetLength();
						fix->fixRefName = new TCHAR[len + 1];
						res = StringCchCopy(fix->fixRefName, len + 1, (LPCTSTR)temp);
						fix->attRef = dAttr;
						fix->s_fixups = f_attrFixups;
						f_attrFixups = fix;
					}
					if (xml.FindChildElem(_T("Descr"))) {
						temp = xml.GetChildData();
						len = temp.GetLength();
						dAttr->attrDescription = new TCHAR[len + 1];
						res = StringCchCopy(dAttr->attrDescription, len + 1, (LPCTSTR)temp);
					}
				}
			}

			while (xml.FindElem(_T("setOwnDef"))) {					// set ownership information for this entity
				dRef = (defRef*)calloc(1, sizeof(defRef));
				dRef->s_defRefs = eType->f_owndSetRefs;
				eType->f_owndSetRefs = dRef;
				dRef->drType = ref_set;
				temp = xml.GetAttrib("dbId");
				dRef->dbId = _tcstol(temp, &zero, 10);
				temp = xml.GetData();
				len = temp.GetLength();
				dRef->refName = new TCHAR[len + 1];
				res = StringCchCopy(dRef->refName, len + 1, (LPCTSTR)temp);

				fix = (fixup*)calloc(1, sizeof(fixup));
				fix->fixRef = dRef;
				fix->s_fixups = f_setFixups;
				f_setFixups = fix;
			}

			//while (xml.FindElem(_T("setBelongDef"))) {					// set membership information for this entity
			//	dRef = (defRef*)calloc(1, sizeof(defRef));
			//	dRef->s_defRefs = eType->f_mmbrSetRefs;
			//	eType->f_mmbrSetRefs = dRef;
			//	dRef->drType = ref_set;
			//	temp = xml.GetAttrib("dbId");
			//	dRef->dbId = _tcstol(temp, &zero, 10);
			//	temp = xml.GetData();
			//	len = temp.GetLength();
			//	dRef->refName = new TCHAR[len + 1];
			//	res = StringCchCopy(dRef->refName, len + 1, (LPCTSTR)temp);

			//	fix = (fixup*)calloc(1, sizeof(fixup));
			//	fix->fixRef = dRef;
			//	fix->s_fixups = aCombo;
			//	aCombo = fix;
			//}

		}
/*		else {
			eType = (entityTypeDef*)calloc(1, sizeof(entityTypeDef));		// create new type definition ???
			eType->dbRef = dbSchema;
			dbSchema->theSystem = eType;
		}
*/
	}
	xml.OutOfElem();		// entityType
	xml.OutOfElem();		// SYSTEM

	if (!dbSchema->isSystemDefined)
		ScriptSysAttributes(dbSchema);		// generate a 'global' system attribute for each entity type

	if (xml.FindElem(_T("SUBST"))) {
		xml.IntoElem();
		while (xml.FindElem(_T("d2m"))) {
			temp = xml.GetAttrib("term");
			aSubst = (substdef*)calloc(1, sizeof(substdef));
			len = temp.GetLength();
			aSubst->term = new TCHAR[len + 1];
			StringCchCopy(aSubst->term, len + 1, (LPCTSTR)temp);
			xml.FindChildElem(_T("substxt"));
			temp = xml.GetChildData();
			len = temp.GetLength();
			aSubst->substxt = new TCHAR[len + 1];
			StringCchCopy(aSubst->substxt, len + 1, (LPCTSTR)temp);
			aSubst->s_substs = dbSchema->f_substs;
			dbSchema->f_substs = aSubst;
		}
		xml.OutOfElem();
	}
}
void ScriptSysAttributes(EASdbSchema* dbSchema) {

	entityTypeDef* aSys;
	defRef* dRef;
	defRef* nRef;
	entityTypeDef* eType;

	aSys = dbSchema->theSystem;
	eType = dbSchema->f_eTypes;
	while (eType) {
		if (!eType->isProc) {
			nRef = (defRef*)calloc(1, sizeof(defRef));
			nRef->entRef = eType;
			nRef->drType = ref_ent;
			dRef = aSys->f_sysAttrs;
			if (dRef) {
				while (dRef->s_defRefs)
					dRef = dRef->s_defRefs;
				dRef->s_defRefs = nRef;
			}
			else
				aSys->f_sysAttrs = nRef;
		}
		eType = eType->s_entityTypes;
	}
}

void FixUpEASEschemas() {

	fixup* fix;
	attrDef* dAttr;
	defRef* dRef;
	fixup* dead;
	entTypeRef* eRef;


	fix = f_attrFixups;				// from attribute definitions, resolve name references to entity types
	while (fix) {
		dAttr = fix->attRef;
		dAttr->attrDefType = FindETypeByName((LPCTSTR)fix->fixRefName, fix->dbId);
		dead = fix;
		fix = fix->s_fixups;
		delete dead->fixRefName;
		delete dead;
	}
	f_attrFixups = NULL;

	fix = f_setFixups;
	while (fix) {
		dRef = fix->fixRef;
		if (dRef)
			dRef->setRef = FindSetDefByName((LPCTSTR)dRef->refName, dRef->dbId);
		if (fix->entRef) {
			eRef = (entTypeRef*)calloc(1, sizeof(entTypeRef));
			eRef->entType = fix->entRef;
			eRef->s_entTypeRefs = dRef->setRef->f_setMmbrs;
			dRef->setRef->f_setMmbrs = eRef;
		}
		dead = fix;
		fix = fix->s_fixups;
		delete dead;
	}
	f_setFixups = NULL;
}


entityTypeDef* FindETypeByName(LPCTSTR eTypeName, int dbId) {

	entityTypeDef* eType;
	entityTypeDef* found = NULL;
	EASdbSchema* dbSchema;

	// matching name with matching dbId takes precedence, but base types are in dbId == 0 (is this wise?)
	dbSchema = f_dbSchemas;
	while (dbSchema) {
		eType = dbSchema->f_eTypes;
		while (eType) {
			if (_tcscmp(eType->entityTypeName, eTypeName) == 0) {
				found = eType;
				if (dbSchema->dbID == dbId) 
					return found;		// look no further
			}
			eType = eType->s_entityTypes;
		}
		dbSchema = dbSchema->s_dbSchemas;
	}
	return found;
}

setDef* FindSetDefByName(LPCTSTR attrName, int dbId) {

	setDef* sDef;
	EASdbSchema* dbSchema;

	dbSchema = f_dbSchemas;
	while (dbSchema) {
		sDef = dbSchema->f_setDefs;
		while (sDef) {
			if (_tcscmp(sDef->setName, attrName) == 0)
				return sDef;
			sDef = sDef->s_setDefs;
		}
		dbSchema = dbSchema->s_dbSchemas;
	}
	return NULL;
}


entityTypeDef* FindETypeByTypeID(int eTypeId, int dbId) {

	entityTypeDef* eType;
	EASdbSchema* dbSchema;

	dbSchema = f_dbSchemas;
	while (dbSchema) {
		if (dbSchema->dbID == dbId) {
			eType = dbSchema->f_eTypes;
			while (eType) {
				if (eType->entityTypeID == eTypeId)
					return eType;
				eType = eType->s_entityTypes;
			}
		}
		dbSchema = dbSchema->s_dbSchemas;
	}
	return NULL;
}


void WriteEASEschema(EASdbSchema* dbSchema) {

	CFile file;
	CString csText;
	CMarkup xml;
	entityTypeDef*  eType;
	setDef* sDef;
	attrDef* dAttr;
	defRef* dRef;
	rankAttr* rAtt;
	CString temp;
	int len;
	TCHAR numberTxt[24] = _T("");
	TCHAR bak[4] = _T("bak");
	substdef* aSubst;
	BOOL res;

	temp = dbSchema->schemaFilename;
	len = temp.GetLength();
	temp.SetAt(len - 3, bak[0]);
	temp.SetAt(len - 2, bak[1]);
	temp.SetAt(len - 1, bak[2]);

	res = file.Open(temp, CFile::modeRead);
	if (res) {
		file.Close();
		CFile::Remove(temp);
	}

	res = (file.Open(dbSchema->schemaFilename, CFile::modeWrite));
	if (res) {
		file.Close();
		CFile::Rename(dbSchema->schemaFilename, temp);
	}

	if (!file.Open(dbSchema->schemaFilename, CFile::modeCreate | CFile::modeWrite)) {
		AfxMessageBox(_T("Cannot open file"), MB_OK);
		return;
	}

	xml.SetDoc("<?xml version=\"1.0\"?>\r\n");
	xml.AddElem(_T("EASE-Database"));
	sprintf(numberTxt, "%d", dbSchema->dbID);
	xml.SetAttrib(_T("ID"), numberTxt);
	if (dbSchema->genname)
		xml.SetAttrib(_T("genname"), dbSchema->genname);
	else
		xml.SetAttrib(_T("genname"), dbSchema->dbName);
	xml.IntoElem();
	eType = dbSchema->f_eTypes;
	if (eType) {
		xml.AddElem(_T("ENTITIES"));
		xml.IntoElem();
		while (eType) {
			if (!eType->isSystemDefined & !eType->deleted) {
				xml.AddElem(_T("entityType"));
				sprintf(numberTxt, "%d", eType->entityTypeID);
				xml.SetAttrib(_T("ID"), numberTxt);
				if (eType->isProc)	xml.SetAttrib(_T("isProcedure"), _T("Y"));
				if (eType->isSystemDefined)	xml.SetAttrib(_T("isSystemDefined"), _T("Y"));
				if (eType->isHidden)	xml.SetAttrib(_T("isHidden"), _T("Y"));
				if (eType->isPersistent)	xml.SetAttrib(_T("isPersistent"), _T("Y"));

				xml.IntoElem();						// into Entity Type
				xml.AddElem("entityTypeName", eType->entityTypeName);

				if (eType->entDescription != NULL)
					xml.AddElem(_T("Descr"), eType->entDescription, 1);		// compiler does not recognize MNF_WITHCDATA
				if (eType->procBody != NULL)
					xml.AddElem(_T("Body"), eType->procBody, 1);

				dRef = eType->f_attrDefs;
				while (dRef) {
					dAttr = dRef->attRef;
					if (!dAttr->attrDefType->deleted) {
						xml.AddElem(_T("attrDef"));
						if (dAttr->embedded)
							xml.SetAttrib(_T("embedded"), _T("Y"));
						if (dAttr->scripted)
							xml.SetAttrib(_T("scripted"), _T("Y"));
						if (dAttr->param)
							xml.SetAttrib(_T("parameter"), _T("Y"));
						if (dAttr->yielded)
							xml.SetAttrib(_T("yielded"), _T("Y"));
						if (dAttr->returns)
							xml.SetAttrib(_T("returntype"), _T("Y"));
						if (dAttr->subscripts > 0) {
							sprintf(numberTxt, "%d", dAttr->subscripts);
							xml.SetAttrib(_T("subscripts"), numberTxt);
						}
						xml.IntoElem();
						xml.AddElem("attrName", dAttr->attrDefName);
						xml.AddElem("attrTypeName", dAttr->attrDefType->entityTypeName);
						if (dAttr->attrDescription != NULL)
							xml.AddElem(_T("Descr"), dAttr->attrDescription, 1);
						xml.OutOfElem();
					}
					dRef = dRef->s_defRefs;
				}

				dRef = eType->f_owndSetRefs;		// any set ownerships ?
				while (dRef) {
					if (!dRef->setRef->deleted) {
						xml.AddElem("setOwnDef", dRef->setRef->setName);
						sprintf(numberTxt, "%d", dRef->dbId);
						xml.SetAttrib(_T("dbId"), numberTxt);
					}
					dRef = dRef->s_defRefs;
				}
				dRef = eType->f_mmbrSetRefs;		// any set memberships ?
				while (dRef) {
					if (!dRef->setRef->deleted) {
						xml.AddElem("setBelongDef", dRef->setRef->setName);
						sprintf(numberTxt, "%d", dRef->dbId);
						xml.SetAttrib(_T("dbId"), numberTxt);
					}
					dRef = dRef->s_defRefs;
				}

				xml.OutOfElem();	// Entity Type
			}
			else
				eType->isSystemDefined = FALSE;	// how could this be ?
			eType = eType->s_entityTypes;
		}
		xml.OutOfElem();	//ENTITIES
	}

	sDef = dbSchema->f_setDefs;
	if (sDef) {
		xml.AddElem(_T("SETS"));
		xml.IntoElem();
		while (sDef) {
			if (!sDef->deleted) {

				xml.AddElem(_T("setDef"));
				if (sDef->setDiscipline == 0)
					xml.SetAttrib(_T("discipline"), "R");
				if (sDef->setDiscipline == 1)
					xml.SetAttrib(_T("discipline"), "F");
				if (sDef->setDiscipline == 2)
					xml.SetAttrib(_T("discipline"), "L");
				if (sDef->isPersistent)
					xml.SetAttrib(_T("isPersistent"), "Y");
				xml.IntoElem();
				xml.AddElem(_T("setName"), sDef->setName);
				if (sDef->setDiscipline == 0) {
					rAtt = sDef->f_rankAttrs;
					while (rAtt) {
						xml.AddElem(_T("rankAttr"), rAtt->rattName);
						if (rAtt->seqLow)
							xml.SetAttrib(_T("low"), "Y");
						rAtt = rAtt->s_rankAttrs;
					}
				}
				if (sDef->setDescription != NULL)
					xml.AddElem(_T("Descr"), sDef->setDescription, 1);
				xml.OutOfElem();
			}
			sDef = sDef->s_setDefs;
		}
		xml.OutOfElem();	// SETS
	}

	eType = dbSchema->theSystem;

	xml.AddElem(_T("SYSTEM"));			// even an empty new project has a SYSTEM
	xml.IntoElem();
	xml.AddElem(_T("entityType"));
	sprintf(numberTxt, "%d", 0);
	xml.SetAttrib(_T("ID"), numberTxt);

	xml.IntoElem();						// into Entity Type
	xml.AddElem("entityTypeName", _T("SYSTEM"));

	eType = dbSchema->theSystem;
	if (eType->entDescription != NULL)
		xml.AddElem(_T("Descr"), eType->entDescription, 1);
	dRef = eType->f_attrDefs;
	while (dRef) {
		dAttr = dRef->attRef;
		if (!dAttr->attrDefType->deleted) {
			xml.AddElem(_T("attrDef"));
			if (dAttr->embedded)	xml.SetAttrib(_T("embedded"), _T("Y"));
			if (dAttr->subscripts > 0) {
				sprintf(numberTxt, "%d", dAttr->subscripts);
				xml.SetAttrib(_T("subscripts"), numberTxt);
			}
			xml.IntoElem();
			xml.AddElem("attrName", dAttr->attrDefName);
			xml.AddElem("attrTypeName", dAttr->attrDefType->entityTypeName);
			if (dAttr->attrDescription != NULL)
				xml.AddElem(_T("Descr"), dAttr->attrDescription, 1);
			xml.OutOfElem();
		}
		dRef = dRef->s_defRefs;
	}

	dRef = eType->f_sysAttrs;	// 'scripted' global variable for each entity type...
	while (dRef) {
		if (!dRef->entRef->deleted) {
			xml.AddElem(_T("attrDef"));
			xml.SetAttrib(_T("scripted"), _T("Y"));
			xml.IntoElem();
			xml.AddElem("attrName", dRef->entRef->entityTypeName);
			xml.AddElem("attrTypeName", dRef->entRef->entityTypeName);
			xml.OutOfElem();
		}
		dRef = dRef->s_defRefs;
	}

	dRef = eType->f_owndSetRefs;		// any set ownerships ?
	while (dRef) {
		if (!dRef->setRef->deleted) {
			xml.AddElem("setOwnDef", dRef->setRef->setName);
			sprintf(numberTxt, "%d", dRef->dbId);
			xml.SetAttrib(_T("dbId"), numberTxt);
		}
		dRef = dRef->s_defRefs;
	}

	xml.OutOfElem();	// Entity Type
	xml.OutOfElem();	// SYSTEM


	aSubst = dbSchema->f_substs;
	if (aSubst) {
		xml.AddElem(_T("SUBST"));
		xml.IntoElem();
		while (aSubst) {
			xml.AddElem(_T("d2m"));
			xml.SetAttrib(_T("term"), aSubst->term);
			xml.IntoElem();
			xml.AddElem("substxt", aSubst->substxt, 1);
			xml.OutOfElem();
			aSubst = aSubst->s_substs;
		}
		xml.OutOfElem();
	}

	xml.OutOfElem();	// Database

	temp = xml.GetDoc();
	len = temp.GetLength();
	TCHAR* buf = temp.GetBuffer();

	file.Write(buf, len);
	file.Flush();
	file.Close();
}

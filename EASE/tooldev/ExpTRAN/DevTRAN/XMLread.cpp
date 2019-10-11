#include "stdafx.h"
#include "Markup.h"
#include "easlib.h"



CFile file;
CString csText;
CMarkup xml;
int len;
TCHAR* zero = 0;


int XMLOPEN_F(Etxt* schema) {
	CString filename;

	if (schema) {
		schema->refCount++;
		filename = (LPCTSTR(schema->tValue));
	}

	if (!file.Open((LPCTSTR)filename, CFile::modeRead)) {
		AfxMessageBox(_T("Cannot open " + filename), MB_OK);
		return 0;
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
	E_TXTDEL_R(schema);

	bool bResult = xml.SetDoc(csText);
	if (bResult)
		return 1;
	return 0;
}

int XMLFINDELEM_F(Etxt* elem) {
	if (elem) {
		elem->refCount++;
		bool bResult = (xml.FindElem(elem->tValue));
		E_TXTDEL_R(elem);
		if (bResult)
			return 1;
	}
	return 0;
}

int XMLFINDCHILD_F(Etxt* elem) {
	if (elem) {
		elem->refCount++;
		bool bResult = (xml.FindChildElem(elem->tValue));
		E_TXTDEL_R(elem);
		if (bResult)
			return 1;
	}
	return 0;
}

void XMLINTO() {
	xml.IntoElem();		// down 1 level
}

void XMLOUTOF() {
	xml.OutOfElem();	// up 1 level
}


int XMLLATTR_F(Etxt* attrname) {	// return Logical (bool?) attribute value
	int logical = 0;
	if (attrname) {
		attrname->refCount++;
		if (xml.GetAttrib(attrname->tValue) == "Y")
			logical = 1;
		E_TXTDEL_R(attrname);
	}
	return logical;
}

int XMLIATTR_F(Etxt* attrname) {	// return Integer attribute value
	CString temp;
	int i = 0;
	if (attrname) {
		attrname->refCount++;
		temp = xml.GetAttrib(attrname->tValue);
		i = _tcstol(temp, &zero, 10);
		E_TXTDEL_R(attrname);
	}
	return i;
}


Etxt* XMLTATTR_F(Etxt* attrname) {	// return Text attribute value
	CString temp;
	if (attrname) {
		attrname->refCount++;
		temp = xml.GetAttrib(attrname->tValue);
		E_TXTDEL_R(attrname);
		if (temp.GetBuffer() != NULL)
			return E_TXTLIT_F(temp.GetBuffer());
	}
	return NULL;
}

Etxt* XMLGETDATA_F() {	// return Text value
	CString temp;
	temp = xml.GetData();
	if (temp.GetBuffer() != NULL)
		return E_TXTLIT_F(temp.GetBuffer());
	return NULL;
}

Etxt* XMLGETCHILDDATA_F() {	// return Text value
	CString temp;
	temp = xml.GetChildData();
	if (temp.GetBuffer() != NULL)
		return E_TXTLIT_F(temp.GetBuffer());
	return NULL;
}


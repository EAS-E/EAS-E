// NewEntTypDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EASE0002.h"
#include "NewEntTypDlg.h"
#include "afxdialogex.h"
#include "EaseData.h"
#include "EditEntTypDlg.h"
#include "Strsafe.h"



// NewEntTypDlg dialog

IMPLEMENT_DYNAMIC(NewEntTypDlg, CDialogEx)

NewEntTypDlg::NewEntTypDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_NEWTYPDLG, pParent)
{

}

NewEntTypDlg::~NewEntTypDlg()
{
}

void NewEntTypDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NewEntTypDlg, CDialog)
	ON_BN_CLICKED(IDOK, &NewEntTypDlg::OnBnClickedOk)
	ON_LBN_SELCHANGE(IDC_LIST1, &NewEntTypDlg::OnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON1, &NewEntTypDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTONCLEAR, &NewEntTypDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_CHECK3, &NewEntTypDlg::OnBnClickedCheck3)
END_MESSAGE_MAP()


// NewEntTypDlg message handlers



BOOL NewEntTypDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	// Initialize set of possible components of compound entity type

	entityTypeDef* eType;
	CComboBox* dbSchemaList;
	CListBox* entComponentList;
	int i = 0;
	int pos;
	EASdbSchema* dbSchema;

	dbSchemaList = (CComboBox*)GetDlgItem(IDC_SELSCHEMA);
	entComponentList = (CListBox*)GetDlgItem(IDC_LIST1);
	dbSchema = f_dbSchemas;
	while (dbSchema) {
		if (!dbSchema->isHidden) {
			pos = dbSchemaList->AddString((LPCTSTR)dbSchema->dbName);
			dbSchemaList->SetItemData(pos, (DWORD_PTR)dbSchema);
			dbSchemaList->SetCurSel(pos);
		}
		eType = dbSchema->f_eTypes;
		while (eType) {
			if ((!eType->isSetType) & (!eType->isHidden) & (!eType->isProc) & (eType->f_entTypeRefs == 0)) {	// no sets, compounds, ( or permanents? )..
				pos = entComponentList->AddString(eType->entityTypeName);
				int p = entComponentList->SetItemData(pos, (DWORD_PTR)eType);
				i++;
			}
			eType = eType->s_entityTypes;
		}
		dbSchema = dbSchema->s_dbSchemas;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void NewEntTypDlg::OnSelchangeList1()
{
	// TODO: Add your control notification handler code here

}

void NewEntTypDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	entityTypeDef* eType;
	int pos;

	CListBox* candidateComponentList = (CListBox*)GetDlgItem(IDC_LIST1);
	pos = candidateComponentList->GetCurSel();
	if (pos != LB_ERR) {
		eType = (entityTypeDef*)candidateComponentList->GetItemData(pos);
		candidateComponentList->SetCurSel(-1);
		CListBox* componentList = (CListBox*)GetDlgItem(IDC_LIST2);
		pos = componentList->AddString(eType->entityTypeName);
		componentList->SetItemData(pos, (DWORD_PTR)eType);
	}
}


void NewEntTypDlg::OnBnClickedButtonClear()
{
	// TODO: Add your control notification handler code here

	CListBox* componentList = (CListBox*)GetDlgItem(IDC_LIST2);
	componentList->ResetContent();
}


void NewEntTypDlg::OnBnClickedCheck3()
{
	// TODO: Add your control notification handler code here
}


void NewEntTypDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	CDialog::OnOK();
	CWnd* pWnd;
	CString entName;
	CString tempTxt;
	EASdbSchema* dbSchema;
	EASdbSchema* lastSchema;
	bool found = FALSE;
	entityTypeDef* eType;
	entityTypeDef* ent;
	HRESULT res;
	CListBox* entComponentList;
	int pos;
	int len;
	int icount;
	entTypeRef* eRef;
	attrDef* attr;
	defRef* dRef;
	defRef* nRef;
	entityTypeDef* aSys;
	CComboBox* dbSchemaList;

	pWnd = GetDlgItem(IDC_EDIT1);
	pWnd->GetWindowText(entName);
	if (entName == "") {
		AfxMessageBox(_T("No entity name specified"), MB_OK, 0);
		return;
	}

	dbSchemaList = (CComboBox*)GetDlgItem(IDC_SELSCHEMA);
	dbSchemaList->GetWindowText(tempTxt);
	pos = dbSchemaList->GetCurSel();
	if (pos != CB_ERR) {
		dbSchema = (EASdbSchema*)dbSchemaList->GetItemData(pos);
	}
	else {
		dbSchemaList->GetWindowText(tempTxt);
		dbSchema = f_dbSchemas;
		icount = 0;
		while (dbSchema) {
			if (dbSchema->dbName == tempTxt) {
				AfxMessageBox(_T("This schema name already exists"), MB_OK, 0);
				return;
			}
 			lastSchema = dbSchema;
			if (dbSchema->dbID > icount)
				icount = dbSchema->dbID;
			dbSchema = dbSchema->s_dbSchemas;
		}
		dbSchema = (EASdbSchema*)calloc(1, sizeof(EASdbSchema));
		lastSchema->s_dbSchemas = dbSchema;
		dbSchema->dbID = icount + 1;
		len = tempTxt.GetLength();
		dbSchema->dbName = new TCHAR[len + 1];
		res = StringCchCopy(dbSchema->dbName, len + 1, (LPCTSTR)tempTxt);
		pos = dbSchemaList->AddString((LPCTSTR)dbSchema->dbName);
		dbSchemaList->SetItemData(pos, (DWORD_PTR)dbSchema);
		dbSchemaList->SetCurSel(pos);
	}

	// search for already existing?
	eType = dbSchema->f_eTypes;		// pointer to first in set
	while (eType) {
		if (eType->entityTypeName == entName) {
			found = TRUE;
			break;
		}
		eType = eType->s_entityTypes;
	}
	if (found) {
		AfxMessageBox(_T("This entity name already exists in this schema"), MB_OK, 0);
		return;
	}

	entComponentList = (CListBox*)GetDlgItem(IDC_LIST2);
	icount = entComponentList->GetCount();
	if (icount == 1) {
		AfxMessageBox(_T("Compound entity needs more than 1 component"), MB_OK, 0);
		return;
	}

	// create a new type
	eType = (entityTypeDef*)calloc(1, sizeof(entityTypeDef));
	len = entName.GetLength();
	eType->entityTypeName = new TCHAR[len + 1];
	res = StringCchCopy(eType->entityTypeName, len + 1, (LPCTSTR)entName);

	pWnd = GetDlgItem(IDC_EDENTDESC);
	pWnd->GetWindowText(tempTxt);
	len = tempTxt.GetLength();
	if (len) {
		if (eType->entDescription != NULL)
			delete eType->entDescription;
		eType->entDescription = new TCHAR[len + 1];
		res = StringCchCopy(eType->entDescription, len + 1, (LPCTSTR)tempTxt);
	}

	icount--;
	while (icount >= 0) {
		eRef = (entTypeRef*)calloc(1, sizeof(entTypeRef));
		eRef->entType = (entityTypeDef*)entComponentList->GetItemData(icount);
		eRef->s_entTypeRefs = eType->f_entTypeRefs;
		eType->f_entTypeRefs = eRef;
		attr = (attrDef*)calloc(1, sizeof(attrDef));
		attr->attrDefType = eRef->entType;
		tempTxt = attr->attrDefType->entityTypeName;
		len = tempTxt.GetLength();
		attr->attrDefName = new TCHAR[len+1];
		res = StringCchCopy(attr->attrDefName, len+1, tempTxt);
		attr->scripted = TRUE;
		//attr->s_attrDefs = eType->f_attrDefs;  need to fix this **********************
		//eType->f_attrDefs = attr;
		icount--;
	}

	eType->dbRef = dbSchema;
	dbSchema->lastTypeID++;
	eType->entityTypeID = dbSchema->lastTypeID;

	ent = dbSchema->f_eTypes;
	if (ent) {
		while (ent->s_entityTypes) ent = ent->s_entityTypes;
		ent->s_entityTypes = eType;								// file last...
	}
	else
		dbSchema->f_eTypes = eType;

	aSys = dbSchema->theSystem;
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


	// THE SYSTEM definition gets an attribute type for this entity type

	//if (!eType->isSystemDefined & !eType->isSetType) {			// is this possible, here?
	//	sAttr = (attrDef*)calloc(1, sizeof(attrDef));
	//	tempTxt = eType->entityTypeName;
	//	len = tempTxt.GetLength();
	//	sAttr->attrDefName = new TCHAR[len + 1];
	//	res = StringCchCopy(sAttr->attrDefName, len + 1, (LPCTSTR)eType->entityTypeName);
	//	sAttr->attrDefType = eType;
	//	sAttr->scripted = TRUE;
	//	dRef = (defRef*)calloc(1, sizeof(defRef));
	//	dRef->drType = ref_att;
	//	dRef->attRef = sAttr;

	//	dRef->s_defRefs = dbSchema->theSystem->f_attrDefs;
	//	dbSchema->theSystem->f_attrDefs = dRef;
	//}
}


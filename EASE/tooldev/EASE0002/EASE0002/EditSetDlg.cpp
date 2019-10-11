// EditSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EASE0002.h"
#include "EaseData.h"
#include "EditSetDlg.h"
#include "afxdialogex.h"
#include "Strsafe.h"


// EditSetDlg dialog

IMPLEMENT_DYNAMIC(EditSetDlg, CDialogEx)

EditSetDlg::EditSetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EDITSETDLG, pParent)
{

}

EditSetDlg::~EditSetDlg()
{
}

void EditSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(EditSetDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &EditSetDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTONADD, &EditSetDlg::OnBnClickedButtonadd)
	ON_CBN_SELCHANGE(IDC_COMBODISPLN, &EditSetDlg::OnCbnSelchangeCombodispln)
	ON_LBN_SELCHANGE(IDC_LISTRANKATTS, &EditSetDlg::OnLbnSelchangeListrankatts)
	ON_BN_CLICKED(IDC_DOWNORDER, &EditSetDlg::OnBnClickedDownorder)
	ON_BN_CLICKED(IDC_SETPERSIST, &EditSetDlg::OnBnClickedSetpersist)
END_MESSAGE_MAP()


// EditSetDlg message handlers


BOOL EditSetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	SetWindowText(_T("Edit set definition"));

	CWnd* pWnd;
	CString sName;
	CComboBox* aCombo;
	CListBox* aList;
	EASdbSchema* schema;
	int pos;
	int discipline;
	entityTypeDef* eType;
	defRef* dRef;
	rankAttr* rAtt;
	entTypeRef* mmbrRef;
	CButton* ispersist;

	aCombo = (CComboBox*)GetDlgItem(IDC_COMBODISPLN);
	pos = aCombo->AddString(_T("Ranked"));
	pos = aCombo->AddString(_T("FIFO"));
	pos = aCombo->AddString(_T("LIFO"));

	if (m_set != NULL) {		// editing existing set
		pWnd = GetDlgItem(IDC_EDTSETNAME);
		pWnd->SetWindowText(m_set->setName);

		pWnd = GetDlgItem(IDC_STATIC);
		pWnd->ShowWindow(SW_HIDE);
		pWnd = GetDlgItem(IDC_COMBOSCHEMA);
		pWnd->ShowWindow(SW_HIDE);

		discipline = m_set->setDiscipline;
		aCombo = (CComboBox*)GetDlgItem(IDC_COMBODISPLN);
		aCombo->SetCurSel(discipline);

		if (discipline == 0) {				// ranked
			aList = (CListBox*)GetDlgItem(IDC_LISTMMBRATTS);
			mmbrRef = m_set->f_setMmbrs;	// for now.. we could check for common attributes only
			eType = mmbrRef->entType;
			dRef = eType->f_attrDefs;
			while (dRef) {
				pos = aList->AddString(dRef->attRef->attrDefName);
				aList->SetItemData(pos, (DWORD_PTR)dRef->attRef);
				dRef = dRef->s_defRefs;
			}
			aList = (CListBox*)GetDlgItem(IDC_LISTRANKATTS);
			rAtt = m_set->f_rankAttrs;
			while (rAtt) {
				pos = aList->AddString(rAtt->rattName);
				aList->SetItemData(pos, (DWORD_PTR)rAtt->seqLow);
				rAtt = rAtt->s_rankAttrs;
			}
		}
		else {
			pWnd = (CWnd*)GetDlgItem(IDC_BUTTONADD);
			pWnd->EnableWindow(FALSE);
			pWnd = (CWnd*)GetDlgItem(IDC_BUTTONREMV);
			pWnd->EnableWindow(FALSE);
			pWnd = (CWnd*)GetDlgItem(IDC_DOWNORDER);
			pWnd->EnableWindow(FALSE);
		}

		ispersist = (CButton*)GetDlgItem(IDC_SETPERSIST);
		if ( m_set->isPersistent != 0)
			ispersist->SetCheck(BST_CHECKED);
		else
			ispersist->SetCheck(BST_UNCHECKED);

	}
	else {						// new set definition? - we'll see at OK
		aCombo = (CComboBox*)GetDlgItem(IDC_COMBOSCHEMA);
		schema = f_dbSchemas;
		while (schema) {
			pos = aCombo->AddString((LPCTSTR)schema->dbName);
			aCombo->SetItemData(pos, (DWORD_PTR)schema);
			aCombo->SetCurSel(pos);
			schema = schema->s_dbSchemas;
		}
		aCombo = (CComboBox*)GetDlgItem(IDC_COMBODISPLN);
		aCombo->SetCurSel(1);	// default FIFO
	}


	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void EditSetDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	CString sName;
	CComboBox* aCombo;
	int pos;
	EASdbSchema* aSchema = NULL;
	setDef* sDef;
	int len;
	rankAttr* rAtt;
	rankAttr* lrAtt;
	CListBox* aList;
	int n;
	CString str;
	CButton* ispersist;

	GetDlgItemText(IDC_EDTSETNAME, sName);
	if (sName == _T("")) {
		AfxMessageBox(_T("No set name specified"), MB_OK);
		return;
	}

	aCombo = (CComboBox*)GetDlgItem(IDC_COMBOSCHEMA);
	pos = aCombo->GetCurSel();
	if (m_set == NULL) {	// creating new set?
		if (pos == CB_ERR) {
			AfxMessageBox(_T("No subsystem selected"), MB_OK);
			return;
		}
		aSchema = (EASdbSchema*)aCombo->GetItemData(pos);
		sDef = aSchema->f_setDefs;
		while (sDef) {
			if (_tcscmp(sDef->setName, sName) == 0)
				break;
			sDef = sDef->s_setDefs;
		}
		if (sDef) {
			AfxMessageBox(_T("Duplicate set name"), MB_OK);
			return;
		}
	}

	sDef = m_set;
	if (sDef == NULL) {
		sDef = (setDef*)calloc(1, sizeof(setDef));
		sDef->s_setDefs = aSchema->f_setDefs;
		aSchema->f_setDefs = sDef;
	}
	else {
		if (sDef->setName != NULL)
			delete sDef->setName;
	}
	len = sName.GetLength();
	sDef->setName = (TCHAR*)calloc(len + 1, sizeof(TCHAR));
	StringCchCopy(sDef->setName, len + 1, (LPCTSTR)sName);

	ispersist = (CButton*)GetDlgItem(IDC_SETPERSIST);
	if (ispersist->GetCheck() == BST_CHECKED)
		sDef->isPersistent = true;
	else
		sDef->isPersistent = false;

	aCombo = (CComboBox*)GetDlgItem(IDC_COMBODISPLN);
	sDef->setDiscipline = aCombo->GetCurSel();

	rAtt = sDef->f_rankAttrs;			// clear these... 
	while (rAtt) {
		lrAtt = rAtt;
		rAtt = rAtt->s_rankAttrs;
		delete lrAtt;
	}
	sDef->f_rankAttrs = NULL;

	if (sDef->setDiscipline == 0) {		// ranked?

		rAtt = sDef->f_rankAttrs;
		while (rAtt) {
			lrAtt = rAtt;
			rAtt = rAtt->s_rankAttrs;
			delete lrAtt;
		}
		sDef->f_rankAttrs = NULL;

		aList = (CListBox*)GetDlgItem(IDC_LISTRANKATTS);
		n = aList->GetCount();
		pos = 0;
		while (pos < n) {
			rAtt = (rankAttr*)calloc(1, sizeof(rankAttr));
			if (sDef->f_rankAttrs == NULL)
				sDef->f_rankAttrs = rAtt;
			else
				lrAtt->s_rankAttrs = rAtt;
			lrAtt = rAtt;
			aList->GetText(pos, str);
			len = str.GetLength();
			rAtt->rattName = new TCHAR[len + 1];
			StringCchCopy(rAtt->rattName, len + 1, (LPCTSTR)str);
			rAtt->seqLow = (int)aList->GetItemData(pos);
			pos++;
		}
	}
	CDialogEx::OnOK();
}


void EditSetDlg::OnBnClickedButtonadd()
{
	// TODO: Add your control notification handler code here

	CString sName;
	CListBox* attList;
	int pos;
	attrDef* dAttr;
	CListBox* rankList;
	int rpos;


	attList = (CListBox*)GetDlgItem(IDC_LISTMMBRATTS);
	rankList = (CListBox*)GetDlgItem(IDC_LISTRANKATTS);

	pos = attList->GetCurSel();		// selected attribute for ranking
	if (pos == LB_ERR) {
		AfxMessageBox(_T("No attribute selected"), MB_OK);
		return;
	}
	dAttr = (attrDef*)attList->GetItemData(pos);

	rpos = rankList->FindStringExact(-1, dAttr->attrDefName);
	if (rpos != LB_ERR) {
		AfxMessageBox(_T("Already selected for ranking"), MB_OK);
		return;
	}
	pos = rankList->AddString(dAttr->attrDefName);
	rankList->SetItemData(pos, (DWORD_PTR)0);	// being careful
}


void EditSetDlg::OnCbnSelchangeCombodispln()
{
	// TODO: Add your control notification handler code here

	CListBox* aList;
	CComboBox* aCombo;
	CWnd* pWnd;
	int pos;
	int discipline;
	entityTypeDef* eType;
	defRef* dRef;
	rankAttr* rAtt;
	entTypeRef* mmbrRef;

	aList = (CListBox*)GetDlgItem(IDC_LISTRANKATTS);
	aCombo = (CComboBox*)GetDlgItem(IDC_COMBODISPLN);
	discipline = aCombo->GetCurSel();
	if (discipline != 0) {
		aList = (CListBox*)GetDlgItem(IDC_LISTMMBRATTS);
		aList->ResetContent();
		aList = (CListBox*)GetDlgItem(IDC_LISTRANKATTS);
		aList->ResetContent();
		pWnd = (CWnd*)GetDlgItem(IDC_BUTTONADD);
		pWnd->EnableWindow(FALSE);
		pWnd = (CWnd*)GetDlgItem(IDC_BUTTONREMV);
		pWnd->EnableWindow(FALSE);
		pWnd = (CWnd*)GetDlgItem(IDC_DOWNORDER);
		pWnd->EnableWindow(FALSE);
	}
	else {
		if (m_set != NULL) {
			aList = (CListBox*)GetDlgItem(IDC_LISTMMBRATTS);
			mmbrRef = m_set->f_setMmbrs;	// for now.. we could check for common attributes only
			eType = mmbrRef->entType;
			dRef = eType->f_attrDefs;
			while (dRef) {
				pos = aList->AddString(dRef->attRef->attrDefName);
				aList->SetItemData(pos, (DWORD_PTR)dRef->attRef);
				dRef = dRef->s_defRefs;
			}
			aList = (CListBox*)GetDlgItem(IDC_LISTRANKATTS);
			rAtt = m_set->f_rankAttrs;
			while (rAtt) {
				aList->AddString(rAtt->rattName);
				aList->SetItemData(pos, (DWORD_PTR)rAtt->seqLow);
				rAtt = rAtt->s_rankAttrs;
			}
			pWnd = (CWnd*)GetDlgItem(IDC_BUTTONADD);
			pWnd->EnableWindow(TRUE);
			pWnd = (CWnd*)GetDlgItem(IDC_BUTTONREMV);
			pWnd->EnableWindow(TRUE);
			pWnd = (CWnd*)GetDlgItem(IDC_DOWNORDER);
			pWnd->EnableWindow(TRUE);
		}
	}
}


void EditSetDlg::OnLbnSelchangeListrankatts()
{
	// TODO: Add your control notification handler code here

	CListBox* aList;
	CButton* desc;
	int isLow;

	aList = (CListBox*)GetDlgItem(IDC_LISTRANKATTS);
	int pos = aList->GetCurSel();			// selected rank attribute
	if (pos == LB_ERR)
		return;
	isLow = (int)aList->GetItemData(pos);

	desc = (CButton*)GetDlgItem(IDC_DOWNORDER);
	if (isLow == 1)
		desc->SetCheck(BST_CHECKED);
	else
		desc->SetCheck(BST_UNCHECKED);
}


void EditSetDlg::OnBnClickedDownorder()
{
	// TODO: Add your control notification handler code here
	CListBox* aList;
	CButton* desc;

	aList = (CListBox*)GetDlgItem(IDC_LISTRANKATTS);
	int pos = aList->GetCurSel();			// selected rank attribute
	if (pos == LB_ERR)
		return;

	desc = (CButton*)GetDlgItem(IDC_DOWNORDER);
	if (desc->GetCheck() == BST_CHECKED)
		aList->SetItemData(pos, (DWORD_PTR)1);
	else
		aList->SetItemData(pos, (DWORD_PTR)0);

}



void EditSetDlg::OnBnClickedSetpersist()
{
	// TODO: Add your control notification handler code here
}

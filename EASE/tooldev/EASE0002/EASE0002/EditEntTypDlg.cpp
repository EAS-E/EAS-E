// EditEntTypDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EASE0002.h"
#include "EditEntTypDlg.h"
#include "EaseData.h"
#include "afxdialogex.h"
#include "Strsafe.h"


// EditEntTypDlg dialog

IMPLEMENT_DYNAMIC(EditEntTypDlg, CDialogEx)

EditEntTypDlg::EditEntTypDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EDITENTTYPDLG, pParent)
{

}

EditEntTypDlg::EditEntTypDlg(entityTypeDef* eType, CWnd* pParent) {
	m_eType = eType;
}


EditEntTypDlg::~EditEntTypDlg()
{
}

void EditEntTypDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(EditEntTypDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &EditEntTypDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BNEEATTRDEL, &EditEntTypDlg::OnBnClickedAttrDel)
	ON_LBN_SELCHANGE(IDC_LIST2, &EditEntTypDlg::OnLbnSelchangeList2)
	ON_BN_CLICKED(IDC_BUTTON4, &EditEntTypDlg::OnBnClickedButton4)
	ON_LBN_SELCHANGE(IDC_LIST1, &EditEntTypDlg::OnLbnSelchangeList1)
	ON_LBN_SELCHANGE(IDC_LISTMSETS, &EditEntTypDlg::OnLbnSelchangeListosets)
	ON_BN_CLICKED(IDOK, &EditEntTypDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT2, &EditEntTypDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_ATTDIMS, &EditEntTypDlg::OnEnChangeAttdims)
	ON_STN_CLICKED(IDC_STATICSETS, &EditEntTypDlg::OnStnClickedStaticsets)
	ON_LBN_SELCHANGE(IDC_LISTOSETS, &EditEntTypDlg::OnLbnSelchangeListosets)
	ON_EN_CHANGE(IDC_EDIT3, &EditEntTypDlg::OnEnChangeEdit3)
	ON_EN_SETFOCUS(IDC_EDIT3, &EditEntTypDlg::OnEnSetfocusEdit3)
	ON_EN_KILLFOCUS(IDC_EDIT3, &EditEntTypDlg::OnEnKillfocusEdit3)
	ON_BN_CLICKED(IDC_ENTPERSIST, &EditEntTypDlg::OnBnClickedEntpersist)
END_MESSAGE_MAP()


// EditEntTypDlg message handlers


BOOL EditEntTypDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	CWnd* pWnd;
	entityTypeDef* attrDefType;
	defRef* dRef;
	attrDef* attr;
	setDef* set;
	CListBox* attrList;
	CListBox* typeList;
	CListBox* setOlist;
	CListBox* setMlist;
	int pos;
	EASdbSchema* dbSchema;
	CButton* ispersist;

	SetWindowText(_T("Edit entity definition"));

	pWnd = GetDlgItem(IDC_EDIT3);					// entity name edit control
	pWnd->SetWindowText(m_eType->entityTypeName);

	typeList = (CListBox*)GetDlgItem(IDC_LIST1);	// show list of possible attribute types

	dbSchema = f_dbSchemas;
	while (dbSchema) {
		attrDefType = dbSchema->f_eTypes;
		while (attrDefType) {
			if (!attrDefType->isHidden & !attrDefType->isProc & !attrDefType->deleted) {
				pos = typeList->AddString(attrDefType->entityTypeName);
				typeList->SetItemData(pos, (DWORD_PTR)attrDefType);
			}
			attrDefType = attrDefType->s_entityTypes;
		}
		setMlist = (CListBox*)GetDlgItem(IDC_LISTMSETS);	// show list of candidate set memberships
		setOlist = (CListBox*)GetDlgItem(IDC_LISTOSETS);	// show list of candidate set memberships
		set = dbSchema->f_setDefs;
		while (set) {
			if (!set->deleted) {
				pos = setMlist->AddString(set->setName);
				setMlist->SetItemData(pos, (DWORD_PTR)set);
				pos = setOlist->AddString(set->setName);
				setOlist->SetItemData(pos, (DWORD_PTR)set);
			}
			set = set->s_setDefs;
		}
		dbSchema = dbSchema->s_dbSchemas;
	}

	attrList = (CListBox*)GetDlgItem(IDC_LIST2);	// show existing attributes of this entity type
	if (m_eType) {
		dRef = m_eType->f_attrDefs;
		while (dRef) {
			attr = dRef->attRef;
			if (!attr->attrDefType->deleted) {
				pos = attrList->AddString(attr->attrDefName);
				int p = attrList->SetItemData(pos, (DWORD_PTR)dRef);
			}
			dRef = dRef->s_defRefs;
		}
	}
	m_lastSelAttr = NULL;

	dRef = m_eType->f_mmbrSetRefs;
	while (dRef) {
		set = dRef->setRef;
		pos = setMlist->FindStringExact(-1, dRef->setRef->setName);
		if (pos != LB_ERR)
			pos = setMlist->SetSel(pos, TRUE);		// show set membership defined for this entity type
		dRef = dRef->s_defRefs;
	}

	dRef = m_eType->f_owndSetRefs;
	while (dRef) {
		set = dRef->setRef;
		pos = setOlist->FindStringExact(-1, dRef->setRef->setName);
		if (pos != LB_ERR)
			pos = setOlist->SetSel(pos, TRUE);		// show set ownership defined for this entity type
		dRef = dRef->s_defRefs;
	}

	pWnd = GetDlgItem(IDC_BNEEATTRDEL);
/*	if (m_eType->f_instanceRefs != NULL)
		pWnd->EnableWindow(FALSE);
	else */
		pWnd->EnableWindow(TRUE);

	pWnd = GetDlgItem(IDC_BUTTON1);
/*	if (m_eType->f_instanceRefs != NULL)
		pWnd->EnableWindow(FALSE);
	else */
		pWnd->EnableWindow(TRUE);

	pWnd = GetDlgItem(IDC_LIST1);
/*	if (m_eType->f_instanceRefs != NULL)
		pWnd->EnableWindow(FALSE);
	else */
		pWnd->EnableWindow(TRUE);

	pWnd = GetDlgItem(IDC_LISTMSETS);
	if (m_eType->isSys)
		pWnd->EnableWindow(FALSE);
	else
		pWnd->EnableWindow(TRUE);

	pWnd = GetDlgItem(IDC_ENTPERSIST);
	if (m_eType->isSys)
		pWnd->EnableWindow(FALSE);
	else {
		ispersist = (CButton*)GetDlgItem(IDC_ENTPERSIST);
		if (m_eType->isPersistent != 0)
			ispersist->SetCheck(BST_CHECKED);
		else
			ispersist->SetCheck(BST_UNCHECKED);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void EditEntTypDlg::OnBnClickedButton1()		// add new attribute
{
	// TODO: Add your control notification handler code here
	CListBox* typeList;
	CListBox* attrList;
	CButton* isEmbed;
	CString attrName;
	attrDef* newAttr;
	defRef* nRef;
	defRef* dRef;
	int pos;
	int len;
	DWORD_PTR itemData;
	HRESULT res;

	typeList = (CListBox*)GetDlgItem(IDC_LIST1);
	pos = typeList->GetCurSel();				// selected type definition
	if (pos == LB_ERR) {
		AfxMessageBox(_T("No attribute type selected"), MB_OK, 0);
		return;
	}
	GetDlgItemText(IDC_EDIT1, attrName);		// new attribute name?
	if (attrName == "") {
		AfxMessageBox(_T("No attribute name specified"), MB_OK, 0);
		return;
	}
	SetDlgItemText(IDC_EDIT1, _T(""));

	dRef = m_eType->f_attrDefs;
	while (dRef) {
		if (_tcscmp(dRef->attRef->attrDefName, (LPCTSTR)(attrName)) == 0) {
			AfxMessageBox("attribute already defined", MB_OK);
			return;
		}
		else
			dRef = dRef->s_defRefs;
	}

	newAttr = (attrDef*)calloc(1, sizeof(attrDef));
	newAttr->s_attrDefs = NULL;				// overkill...
	len = attrName.GetLength();
	newAttr->attrDefName = new TCHAR[len+1];
	res = StringCchCopy(newAttr->attrDefName, len+1, (LPCTSTR)attrName);
	newAttr->attrDefType = (entityTypeDef*)typeList->GetItemData(pos);
	newAttr->ownerType = m_eType;
	attrList = (CListBox*)GetDlgItem(IDC_LIST2);
	pos = attrList->AddString(attrName);
	itemData = (DWORD_PTR)newAttr;
	attrList->SetItemData(pos, itemData);

	nRef = (defRef*)calloc(1, sizeof(defRef));
	nRef->attRef = newAttr;
	dRef = m_eType->f_attrDefs;
	if (dRef) {
		while (dRef->s_defRefs)
			dRef = dRef->s_defRefs;
		dRef->s_defRefs = nRef;
	}
	else
		m_eType->f_attrDefs = nRef;

	isEmbed = (CButton*)GetDlgItem(IDC_CHECK1);
	if (isEmbed->GetState() == BST_CHECKED)
		newAttr->embedded = TRUE;

	//if (newAttr->attrDefType->isSetType) {				// keep track of all set-type attributes
	//	newAttr->isSetAttr = TRUE;
	//	setList = (CListBox*)GetDlgItem(IDC_LISTMSETS);
	//	setRef = (setDefRef*)calloc(1, sizeof(setDefRef));
	//	setRef->dAttr = newAttr;
	//	setRef->s_setDefRef = newAttr->attrDefType->f_setAttrRefs;
	//	newAttr->attrDefType->f_setAttrRefs = setRef;
	//	pos = setList->AddString(setRef->dAttr->attrDefName);		// update set of candidate set memberships
	//	setList->SetItemData(pos, (DWORD_PTR)setRef->dAttr);
	//}
}


void EditEntTypDlg::OnBnClickedAttrDel()				// delete attribute from definition
{
	// TODO: Add your control notification handler code here

	CListBox* attrList;
	CString attrName;
	attrDef* dAttr = NULL;
	defRef* dRef;
	defRef* ldRef;
	int pos;

	attrList = (CListBox*)GetDlgItem(IDC_LIST2);
	pos = attrList->GetCurSel();

	if (pos == LB_ERR )
		AfxMessageBox(_T("No attribute selected"), MB_OK, 0);
	else {
		dRef = m_eType->f_attrDefs;
		if (!dRef)
			AfxMessageBox(_T("No attributes exist"), MB_OK, 0);
		else {
			ldRef = NULL;
			while (pos) {
				pos--;
				ldRef = dRef;
				dRef = dRef->s_defRefs;
			}
			if (dRef->attRef->scripted)
				AfxMessageBox(_T("Cannot delete scripted attribute"), MB_OK, 0);
			else {
				if (ldRef)
					ldRef->s_defRefs = dRef->s_defRefs;
				else {
					m_eType->f_attrDefs = dRef->s_defRefs;
				}
				pos = attrList->GetCurSel();
				pos = attrList->DeleteString(pos);

				//if (dAttr->isSetAttr) {
				//	if (dAttr->attrDefType) {			// this may cause problems....
				//		setEntDef = dAttr->attrDefType;
				//		setRef = setEntDef->f_setAttrRefs;
				//		lSetRef = NULL;
				//		while (setRef) {
				//			// delete the set attribute reference from the set-type definition
				//			if (setRef->dAttr == dAttr) {
				//				if (lSetRef == NULL)
				//					setEntDef->f_setAttrRefs = setRef->s_setDefRef;
				//				else
				//					lSetRef->s_setDefRef = setRef->s_setDefRef;
				//				delete setRef->dAttrName;
				//				delete setRef;
				//				break;
				//			}
				//			lSetRef = setRef;
				//			setRef = setRef->s_setDefRef;
				//		}
				//	}
				//}
				delete dAttr;
				delete dRef;
			}
		}
	}
}


void EditEntTypDlg::OnLbnSelchangeList2()		// select a different attribute
{
	// TODO: Add your control notification handler code here

	CWnd* pWnd;
	attrDef* dAttr;
	CListBox* attrList;
	int pos;
	CString attrName;
	entityTypeDef* attrType;
	defRef* dRef;
	CListBox* typeList;
	int i;
	int res;
	CString itemText;
	TCHAR dim[2];
	TCHAR* zero = 0;


	attrList = (CListBox*)GetDlgItem(IDC_LIST2);
	pos = attrList->GetCurSel();
	if (pos == LB_ERR)
		return;

	CButton* isEmbed = (CButton*)GetDlgItem(IDC_CHECK1);

	dAttr = m_lastSelAttr;
	if (dAttr) {
		if (isEmbed->GetCheck())
			dAttr->embedded = TRUE;
		else
			dAttr->embedded = FALSE;

		pWnd = GetDlgItem(IDC_ATTDIMS);
		pWnd->GetWindowText(itemText);
		dAttr->subscripts = _tcstol(itemText, &zero, 10);
	}

	pWnd = GetDlgItem(IDC_EDIT1);				// attribute name edit control
	attrList->GetText(pos, attrName);
	pWnd->SetWindowText(attrName);

	// find attribute type in list and set as 'selected'
	dRef = (defRef*)attrList->GetItemData(pos);
	dAttr = dRef->attRef;
	m_lastSelAttr = dAttr;				// remember this for description edit

	typeList = (CListBox*)GetDlgItem(IDC_LIST1);
	attrType = dAttr->attrDefType;
	if (attrType) {
		i = typeList->GetCount();
		while (i) {
			if (attrType == (entityTypeDef*)typeList->GetItemData(i - 1)) {
				res = typeList->SetCurSel(i - 1);
				break;
			}
			i--;
		}
		//pos = attrList->GetCurSel();
		//CWnd* editSet = (CButton*)GetDlgItem(IDC_EDITSET);
		//if (attrType->isSetType)
		//	editSet->ShowWindow(SW_SHOW);
		//else
		//	editSet->ShowWindow(SW_HIDE);
	}
	else
		typeList->SetCurSel(-1);

	if (dAttr->embedded)
		isEmbed->SetCheck(BST_CHECKED);		// typically, these will be embedded
	else
		isEmbed->SetCheck(BST_UNCHECKED);	// typically referenced through a pointer attribute

	pWnd = GetDlgItem(IDC_ATTDIMS);
	sprintf(dim, "%d", dAttr->subscripts);
	pWnd->SetWindowText(dim);

	//if (m_eType->f_instanceRefs != NULL)
	//	return;

	pWnd = GetDlgItem(IDC_BUTTON4);
	if (dAttr->scripted)
		pWnd->EnableWindow(FALSE);
	else
		pWnd->EnableWindow(TRUE);

	pWnd = GetDlgItem(IDC_BNEEATTRDEL);
	if (dAttr->scripted)
		pWnd->EnableWindow(FALSE);
	else
		pWnd->EnableWindow(TRUE);
}


void EditEntTypDlg::OnBnClickedButton4()		// attribute rename request
{
	// TODO: Add your control notification handler code here

	attrDef* thisAttr = NULL;
	CListBox* attrList;
	int pos;
	int len;
	CString attrName;
	DWORD_PTR itemData;
	defRef* dRef;
	HRESULT res;


	GetDlgItemText(IDC_EDIT1, attrName);		// new attribute name?
	attrList = (CListBox*)GetDlgItem(IDC_LIST2);
	pos = attrList->GetCurSel();
	if ((pos != LB_ERR) & (attrName != "")) {
		itemData = attrList->GetItemData(pos);
		dRef = (defRef*)itemData;
		thisAttr = (attrDef*)dRef->attRef;
		if (thisAttr->attrDefName != NULL)
			delete thisAttr->attrDefName;
		len = attrName.GetLength();
		thisAttr->attrDefName = new TCHAR[len+1];
		res = StringCchCopy(thisAttr->attrDefName, len+1, (LPCTSTR)attrName);
		attrList->DeleteString(pos);
		attrList->InsertString(pos, attrName);
		attrList->SetItemData(pos, itemData);
	}
}


void EditEntTypDlg::OnLbnSelchangeList1()
{
	// TODO: Add your control notification handler code here

	CButton* isEmbed = (CButton*)GetDlgItem(IDC_CHECK1);
	CListBox* typeList = (CListBox*)GetDlgItem(IDC_LIST1);
	int pos = typeList->GetCurSel();		// selected type definition

	entityTypeDef* eType = (entityTypeDef*)typeList->GetItemData(pos);
	if (eType->isSystemDefined & !eType->isSetType)
		isEmbed->SetCheck(BST_CHECKED);		// typically, these will be embedded
	else
		isEmbed->SetCheck(BST_UNCHECKED);	// typically referenced through a pointer to an instance reference

}


void EditEntTypDlg::OnLbnSelchangeListosets()
{
	// TODO: Add your control notification handler code here

	CListBox* setList;
	int pos;
	DWORD_PTR itemData;
	setDef* sDef;


	setList = (CListBox*)GetDlgItem(IDC_LISTMSETS);	// show list of candidate set memberships

	pos = setList->GetCurSel();
	if (pos != LB_ERR) {
		itemData = setList->GetItemData(pos);
		sDef = (setDef*)itemData;		// what is this all about?
	}
}


void EditEntTypDlg::OnBnClickedOk() {
	// TODO: Add your control notification handler code here

	setDef* dSet;
	defRef* dead;
	defRef* dRef;
	defRef* ldRef;
	CListBox* setList;
	int pos;
	int count;
	CString temp;
	int len;
	BOOL res;
	CButton* ispersist;

	ispersist = (CButton*)GetDlgItem(IDC_ENTPERSIST);
	if (ispersist->GetCheck() == BST_CHECKED)
		m_eType->isPersistent = true;
	else
		m_eType->isPersistent = false;

	setList = (CListBox*)GetDlgItem(IDC_LISTMSETS);

	dRef = m_eType->f_mmbrSetRefs;		// check for deletions to existing set memberships
	ldRef = NULL;
	while (dRef) {
		dead = NULL;
		pos = setList->FindStringExact(-1, dRef->setRef->setName);
		if (pos != LB_ERR) {
			dead = NULL;
			pos = setList->GetSel(pos);
			if (pos > 0) 				// still selected
				ldRef = dRef;
			else {
				dead = dRef;
				if (ldRef == NULL)
					m_eType->f_mmbrSetRefs = dRef->s_defRefs;
				else
					ldRef->s_defRefs = dRef->s_defRefs;
			}
		}
		dRef = dRef->s_defRefs;
		if (dead)
			delete dead;
	}

	count = setList->GetCount();		// now check for any set membership additions
	while (count) {
		pos = setList->GetSel(count-1);
		if (pos > 0) {					// this one is selected
			dSet = (setDef*)setList->GetItemData(count-1);
			dRef = m_eType->f_mmbrSetRefs;
			while (dRef) {
				if (dRef->setRef == dSet)
					break;
				dRef = dRef->s_defRefs;
			}
			if (dRef == NULL) {			// must be newly selected... we have no reference
				dRef = (defRef*)calloc(1, sizeof(defRef));
				dRef->setRef = dSet;
				dRef->drType = ref_set;
				temp = dSet->setName;
				len = temp.GetLength();
				dRef->refName = new TCHAR[len+1];
				res = StringCchCopy(dRef->refName, len+1, (LPCTSTR)temp);	// is this needed
				dRef->s_defRefs = m_eType->f_mmbrSetRefs;
				m_eType->f_mmbrSetRefs = dRef;
			}
		}
		count--;
	}	

	setList = (CListBox*)GetDlgItem(IDC_LISTOSETS);

	dRef = m_eType->f_owndSetRefs;		// check for deletions to existing set ownerships
	ldRef = NULL;
	while (dRef) {
		dead = NULL;
		pos = setList->FindStringExact(-1, dRef->setRef->setName);
		if (pos != LB_ERR) {
			dead = NULL;
			pos = setList->GetSel(pos);
			if (pos > 0) 				// still selected
				ldRef = dRef;
			else {
				dead = dRef;
				if (ldRef == NULL)
					m_eType->f_owndSetRefs = dRef->s_defRefs;
				else
					ldRef->s_defRefs = dRef->s_defRefs;
			}
		}
		dRef = dRef->s_defRefs;
		if (dead)
			delete dead;
	}

	count = setList->GetCount();		// now check for any set membership additions
	while (count) {
		pos = setList->GetSel(count - 1);
		if (pos > 0) {					// this one is selected
			dSet = (setDef*)setList->GetItemData(count - 1);
			dRef = m_eType->f_owndSetRefs;
			while (dRef) {
				if (dRef->setRef == dSet)
					break;
				dRef = dRef->s_defRefs;
			}
			if (dRef == NULL) {			// must be newly selected... we have no reference
				dRef = (defRef*)calloc(1, sizeof(defRef));
				dRef->setRef = dSet;
				dRef->drType = ref_set;
				temp = dSet->setName;
				len = temp.GetLength();
				dRef->refName = new TCHAR[len + 1];
				res = StringCchCopy(dRef->refName, len + 1, (LPCTSTR)temp);	// is this needed
				dRef->s_defRefs = m_eType->f_owndSetRefs;
				m_eType->f_owndSetRefs = dRef;
			}
		}
		count--;
	}

	CDialogEx::OnOK();
}


void EditEntTypDlg::OnEnChangeEditattrdesc()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

}


/*
void EditEntTypDlg::OnEnKillfocusEditattrdesc()
{
	// TODO: Add your control notification handler code here

	CWnd* pWnd;
	attrDef* dAttr;
	CString descr;
	BOOL res;


	//pWnd = GetDlgItem(IDC_EDITATTRDESC);
	//dAttr = m_lastSelAttr;
	//if (dAttr == NULL)
	//	return;
	//if (dAttr->attrDescription != NULL)
	//	delete dAttr->attrDescription;

	//pWnd->GetWindowText(descr);
	//len = descr.GetLength();
	//dAttr->attrDescription = new TCHAR[len + 1];
	//res = StringCchCopy(dAttr->attrDescription, len + 1, (LPCTSTR)descr);
}


void EditEntTypDlg::OnEnSetfocusEditattrdesc()
{
	// TODO: Add your control notification handler code here
}
*/

void EditEntTypDlg::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void EditEntTypDlg::OnEnChangeAttdims()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void EditEntTypDlg::OnStnClickedStaticsets()
{
	// TODO: Add your control notification handler code here
}


void EditEntTypDlg::OnLbnSelchangeListmsets()
{
	// TODO: Add your control notification handler code here
	CListBox* setList;
	int pos;
	DWORD_PTR itemData;
	setDef* sDef;


	setList = (CListBox*)GetDlgItem(IDC_LISTMSETS);	// show list of candidate set memberships

	pos = setList->GetCurSel();
	CWnd* editSet = (CButton*)GetDlgItem(IDC_EDITSET);
	if (pos != LB_ERR) {
		itemData = setList->GetItemData(pos);
		sDef = (setDef*)itemData;
		if (sDef->setDiscipline == 1)		// no idea....
			editSet->ShowWindow(SW_SHOW);
		else
			editSet->ShowWindow(SW_HIDE);
	}


}


void EditEntTypDlg::OnEnChangeEdit3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

}


void EditEntTypDlg::OnEnSetfocusEdit3()
{
	// TODO: Add your control notification handler code here
}


void EditEntTypDlg::OnEnKillfocusEdit3()
{
	// TODO: Add your control notification handler code here


	CString eName;
	int len;
	CWnd* pWnd;

	GetDlgItemText(IDC_EDIT3, eName);					// entity rename?
	if (_tcscmp(m_eType->entityTypeName, eName) == 0)
		return;
	if (eName == _T("")) {								// blank not allowed
		pWnd = GetDlgItem(IDC_EDIT3);
		pWnd->SetWindowText(m_eType->entityTypeName);
		return;
	}

	if (m_eType->entityTypeName != NULL)
		delete m_eType->entityTypeName;
	len = eName.GetLength();
	m_eType->entityTypeName = new TCHAR[len + 1];
	StringCchCopy(m_eType->entityTypeName, len + 1, (LPCTSTR)eName);

}


void EditEntTypDlg::OnBnClickedEntpersist()
{
	// TODO: Add your control notification handler code here
}

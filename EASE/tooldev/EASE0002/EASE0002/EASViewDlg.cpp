// EASViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EASE0002.h"
#include "EASViewDlg.h"
#include "afxdialogex.h"
#include "EaseData.h"
#include "EditEntTypDlg.h"
#include "NewEntTypDlg.h"
#include "EditSetDlg.h"
#include "NewProcDlg.h"
#include "Strsafe.h"


// EASViewDlg dialog

IMPLEMENT_DYNAMIC(EASViewDlg, CDialog)

EASViewDlg::EASViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_EASVIEWDLG, pParent)
{

}

EASViewDlg::~EASViewDlg()
{
}

void EASViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BOOL FillEntityTree(CTreeCtrl* entityTree);
HTREEITEM firstVis;

BEGIN_MESSAGE_MAP(EASViewDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &EASViewDlg::OnBnClickedEditDefn)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &EASViewDlg::OnTvnSelchangedTree1)
	ON_BN_CLICKED(IDC_BNVWDELTYPE, &EASViewDlg::OnBnClickedBnvwdeltype)
	ON_BN_CLICKED(IDC_BUTTONSAVE, &EASViewDlg::OnBnClickedButtonsave)
	ON_BN_CLICKED(IDC_BTNNEWENT, &EASViewDlg::OnBnClickedBtnnewent)
	ON_BN_CLICKED(IDC_BTNNEWSET, &EASViewDlg::OnBnClickedBtnnewset)
	ON_BN_CLICKED(IDC_BTNNEWPROC, &EASViewDlg::OnBnClickedBtnnewproc)
END_MESSAGE_MAP()


// EASViewDlg message handlers


BOOL EASViewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	CTreeCtrl* entityTree;
	CWnd* pWnd;

	SetWindowText(_T("EAS-E project view"));

	entityTree = (CTreeCtrl*)GetDlgItem(IDC_TREE1);
	FillEntityTree(entityTree);
	
	pWnd = GetDlgItem(IDC_BUTTON1);
	pWnd->EnableWindow(FALSE);

	pWnd = GetDlgItem(IDC_BNVWDELTYPE);
	pWnd->EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL FillEntityTree(CTreeCtrl* entityTree) {

	HTREEITEM treeItem;
	HTREEITEM subTreeItem;
	TVINSERTSTRUCT tvInsert;
	entityTypeDef* eType;
	EASdbSchema* dbSchema;
	attrDef* dAttr;
	defRef* dRef;
	CString tStr;
	BOOL res = FALSE;
	TCHAR dsplyLine[128];

	// Populate set of defined entity types from loaded schemas

	entityTree->DeleteAllItems();

	tvInsert.item.mask = TVIF_TEXT;
	tvInsert.hInsertAfter = TVI_LAST;

	dbSchema = f_dbSchemas;
	while (dbSchema) {
		if (!dbSchema->isHidden) {

			tvInsert.hParent = TVI_ROOT;
			tStr = _T("SYSTEM  (");
			tStr = tStr + dbSchema->dbName;
			tStr = tStr + _T(")");
			tvInsert.item.pszText = tStr.GetBuffer();
			treeItem = entityTree->InsertItem(&tvInsert);
			if (firstVis == NULL)
				firstVis = treeItem;

			if (dbSchema->theSystem) {
				eType = dbSchema->theSystem;
				entityTree->SetItemData(treeItem, (DWORD_PTR(eType)));	// save type reference

				tvInsert.hParent = treeItem;
				dRef = eType->f_attrDefs;	// add attributes as children
				while (dRef) {
					sprintf(dsplyLine, "%-30s %s", " ", dRef->attRef->attrDefName);
					tvInsert.item.pszText = dsplyLine;
					subTreeItem = entityTree->InsertItem(&tvInsert);
					entityTree->SetItemData(subTreeItem, (DWORD_PTR(dRef)));
					dRef = dRef->s_defRefs;
				}
				dRef = eType->f_sysAttrs;	// add 'scripted' attributes as children
				while (dRef) {
					if (!dRef->entRef->deleted) {
						sprintf(dsplyLine, "%-30s %s", " ", dRef->entRef->entityTypeName);
						tvInsert.item.pszText = dsplyLine;
						subTreeItem = entityTree->InsertItem(&tvInsert);
						entityTree->SetItemData(subTreeItem, (DWORD_PTR(0)));
					}
					dRef = dRef->s_defRefs;
				}
				dRef = eType->f_owndSetRefs;		// add owned sets - greater indent
				while (dRef) {
					if (!dRef->setRef->deleted) {
						sprintf(dsplyLine, "%-60s %s", " ", dRef->setRef->setName);
						tvInsert.item.pszText = dsplyLine;
						subTreeItem = entityTree->InsertItem(&tvInsert);
						entityTree->SetItemData(subTreeItem, (DWORD_PTR(dRef)));
					}
					dRef = dRef->s_defRefs;
				}
				entityTree->Expand(treeItem, TVE_EXPAND);
			}
			else
				entityTree->SetItemData(treeItem, (DWORD_PTR(NULL)));

			eType = dbSchema->f_eTypes;		// pointer to first entity definition in schema
			while (eType) {
				if ((!eType->isSystemDefined) & (!eType->isProc) &(!eType->deleted)) {
					res = TRUE;

					tvInsert.hParent = TVI_ROOT;
					tvInsert.item.pszText = eType->entityTypeName;
					treeItem = entityTree->InsertItem(&tvInsert);
					if (firstVis == NULL)
						firstVis = treeItem;
					entityTree->SetItemData(treeItem, (DWORD_PTR(eType)));	// save type reference

					tvInsert.hParent = treeItem;
					dRef = eType->f_attrDefs;			// add attributes as children
					while (dRef) {
						if (!dRef->attRef->attrDefType->deleted) {
							sprintf(dsplyLine, "%-30s %s", " ", dRef->attRef->attrDefName);
							tvInsert.item.pszText = dsplyLine;
							subTreeItem = entityTree->InsertItem(&tvInsert);
							entityTree->SetItemData(subTreeItem, (DWORD_PTR(dRef)));
						}
						dRef = dRef->s_defRefs;
					}
					dRef = eType->f_owndSetRefs;		// add owned sets, also - greater indent
					while (dRef) {
						if (!dRef->setRef->deleted) {
							sprintf(dsplyLine, "%-60s %s", " ", dRef->setRef->setName);
							tvInsert.item.pszText = dsplyLine;
							subTreeItem = entityTree->InsertItem(&tvInsert);
							entityTree->SetItemData(subTreeItem, (DWORD_PTR(dRef)));
						}
						dRef = dRef->s_defRefs;
					}
					dRef = eType->f_mmbrSetRefs;		// add set memberships - even greater insent
					while (dRef) {
						if (!dRef->setRef->deleted) {
							sprintf(dsplyLine, "%-90s %s", " ", dRef->setRef->setName);
							tvInsert.item.pszText = dsplyLine;
							subTreeItem = entityTree->InsertItem(&tvInsert);
							entityTree->SetItemData(subTreeItem, (DWORD_PTR(dRef)));	// save type reference here, also...
						}
						dRef = dRef->s_defRefs;
					}
					entityTree->Expand(treeItem, TVE_EXPAND);
				}
				eType = eType->s_entityTypes;		// successor in set
			}

			eType = dbSchema->f_eTypes;		// now add procedures
			while (eType) {
				if (eType->isProc & !eType->isHidden & !eType->deleted) {
					dAttr = 0;
					dRef = eType->f_attrDefs;
					while (dRef) {
						dAttr = dRef->attRef;
						if (dAttr->returns)		// function ? - this does not work.. until parsed
							break;
						dRef = dRef->s_defRefs;
					}
					if (dAttr)
						sprintf(dsplyLine, "%s %-12s", "procedure", eType->entityTypeName);
						//sprintf(dsplyLine, "%s %-12s", "function", eType->entityTypeName);
					else
						sprintf(dsplyLine, "%s %-12s", "procedure", eType->entityTypeName);

					tvInsert.hParent = TVI_ROOT;
					tvInsert.item.pszText = dsplyLine;
					treeItem = entityTree->InsertItem(&tvInsert);
					entityTree->SetItemData(treeItem, (DWORD_PTR(eType)));	// save type reference
					tvInsert.item.pszText = dsplyLine;
					entityTree->Expand(treeItem, TVE_EXPAND);
				}
				eType = eType->s_entityTypes;		// successor in set
			}
		}
		dbSchema = dbSchema->s_dbSchemas;
	}
	res = entityTree->SelectSetFirstVisible(firstVis);
	return res;
}


void EASViewDlg::OnBnClickedEditDefn()		// edit entity definition
{
	// TODO: Add your control notification handler code here

	CTreeCtrl* entityTree;
	HTREEITEM selected;
	HTREEITEM parent;
	defRef* dRef;
	entityTypeDef* eType = NULL;
	setDef* sDef;
	CWnd* pWnd;


	entityTree = (CTreeCtrl*)GetDlgItem(IDC_TREE1);
	selected = entityTree->GetSelectedItem();
	if (selected == NULL)
		return;

	parent = entityTree->GetParentItem(selected);
	if (parent != NULL) {			// either attribute or set selected
		dRef = (defRef*)entityTree->GetItemData(selected);
		if (dRef->drType == ref_att)
			eType = (entityTypeDef*)entityTree->GetItemData(parent);	// edit the attribute's owner
		else
			sDef = dRef->setRef;
	}
	else
		eType = (entityTypeDef*)entityTree->GetItemData(selected);		// entity selected

	if (eType) {
		if (!eType->isProc) {
			EditEntTypDlg editDlg;
			editDlg.m_eType = eType;
			editDlg.DoModal();
		}
		else {
			NewProcDlg procDlg;
			procDlg.m_eType = eType;
			procDlg.DoModal();
		}
	}
	else {
		EditSetDlg editDlg;
		editDlg.m_set = sDef;
		editDlg.DoModal();
	}

	FillEntityTree(entityTree);		// refresh view
	
	pWnd = GetDlgItem(IDC_BUTTON1);
	pWnd->EnableWindow(FALSE);

	pWnd = GetDlgItem(IDC_BNVWDELTYPE);
	pWnd->EnableWindow(FALSE);
}


void EASViewDlg::OnBnClickedNewEntityType()		// Create new entity type definition
{
	// TODO: Add your control notification handler code here

	CTreeCtrl* entityTree;

	NewEntTypDlg NewTypDlg;
	NewTypDlg.DoModal();		// display the dialog

	entityTree = (CTreeCtrl*)GetDlgItem(IDC_TREE1);
	FillEntityTree(entityTree);
}


void EASViewDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	// TODO: Add your control notification handler code here

	CWnd* pWnd;
	entityTypeDef* eType = NULL;
	CTreeCtrl* entTree;
	HTREEITEM treeItem;
	HTREEITEM parent;
	attrDef* dAttr;
	defRef* dRef = NULL;
	BOOL isSet = FALSE;
	BOOL res = FALSE;
	CEdit* edit;
	CString descr;
	int len;
	setDef* sDef;

	edit = (CEdit*)GetDlgItem(IDC_VWDESCR);
	res = edit->GetModify();
	if (res) {							// changed description?
		edit->GetWindowText(descr);
		len = descr.GetLength();

		if (m_lastAttr) {
			dAttr = m_lastAttr;
			if (dAttr->attrDescription != NULL)
				delete dAttr->attrDescription;
			if (len > 0) {
				dAttr->attrDescription = new TCHAR[len + 1];
				res = StringCchCopy(dAttr->attrDescription, len + 1, (LPCTSTR)descr);
			}
		}
		if (m_lastEnt) {
			eType = m_lastEnt;
			if (eType->entDescription != NULL)
				delete eType->entDescription;
			if (len > 0) {
				eType->entDescription = new TCHAR[len + 1];
				res = StringCchCopy(eType->entDescription, len + 1, (LPCTSTR)descr);
			}
		}
		if (m_lastSet) {
			sDef = m_lastSet;
			if (sDef->setDescription != NULL)
				delete sDef->setDescription;
			if (len > 0) {
				sDef->setDescription = new TCHAR[len + 1];
				res = StringCchCopy(sDef->setDescription, len + 1, (LPCTSTR)descr);
			}
		}
	}

	m_lastEnt = NULL;
	m_lastAttr = NULL;
	m_lastSet = NULL;

	entTree = (CTreeCtrl*)GetDlgItem(IDC_TREE1);
	treeItem = entTree->GetSelectedItem();
	if (treeItem == NULL)
		return;

	parent = entTree->GetParentItem(treeItem);

	if (parent != NULL) {									// treeItem is a child - an attribute or set
		dRef = (defRef*)entTree->GetItemData(treeItem);
		if (dRef != NULL) {									// not 'scripted' ?
			if (dRef->drType == ref_att) {
				edit->SetWindowText(dRef->attRef->attrDescription);		// show attribute description..
				m_lastAttr = dRef->attRef;
			}
			else {
				edit->SetWindowText(dRef->setRef->setDescription);		// show set description..
				m_lastSet = dRef->setRef;
			}
			treeItem = parent;								// ..but prepare to get parent ItemData for edit
		}
		else {
			edit->SetWindowText(_T("system generated variable"));
			pWnd = GetDlgItem(IDC_BUTTON1);
			pWnd->EnableWindow(FALSE);
			pWnd = GetDlgItem(IDC_BNVWDELTYPE);
			pWnd->EnableWindow(FALSE);
			edit->EnableWindow(FALSE);
			return;
		}
	} else {
		eType = (entityTypeDef*)entTree->GetItemData(treeItem);
		edit->SetWindowText(eType->entDescription);			// show entity description
		m_lastEnt = eType;
	}

	pWnd = GetDlgItem(IDC_BUTTON1);							// edit definition
	pWnd->EnableWindow(TRUE);

	pWnd = GetDlgItem(IDC_BNVWDELTYPE);
	pWnd->EnableWindow(TRUE);
	if (eType != NULL) {
		if (eType->isSys)
			pWnd->EnableWindow(FALSE);			// cannot delete SYSTEM
	}
	if (m_lastAttr != NULL)
		pWnd->EnableWindow(FALSE);				// cannot directly delete attribute

	edit->EnableWindow(TRUE);

	*pResult = 0;
}


void EASViewDlg::OnBnClickedBnvwdeltype()
{
	// TODO: Add your control notification handler code here

	CTreeCtrl* entTree;
	HTREEITEM selected;
	HTREEITEM parent;
	defRef* dRef;
	entityTypeDef* eType = NULL;
	setDef* sDef;
	CString temp;

	entTree = (CTreeCtrl*)GetDlgItem(IDC_TREE1);
	selected = entTree->GetSelectedItem();
	if (selected == NULL)
		return;

	parent = entTree->GetParentItem(selected);
	if (parent != NULL) {			// either attribute or set selected
		dRef = (defRef*)entTree->GetItemData(selected);
		if (dRef->drType == ref_att)
			eType = (entityTypeDef*)entTree->GetItemData(parent);	// edit the attribute's owner entity
	}
	else
		eType = (entityTypeDef*)entTree->GetItemData(selected);

	if (eType) {
		temp = eType->entityTypeName;
		if (!eType->isProc) {
			if (AfxMessageBox(_T("Delete entity ") + temp, MB_OKCANCEL) == IDCANCEL)
				return;
		}
		else {
			if (AfxMessageBox(_T("Delete procedure ") + temp, MB_OKCANCEL) == IDCANCEL)
					return;
		}
		eType->deleted = true;		// just mark it...
	}
	else {
		sDef = dRef->setRef;
		temp = sDef->setName;
		if (AfxMessageBox(_T("Delete set ") + temp, MB_OKCANCEL) == IDCANCEL)
			return;
		sDef->deleted = true;
	}

	FillEntityTree(entTree);
}

/*
void EASViewDlg::OnEnKillfocusVwdescr()
{
	// TODO: Add your control notification handler code here
	CEdit* edit;
	attrDef* dAttr;
	entityTypeDef* eType;
	setDef* sDef;
	int len;
	CString descr;
	BOOL res;

	edit = (CEdit*)GetDlgItem(IDC_VWDESCR);
	res = edit->GetModify();
	//if (!edit->GetModify())
	//	return;

	edit->GetWindowText(descr);

	if (m_lastAttr) {
		dAttr = m_lastAttr;
		if (dAttr->attrDescription != NULL)
			delete dAttr->attrDescription;

		len = descr.GetLength();
		dAttr->attrDescription = new TCHAR[len + 1];
		res = StringCchCopy(dAttr->attrDescription, len + 1, (LPCTSTR)descr);
	}
	if (m_lastEnt) {
		eType = m_lastEnt;
		len = descr.GetLength();
//		if (!eType->isProc) {
			if (eType->entDescription != NULL)
				delete eType->entDescription;
			eType->entDescription = new TCHAR[len + 1];
			res = StringCchCopy(eType->entDescription, len + 1, (LPCTSTR)descr);
		//}
		//else {
		//	if (eType->procBody != NULL)
		//		delete eType->procBody;
		//	eType->procBody = new TCHAR[len + 1];
		//	res = StringCchCopy(eType->procBody, len + 1, (LPCTSTR)descr);
		//}
	}
	if (m_lastSet) {
		sDef = m_lastSet;
		if (sDef->setDescription != NULL)
			delete sDef->setDescription;

		len = descr.GetLength();
		sDef->setDescription = new TCHAR[len + 1];
		res = StringCchCopy(sDef->setDescription, len + 1, (LPCTSTR)descr);
	}
}
*/


void EASViewDlg::OnBnClickedButtonsave()
{
	// TODO: Add your control notification handler code here
	EASdbSchema* dbSchema;

	dbSchema = f_dbSchemas;
	while (dbSchema) {
		if ((!dbSchema->isSystemDefined) & (!dbSchema->isHidden))
			WriteEASEschema(dbSchema);
		dbSchema = dbSchema->s_dbSchemas;
	}
}


void EASViewDlg::OnBnClickedBtnnewent()
{
	// TODO: Add your control notification handler code here
	NewEntTypDlg NewTypDlg;
	CTreeCtrl* entityTree;

	NewTypDlg.DoModal();		// display the dialog

	entityTree = (CTreeCtrl*)GetDlgItem(IDC_TREE1);
	FillEntityTree(entityTree);
}


void EASViewDlg::OnBnClickedBtnnewset()
{
	// TODO: Add your control notification handler code here

	EditSetDlg NewSetDlg;
	CTreeCtrl* entityTree;
	
	NewSetDlg.m_set = NULL;
	NewSetDlg.DoModal();

	entityTree = (CTreeCtrl*)GetDlgItem(IDC_TREE1);
	FillEntityTree(entityTree);
}


void EASViewDlg::OnBnClickedBtnnewproc()
{
	// TODO: Add your control notification handler code here

	NewProcDlg procDlg;
	CTreeCtrl* entityTree;

	procDlg.m_eType = NULL;
	procDlg.DoModal();

	entityTree = (CTreeCtrl*)GetDlgItem(IDC_TREE1);
	FillEntityTree(entityTree);
}

// NewProcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EASE0002.h"
#include "NewProcDlg.h"
#include "afxdialogex.h"
#include "Strsafe.h"


// NewProcDlg dialog

IMPLEMENT_DYNAMIC(NewProcDlg, CDialogEx)

NewProcDlg::NewProcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NEWPROCDLG, pParent)
{

}

NewProcDlg::~NewProcDlg()
{
}

void NewProcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NewProcDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &NewProcDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &NewProcDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// NewProcDlg message handlers


BOOL NewProcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	CComboBox* dbSchemaList;
	int pos;
	EASdbSchema* dbSchema; 
	CWnd* pWnd;

	SetWindowText(_T("Edit procedure"));

	dbSchemaList = (CComboBox*)GetDlgItem(IDC_SELSCHEMA);
	dbSchema = f_dbSchemas;
	while (dbSchema) {
		if (!dbSchema->isHidden) {
			pos = dbSchemaList->AddString((LPCTSTR)dbSchema->dbName);
			dbSchemaList->SetItemData(pos, (DWORD_PTR)dbSchema);
			dbSchemaList->SetCurSel(pos);
		}
		dbSchema = dbSchema->s_dbSchemas;
	}

	if (m_eType) {		// existing ?
		pWnd = GetDlgItem(IDC_EDIT1);	// entity name edit control
		pWnd->SetWindowText(m_eType->entityTypeName);

		pWnd = GetDlgItem(IDC_SELSCHEMA);
		pWnd->EnableWindow(FALSE);		// cannot change this

		pWnd = GetDlgItem(IDC_EDITSRC);	// source code edit control

		CEdit* theEdit = (CEdit*)GetDlgItem(IDC_EDITSRC);

		// get the font the control is using
		CFont* pFont = theEdit->GetFont();
		TEXTMETRIC tm;

		// get the control's DC, too
		CDC* pDC = theEdit->GetDC();

		// Select the font that the control uses by default into the DC. 
		// We must do this because the control may or may not be using 
		// that font at this exact moment
		CFont* pOldFont = pDC->SelectObject(pFont);

		// Retrieve text metrics for that font and return the previously 
		// selected font.
		pDC->GetTextMetrics(&tm);
		pDC->SelectObject(pOldFont);

		// Get an identity rectangle and map it to dialog units
		CRect rect(0, 0, 100, 1);
		::MapDialogRect((HWND)this, rect);

		// We now know that 100 dialog units are rect.Width() screen units, 
		// so we can multiply screen units by 100 and divide by rect.Width() 
		// to find dialog units from screen units. tm.tmAveCharWidth is 
		// the width of _one_ character, so setting the tabs at every 
		// four characters means we also multiply by four.
		int res = theEdit->SetTabStops((4 * tm.tmAveCharWidth * 100) / rect.Width());

		pWnd->SetWindowText(m_eType->procBody);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void NewProcDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	CWnd* pWnd;
	CString procName;
	int len;
	entityTypeDef* eType;
	CEdit* edit;
	CString src;
	CComboBox* dbSchemaList;
	int pos;
	EASdbSchema* dbSchema;
	entityTypeDef* ent;

	if (!m_eType) {			// new?
		pWnd = GetDlgItem(IDC_EDIT1);	// entity name edit control
		GetDlgItemText(IDC_EDIT1, procName);
		if (procName == "") {
			AfxMessageBox(_T("No name specified"), MB_OK, 0);
			return;
		}

		dbSchemaList = (CComboBox*)GetDlgItem(IDC_SELSCHEMA);
		pos = dbSchemaList->GetCurSel();
		if (pos == CB_ERR) {
			AfxMessageBox(_T("No subsystem selected"), MB_OK, 0);
			return;
		}
		dbSchema = (EASdbSchema*)dbSchemaList->GetItemData(pos);

		eType = (entityTypeDef*)calloc(1, sizeof(entityTypeDef));
		eType->isProc = TRUE;

		ent = dbSchema->f_eTypes;
		if (ent) {
			while (ent->s_entityTypes) ent = ent->s_entityTypes;
			ent->s_entityTypes = eType;								// file last...
		}
		else
			dbSchema->f_eTypes = eType;

		m_eType = eType;
	}

	pWnd = GetDlgItem(IDC_EDIT1);	// entity name edit control
	GetDlgItemText(IDC_EDIT1, procName);
	if (m_eType->entityTypeName != NULL)
		delete m_eType->entityTypeName;
	len = procName.GetLength();
	m_eType->entityTypeName = new TCHAR[len + 1];
	StringCchCopy(m_eType->entityTypeName, len + 1, (LPCTSTR)procName);

	pWnd = GetDlgItem(IDC_EDITSRC);	// source code edit control
	edit = (CEdit*)GetDlgItem(IDC_EDITSRC);
	if (edit->GetModify()) {
		edit->GetWindowText(src);

		if (m_eType->procBody != NULL)
			delete m_eType->procBody;

		len = src.GetLength();
		m_eType->procBody = new TCHAR[len + 1];
		StringCchCopy(m_eType->procBody, len + 1, (LPCTSTR)src);
	}
	CDialogEx::OnOK();
}


void NewProcDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

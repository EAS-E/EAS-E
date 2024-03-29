// NewProjectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EASE0002.h"
#include "NewProjectDlg.h"
#include "afxdialogex.h"
#include "Strsafe.h"
#include "stdio.h"
#include "EaseData.h"


// NewProjectDlg dialog

IMPLEMENT_DYNAMIC(NewProjectDlg, CDialogEx)

NewProjectDlg::NewProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_NEWPROJECTDLG, pParent)
{

}

NewProjectDlg::~NewProjectDlg()
{
}

void NewProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NewProjectDlg, CDialog)
	ON_BN_CLICKED(IDOK, &NewProjectDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_LOCBROWSE, &NewProjectDlg::OnBnClickedLocbrowse)
END_MESSAGE_MAP()


// NewProjectDlg message handlers


void NewProjectDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	CString path;
	CString name;
	CString filename;
	CStdioFile projfile;
	CString txt;
	CStdioFile file;
	BOOL fail = false;
	EASdbSchema* dbSchema;
	entityTypeDef* eType;
	int len;
	TCHAR* zero = 0;
	

	GetDlgItemText(IDC_PROJNAME, name);
	if (name == "") {
		AfxMessageBox(_T("Must specify a valid name"), MB_OK);
		return;
	}

	dbSchema = (EASdbSchema*)calloc(1, sizeof(EASdbSchema));
	f_dbSchemas->s_dbSchemas = dbSchema;	// only 1 exists - easetypes
	dbSchema->dbName = new TCHAR[11];
	StringCchCopy(dbSchema->dbName, 11, name);
	GetDlgItemText(IDC_PROJID, txt);
	dbSchema->dbID = _tcstol(txt, &zero, 10);

	GetDlgItemText(IDC_LOCATION, path);
	path = path + name;

	if (!CreateDirectory(path, NULL)) {
		AfxMessageBox(_T("Cannot create folder") + path, MB_OK);
		return;
	}
	if (!file.Open(path + _T("\\project.eas"), CFile::modeCreate | CFile::modeWrite)) {
		AfxMessageBox(_T("Cannot create project file"), MB_OK);
		return;
	}
	file.WriteString(path + _T("\\gen\\"));
	file.WriteString(_T("\n"));	// why is this needed?
	file.WriteString(name);
	file.Close();

	if (!CreateDirectory(path + _T("\\gen"), NULL)) {
		AfxMessageBox(_T("Cannot create gen folder") + path, MB_OK);
		return;
	}

	filename = path + _T("\\") + name + _T(".xml");
	len = filename.GetLength();
	dbSchema->schemaFilename = new TCHAR[len + 1];
	StringCchCopy(dbSchema->schemaFilename, len + 1, filename);
	eType = (entityTypeDef*)calloc(1, sizeof(entityTypeDef));		// create empty THE SYSTEM entity definition
	eType->dbRef = dbSchema;
	dbSchema->theSystem = eType;
	eType->entityTypeName = new TCHAR[7];
	StringCchCopy(eType->entityTypeName, 7, _T("SYSTEM"));
	eType->isSys = TRUE;

	CDialog::OnOK();
}


void NewProjectDlg::OnBnClickedLocbrowse()
{
	// TODO: Add your control notification handler code here

	CFolderPickerDialog dlg(m_path, 0, NULL, 0);
	if (dlg.DoModal() == IDOK) {
		m_path = dlg.GetPathName() +_T("\\");
		SetDlgItemText(IDC_LOCATION, m_path);
	}
}


BOOL NewProjectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	SetWindowText(_T("New project creation dialog"));
	SetDlgItemText(IDC_LOCATION, m_path);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

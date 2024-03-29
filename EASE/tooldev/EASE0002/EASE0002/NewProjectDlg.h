#pragma once


// NewProjectDlg dialog

class NewProjectDlg : public CDialog
{
	DECLARE_DYNAMIC(NewProjectDlg)

public:
	NewProjectDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~NewProjectDlg();

public:
	CString m_path;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWPROJECTDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedLocbrowse();
	virtual BOOL OnInitDialog();
};

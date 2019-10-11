#pragma once


// NewEntTypDlg dialog

class NewEntTypDlg : public CDialog
{
	DECLARE_DYNAMIC(NewEntTypDlg)

public:
	NewEntTypDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~NewEntTypDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWTYPDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeList1();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedCheck3();
};

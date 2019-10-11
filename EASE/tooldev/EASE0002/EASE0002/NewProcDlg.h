#pragma once
#include "EaseData.h"


// NewProcDlg dialog

class NewProcDlg : public CDialogEx
{
	DECLARE_DYNAMIC(NewProcDlg)

public:
	NewProcDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~NewProcDlg();
	entityTypeDef* m_eType;


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWPROCDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};

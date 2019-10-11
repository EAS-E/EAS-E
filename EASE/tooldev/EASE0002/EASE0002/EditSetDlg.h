#pragma once


// EditSetDlg dialog

class EditSetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(EditSetDlg)

public:
	EditSetDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~EditSetDlg();

public:
	setDef* m_set;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDITSETDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonadd();
	afx_msg void OnCbnSelchangeCombodispln();
	afx_msg void OnLbnSelchangeListrankatts();
	afx_msg void OnBnClickedDownorder();
	afx_msg void OnBnClickedSetpersist();
};

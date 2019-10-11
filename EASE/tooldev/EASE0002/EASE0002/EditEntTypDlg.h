#pragma once
#include "EaseData.h"


// EditEntTypDlg dialog

class EditEntTypDlg : public CDialogEx
{
	DECLARE_DYNAMIC(EditEntTypDlg)

public:
	EditEntTypDlg(CWnd* pParent = NULL);   // standard constructor
	EditEntTypDlg(entityTypeDef* eType, CWnd* pParent);
	virtual ~EditEntTypDlg();

public:
	entityTypeDef* m_eType;
	attrDef* m_lastSelAttr;					// most recently selected attribute

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDITENTTYPDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedAttrDel();
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnLbnSelchangeListosets();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEditattrdesc();
	afx_msg void OnEnKillfocusEditattrdesc();
	afx_msg void OnEnSetfocusEditattrdesc();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeAttdims();
	afx_msg void OnStnClickedStaticsets();
	afx_msg void OnLbnSelchangeListmsets();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnSetfocusEdit3();
	afx_msg void OnEnKillfocusEdit3();
	afx_msg void OnBnClickedEntpersist();
};

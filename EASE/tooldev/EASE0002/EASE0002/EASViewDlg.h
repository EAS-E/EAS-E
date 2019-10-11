#pragma once
#include "EaseData.h"


// EASViewDlg dialog

class EASViewDlg : public CDialog
{
	DECLARE_DYNAMIC(EASViewDlg)

public:
	EASViewDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~EASViewDlg();

public:
	entityTypeDef* m_lastEnt;			// most recently selected entity
	attrDef* m_lastAttr;				// most recently selected attribute
	setDef* m_lastSet;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EASVIEWDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedEditDefn();
	afx_msg void OnBnClickedNewEntityType();
	afx_msg void OnEnKillfocusVwdescr();
	afx_msg void OnTvnSelchangedTree2(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnBnClickedEditSysAttrs();
	afx_msg void OnBnClickedBrowseInstances();
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBrowseset();
	afx_msg void OnBnClickedBnvwfileremove();
	afx_msg void OnBnClickedBnvwcreatdest();
	afx_msg void OnBnClickedBnvwdeltype();
	afx_msg void OnBnClickedBnvwsearch();
	afx_msg void OnBnClickedButtonsave();
	afx_msg void OnBnClickedBtnnewent();
	afx_msg void OnBnClickedBtnnewset();
	afx_msg void OnBnClickedBtnnewproc();
};

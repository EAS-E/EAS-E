
// EASE0002.h : main header file for the EASE0002 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CEASE0002App:
// See EASE0002.cpp for the implementation of this class
//

class CEASE0002App : public CWinApp
{
public:
	CEASE0002App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnViewSystem();
	afx_msg void OnSaveSaveEASschema();
	afx_msg void OnFileImport();
	afx_msg void OnProjectSelect();
	afx_msg void OnProjectClose();
	afx_msg void OnProjectNew();
};

extern CEASE0002App theApp;
extern CString ProjectsDirectory;


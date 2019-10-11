
// DevTRAN.h : main header file for the DevTRAN application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CDevTRANApp:
// See DevTRAN.cpp for the implementation of this class
//

class CDevTRANApp : public CWinApp
{
public:
	CDevTRANApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFileOpenproject();
};

extern CDevTRANApp theApp;

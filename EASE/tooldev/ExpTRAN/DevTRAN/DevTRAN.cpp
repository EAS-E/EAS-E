
// DevTRAN.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "DevTRAN.h"
#include "MainFrm.h"
#include "Strsafe.h"
#include "stdio.h"

#include "easlib.h"
#include "EASEmain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString ProjectsDirectory;
CString SysdataDirectory;

// CDevTRANApp

BEGIN_MESSAGE_MAP(CDevTRANApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CDevTRANApp::OnAppAbout)
	ON_COMMAND(ID_FILE_OPENPROJECT, &CDevTRANApp::OnFileOpenproject)
END_MESSAGE_MAP()


// CDevTRANApp construction

CDevTRANApp::CDevTRANApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("DevTRAN.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CDevTRANApp object

CDevTRANApp theApp;


// CDevTRANApp initialization

BOOL CDevTRANApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));


	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// create and load the frame with its resources
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->SetWindowText(_T("EAS-E translate-to-C"));
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	CStdioFile projfile;

/*
	was having some difficulty establishing 'current directory'...
	TCHAR buff[128];
	GetCurrentDirectory(127, buff);
	if (projfile.Open((LPCTSTR)(_T("C:\\EASEprojects\\dir.txt")), CFile::modeCreate | CFile::modeWrite)) {
		projfile.WriteString(buff);
		projfile.Close();
	}
*/

	if (projfile.Open((LPCTSTR)(_T("config.dat")), CFile::modeRead)) {
		projfile.ReadString(ProjectsDirectory);
		projfile.ReadString(SysdataDirectory);
		projfile.Close();
	}

	CDevTRANApp::OnFileOpenproject();		// bring up project selection dialog

	return TRUE;
}

int CDevTRANApp::ExitInstance()
{
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CDevTRANApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CDevTRANApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CDevTRANApp message handlers


void CDevTRANApp::OnFileOpenproject()
{
	// TODO: Add your command handler code here

	int errs;

	CFolderPickerDialog dlg(ProjectsDirectory, 0, NULL, 0);
	if (dlg.DoModal() != IDOK)
		return;

	ProjectsDirectory = dlg.GetPathName() + _T("\\");

	easinit();
	errs = EASECOMPILE(E_TXTLIT_F(ProjectsDirectory.GetBuffer()), E_TXTLIT_F(SysdataDirectory.GetBuffer()));

	if (errs < 0)
		AfxMessageBox(_T("Not a valid EASE project selection"), MB_OK, 0);

	if (errs > 0)
		AfxMessageBox(_T("Compilation errors - see listing"), MB_OK, 0);

	PostQuitMessage(errs);
}

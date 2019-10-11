
// EASE0002.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "EASE0002.h"
#include "MainFrm.h"
#include "Strsafe.h"
#include "stdio.h"

#include "EASE0002Doc.h"
#include "EASE0002View.h"
#include "NewEntTypDlg.h"
#include "EaseData.h"
#include "EASViewDlg.h"
#include "EditSetDlg.h"
#include "NewProcDlg.h"
#include "NewProjectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString ProjectsDirectory;
CString SysdataDirectory;

// CEASE0002App

BEGIN_MESSAGE_MAP(CEASE0002App, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CEASE0002App::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_NEW_FILE, &CWinApp::OnFileNew)
	ON_COMMAND(ID_OPEN_FILE, &CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
	ON_COMMAND(ID_VIEW_SYSTEM, &CEASE0002App::OnViewSystem)
	ON_COMMAND(ID_SAVE_SAVEDATABASE, &CEASE0002App::OnSaveSaveEASschema)
	ON_COMMAND(ID_FILE_IMPORT, &CEASE0002App::OnFileImport)
	ON_COMMAND(ID_PROJECT_SELECT, &CEASE0002App::OnProjectSelect)
	ON_COMMAND(ID_PROJECT_CLOSE, &CEASE0002App::OnProjectClose)
	ON_COMMAND(ID_PROJECT_NEW32793, &CEASE0002App::OnProjectNew)
END_MESSAGE_MAP()


// CEASE0002App construction

CEASE0002App::CEASE0002App()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("EASE0002.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CEASE0002App object

CEASE0002App theApp;


// CEASE0002App initialization

BOOL CEASE0002App::InitInstance()
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
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)


	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CEASE0002Doc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CEASE0002View));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->SetWindowText(_T("EAS-E project developer"));
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

//	TCHAR buff[128];
//	GetCurrentDirectory(127, buff);

	CStdioFile projfile;

	if (projfile.Open((LPCTSTR)"config.dat", CFile::modeRead)) {
		projfile.ReadString(ProjectsDirectory);
		projfile.ReadString(SysdataDirectory);
		projfile.Close();
	}
	ReadEASEschema(SysdataDirectory, _T("easetypes"), false);

	return TRUE;
}

int CEASE0002App::ExitInstance()
{
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CEASE0002App message handlers


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
void CEASE0002App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CEASE0002App message handlers

// App command to run the dialog
void CEASE0002App::OnViewSystem()
{
	FixUpEASEschemas();
	
	EASViewDlg EASViewDlg;
	EASViewDlg.DoModal();
}


void CEASE0002App::OnSaveSaveEASschema()
{
	// TODO: Add your command handler code here

	EASdbSchema* dbSchema;

	dbSchema = f_dbSchemas;
	while (dbSchema) {
		if ((!dbSchema->isSystemDefined) & (!dbSchema->isHidden))
			WriteEASEschema(dbSchema);
		dbSchema = dbSchema->s_dbSchemas;
	}
}


void CEASE0002App::OnFileImport()
{
	// TODO: Add your command handler code here

	CString pathname;

	AfxMessageBox(_T("Not yet supported."), MB_OK);
	return;

	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK) {
		pathname = dlg.GetPathName();
		ReadEASEschema(pathname, NULL, TRUE);
	}
}


void CEASE0002App::OnProjectSelect()
{
	// TODO: Add your command handler code here

	CString path;
	CString filename;
	CStdioFile projfile;
	CString temp;
	CStdioFile file;
	BOOL neof;

	if (f_dbSchemas->s_dbSchemas != NULL) {
		AfxMessageBox(_T("A project is already open; restart"), MB_OK); // more than just easetypes loaded..
		return;
	}

	CFolderPickerDialog dlg(ProjectsDirectory, 0, NULL, 0);
	if (dlg.DoModal() == IDOK) {
		path = dlg.GetPathName() + _T("\\");
		filename = path + _T("project.eas");
		if (!projfile.Open(filename, CFile::modeRead)) {
			AfxMessageBox(_T("Cannot open project file"), MB_OK);
			return;
		}
		else {
			neof = projfile.ReadString(temp);	// .. discard gen folder path

			while (neof) {
				neof = projfile.ReadString(temp);	// read source file name
				if (!temp.IsEmpty()) {
					filename = temp;
					ReadEASEschema(path, filename, false);
				}
			}
			CEASE0002App::OnViewSystem();	// display the table view
		}
	}
}


void CEASE0002App::OnProjectClose()
{
	// TODO: Add your command handler code here

	AfxMessageBox(_T("Not implemented; restart application"), MB_OK);

}


void CEASE0002App::OnProjectNew()
{
	// TODO: Add your command handler code here

	NewProjectDlg projDlg;
	projDlg.m_path = ProjectsDirectory;
	if (projDlg.DoModal() == IDOK)
		CEASE0002App::OnViewSystem();	// display the table view
}

// Downright.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Downright.h"
#include "SettingsDlg.h"
#include "DownrightDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDownrightApp

BEGIN_MESSAGE_MAP(CDownrightApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDownrightApp construction

CDownrightApp::CDownrightApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CDownrightApp object

CDownrightApp theApp;


// CDownrightApp initialization

BOOL CDownrightApp::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();
	SetRegistryKey(_T("Shergin lab"));

	theProperties.Load();
	//CSettingsDlg dlg;
	CDownrightDlg dlg;

	m_pMainWnd=&dlg;
	m_Identify.Load(theProperties.m_FileName);
	dlg.m_pIdentify=&m_Identify;
	INT_PTR nResponse = dlg.DoModal();
	m_Identify.Save(theProperties.m_FileName);
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	theProperties.Save();
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.

	return FALSE;
}

// DownrightKeyGeneratorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DownrightKeyGenerator.h"
#include "DownrightKeyGeneratorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "../properties.h"
#include ".\downrightkeygeneratordlg.h"

// CDownrightKeyGeneratorDlg dialog



CDownrightKeyGeneratorDlg::CDownrightKeyGeneratorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDownrightKeyGeneratorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDownrightKeyGeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
CDialog::DoDataExchange(pDX);
DDX_Control(pDX, IDC_USERNAME, m_cUserName);
DDX_Control(pDX, IDC_HARDWARE, m_cHardware);
DDX_Control(pDX, IDC_SERIALNUMBER, m_cSerialNumber);
DDX_Control(pDX, IDC_INFO, m_cInfo);
}

BEGIN_MESSAGE_MAP(CDownrightKeyGeneratorDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_USERNAME, OnEnChangeUsername)
	ON_EN_CHANGE(IDC_HARDWARE, OnEnChangeHardware)
//	ON_EN_KILLFOCUS(IDC_INFO, OnEnKillfocusInfo)
ON_WM_KILLFOCUS()
END_MESSAGE_MAP()


// CDownrightKeyGeneratorDlg message handlers

BOOL CDownrightKeyGeneratorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDownrightKeyGeneratorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDownrightKeyGeneratorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDownrightKeyGeneratorDlg::OnEnChangeUsername()
	{
	CString hardware,username;
	m_cHardware.GetWindowText(hardware);
	m_cUserName.GetWindowText(username);
	CProperties obj;
	m_cSerialNumber.SetWindowText(obj.GetKeyEx(hardware,username));
	CString info=_T("User name: ")+username+_T("\r\nHardware ID: ")+hardware+_T("\r\nKey: ")+obj.GetKeyEx(hardware,username);
	m_cInfo.SetWindowText(info);
	}

void CDownrightKeyGeneratorDlg::OnEnChangeHardware()
	{
	OnEnChangeUsername();
	}


void CDownrightKeyGeneratorDlg::OnKillFocus(CWnd* pNewWnd)
	{
	CDialog::OnKillFocus(pNewWnd);
	CString s;
	m_cInfo.GetWindowText(s);
	if(!s.IsEmpty())m_cInfo.Copy();
	}

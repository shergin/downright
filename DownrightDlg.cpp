// DownrightDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Downright.h"
#include "DownrightDlg.h"

//#include "uxtheme.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


UINT UWM_MOUSEMOVE = ::RegisterWindowMessage(UWM_DOWNRIGHT_MIRROR_MSG);

// CDownrightDlg dialog

CDownrightDlg::CDownrightDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDownrightDlg::IDD, pParent)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bHookActive=0;
	m_pSettingsDlg=NULL;
}

void CDownrightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDownrightDlg, CDialog)
	ON_REGISTERED_MESSAGE(UWM_MOUSEMOVE, OnMouseMirror)


	ON_MESSAGE(WM_SYSTRAY,OnSysTray)
	ON_MESSAGE(WM_SETTINGS_DLG_MESSAGE,OnSettingsDlg)
	ON_MESSAGE(WM_IDENTIFY,OnIdentify)

	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_COMMAND(IDM_SYSTRAY_SHOW, OnShow)
	ON_WM_CLOSE()
	ON_COMMAND(IDM_SYSTRAY_EXIT, OnSystrayExit)
	ON_WM_TIMER()
	ON_COMMAND(IDM_SYSTRAY_ENABLE, OnEnable)
END_MESSAGE_MAP()


// CDownrightDlg message handlers


UINT LogoDialogThread(LPVOID pParam)
{
	CIntroDialog dlg;
	dlg.DoModal();
	return 0;
}


BOOL CDownrightDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_pIdentify->m_hServerWnd=GetSafeHwnd();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	//SetIcon(m_hIcon, TRUE);			// Set big icon
	//SetIcon(m_hIcon, FALSE);		// Set small icon

	SendMessage(WM_CLOSE,0,0);
	MoveWindow(-100,-100,50,50,true);

	// TODO: Add extra initialization here


	// добавляем иконку в трей
	NOTIFYICONDATA nid;
	memset(&nid, 0, sizeof(nid));//??
	nid.cbSize=sizeof(nid);
	nid.hWnd=GetSafeHwnd();
	nid.uID=SYSTRAYICONID;
	nid.uCallbackMessage=WM_SYSTRAY;
	lstrcpyn(nid.szTip,_T("downright blackrain"),sizeof(nid.szTip)/sizeof(nid.szTip[0]));
	
	//nid.hIcon=AfxGetApp()->LoadIcon(IDI_SYSTRAY);
	m_SysTrayIcon[0]=(HICON)::LoadImage(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_SYSTRAY0),IMAGE_ICON,16,16,0);
	m_SysTrayIcon[1]=(HICON)::LoadImage(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_SYSTRAY1),IMAGE_ICON,16,16,0);
	if(m_bHookActive)
		nid.hIcon=m_SysTrayIcon[0];
	else
		nid.hIcon=m_SysTrayIcon[1];
	nid.uFlags=NIF_ICON | NIF_TIP | NIF_MESSAGE;
	BOOL bTray=Shell_NotifyIcon(NIM_ADD,&nid);



	SetTimer(1001,600,NULL);
	//SetTimer(1002,60000,NULL);

	OnEnable();
	if(theProperties.m_ShowSplash!=0)AfxBeginThread(LogoDialogThread,this,THREAD_PRIORITY_NORMAL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}
void CDownrightDlg::OnTimer(UINT nIDEvent)
{
	if(nIDEvent==1001)
		SendMessage(WM_CLOSE);
	if(nIDEvent==1002)
		Exit();
	CDialog::OnTimer(nIDEvent);
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDownrightDlg::OnPaint() 
{
/*	if (IsIconic())
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
	}*/
	CDialog::OnPaint();
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDownrightDlg::OnQueryDragIcon()
{
	return NULL;
	//return static_cast<HCURSOR>(m_hIcon);
}


LRESULT CDownrightDlg::OnMouseMirror(WPARAM wParam, LPARAM lParam)
{
	m_pIdentify->NextPoint(wParam,lParam);

	//TRACE("Mirror: %i, %i \n",(SHORT)wParam,lParam);

	//if(wParam==2)Beep(100,100);
	
	//SHORT key;
	//key=GetKeyState(MK_RBUTTON);
	//CString s;
	//s.Format("GMM! %u, [%u] \n",(long)wParam,GetKeyState(MK_RBUTTON));
	//TRACE(s);

	//if((IsTopParentActive())&&(!IsIconic())&&(m_ActiveGroup==1)&&(IsWindowVisible())&&(m_0_cSymbolEdit.GetCheck()==1))
	//	lParam=NULL;
	
	//m_pIdentify->NextPoint(pt.x, pt.y, (long)wParam, (HWND)lParam);
	return 0;
}


// обработка сообщений от трея
LONG CDownrightDlg::OnSysTray(UINT wParam, LONG lParam)
{
	static bool bMenuShow=false;
	if(bMenuShow)return 0;
	if(wParam==SYSTRAYICONID)// моя иконка
	{
		switch(lParam)
		{
		case WM_CONTEXTMENU:
		case WM_RBUTTONDOWN:
			{
				HMENU hMenu=::LoadMenu(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDR_SYSTRAYMENU));
				if(!hMenu)return 1;
				HMENU hPopup=::GetSubMenu(hMenu,0);
				//HMENU hEnable=::GetSubMenu(hMenu,2);
				if(!hPopup)return 1;
				theProperties.m_Language.LocalizationMenu(hPopup,IDR_SYSTRAYMENU);
				if(m_bHookActive)
					::CheckMenuItem(hPopup,IDM_SYSTRAY_ENABLE,MF_CHECKED);
				//if(m_pSettingsDlg)
				//	::EnableMenuItem(hPopup,IDM_SYSTRAY_SHOW,MF_GRAYED);
				::SetForegroundWindow(GetSafeHwnd());
				POINT pt;
				::GetCursorPos(&pt);
				bMenuShow=true;
				::TrackPopupMenu(hPopup, 0, pt.x, pt.y, 0, GetSafeHwnd(), NULL);
				::DestroyMenu(hMenu);
				bMenuShow=false;
			}
		break;
		case WM_LBUTTONDBLCLK:
			OnShow();
		break;
		}
	}
	return 0;
}
void CDownrightDlg::Exit(void)
{
	if(m_pSettingsDlg)
	{
		m_pSettingsDlg->OnCancel();
	}
	if(m_bHookActive)
	{
		clearMyHook(m_hWnd);
		m_bHookActive=false;
	}
	NOTIFYICONDATA nid;
	memset(&nid, 0, sizeof(nid));
	nid.cbSize=sizeof(nid);
	nid.hWnd=GetSafeHwnd();
	nid.uID=SYSTRAYICONID;
	Shell_NotifyIcon(NIM_DELETE,&nid);

	DestroyIcon(m_SysTrayIcon[0]);
	DestroyIcon(m_SysTrayIcon[1]);
	
	OnOK();
}

void CDownrightDlg::OnBnClickedCancel()
{Exit();}
void CDownrightDlg::OnBnClickedOk()
{Exit();}


////////////////////////////////////////////////////////////////////////
// Settings dialog thread //////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

UINT SettingsDialogThread(LPVOID pParam)
{
	TRACE("Settings dialog thread [start]\n");
	CDownrightDlg* pThisDialog=static_cast<CDownrightDlg*>(pParam);
	CSettingsDlg dlg;
	pThisDialog->m_pSettingsDlg=&dlg;
	dlg.m_pServer=pThisDialog;
	dlg.m_pIdentify=pThisDialog->m_pIdentify;
	dlg.m_ActiveSystemInFirstMoment=pThisDialog->m_bHookActive;
	dlg.DoModal();
	pThisDialog->m_pSettingsDlg=NULL;
	// сохраняем настройки
	pThisDialog->m_pIdentify->Save(theProperties.m_FileName);
	theProperties.Save();
	TRACE("Settings dialog thread [finish]\n");
	return 0;
}

void CDownrightDlg::OnShow()
{
	if(m_pSettingsDlg)
	{
		m_pSettingsDlg->SetForegroundWindow();
	}
	else
	{
		AfxBeginThread(SettingsDialogThread,this,THREAD_PRIORITY_NORMAL);
	}
}
LONG CDownrightDlg::OnSettingsDlg(UINT wParam, LONG lParam)
{
	switch(wParam)
	{
		case 0: // установить режим активности
			SetSystemActivity(lParam);
		break;
		case 1: // обновить параметры хука
			if(m_bHookActive)
			{
				unsigned int up, down, key;
				CreateHookParam(up,down,key);
				setHookParam(down,up,key);
				SetHookOutcast();
			}
		break;
		case 2: // обновить только список игнорируемых прог
			if(m_bHookActive)
			{
				SetHookOutcast();
			}
		break;
	}
	return 0;
}
void CDownrightDlg::OnClose() // изменить на случай вырубания компа
{ShowWindow(SW_HIDE);}

void CDownrightDlg::OnSystrayExit()
{
	Exit();
}


void CDownrightDlg::OnEnable()
{
	SetSystemActivity(!m_bHookActive);
}

void CDownrightDlg::CreateHookParam(unsigned int &up, unsigned int &down, unsigned int &key)
{
	switch(theProperties.m_MouseButton)
	{
		case 0: // right
			up=WM_RBUTTONUP;
			down=WM_RBUTTONDOWN;
		break;
		case 1: // left
			up=WM_LBUTTONUP;
			down=WM_LBUTTONDOWN;
		break;
		case 2: // middle
			up=WM_MBUTTONUP;
			down=WM_MBUTTONDOWN;
		break;
	}
	switch(theProperties.m_DisableKey)
	{
		case 0:key=0x0100;break; // none
		case 1:key=MK_CONTROL;break; // ctrl
		case 2:key=MK_SHIFT;break; // shift
	}
}

void CDownrightDlg::SetHookOutcast()
{
	static CString old;
	if(old==theProperties.m_IgnoreProgram)return;
	old=theProperties.m_IgnoreProgram;
	const TCHAR* buffer=(LPCTSTR)old;
	setOutcast(const_cast<TCHAR*>(buffer));
}

BOOL CDownrightDlg::SetSystemActivity(int activity)
{
	if(m_bHookActive==activity)return 1;
	if(activity)
	{
		unsigned int up, down, key;
		SetHookOutcast();
		CreateHookParam(up,down,key);
		m_bHookActive=setMyHook(m_hWnd,down,up,key)!=0;
		if(!m_bHookActive)
			ShowSysTrayBalloon(_lng(_T("SystemTray-Error-Title")),_lng(_T("SystemTray-Error-Hook")),NIIF_ERROR);
	}
	else
	{
		clearMyHook(m_hWnd);
		m_bHookActive=false;
	}
	if(m_pSettingsDlg)
	{
		m_pSettingsDlg->m_2_cSystemActive.SetCheck(m_bHookActive);
	}
	NOTIFYICONDATA nid;
	memset(&nid, 0, sizeof(nid));//??
	nid.cbSize=sizeof(nid);
	nid.hWnd=GetSafeHwnd();
	nid.uID=SYSTRAYICONID;
	if(m_bHookActive)
		nid.hIcon=m_SysTrayIcon[0];
	else
		nid.hIcon=m_SysTrayIcon[1];
	nid.uFlags=NIF_ICON;
	Shell_NotifyIcon(NIM_MODIFY,&nid);
	return 0;
}

void CDownrightDlg::ShowSysTrayBalloon(CString title, CString text, int type)
{
	NOTIFYICONDATA nid;

	memset(&nid, 0, sizeof(nid));//??
	nid.cbSize=sizeof(nid);
	nid.hWnd=GetSafeHwnd();
	nid.uID=SYSTRAYICONID;

	lstrcpyn(nid.szInfo,text,sizeof(nid.szInfo)/sizeof(nid.szInfo[0]));
	lstrcpyn(nid.szInfoTitle,title,sizeof(nid.szInfoTitle)/sizeof(nid.szInfoTitle[0]));

	nid.dwInfoFlags=type;
	nid.uTimeout=10000;
	nid.uFlags=NIF_INFO;
	Shell_NotifyIcon(NIM_MODIFY,&nid);
} 

LRESULT CDownrightDlg::OnIdentify(WPARAM wParam, LPARAM lParam)
{
	CGesture* pGesture=(CGesture*)lParam;
	switch(wParam)
	{
		case 1: //распознано
			if(theProperties.m_ShowBalloon)
				ShowSysTrayBalloon(_lng(_T("SystemTray-Identify-Title")),pGesture->m_Name,NIIF_INFO);
		break;
	}
	return 0;
}

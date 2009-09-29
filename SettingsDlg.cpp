// SettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Downright.h"
#include "SettingsDlg.h"
#include ".\settingsdlg.h"
//#include ".\settingsdlg.h"

#include "key.h"

//#include "uxtheme.h"

// CSettingsDlg dialog

IMPLEMENT_DYNAMIC(CSettingsDlg, CDialog)
CSettingsDlg::CSettingsDlg(CWnd* pParent /*=NULL*/)
: CDialog(CSettingsDlg::IDD, pParent)
	{
	m_hIcon=AfxGetApp()->LoadIcon(IDI_SYSTRAY0);
	TRACE(_T("====================== \n"));
	TRACE(_T("====================== Constructor \n"));
	TRACE(_T("====================== \n"));
	m_ActiveGestureNumber=-1;
	m_bControlSettings=false;
	m_AddSymbolState=0;
	m_bDraw=0;
	m_ActiveSystemInFirstMoment=0;
	m_pServer=NULL;
	int i=0;
	for(i=0;i<4;i++)m_Position[i]=-1;
	for(i=0;i<5;i++)m_static[i]=-1;
	m_static[0]=0;
	m_2_pExplorer=NULL;
	}

CSettingsDlg::~CSettingsDlg()
	{
	TRACE(_T("====================== \n"));
	TRACE(_T("====================== Destructor \n"));
	TRACE(_T("====================== \n"));}

void CSettingsDlg::DoDataExchange(CDataExchange* pDX)
	{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE, m_0_cTree);
	DDX_Control(pDX, IDC_MAINTAB, m_cMainTab);
	DDX_Control(pDX, IDC_0_GESTURETAB, m_0_cGestureTab);
	DDX_Control(pDX, IDC_0_COMMANDTAB, m_0_cCommandTab);
	DDX_Control(pDX, IDC_0_0_COMMANDS, m_0_0_cCommands);
	DDX_Control(pDX, IDC_0_2_TEXT, m_0_2_cText);
	DDX_Control(pDX, IDC_0_1_C_NAME, m_0_1_cCName);
	DDX_Control(pDX, IDC_0_1_C_PATH, m_0_1_cCPath);
	DDX_Control(pDX, IDC_0_1_C_PARAM, m_0_1_cCParam);
	DDX_Control(pDX, IDC_0_1_NAME, m_0_1_cName);
	DDX_Control(pDX, IDC_0_1_BROWSE, m_0_1_cBrowse);
	DDX_Control(pDX, IDC_0_1_PATH, m_0_1_cPath);
	DDX_Control(pDX, IDC_0_1_PARAM, m_0_1_cParam);
	DDX_Control(pDX, IDC_0_COMMANDS, m_0_cCommands);
	DDX_Control(pDX, IDC_0_4_C_NUMBER, m_0_4_cCNumber);
	DDX_Control(pDX, IDC_0_4_C_WPARAM, m_0_4_cCWParam);
	DDX_Control(pDX, IDC_0_4_C_LPARAM, m_0_4_cCLParam);
	DDX_Control(pDX, IDC_0_4_NUMBER, m_0_4_cNumber);
	DDX_Control(pDX, IDC_0_4_WPARAM, m_0_4_cWParam);
	DDX_Control(pDX, IDC_0_4_LPARAM, m_0_4_cLParam);
	DDX_Control(pDX, IDC_3_COMPATIBILITY_TYPE, m_3_cCompatibilityType);
	DDX_Control(pDX, IDC_3_COMPATIBILITY_LIST, m_3_cCompatibilityList);
	DDX_Control(pDX, IDC_3_COMPATIBILITY_EDIT, m_3_cCompatibilityEdit);
	DDX_Control(pDX, IDC_0_GESTURENAME, m_0_cGestureName);
	DDX_Control(pDX, IDC_0_GESTUREDESCRIPTION, m_0_cGestureDescription);
	DDX_Control(pDX, IDC_0_GESTURE_ENABLE, m_0_cGestureEnable);
	DDX_Control(pDX, IDC_2_SETTINGSTAB, m_2_cSettingsTab);
	DDX_Control(pDX, IDC_2_SYSTEMACTIVE, m_2_cSystemActive);
	DDX_Control(pDX, IDC_2_SHOWBALLOON, m_2_cShowBalloon);
	DDX_Control(pDX, IDC_2_SHOWSPLASH, m_2_cShowSplash);
	DDX_Control(pDX, IDC_2_STARTUP, m_2_cStartUp);
	DDX_Control(pDX, IDC_2_MOUSEBUTTON, m_2_cMouseButton);
	DDX_Control(pDX, IDC_2_C_MOUSEBUTTON, m_2_C_cMouseButton);
	DDX_Control(pDX, IDC_2_DISABLEKEY, m_2_cDisableKey);
	DDX_Control(pDX, IDC_2_C_DISABLEKEY, m_2_C_cDisableKey);
	DDX_Control(pDX, IDC_2_LANGUAGE, m_2_cLanguage);
	DDX_Control(pDX, IDC_2_C_LANGUAGE, m_2_C_cLanguage);
	DDX_Control(pDX, IDC_2_IGNORE_PROGRAM_EDIT, m_2_cIgnoreProgramEdit);
	DDX_Control(pDX, IDC_2_IGNORE_PROGRAM_LIST, m_2_cIgnoreProgramList);
	DDX_Control(pDX, IDC_2_USERNAME, m_2_cUserName);
	DDX_Control(pDX, IDC_2_HARDWAREID, m_2_cHardwareID);
	DDX_Control(pDX, IDC_2_REGISTRATIONKEY, m_2_cRegistrationKey);
	DDX_Control(pDX, IDC_2_SERIAL_NUMBER_STATUS, m_2_C_cSerialNumberStatus);
	DDX_Control(pDX, IDC_2_C_FILE_NAME, m_2_C_cFileName);
	DDX_Control(pDX, IDC_2_FILE_NAME, m_2_cFileName);
	DDX_Control(pDX, IDC_2_BROWSE, m_2_cBrowse);
	DDX_Control(pDX, IDC_2_C_USERNAME, m_2_C_cUserName);
	DDX_Control(pDX, IDC_2_C_HARDWAREID, m_2_C_cHardwareID);
	DDX_Control(pDX, IDC_2_C_REGISTRATIONKEY, m_2_C_cRegistrationKey);
	DDX_Control(pDX, IDC_0_3_KEY_TREE, m_0_3_cKeyTree);
	DDX_Control(pDX, IDC_0_3_ALL_KEY_TREE, m_0_3_cAllKeyTree);
	}


BEGIN_MESSAGE_MAP(CSettingsDlg, CDialog)
	ON_MESSAGE(WM_REDRAWTABCONTENT,OnRedrawTabContent)

	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_NOTIFY(TCN_SELCHANGE, IDC_MAINTAB, OnTcnSelchangeMaintab)
	ON_NOTIFY(TCN_SELCHANGE, IDC_0_GESTURETAB, OnTcnSelchange0Gesturetab)
	ON_NOTIFY(TCN_SELCHANGE, IDC_0_COMMANDTAB, OnTcnSelchange0Commandtab)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, OnTvnSelchangedTree)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(NM_RCLICK, IDC_TREE, OnNMRclickTree)
	ON_COMMAND(IDM_DELGESTURE, OnDelGesture)
	ON_COMMAND(IDM_ADDGESTURE, OnAddGesture)
	ON_COMMAND(IDM_ADDGROUP, OnAddGroup)
	ON_LBN_SELCHANGE(IDC_0_COMMANDS, OnLbnSelchange0Commands)
	ON_COMMAND(IDM_ADDCOMMAND, OnAddCommand)
	ON_COMMAND(IDM_DELCOMMAND, OnDelCommand)
	ON_COMMAND(IDM_COMMANDUP, OnCommandUp)
	ON_COMMAND(IDM_COMMANDDOWN, OnCommandDown)
	ON_LBN_SELCHANGE(IDC_0_0_COMMANDS, OnLbnSelchange00Commands)
	ON_EN_CHANGE(IDC_0_1_NAME, OnEnChange01Name)
	ON_EN_CHANGE(IDC_0_1_PATH, OnEnChange01Path)
	ON_EN_CHANGE(IDC_0_1_PARAM, OnEnChange01Param)
	ON_EN_CHANGE(IDC_0_2_TEXT, OnEnChange02Text)
	ON_EN_CHANGE(IDC_0_4_NUMBER, OnEnChange04Number)
	ON_EN_CHANGE(IDC_0_4_WPARAM, OnEnChange04Wparam)
	ON_EN_CHANGE(IDC_0_4_LPARAM, OnEnChange04Lparam)
	ON_WM_INITMENUPOPUP()
	ON_COMMAND(IDR_ADD, OnKeyAdd)
	ON_COMMAND(IDR_ADD_GROUP, OnKeyAddGroup)
	ON_COMMAND(IDR_DEL, OnKeyDel)
	ON_COMMAND(IDR_DOWN, OnKeyDown)
	ON_COMMAND(IDR_UP, OnKeyUp)
	ON_LBN_SELCHANGE(IDC_3_COMPATIBILITY_LIST, OnLbnSelchange3CompatibilityList)
	ON_EN_CHANGE(IDC_3_COMPATIBILITY_EDIT, OnEnChange3CompatibilityEdit)
	ON_CBN_SELCHANGE(IDC_3_COMPATIBILITY_TYPE, OnCbnSelchange3CompatibilityType)
	ON_COMMAND(IDM_ADDCOMPATIBILITY, OnAddCompatibility)
	ON_COMMAND(IDM_DELCOMPATIBILITY, OnDelCompatibility)
	ON_EN_CHANGE(IDC_0_GESTURENAME, OnEnChange0Gesturename)
	ON_EN_CHANGE(IDC_0_GESTUREDESCRIPTION, OnEnChange0Gesturedescription)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_0_1_BROWSE, OnBnClicked01Browse)
	ON_BN_CLICKED(IDC_0_GESTURE_ENABLE, OnBnClicked0GestureEnable)
	ON_BN_CLICKED(IDC_2_SYSTEMACTIVE, OnBnClicked2Systemactive)
	ON_BN_CLICKED(IDC_2_SHOWBALLOON, OnBnClicked2Showballoon)
	ON_BN_CLICKED(IDC_2_SHOWSPLASH, OnBnClicked2Showsplash)
	ON_BN_CLICKED(IDC_2_STARTUP, OnBnClicked2Startup)
	ON_CBN_SELCHANGE(IDC_2_MOUSEBUTTON, OnCbnSelchange2Mousebutton)
	ON_CBN_SELCHANGE(IDC_2_DISABLEKEY, OnCbnSelchange2Disablekey)
	ON_NOTIFY(TCN_SELCHANGE, IDC_2_SETTINGSTAB, OnTcnSelchange2Settingstab)
	ON_LBN_SELCHANGE(IDC_2_IGNORE_PROGRAM_LIST, OnLbnSelchange2IgnoreProgramList)
	ON_EN_CHANGE(IDC_2_IGNORE_PROGRAM_EDIT, OnEnChange2IgnoreProgramEdit)
	ON_COMMAND(IDM_ADDIGNOREPROGRAM, OnAddIgnoreProgram)
	ON_COMMAND(IDM_DELIGNOREPROGRAM, OnDelIgnoreProgram)
	ON_EN_KILLFOCUS(IDC_2_IGNORE_PROGRAM_EDIT, OnEnKillfocus2IgnoreProgramEdit)
	ON_EN_CHANGE(IDC_2_USERNAME, OnEnChange2Username)
	ON_EN_CHANGE(IDC_2_REGISTRATIONKEY, OnEnChange2Registrationkey)
	ON_EN_SETFOCUS(IDC_2_REGISTRATIONKEY, OnEnSetfocus2Registrationkey)
	ON_EN_KILLFOCUS(IDC_2_REGISTRATIONKEY, OnEnKillfocus2Registrationkey)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE, OnNMDblclkTree)
//	ON_LBN_DBLCLK(IDC_3_COMPATIBILITY_LIST, OnLbnDblclk3CompatibilityList)
//	ON_LBN_DBLCLK(IDC_2_IGNORE_PROGRAM_LIST, OnLbnDblclk2IgnoreProgramList)
//	ON_LBN_DBLCLK(IDC_0_COMMANDS, OnLbnDblclk0Commands)
	//	ON_WM_LBUTTONDBLCLK()
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_2_BROWSE, OnBnClicked2Browse)
//	ON_STN_CLICKED(IDC_2_C_USERNAME, OnStnClicked2CUsername)
ON_CBN_SELCHANGE(IDC_2_LANGUAGE, OnCbnSelchange2Language)
ON_NOTIFY(NM_DBLCLK, IDC_0_3_KEY_TREE, OnNMDblclk03KeyTree)
ON_NOTIFY(NM_RCLICK, IDC_0_3_KEY_TREE, OnNMRclick03KeyTree)
ON_COMMAND(IDM_INSERTKEYBEFORE, OnInsertKeyBefore)
ON_COMMAND(IDM_INSERTKEYINSIDE, OnInsertKeyInside)
ON_COMMAND(IDM_INSERTKEYAFTER, OnInsertKeyAfter)
ON_COMMAND(IDM_KEYDELETE, OnKeyDelete)
ON_NOTIFY(TVN_SELCHANGED, IDC_0_3_ALL_KEY_TREE, OnTvnSelchanged03AllKeyTree)
ON_NOTIFY(TVN_SELCHANGED, IDC_0_3_KEY_TREE, OnTvnSelchanged03KeyTree)
END_MESSAGE_MAP()


// CSettingsDlg message handlers
// [*----] обработчик кнопки [_]
void CSettingsDlg::OnSysCommand(UINT nID, LPARAM lParam)
	{
	if((nID&0xFFF0)==SC_MINIMIZE)
		OnCancel();
	CDialog::OnSysCommand(nID, lParam);
	}

void CSettingsDlg::OnSize(UINT nType, int cx, int cy)
	{
	TRACE(_T("OnSize(): m_bDraw=1;\n"));
	m_bDraw=1;
	CDialog::OnSize(nType, cx, cy);
	if(m_0_cTree.GetSafeHwnd())
		MoveElements(cx,cy);
	}

void CSettingsDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
	{
	lpMMI->ptMinTrackSize=CPoint(700, 500);
	CDialog::OnGetMinMaxInfo(lpMMI);
	}

void CSettingsDlg::ApplyLanguage(void)
	{
	// название окна
	SetWindowText(_lng(_T("Settings-Title")));

	m_0_cGestureEnable.SetWindowText(_lng(_T("Settings-Gesture-Description-Disable")));

	m_0_1_cCName.SetWindowText(_lng(_T("Settings-Gesture-Command-Execute-Name")));
	m_0_1_cBrowse.SetWindowText(_lng(_T("Settings-Gesture-Command-Execute-Browse")));
	m_0_1_cCPath.SetWindowText(_lng(_T("Settings-Gesture-Command-Execute-Path")));
	m_0_1_cCParam.SetWindowText(_lng(_T("Settings-Gesture-Command-Execute-Param")));

	m_0_4_cCNumber.SetWindowText(_lng(_T("Settings-Gesture-Command-Message-Number")));
	m_0_4_cCLParam.SetWindowText(_lng(_T("Settings-Gesture-Command-Message-LParam")));
	m_0_4_cCWParam.SetWindowText(_lng(_T("Settings-Gesture-Command-Message-WParam")));

	m_2_cSystemActive.SetWindowText(_lng(_T("Settings-Stiings-SystemActive")));
	m_2_cShowBalloon.SetWindowText(_lng(_T("Settings-Stiings-ShowBalloons")));
	m_2_cShowSplash.SetWindowText(_lng(_T("Settings-Stiings-ShowSplash")));
	m_2_cStartUp.SetWindowText(_lng(_T("Settings-Stiings-StartUp")));
	m_2_C_cDisableKey.SetWindowText(_lng(_T("Settings-Stiings-DisableKey")));
	m_2_C_cMouseButton.SetWindowText(_lng(_T("Settings-Stiings-MouseButton")));

	m_2_C_cUserName.SetWindowText(_lng(_T("Settings-Registration-UserName")));
	m_2_C_cHardwareID.SetWindowText(_lng(_T("Settings-Registration-HardwareID")));
	m_2_C_cRegistrationKey.SetWindowText(_lng(_T("Settings-Registration-SerialNumber")));


	m_2_C_cFileName.SetWindowText(_lng(_T("Settings-Stiings-FileName")));
	m_2_cBrowse.SetWindowText(_lng(_T("Settings-Stiings-Browse")));


	m_0_0_cCommands.ResetContent();
	int i=0;
	for(i=0;i<StandartActionCount;i++)
		m_0_0_cCommands.AddString(_lng(_T("Settings-Gesture-Command-Standart-")+StandartAction[i]));

	m_3_cCompatibilityType.ResetContent();
	m_3_cCompatibilityType.AddString(_lng(_T("Settings-CompatibilityType-All"))/*"Совместим со всеми"*/);
	m_3_cCompatibilityType.AddString(_lng(_T("Settings-CompatibilityType-Except"))/*"Совместим со всеми, кроме указанных"*/);
	m_3_cCompatibilityType.AddString(_lng(_T("Settings-CompatibilityType-Only"))/*"Совместим только с указанными"*/);

	m_2_cDisableKey.ResetContent();
	m_2_cDisableKey.AddString(_lng(_T("Settings-Stiings-DisableKey-None")));
	m_2_cDisableKey.AddString(_lng(_T("Settings-Stiings-DisableKey-Ctrl")));
	m_2_cDisableKey.AddString(_lng(_T("Settings-Stiings-DisableKey-Shift")));

	m_2_cMouseButton.ResetContent();
	m_2_cMouseButton.AddString(_lng(_T("Settings-Stiings-MouseButton-Right")));
	m_2_cMouseButton.AddString(_lng(_T("Settings-Stiings-MouseButton-Left")));
	m_2_cMouseButton.AddString(_lng(_T("Settings-Stiings-MouseButton-Middle")));

	TC_ITEM tci;// в нее записываются параметры создаваемой закладки
	memset(&tci,0,sizeof(tci));
	tci.mask = TCIF_TEXT;// у закладки будет только текст
	TCHAR buffer[1024];
	tci.pszText=buffer;
	m_cMainTab.DeleteAllItems();
	StringCopy(_lng(_T("Settings-MainTab-Logo")),tci.pszText);
	m_cMainTab.InsertItem(0,&tci);
	StringCopy(_lng(_T("Settings-MainTab-Gestures")),tci.pszText);
	m_cMainTab.InsertItem(1,&tci);
	StringCopy(_lng(_T("Settings-MainTab-Settings")),tci.pszText);
	m_cMainTab.InsertItem(2,&tci);
	StringCopy(_lng(_T("Settings-MainTab-Help")),tci.pszText);
	m_cMainTab.InsertItem(3,&tci);

	m_2_cSettingsTab.DeleteAllItems();
	StringCopy(_lng(_T("Settings-SettingsTab-General")),tci.pszText);
	m_2_cSettingsTab.InsertItem(0,&tci);
	StringCopy(_lng(_T("Settings-SettingsTab-IngnoreProgram")),tci.pszText);
	m_2_cSettingsTab.InsertItem(1,&tci);
	StringCopy(_lng(_T("Settings-SettingsTab-Registration")),tci.pszText);
	m_2_cSettingsTab.InsertItem(2,&tci);

	m_2_cLanguage.ResetContent();
	i=0;
	CString name,firstletter,language=theProperties.m_LanguageName;
	language.MakeLower();
	WIN32_FIND_DATA fd; 
	HANDLE h=::FindFirstFile(theProperties.m_ProgramDirectory+_T("\\Languages\\*.lng"),&fd); 
	if(h!=INVALID_HANDLE_VALUE) 
		{ 
		do{ 
			if(fd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) 
				continue;
			name=fd.cFileName;
			if(name.IsEmpty())continue;
			firstletter=name.GetAt(0);
			firstletter.MakeUpper();
			name.MakeLower();
			name.SetAt(0,firstletter.GetAt(0));
			name=name.Left(name.GetLength()-4);
			m_2_cLanguage.AddString(name);
			name.MakeLower();
			if(name==language)
				m_2_cLanguage.SetCurSel(i);
			i++;
			} 
	while(::FindNextFile(h,&fd));
		} 
	::FindClose(h);
	}





void CSettingsDlg::CreateTree(void)
	{

	m_0_cTree.DeleteAllItems();
	TV_INSERTSTRUCT tvinsert;
	tvinsert.hParent = NULL;
	tvinsert.hInsertAfter=TVI_SORT;
	tvinsert.item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	tvinsert.item.hItem=NULL; 
	tvinsert.item.state=0;
	tvinsert.item.stateMask=0;
	tvinsert.item.cchTextMax=6;
	tvinsert.item.iImage=0;// empty meaning
	tvinsert.item.iSelectedImage=0;// empty meaning
	tvinsert.item.cChildren=0;
	tvinsert.item.lParam=0;// empty meaning

	// top level
	TCHAR buffer[1024];
	HTREEITEM hGestureLevel,thTreeItem;
	HTREEITEM hParent[32];
	long CurrentLevel=0;

	tvinsert.item.iImage=0;
	tvinsert.item.iSelectedImage=0;
	StringCopy(_lng(_T("Settings-Tree-Gestures")),buffer);
	tvinsert.item.pszText=buffer;


	hGestureLevel=m_0_cTree.InsertItem(&tvinsert);
	m_0_cTree.SetItemData(hGestureLevel,0);

	hParent[0]=hGestureLevel;

	CString s;
	for(long i=0;i<m_pIdentify->m_nGestures;i++)
		{
		switch(m_pIdentify->m_Gestures[i].m_GroupStatus)
			{
			case 0: // gesture
				tvinsert.hParent=hParent[CurrentLevel];
				s=m_pIdentify->m_Gestures[i].m_Name;
				tvinsert.item.pszText=s.GetBuffer(s.GetLength());
				if(m_pIdentify->m_Gestures[i].m_Disable)
					{
					tvinsert.item.iImage=3;
					tvinsert.item.iSelectedImage=3;
					}
				else
					{
					tvinsert.item.iImage=2;
					tvinsert.item.iSelectedImage=2;
					}
				thTreeItem=m_0_cTree.InsertItem(&tvinsert);
				m_0_cTree.SetItemData(thTreeItem,m_pIdentify->m_Tunnel.Add(i));
				m_0_cTree.Sort(hParent[CurrentLevel]);
				break;
			case 1: // open group
				tvinsert.hParent=hParent[CurrentLevel];
				s=m_pIdentify->m_Gestures[i].m_Name;
				tvinsert.item.pszText=s.GetBuffer(s.GetLength());
				tvinsert.item.iImage=0;
				tvinsert.item.iSelectedImage=0;
				thTreeItem=m_0_cTree.InsertItem(&tvinsert);
				m_0_cTree.SetItemData(thTreeItem,m_pIdentify->m_Tunnel.Add(i));
				m_0_cTree.Sort(hParent[CurrentLevel]);
				CurrentLevel++;
				hParent[CurrentLevel]=thTreeItem;
				break;
			case 2: // close group
				CurrentLevel--;
				ASSERT(CurrentLevel>=0);
				break;
			}
		}
	m_0_cTree.Expand(hGestureLevel,TVE_EXPAND);
	m_0_cTree.SelectItem(hGestureLevel);

	HTREEITEM hKeyGroup=NULL;
	// формирование дерева клавишь
	m_0_3_cAllKeyTree.DeleteAllItems();
	tvinsert.hInsertAfter=TVI_LAST;
	for(int i=0;i<KeyTreeNumber;i++)
		{
		if(KeyTree[i].code==-1)
			{
			// create group
			tvinsert.hParent=NULL;
			s=KeyTree[i].name;
			tvinsert.item.pszText=s.GetBuffer(s.GetLength());
			tvinsert.item.iImage=0;
			tvinsert.item.iSelectedImage=0;
			thTreeItem=m_0_3_cAllKeyTree.InsertItem(&tvinsert);
			KeyTree[i].hItem=thTreeItem;
			m_0_3_cAllKeyTree.SetItemData(thTreeItem,-1);
			hKeyGroup=thTreeItem;
			}
		else
			{
			// add key
			tvinsert.hParent=hKeyGroup;
			s=KeyTree[i].name;
			tvinsert.item.pszText=s.GetBuffer(s.GetLength());
			tvinsert.item.iImage=0;
			tvinsert.item.iSelectedImage=0;
			thTreeItem=m_0_3_cAllKeyTree.InsertItem(&tvinsert);
			KeyTree[i].hItem=thTreeItem;
			m_0_3_cAllKeyTree.SetItemData(thTreeItem,KeyTree[i].code);
			}
		}
	}


BOOL CSettingsDlg::OnInitDialog()
	{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	// перемещаем окно в старую позицию
	if(theProperties.m_WindowPosition.right!=0)
		if((theProperties.m_WindowPosition.left==-4)&&(theProperties.m_WindowPosition.top==-4))
			ShowWindow(SW_MAXIMIZE);
		else
			MoveWindow(&theProperties.m_WindowPosition,TRUE);

	// загружаем акселераторы
	m_Accel=::LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR));
	// инициализируем тултипы
	m_cToolTip.Create(this);


	ApplyLanguage();
	DWORD Serial=0;
	GetVolumeInformation(_T("c:\\"),NULL,NULL,&Serial,NULL,NULL,NULL,NULL);
	m_2_cHardwareID.SetWindowText(UnsignedLongToString(Serial));
	m_2_cRegistrationKey.SetWindowText(theProperties.m_RegKey);
	m_2_cUserName.SetWindowText(theProperties.m_UserName);



	m_2_cSystemActive.SetCheck(m_ActiveSystemInFirstMoment);
	m_2_cShowBalloon.SetCheck(theProperties.m_ShowBalloon);
	m_2_cShowSplash.SetCheck(theProperties.m_ShowSplash);
	m_2_cStartUp.SetCheck((int)theProperties.IsAutoRunKey());
	m_2_cFileName.SetWindowText(theProperties.m_FileName);
	m_2_cDisableKey.SetCurSel(theProperties.m_DisableKey);
	m_2_cMouseButton.SetCurSel(theProperties.m_MouseButton);


	int length=theProperties.m_IgnoreProgram.GetLength();
	CString str;
	TCHAR ch=0;
	for(int i=0;i<length;i++)
		{
		ch=theProperties.m_IgnoreProgram.GetAt(i);
		if((ch<=1)||(i+1==length))
			{
			if(i+1==length)str+=ch;
			if(!str.IsEmpty())
				{
				m_2_cIgnoreProgramList.AddString(str);
				str.Empty();
				}
			}
		else
			str+=ch;
		}
	m_2_cIgnoreProgramList.SetCurSel(0);
	OnLbnSelchange2IgnoreProgramList();



	SetGestureTabState(0);
	SetCommandTabState(0);


	m_cMainTab.SetCurSel(0);
	m_0_cGestureTab.SetCurSel(0);
	m_0_cCommandTab.SetCurSel(0);

	m_Graph.Init(this,&m_Size,NULL,m_pIdentify);
	m_Splitter.Init(&m_Graph);
	m_0_cTree.Init(m_pIdentify);

	RECT r;
	GetClientRect(&r);
	MoveElements(r.right,r.bottom);



	#define IDS_UTIL_UXTHEME        _T("UxTheme.dll")
	#define IDS_UTIL_THEMETEXTURE   "EnableThemeDialogTexture"
	HWND hwndDlg=GetSafeHwnd();
	HINSTANCE hDll=LoadLibrary(CString((LPCTSTR)IDS_UTIL_UXTHEME));							// 'UxTheme.dll'
	if(hDll==NULL)
		return 0;	// the DLL won't be available on anything except Windows XP
	ULONG (PASCAL *lpfnEnableTheme)(HWND, DWORD);
	(FARPROC&)lpfnEnableTheme=GetProcAddress(hDll,IDS_UTIL_THEMETEXTURE);	// 'EnableThemeDialogTexture'
	if(lpfnEnableTheme)
		lpfnEnableTheme(hwndDlg, 6);		// ETDT_ENABLETAB = (ETDT_ENABLE | ETDT_USETABTEXTURE) = (2|4) = 6
	else ASSERT(FALSE);
	FreeLibrary(hDll);



	// фигня!
	//m_pIdentify->Load("c:\\template.dr"));

	// формирование картинок для дерева

	//	m_ImageList.Create(0,0,ILC_COLOR24,16,1);
	//	CBitmap bmp;
	//	bmp.LoadOEMBitmap(IDB_TREEIMAGES);
	//	//bool b=bmp.LoadBitmap(IDB_TREEIMAGES);
	//	int xxx=m_ImageList.Add(&bmp,RGB(255,255,255));


	//m_ImageList.Create(IDB_TREEIMAGES,16,1,RGB(255,255,255));

	//HICON hIcon;


	//m_ImageList.Create(16, 16, 0, 8, 8);
	m_ImageList.Create(16,16,ILC_MASK|ILC_COLOR24,16,1);
	m_ImageList.SetBkColor(GetSysColor(COLOR_WINDOW));
	//hIcon=AfxGetApp()->LoadIcon(IDI_WHITE);
	//m_ImageList.Add((HICON)::LoadImage(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_FOLDERCLOSE),IMAGE_ICON,16,16,LR_LOADMAP3DCOLORS));

	/*CBitmap bmp;
	int x=bmp.LoadBitmap(IDI_FOLDERCLOSE);
	x=m_ImageList.Add(&bmp,RGB(255,0,255));
	*/
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_FOLDERCLOSE));

	m_ImageList.Add((HICON)::LoadImage(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_FOLDEROPEN),IMAGE_ICON,16,16,0));
	m_ImageList.Add((HICON)::LoadImage(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_SYSTRAY0),IMAGE_ICON,16,16,0));
	m_ImageList.Add((HICON)::LoadImage(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_SYSTRAY1),IMAGE_ICON,16,16,0));

	m_0_cTree.SetImageList(&m_ImageList,TVSIL_NORMAL);
	m_0_3_cKeyTree.SetImageList(&m_ImageList,TVSIL_NORMAL);
	m_0_3_cAllKeyTree.SetImageList(&m_ImageList,TVSIL_NORMAL);


	// формирование дерева
	CreateTree();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
	}

void CSettingsDlg::MoveElements(int cx, int cy)
	{
	TRACE(_T("MoveElements\n"));
	RECT r;
	if(cx!=-1)m_Size.SetPoint(cx,cy);
	int x=m_Size.x;
	int y=m_Size.y;
#define skin 0
	if(cy!=-2)
		{
		move(m_cMainTab,3,3,x-1-skin,y-1-skin);

		move(m_0_cTree,68,27,m_Splitter.m_Position-3,y-7);
		move(m_0_cGestureTab,m_Splitter.m_Position+8,27,x-5-skin,y-5-skin);
		move(m_2_cSettingsTab,68,27,x-5-skin,y-5-skin);
		move(m_0_cCommandTab,m_Splitter.m_Position+12,y-127,x-9-skin,y-9-skin);
		move(m_0_cCommands,m_Splitter.m_Position+12,52,x-11-skin,y-131);
		// элементы во вкладках m_0_cCommandTab
		move(m_0_0_cCommands,m_Splitter.m_Position+16,y-103-skin,x-15-skin,y-15-skin);

		move(m_0_1_cCName	,m_Splitter.m_Position+16,y-15-88,m_Splitter.m_Position+96,y-70-15);
		move(m_0_1_cName	,m_Splitter.m_Position+98,y-15-78,x-90,y-60-15);
		move(m_0_1_cBrowse	,x-88,y-15-78,x-15,y-60-15);
		move(m_0_1_cCPath	,m_Splitter.m_Position+16,y-15-58,m_Splitter.m_Position+96,y-40-15);
		move(m_0_1_cPath	,m_Splitter.m_Position+98,y-15-48,x-15,y-30-15);
		move(m_0_1_cCParam	,m_Splitter.m_Position+16,y-15-28,m_Splitter.m_Position+96,y-10-15);
		move(m_0_1_cParam	,m_Splitter.m_Position+98,y-15-18,x-15,y-00-15);

		move(m_0_2_cText,m_Splitter.m_Position+16,y-103,x-15-skin,y-15-skin);

		move(m_0_3_cKeyTree,m_Splitter.m_Position+16,y-103,x-15-200,y-15);
		move(m_0_3_cAllKeyTree,x-15-200+3,y-103,x-15,y-15);

		move(m_0_4_cCNumber	,m_Splitter.m_Position+16,y-15-88-skin,m_Splitter.m_Position+66,y-70-15-skin);
		move(m_0_4_cNumber	,m_Splitter.m_Position+68,y-15-78-skin,x-15-skin,y-60-15-skin);
		move(m_0_4_cCWParam	,m_Splitter.m_Position+16,y-15-58-skin,m_Splitter.m_Position+66,y-40-15-skin);
		move(m_0_4_cWParam	,m_Splitter.m_Position+68,y-15-48-skin,x-15-skin,y-30-15-skin);
		move(m_0_4_cCLParam	,m_Splitter.m_Position+16,y-15-28-skin,m_Splitter.m_Position+66,y-10-15-skin);
		move(m_0_4_cLParam	,m_Splitter.m_Position+68,y-15-18-skin,x-15-skin,y-00-15-skin);
/*
		move(	,m_Splitter.m_Position+16,y-15-58-skin,m_Splitter.m_Position+80,y-40-15-skin);
		move(	,m_Splitter.m_Position+16,y-15-38-skin,m_Splitter.m_Position+80,y-20-15-skin);
		move(	,m_Splitter.m_Position+16,y-15-18-skin,m_Splitter.m_Position+80,y-00-15-skin);
		move(	,m_Splitter.m_Position+83,y-15-58-skin,x-15-skin,y-40-15-skin);
		move(	,m_Splitter.m_Position+83,y-15-38-skin,x-15-skin,y-20-15-skin);
		move(	,m_Splitter.m_Position+83,y-15-18-skin,x-15-skin,y-00-15-skin);
*/
		// вкладка совместимость
		move(m_3_cCompatibilityType,m_Splitter.m_Position+12,52,x-11-skin,200);
		move(m_3_cCompatibilityEdit,m_Splitter.m_Position+12,76,x-11-skin,94);
		move(m_3_cCompatibilityList,m_Splitter.m_Position+12,97,x-11-skin,y-11);

		move(m_0_cGestureName,m_Splitter.m_Position+13,52,x-11,72);
		move(m_0_cGestureEnable,m_Splitter.m_Position+13,73,x-11,91);

		// настройки
		move(m_2_cSystemActive	,73, 50,x-11, 69);
		move(m_2_cShowBalloon	,73, 70,x-11, 89);
		move(m_2_cShowSplash	,73, 90,x-11,109);
		move(m_2_cStartUp		,73,110,x-11,129);

		move(m_2_C_cFileName	,73,133,300,153);
		move(m_2_cFileName		,305,133,x-92,153);
		move(m_2_cBrowse		,x-90,133,x-11,153);

		move(m_2_C_cMouseButton	,73,155,300,175+1);
		move(m_2_cMouseButton	,305,155,x-11,175);
		move(m_2_C_cDisableKey	,73,178,300,198+1);
		move(m_2_cDisableKey	,305,178,x-11,198);	
		move(m_2_C_cLanguage	,73,201,300,221+1);
		move(m_2_cLanguage		,305,201,x-11,221);

		move(m_2_cIgnoreProgramEdit,72,52,x-11,72);
		move(m_2_cIgnoreProgramList,72,76,x-11,y-11);

		move(m_2_C_cUserName		,72,52,180,72);
		move(m_2_C_cHardwareID		,72,75,180,95);
		move(m_2_C_cRegistrationKey	,72,98,180,118);


		move(m_2_cUserName				,182,52,x-11,72);
		move(m_2_cHardwareID			,182,75,x-11,95);
		move(m_2_cRegistrationKey		,182,98,x-11,118);
		move(m_2_C_cSerialNumberStatus	,182,121,x-11,141);

		if((m_Position[0]==3)&&(m_2_pExplorer))
			{move((*m_2_pExplorer),68,27,x-7,y-7);}
		}
	if(m_Position[1]==2)
		{move(m_0_cGestureDescription,m_Splitter.m_Position+13,75,x-11,y-11);}
	else
		{move(m_0_cGestureDescription,m_Splitter.m_Position+13,91,x-11,y-11);}
	}

void CSettingsDlg::OnPaint()
	{
	TRACE(_T("OnPaint(): m_bDraw=1;\n"));
	m_bDraw=1;
	CPaintDC dc(this); 
	}

void CSettingsDlg::OnMouseMove(UINT nFlags, CPoint point)
	{
	if(m_Graph.m_bShowSplitter)m_Splitter.MouseMove(point);

	if(m_AddSymbolState)
		{
		m_pIdentify->NextPoint(1,_point_to_int((POINT)point));
		}

	CDialog::OnMouseMove(nFlags, point);
	}

void CSettingsDlg::OnLButtonUp(UINT nFlags, CPoint point)
	{
	if(m_Graph.m_bShowSplitter)
		if(m_Splitter.MouseUp(point))
			{
			MoveElements(-1,-1);
			m_Graph.Draw(m_0_cGestureTab.GetCurSel()==2, m_ActiveGestureNumber);
			}

		if(m_AddSymbolState)
			{
			m_AddSymbolState=0;
			m_pIdentify->NextPoint(1,_point_to_int((POINT)point));
			m_pIdentify->NextPoint(2,NULL);
			if(m_pIdentify->theSymbol.m_nDirection>0)
				{
				int &number=m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Symbols.m_nSymbol;
				m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Symbols.m_Symbol.SetAtGrow(number,m_pIdentify->theSymbol);
				number++;
				m_Graph.Draw(m_0_cGestureTab.GetCurSel()==2, m_ActiveGestureNumber);
				}
			}
		CDialog::OnLButtonUp(nFlags, point);
	}

void CSettingsDlg::OnLButtonDown(UINT nFlags, CPoint point)
	{
	if(m_Graph.m_bShowSplitter)m_Splitter.MouseDown(point);
	if((m_Position[0]==1)&&(m_Position[1]==1)&&(m_Position[2]==2))
		{
		CRect r;
		r.SetRect(m_Splitter.m_Position+12,51,m_Size.x-11,m_Size.y-11);
		if(r.PtInRect(point))
			{
			m_AddSymbolState=1;
			m_pIdentify->NextPoint(0,_point_to_int((POINT)point));
			}
		}
	CDialog::OnLButtonDown(nFlags, point);
	}


void CSettingsDlg::OnRButtonDown(UINT nFlags, CPoint point)
	{
	if((m_Position[0]==1)&&(m_Position[1]==1)&&(m_Position[2]==2))
		{
		CRect r;
		r.SetRect(m_Splitter.m_Position+12,51,m_Size.x-11,m_Size.y-11);
		if(r.PtInRect(point))
			{
			int x=0,y=0,level=0;
			int x2=m_Size.x-11;
			int y2=m_Size.y-11;
			CPoint slidePoint;
			CSymbols &symbols=m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Symbols;
			for(int i=0;i<symbols.m_nSymbol;i++)
				{
				slidePoint.x=x2-57-x*53;
				slidePoint.y=y2-57-y*53;
				r.SetRect(slidePoint.x-3,slidePoint.y-3,slidePoint.x+47,slidePoint.y+47);

				if(r.PtInRect(point))
					{
					symbols.m_Symbol.RemoveAt(i);
					symbols.m_nSymbol--;
					// фишка вроде как не нужна
					//m_0_cGestureTab.Invalidate();
					//m_0_cGestureTab.OnPaint();
					//MessagePause();
					m_bDraw=1;
					OnRedrawTabContent(0,0);
					break;
					}
				x++;y--;
				if(y<0){level++;y=level;x=0;}
				}
			}
		}
	CDialog::OnRButtonDown(nFlags, point);
	}

void CSettingsDlg::OnRButtonDblClk(UINT nFlags, CPoint point)
	{
	OnRButtonDown(nFlags,point);
	CDialog::OnRButtonDblClk(nFlags, point);
	}

LRESULT CSettingsDlg::OnRedrawTabContent(WPARAM wParam, LPARAM lParam)
	{
	if(!m_bDraw)return 0;
	m_bDraw=0;
	int param=0;

	if(m_Position[0]==1 && m_Position[1]==1 && m_Position[2]==2) param=1; // сисуем символы
	if(m_Position[0]==0) param=2; // рисуем заставку
	if(m_Position[0]==1 && m_Position[1]==0) param=3; // рисуем логитип в жестах
	m_Graph.Draw(param, m_ActiveGestureNumber);
	return 0;
	}
/*
a - m_cMainTab
b - m_0_cTree
c -	m_0_cGestureTab
d - m_0_cCommandTab
*/
void CSettingsDlg::SetPosition(int a, int b, int c, int d)
	{
	TRACE(_T("SetPosition(%i,%i,%i,%i)\n"),a,b,c,d);
	// level показывает сколько уровней начиная с самого глобального НЕ надо перересовывать
	int level=0;
	if(m_Position[0]==a)
		{
		level=1;
		//if(a==1)level=2;//?
		if(m_Position[1]==b)
			{
			level=2;
			if(m_Position[2]==c)
				{
				level=3;
				if(m_Position[3]==d)
					level=4;
				}
			}
		}
	TRACE(_T("Visibility control, level=%u\n"),level);

	SetVisibilityGroup(m_Position[0],m_Position[1],m_Position[2],m_Position[3],false,level);
	m_Position[0]=a;
	m_Position[1]=b;
	m_Position[2]=c;
	m_Position[3]=d;
	SetVisibilityGroup(a,b,c,d,true,level);
	}

#define _visibility(e); e.ShowWindow(visibility);
void CSettingsDlg::SetVisibilityGroup(int a, int b, int c, int d, bool visibility, int level)
	{
	m_Graph.m_bShowSplitter=(a==1);
	switch(a)
		{
		case 0: // m_cMainTab - Предварительный просмотр
			if(level<1)
				{
				//_visibility(m_0_cGesturePreviewScroll);
				}
			break;
		case 1: // m_cMainTab - Жесты
			if(level<1)
				{
				_visibility(m_0_cTree);
				}
			switch(b)
				{
				case 0: // m_0_cTree - бяка
					if(level<2)
						{
						_visibility(m_0_cGestureTab);
						}
					break;
				case 2: // m_0_cTree - Группа жестов
					if(level<2)
						{
						_visibility(m_0_cGestureTab);
						}
					if(level<3)
						{
						if(visibility)MoveElements(-1,-2);
						_visibility(m_0_cGestureDescription);
						_visibility(m_0_cGestureName);
						//_visibility(m_0_cGestureEnable);
						}
					break;
				case 1: // m_0_cTree - Обычный жест
					if(level<2)
						{
						_visibility(m_0_cGestureTab);
						}
					switch(c)
						{
						case 0:
							if(level<3)
								{
								if(visibility)MoveElements(-1,-2);
								_visibility(m_0_cGestureDescription);
								_visibility(m_0_cGestureName);
								_visibility(m_0_cGestureEnable);
								}
							break;
						case 1: // m_0_cGestureTab - Комманды
							if(level<3)
								{
								_visibility(m_0_cCommands);
								_visibility(m_0_cCommandTab);
								}
							switch(d)
								{
								case 0: // m_0_cCommandTab - Обычные
									if(level<4)
										{
										_visibility(m_0_0_cCommands);
										}
									break;
								case 1: // m_0_cCommandTab - Запуск
									if(level<4)
										{
										_visibility(m_0_1_cCName);
										_visibility(m_0_1_cCPath);
										_visibility(m_0_1_cCParam);

										_visibility(m_0_1_cName);
										_visibility(m_0_1_cBrowse);
										_visibility(m_0_1_cPath);
										_visibility(m_0_1_cParam);
										}
									break;
								case 2: // m_0_cCommandTab - Текст
									if(level<4)
										{
										_visibility(m_0_2_cText);
										}
									break;				
								case 3: // m_0_cCommandTab - Клавиши
									if(level<4)
										{
										_visibility(m_0_3_cKeyTree);
										_visibility(m_0_3_cAllKeyTree);
										}
									break;				
								case 4: // m_0_cCommandTab - Сообщение
									if(level<4)
										{
										_visibility(m_0_4_cCNumber);
										_visibility(m_0_4_cCWParam);
										_visibility(m_0_4_cCLParam);
										_visibility(m_0_4_cNumber);
										_visibility(m_0_4_cWParam);
										_visibility(m_0_4_cLParam);
										}
									break;				
								}
							break;
						case 3:
							if(level<3)
								{
								_visibility(m_3_cCompatibilityType);
								_visibility(m_3_cCompatibilityEdit);
								_visibility(m_3_cCompatibilityList);
								}
							break;
						}
					break;
				}
			break;
		case 2: // m_cMainTab - Настройка
			if(level<1)
				{
				_visibility(m_2_cSettingsTab);
				}
			switch(b)
				{
				case 0: // m_cSettingsTab - Общие
					if(level<2)
						{
						_visibility(m_2_cSystemActive);
						_visibility(m_2_cShowBalloon);
						_visibility(m_2_cShowSplash);
						_visibility(m_2_cStartUp);
						_visibility(m_2_cMouseButton);
						_visibility(m_2_C_cMouseButton);
						_visibility(m_2_cDisableKey);
						_visibility(m_2_C_cDisableKey);
						_visibility(m_2_cLanguage);
						_visibility(m_2_C_cLanguage);

						_visibility(m_2_C_cFileName);
						_visibility(m_2_cFileName);
						_visibility(m_2_cBrowse);
						}
					break;
				case 1: // m_cSettingsTab - Игнорировать программы
					if(level<2)
						{
						_visibility(m_2_cIgnoreProgramEdit);
						_visibility(m_2_cIgnoreProgramList);
						}
					break;
				case 2: // m_cSettingsTab - Регистрация
					if(level<2)
						{
						_visibility(m_2_C_cUserName);
						_visibility(m_2_C_cHardwareID);
						_visibility(m_2_C_cRegistrationKey);

						_visibility(m_2_cUserName);
						_visibility(m_2_cHardwareID);
						_visibility(m_2_cRegistrationKey);
						_visibility(m_2_C_cSerialNumberStatus);
						}
					break;
				}
			break;
		case 3: // m_cMainTab - хелп
			if(level<1)
				{
				//m_static[4]=false;
				if(visibility)
					{
					if(m_2_pExplorer==NULL)
						{
						m_static[4]=TRUE;
						m_2_pExplorer=new CExplorer;
						RECT rect={-10,-10,-10,-10};
						m_2_pExplorer->Create(_T("Downright Explorer"),WS_VISIBLE,rect,this,0);
						m_2_pExplorer->BringWindowToTop();
						
						// good version m_2_pExplorer->Navigate(theProperties.m_ProgramDirectory+"\\help\\russian_help.htm",NULL,NULL,NULL,NULL);
						m_2_pExplorer->Navigate(_T("http://downright.shergin.com"),NULL,NULL,NULL,NULL);
						//m_2_pExplorer->Navigate("file://c:/",NULL,NULL,NULL,NULL);
						}
					MoveElements(m_Size.x,m_Size.y);
					}
				else
					{
					RECT r;
					move((*m_2_pExplorer),-20,-20,-10,-10);
					}
				}
			break;
		}
	}

void CSettingsDlg::OnTcnSelchangeMaintab(NMHDR *pNMHDR, LRESULT *pResult)
	{
	// тестирование... может надо, а может и нет...
	//TRACE(_T("OnTcnSelchangeMaintab(): m_bDraw=1;\n"));
	//m_bDraw=1;

	// m_static[0]
	if(m_static[0]==0)
		{
		TRACE(_T("m_cMainTab.RedrawWindow();\n"));
		CRect rect;
		rect.SetRect(65,24,m_Size.x-10,m_Size.y-10);
		m_cMainTab.RedrawWindow(&rect);
		}
	m_static[0]=m_cMainTab.GetCurSel();

	switch(m_cMainTab.GetCurSel())
		{
		case 0: // лого
			SetPosition(0,-1,-1,-1);
			break;
		case 1: // жесты
			{
			int b=1;
			HTREEITEM hItem=m_0_cTree.GetSelectedItem();
			if(hItem)
				{
				int data=(int)m_0_cTree.GetItemData(hItem);
				if(data==0)b=0;
				else
					if(m_pIdentify->GetGestureById(data)->m_GroupStatus==1)b=2;
				}

			SetPosition(1,b,m_0_cGestureTab.GetCurSel(),m_0_cCommandTab.GetCurSel());
			}
		break;
		case 2: // настройки 
			SetPosition(2,m_2_cSettingsTab.GetCurSel(),-1,-1);
			break;
		case 3: // хелп 
			SetPosition(3,-1,-1,-1);
			break;
		}
	if(pResult)*pResult=0;
	}

void CSettingsDlg::OnTcnSelchange0Gesturetab(NMHDR *pNMHDR, LRESULT *pResult)
	{
	TRACE(_T("OnTcnSelchange0Gesturetab\n"));
	// m_static[1]
	if(m_static[1]==2)
		{
		CRect rect;
		rect.SetRect(4,24,m_Size.x-m_Splitter.m_Position-19,m_Size.y-38);
		m_0_cGestureTab.RedrawWindow(&rect);
		}
	m_static[1]=m_0_cGestureTab.GetCurSel();

	SetPosition(m_cMainTab.GetCurSel(),m_Position[1],m_0_cGestureTab.GetCurSel(),-1/**m_0_cCommandTab.GetCurSel()*/);
	if(m_Position[2]==1)OnLbnSelchange0Commands();
	if(pResult)*pResult = 0;
	}

void CSettingsDlg::OnTcnSelchange0Commandtab(NMHDR *pNMHDR, LRESULT *pResult)
	{
	TRACE(_T("OnTcnSelchange0Commandtab\n"));
	SetPosition(m_cMainTab.GetCurSel(),m_Position[1],m_0_cGestureTab.GetCurSel(),m_0_cCommandTab.GetCurSel());
	if
		(
		(m_cMainTab.GetCurSel()==1)&&
		//(m_0_cGestureTab.GetCurSel()==1)&&
		(m_0_cCommands.GetCurSel()!=-1)
		)
		{
		int action=m_0_cCommands.GetCurSel();
		m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Commands.m_Actions[action].SetActionType(m_0_cCommandTab.GetCurSel());
		if(pResult)ModifyActionInfo(action);
		SetActionControls(&m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Commands.m_Actions[action]);
		}
	if(pResult) *pResult = 0;
	}


void CSettingsDlg::OnTcnSelchange2Settingstab(NMHDR *pNMHDR, LRESULT *pResult)
	{
	SetPosition(m_cMainTab.GetCurSel(),m_2_cSettingsTab.GetCurSel(),-1,-1);
	if(pResult)*pResult = 0;
	}


void CSettingsDlg::OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult)
	{
	//LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	TRACE(_T("== OnTvnSelchangedTree()\n"));
	m_bDraw=1;
	HTREEITEM hItem=m_0_cTree.GetSelectedItem();
	if(hItem!=NULL)
		{
		DWORD_PTR data=m_0_cTree.GetItemData(hItem);
		if(data<1000)
			{
			SetGestureTabState(2);
			if(m_Position[0]==1)// !=0
				SetPosition(1,0,-1,-1);
			//m_Position[1]=0;
			//SetVisibilityGroup(1,1,0,1,false,2);
			}
		else
			{
			int number=m_pIdentify->m_Tunnel.GetNumberById((int)data);
			if(number<0)number=0;
			m_ActiveGestureNumber=number;
			if(m_pIdentify->m_Gestures[number].m_GroupStatus==0)
				{
				SetPosition(1,1,m_Position[2],m_Position[3]);
				SetGestureTabState(0);
				// общее
				m_0_cGestureName.SetWindowText(m_pIdentify->m_Gestures[number].m_Name);
				m_0_cGestureDescription.SetWindowText(m_pIdentify->m_Gestures[number].m_Description);
				// комманды
				m_0_cCommands.ResetContent();
				for(int i=0;i<m_pIdentify->m_Gestures[number].m_Commands.m_nActions;i++)
					m_0_cCommands.AddString(m_pIdentify->m_Gestures[number].m_Commands.m_Actions[i].GetDescription());
				m_0_cCommands.SetCurSel(0);
				OnLbnSelchange0Commands();
				// совместимость
				m_3_cCompatibilityList.ResetContent();
				m_3_cCompatibilityType.SetCurSel(m_pIdentify->m_Gestures[number].m_Compatibility.m_Type);
				for(int i=0;i<m_pIdentify->m_Gestures[number].m_Compatibility.m_nStrings;i++)
					m_3_cCompatibilityList.AddString(m_pIdentify->m_Gestures[number].m_Compatibility.m_Strings[i]);
				m_3_cCompatibilityList.SetCurSel(0);
				// активность
				m_0_cGestureEnable.SetCheck(m_pIdentify->m_Gestures[number].m_Disable);

				OnCbnSelchange3CompatibilityType();
				OnLbnSelchange3CompatibilityList();
				}
			else
				{
				SetPosition(1,2,m_Position[2],m_Position[3]);
				SetGestureTabState(1);
				m_0_cGestureName.SetWindowText(m_pIdentify->m_Gestures[number].m_Name);
				m_0_cGestureDescription.SetWindowText(m_pIdentify->m_Gestures[number].m_Description);
				}
			//m_0_cCommandTab.EnableWindow(m_pIdentify->m_Gestures[number].m_Commands.m_nActions>0);
			}
		}
	if(pResult)*pResult=0;
	}

void CSettingsDlg::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
	{
	// на случай если невнятные координаты
	if (point.x == -1 && point.y == -1)
		{
		CRect rect;
		GetClientRect(rect);
		ClientToScreen(rect);
		point = rect.TopLeft();
		point.Offset(5, 5);
		}
	GetCursorPos(&point);

	int menuId=-1;
	CRect r;
	//	m_0_cTree.GetWindowRect(r);
	//	if(r.PtInRect(point)){menuId=0;goto m;}
	if(m_0_cCommands.IsWindowVisible())
		{
		m_0_cCommands.GetWindowRect(r);
		if(r.PtInRect(point)){menuId=IDR_COMMANDMENU;goto m;}
		}
	if(m_3_cCompatibilityList.IsWindowVisible() && m_3_cCompatibilityList.IsWindowEnabled())
		{
		m_3_cCompatibilityList.GetWindowRect(r);
		if(r.PtInRect(point)){menuId=IDR_COMPATIBILITYMENU;goto m;}
		}
	if(m_2_cIgnoreProgramList.IsWindowVisible() && m_2_cIgnoreProgramList.IsWindowEnabled())
		{
		m_2_cIgnoreProgramList.GetWindowRect(r);
		if(r.PtInRect(point)){menuId=IDR_IGNOREPROGRAMMENU;goto m;}
		}
m:
	if(menuId>=0)
		{
		CMenu menu;
		switch(menuId)
			{
			case IDR_COMMANDMENU:
				m_0_cCommands.SendMessage(WM_LBUTTONDOWN,MK_LBUTTON,(point.x-r.left)+(point.y-r.top)*65536);
				m_0_cCommands.SendMessage(WM_LBUTTONUP,MK_LBUTTON,(point.x-r.left)+(point.y-r.top)*65536);
				break;
			case IDR_COMPATIBILITYMENU:
				m_3_cCompatibilityList.SendMessage(WM_LBUTTONDOWN,MK_LBUTTON,(point.x-r.left)+(point.y-r.top)*65536);
				m_3_cCompatibilityList.SendMessage(WM_LBUTTONUP,MK_LBUTTON,(point.x-r.left)+(point.y-r.top)*65536);
				break;
			case IDR_IGNOREPROGRAMMENU:
				m_2_cIgnoreProgramList.SendMessage(WM_LBUTTONDOWN,MK_LBUTTON,(point.x-r.left)+(point.y-r.top)*65536);
				m_2_cIgnoreProgramList.SendMessage(WM_LBUTTONUP,MK_LBUTTON,(point.x-r.left)+(point.y-r.top)*65536);
				break;
			}
		menu.LoadMenu(menuId);
		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		theProperties.m_Language.LocalizationMenu(pPopup->GetSafeHmenu(),menuId);
		CWnd* pWndPopupOwner = this;
		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, pWndPopupOwner);
		}
	}

void CSettingsDlg::OnNMRclickTree(NMHDR *pNMHDR, LRESULT *pResult)
	{
	TRACE(_T("OnNMRclickTree\n"));
	CPoint ptMousePos;
	::GetCursorPos(&ptMousePos);
	CPoint point=ptMousePos;
	m_0_cTree.ScreenToClient(&ptMousePos);
	UINT uFlags;
	HTREEITEM htItem=m_0_cTree.HitTest(ptMousePos, &uFlags);
	if(htItem==NULL)return;
	m_0_cTree.SelectItem(htItem);
	int data=(int)m_0_cTree.GetItemData(htItem);
	if(data==1)return;

	if(TVHT_ONITEM & uFlags)
		{
		m_0_cTree.SelectItem(htItem);
		CMenu menu;
		menu.LoadMenu(IDR_GESTUREMENU);
		CMenu* pPopup=menu.GetSubMenu(0);
		theProperties.m_Language.LocalizationMenu(pPopup->GetSafeHmenu(),IDR_GESTUREMENU);
		ASSERT(pPopup!=NULL);
		CWnd* pWndPopupOwner=this;

		while(pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);

		*pResult = 0;
		}
	}



// [*----] реакиця на комманду "удалить жест/группу"
void CSettingsDlg::OnDelGesture()
	{
	HTREEITEM hItem=m_0_cTree.GetSelectedItem();
	int data=(int)m_0_cTree.GetItemData(hItem);

	if(data>=1000)
		{
		int number=m_pIdentify->m_Tunnel.GetNumberById(data);
		switch(m_pIdentify->m_Gestures[number].m_GroupStatus)
			{
			case 0: // жест
				m_pIdentify->m_Gestures.RemoveAt(number);
				m_pIdentify->m_nGestures--;
				m_pIdentify->m_Tunnel.Delete(number);
				m_0_cTree.DeleteItem(hItem);
				break;
			case 1:
				if(AfxMessageBox(_lng(_T("Settings-Message-DeleteGroupQuestion")),MB_ICONEXCLAMATION|MB_YESNO,0)==6)
					{
					int level=1;
					int i=0;
					for(i=number+1;i<m_pIdentify->m_nGestures;i++)
						{
						if(m_pIdentify->m_Gestures[i].m_GroupStatus==1)level++;
						if(m_pIdentify->m_Gestures[i].m_GroupStatus==2)level--;
						if(level==0)break;
						}
					i=i-number+1;
					m_pIdentify->m_Gestures.RemoveAt(number,i);
					m_pIdentify->m_nGestures-=i;
					m_pIdentify->m_Tunnel.Delete(number,i);
					m_0_cTree.DeleteItem(hItem);
					}
				break;
			default:
				ASSERT(FALSE);
			}
		}
	}

// [*----] функция добавляет в базу данных и дерево жест или папку
void CSettingsDlg::InsertGesture(int type)
	{
	// 0 - группа
	// 1 - жест
	HTREEITEM hItem=m_0_cTree.GetSelectedItem();
	int data=(int)m_0_cTree.GetItemData(hItem);
	if((data>=1000)||(data==0))
		{
		// поиск родителей
		int position=-1;
		HTREEITEM parent=NULL;

		if(data!=0)
			if(m_pIdentify->GetGestureById(data)->m_GroupStatus==1)
				parent=hItem;
			else
				parent=m_0_cTree.GetParentItem(hItem);

		if(parent!=NULL)
			position=m_pIdentify->m_Tunnel.GetNumberById(data);
		position++;

		if(parent==NULL)parent=hItem;

		if(type==0)
			{
			// группа, два элемента
			CGesture gesture;
			gesture.m_Name=_lng(_T("Settings-Other-NewGroup"));
			gesture.m_GroupStatus=1;
			m_pIdentify->m_Gestures.InsertAt(position,gesture);
			gesture.m_Description.Empty();
			gesture.m_GroupStatus=2;
			m_pIdentify->m_Gestures.InsertAt(position+1,gesture);
			m_pIdentify->m_nGestures+=2;
			}
		else
			{
			// жест, один элемента
			CGesture gesture;
			gesture.m_Name=_lng(_T("Settings-Other-NewGesture"));
			gesture.m_GroupStatus=0;
			if(m_pIdentify->GestureLimit())gesture.m_Disable=true;
			m_pIdentify->m_Gestures.InsertAt(position,gesture);
			m_pIdentify->m_nGestures++;
			}
		// добавляем элемент в дерево
		HTREEITEM thTreeItem;
		TV_INSERTSTRUCT tvinsert;
		tvinsert.hParent=parent;
		tvinsert.hInsertAfter=TVI_SORT;
		tvinsert.item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
		tvinsert.item.hItem=NULL; 
		tvinsert.item.state=0;
		tvinsert.item.stateMask=0;
		tvinsert.item.cchTextMax=6;
		tvinsert.item.cChildren=0;
		tvinsert.item.lParam=0;

		CString s;
		s=m_pIdentify->m_Gestures[position].m_Name;
		tvinsert.item.pszText=s.GetBuffer(s.GetLength());
		if(type==0)
			{
			tvinsert.item.iImage=0;
			tvinsert.item.iSelectedImage=0;
			}
		else
			{
			if(m_pIdentify->GestureLimit())
				{
				tvinsert.item.iImage=3;
				tvinsert.item.iSelectedImage=3;
				}
			else
				{
				tvinsert.item.iImage=2;
				tvinsert.item.iSelectedImage=2;
				}
			}
		thTreeItem=m_0_cTree.InsertItem(&tvinsert);
		m_0_cTree.Expand(parent,TVE_EXPAND);

		if(type==0)
			{
			// модифицируем туннель
			// раздвигаем в тунеле в pisition на два пункта
			// добавляем в тунель соотвествие папки в дереве с элементом открытия группы
			m_pIdentify->m_Tunnel.InsertSpace(position,2);
			}
		else
			{
			m_pIdentify->m_Tunnel.InsertSpace(position,1);
			}
		m_0_cTree.SetItemData(thTreeItem,m_pIdentify->m_Tunnel.Add(position));
		m_0_cTree.Sort(parent);
		}
	}

// [*----] обработчик комманды "добавить жест"
void CSettingsDlg::OnAddGesture()
	{
	InsertGesture(1);
	}

// [*----] обработчик комманды "добавить группу"
void CSettingsDlg::OnAddGroup()
	{
	InsertGesture(0);
	}

// [*----] обработчик даблклика по дереву, сознание нового жеста
void CSettingsDlg::OnNMDblclkTree(NMHDR *pNMHDR, LRESULT *pResult)
	{
	HTREEITEM hItem=m_0_cTree.GetSelectedItem();
	int data=(int)m_0_cTree.GetItemData(hItem);
	if(data>=1000)
		{
		int number=m_pIdentify->m_Tunnel.GetNumberById(data);
		if(number>=0)
			if(m_pIdentify->m_Gestures[number].m_GroupStatus==0)
				InsertGesture(1);
		}
	if(pResult)*pResult=0;
	}


void CSettingsDlg::SetGestureTabState(int state)
	{
	// перерисовка изображения симолов, если надо
	if((state==0)&&(m_0_cGestureTab.GetCurSel()==2))
		OnRedrawTabContent(0,0);

	//m_static[2]
	if(state==m_static[2])return;
	m_static[2]=state;

	TCHAR buffer[1024];
	TC_ITEM tci;
	memset(&tci,0,sizeof(tci));
	tci.mask=TCIF_TEXT;
	tci.pszText=buffer;
	m_0_cGestureTab.DeleteAllItems();
	switch(state)
		{
		case 0: // обычный жест
			StringCopy(_lng(_T("Settings-GestureTab-Description")),tci.pszText);
			m_0_cGestureTab.InsertItem(0,&tci);
			StringCopy(_lng(_T("Settings-GestureTab-Commands")),tci.pszText);
			m_0_cGestureTab.InsertItem(1,&tci);
			StringCopy(_lng(_T("Settings-GestureTab-Symbols")),tci.pszText);
			m_0_cGestureTab.InsertItem(2,&tci);
			StringCopy(_lng(_T("Settings-GestureTab-Compatibility")),tci.pszText);
			m_0_cGestureTab.InsertItem(3,&tci);
			break;
		case 1: // группа жестов
			StringCopy(_lng(_T("Settings-GestureTab-Description")),tci.pszText);
			m_0_cGestureTab.InsertItem(0,&tci);
			break;
		case 2: // корень жестов
			StringCopy(_lng(_T("Settings-Tree-Gestures")),tci.pszText);
			m_0_cGestureTab.InsertItem(0,&tci);
			break;
		default:
			tci.pszText = _T("[SettingsDlg.h]: InternalError.");
			m_0_cGestureTab.InsertItem(0,&tci);
			break;
		}
	OnTcnSelchange0Gesturetab(NULL,NULL);
	// чтобы визуализация выполнялась немедленно
	MessagePause();
	}

void CSettingsDlg::SetCommandTabState(int state)
	{
	//m_static[3]
	if(state==m_static[3])return;
	m_static[3]=state;

	TCHAR buffer[1024];
	TC_ITEM tci;
	memset(&tci,0,sizeof(tci));
	tci.mask=TCIF_TEXT;
	tci.pszText=buffer;
	m_0_cCommandTab.DeleteAllItems();
	switch(state)
		{
		case 0: // команда
			StringCopy(_lng(_T("Settings-CommandTab-Simply")),tci.pszText);
			m_0_cCommandTab.InsertItem(0,&tci);
			StringCopy(_lng(_T("Settings-CommandTab-Start")),tci.pszText);
			m_0_cCommandTab.InsertItem(1,&tci);
			StringCopy(_lng(_T("Settings-CommandTab-Text")),tci.pszText);
			m_0_cCommandTab.InsertItem(2,&tci);
			StringCopy(_lng(_T("Settings-CommandTab-Keyboard")),tci.pszText);
			m_0_cCommandTab.InsertItem(3,&tci);
			StringCopy(_lng(_T("Settings-CommandTab-Message")),tci.pszText);
			m_0_cCommandTab.InsertItem(4,&tci);
			break;
		case 1: // нет команды
			StringCopy(_lng(_T("Settings-CommandTab-NoSelect")),tci.pszText);
			m_0_cCommandTab.InsertItem(0,&tci);
			break;
		default:
			tci.pszText = _T("[SettingsDlg.h]: InternalError.");
			m_0_cCommandTab.InsertItem(0,&tci);
			break;
		}
	}

void CSettingsDlg::OnLbnSelchange0Commands()
	{
	int number=m_0_cCommands.GetCurSel();
	TRACE(_T("OnLbnSelchange0Commands  %i\n"),number);

	m_0_cCommandTab.EnableWindow(number!=-1);

	if(number<0)
		{
		SetCommandTabState(1);
		TRACE(_T("Erasing command control. position[3]=%i\n"),m_Position[3]);
		SetVisibilityGroup(1,1,1,m_Position[3],false,3);
		return;
		}
	else
		{
		SetCommandTabState(0);
		if(m_0_cGestureTab.GetCurSel()==1)
			SetVisibilityGroup(1,1,1,m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Commands.m_Actions[number].m_Type,true,3);
		}

	m_0_cCommandTab.SetCurSel(m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Commands.m_Actions[number].m_Type);
	OnTcnSelchange0Commandtab(NULL,NULL);
	}

void CSettingsDlg::SetActionControls(CAction* pAction)
	{
	TRACE(_T("SetActionControls\n"));
	m_bControlSettings=true;
	switch(pAction->m_Type)
		{
		case 0:
			for(int i=0;i<StandartActionCount;i++)
				if(StandartAction[i]==pAction->m_Param[0])
					{
					m_0_0_cCommands.SetCurSel(i);
					break;
					}
				break;
		case 1:
			m_0_1_cName.SetWindowText(pAction->m_Param[0]);
			m_0_1_cPath.SetWindowText(pAction->m_Param[1]);
			m_0_1_cParam.SetWindowText(pAction->m_Param[2]);
			break;
		case 2:
			m_0_2_cText.SetWindowText(pAction->m_Param[0]);
			break;
		case 3:
			{
			int type=0,key=0;
			HTREEITEM hParent=NULL;
			CString s=pAction->m_Param[0];
			m_0_3_cKeyTree.DeleteAllItems();
			if(s.IsEmpty())
				{
				hParent=m_0_3_cKeyTree.InsertItem(_lng(_T("Settings-Gesture-Command-Keyboard-Empty")),0,0,NULL,TVI_LAST);
				m_0_3_cKeyTree.SetItemData(hParent,-1);
				}
			while(!s.IsEmpty())
				{
				TRACE(_T("g"));
				CAction::GetKeyElement(s,type,key);
				if(type==0)
					{
					hParent=m_0_3_cKeyTree.InsertItem(GetNameByCode(key),0,0,hParent,TVI_LAST);
					m_0_3_cKeyTree.SetItemData(hParent,key);
					}
				else
					{
					hParent=m_0_3_cKeyTree.GetParentItem(hParent);
					}
				}
			m_0_3_cKeyTree.SelectItem(hParent);
			}
		break;
		case 4:
			m_0_4_cNumber.SetWindowText(pAction->m_Param[0]);
			m_0_4_cWParam.SetWindowText(pAction->m_Param[1]);
			m_0_4_cLParam.SetWindowText(pAction->m_Param[2]);
			break;
		}
	m_bControlSettings=false;
	}

void CSettingsDlg::OnAddCommand()
	{
	int number=m_0_cCommands.GetCurSel();
	if(number==-1)number=0;
	CAction action;
	action.m_Type=0;
	action.m_Param[0]=_T("Maximize");
	m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Commands.m_Actions.InsertAt(number,action);
	m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Commands.m_nActions++;
	m_0_cCommands.InsertString(number,action.GetDescription());
	number++;
	if(number>=m_0_cCommands.GetCount()) number=m_0_cCommands.GetCount()-1;
	m_0_cCommands.SetCurSel(number);
	OnLbnSelchange0Commands();
	}


void CSettingsDlg::OnDelCommand()
	{
	int number=m_0_cCommands.GetCurSel();
	if(number!=-1)
		{
		m_0_cCommands.DeleteString(number);
		m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Commands.m_Actions.RemoveAt(number);
		m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Commands.m_nActions--;
		if(number>=m_0_cCommands.GetCount()) number=m_0_cCommands.GetCount()-1;
		m_0_cCommands.SetCurSel(number);
		}
	OnLbnSelchange0Commands();
	}

void CSettingsDlg::OnCommandUp()
	{
	int position=m_0_cCommands.GetCurSel();
	if
		(
		(m_0_cCommands.GetCount()>0)&&
		(m_ActiveGestureNumber!=-1)&&
		(position>0)
		)
		{
		CAction action;
		action=m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Commands.m_Actions[position];
		m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Commands.m_Actions[position]=m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Commands.m_Actions[position-1];
		m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Commands.m_Actions[position-1]=action;

		m_0_cCommands.DeleteString(position);
		m_0_cCommands.InsertString(position-1,m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Commands.m_Actions[position-1].GetDescription());
		m_0_cCommands.SetCurSel(position-1);
		}
	}

void CSettingsDlg::OnCommandDown()
	{
	int position=m_0_cCommands.GetCurSel();
	if
		(
		(m_0_cCommands.GetCount()>0)&&
		(m_ActiveGestureNumber!=-1)&&
		(position>=0)&&
		(position+1<m_0_cCommands.GetCount())
		)
		{
		CAction action;
		action=m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Commands.m_Actions[position];
		m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Commands.m_Actions[position]=m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Commands.m_Actions[position+1];
		m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Commands.m_Actions[position+1]=action;

		m_0_cCommands.DeleteString(position);
		m_0_cCommands.InsertString(position+1,m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Commands.m_Actions[position+1].GetDescription());
		m_0_cCommands.SetCurSel(position+1);
		}
	}

void CSettingsDlg::ModifyActionInfo(int number)
	{
	m_0_cCommands.DeleteString(number);
	m_0_cCommands.InsertString(number,m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Commands.m_Actions[number].GetDescription());
	m_0_cCommands.SetCurSel(number);
	}
void CSettingsDlg::OnLbnSelchange00Commands()
	{
	TRACE(_T("OnLbnSelchange00Commands\n"));
	if(m_bControlSettings)return;
	int number=m_0_cCommands.GetCurSel();
	if(number!=-1)
		{
		long i=m_0_0_cCommands.GetCurSel();
		CString s;
		if(i<StandartActionCount)
			s=StandartAction[i];
		else
			s=_T("InternalError");
		m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Commands.m_Actions[number].m_Param[0]=s;
		ModifyActionInfo(number);
		}
	}
void CSettingsDlg::OnEnChange01Name()
	{
	TRACE(_T("OnEnChange01Name\n"));
	if(m_bControlSettings)return;
	//CString s;
	int number=m_0_cCommands.GetCurSel();
	if(number==-1)return;
	m_0_1_cName.GetWindowText(m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Commands.m_Actions[number].m_Param[0]);
	m_0_1_cPath.GetWindowText(m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Commands.m_Actions[number].m_Param[1]);
	m_0_1_cParam.GetWindowText(m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Commands.m_Actions[number].m_Param[2]);
	ModifyActionInfo(number);
	}

void CSettingsDlg::OnEnChange01Path()
	{OnEnChange01Name();}

void CSettingsDlg::OnEnChange01Param()
	{OnEnChange01Name();}

void CSettingsDlg::OnEnChange02Text()
	{
	TRACE(_T("OnEnChange02Text\n"));
	if(m_bControlSettings)return;
	int number=m_0_cCommands.GetCurSel();
	if(number==-1)return;
	m_0_2_cText.GetWindowText(m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Commands.m_Actions[number].m_Param[0]);
	ModifyActionInfo(number);
	}
// [*----] обработка нажатий, если фокус на дереве кнопок
void CSettingsDlg::KeyEvent(MSG* pMsg)
	{
	// удаляем повторения
	static WPARAM oldKey=0;
	if(pMsg->message==WM_KEYDOWN)
		{
		bool b=false;
		if(oldKey==pMsg->wParam)b=true;
		oldKey=pMsg->wParam;
		if(b)return;
		}
	HTREEITEM hKeyItem=m_0_3_cKeyTree.GetSelectedItem();
	if(hKeyItem==NULL)return;
	if(pMsg->message==WM_KEYDOWN)
		{
		if(m_0_3_cKeyTree.GetItemData(hKeyItem)==-1)
			{
			m_0_3_cKeyTree.SetItemText(hKeyItem,GetNameByCode(pMsg->wParam));
			m_0_3_cKeyTree.SetItemData(hKeyItem,(DWORD)pMsg->wParam);
			m_0_3_cKeyTree.SelectItem(hKeyItem);
			}
		else
			{
			HTREEITEM hNewItem=m_0_3_cKeyTree.InsertItem(GetNameByCode(pMsg->wParam),0,0,hKeyItem,TVI_LAST);
			m_0_3_cKeyTree.SetItemData(hNewItem,pMsg->wParam);
			m_0_3_cKeyTree.SelectItem(hNewItem);
			}
		}
	if(pMsg->message==WM_KEYUP)
		{
		hKeyItem=m_0_3_cKeyTree.GetParentItem(hKeyItem);
		if(hKeyItem!=NULL)m_0_3_cKeyTree.SelectItem(hKeyItem);
		oldKey=0;
		}
	OnTvnSelchanged03KeyTree(NULL,NULL);
	}

void CSettingsDlg::OnEnChange04Number()
	{
	if(m_bControlSettings)return;
	int number=m_0_cCommands.GetCurSel();
	if(number==-1)return;
	CString s[3];
	m_0_4_cNumber.GetWindowText(s[0]);
	m_0_4_cWParam.GetWindowText(s[1]);
	m_0_4_cLParam.GetWindowText(s[2]);
	for(int i=0;i<3;i++)
		{	
		CorrectNumber(s[i]);
		m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Commands.m_Actions[number].m_Param[i]=s[i];
		}
	ModifyActionInfo(number);
	}

void CSettingsDlg::OnEnChange04Wparam()
	{OnEnChange04Number();}

void CSettingsDlg::OnEnChange04Lparam()
	{OnEnChange04Number();}


void CSettingsDlg::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
	{
	CDialog::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	// Команды
	bool b=m_0_cCommands.GetCount()==0;
	pPopupMenu->EnableMenuItem(IDM_DELCOMMAND,b);
	pPopupMenu->EnableMenuItem(IDM_COMMANDUP,b||(m_0_cCommands.GetCurSel()==0));
	pPopupMenu->EnableMenuItem(IDM_COMMANDDOWN,b||(m_0_cCommands.GetCurSel()+1>=m_0_cCommands.GetCount()));
	// Жесты
	pPopupMenu->EnableMenuItem(IDM_DELGESTURE,m_0_cTree.GetItemData(m_0_cTree.GetSelectedItem())<1000);
	pPopupMenu->EnableMenuItem(IDM_DELCOMPATIBILITY,m_3_cCompatibilityList.GetCurSel()==-1);
	pPopupMenu->EnableMenuItem(IDM_DELIGNOREPROGRAM,m_2_cIgnoreProgramList.GetCurSel()==-1);
	// Клавиши
	HTREEITEM hItem=m_0_3_cKeyTree.GetSelectedItem();
	b=(hItem==NULL);

	pPopupMenu->EnableMenuItem(IDM_KEYDELETE,b||(m_0_3_cKeyTree.GetItemData(hItem)==-1));
	pPopupMenu->EnableMenuItem(IDM_INSERTKEYINSIDE,b||(m_0_3_cKeyTree.GetItemData(hItem)==-1));
	pPopupMenu->EnableMenuItem(IDM_KEYMOVEUP,b||(m_0_3_cKeyTree.GetPrevSiblingItem(hItem)==NULL));
	pPopupMenu->EnableMenuItem(IDM_KEYMOVEDOWN,b||(m_0_3_cKeyTree.GetNextSiblingItem(hItem)==NULL));

	/*

	pPopupMenu->CheckMenuItem(IDM_ENABLE, MF_BYCOMMAND | (MF_CHECKED*m_bHookActive));

	bool b=m_0_cCommandList.GetCount()==0;
	pPopupMenu->EnableMenuItem(IDM_DELGESTURE,b);
	pPopupMenu->EnableMenuItem(IDM_ADDGESTURE,m_pIdentify->m_nGestures+1>=MAXGESTURES);
	pPopupMenu->EnableMenuItem(IDM_GESTUREUP,b||(m_0_cCommandList.GetCurSel()==0));
	pPopupMenu->EnableMenuItem(IDM_GESTUREDOWN,b||(m_0_cCommandList.GetCurSel()+1>=m_0_cCommandList.GetCount()));

	b=m_0_cCommandElementList.GetCount()==0;
	pPopupMenu->EnableMenuItem(IDM_DELCOMMAND,b);
	pPopupMenu->EnableMenuItem(IDM_COMMANDUP,b||(m_0_cCommandElementList.GetCurSel()==0));
	pPopupMenu->EnableMenuItem(IDM_COMMANDDOWN,b||(m_0_cCommandElementList.GetCurSel()+1>=m_0_cCommandElementList.GetCount()));

	*/
	}

// [*----] первичный перехват всех сообщений
BOOL CSettingsDlg::PreTranslateMessage(MSG* pMsg)
	{
	// передача информации тултипам
	if(pMsg->message >= WM_MOUSEFIRST && pMsg->message <= WM_MOUSELAST)
		m_cToolTip.RelayEvent(pMsg);
	
	// обработка клавиш
	//if(m_0_3_cKeyTree.IsWindowVisible())
	if(GetFocus()==&m_0_3_cKeyTree)
		if(pMsg->message==WM_KEYDOWN || pMsg->message==WM_KEYUP)
			{
			KeyEvent(pMsg);
			return TRUE;
			}
	

	//if(TranslateAccelerator(GetSafeHwnd(),m_Accel,pMsg))
	//	return TRUE;
	// попытка обработать как акселератор
	TranslateAccelerator(GetSafeHwnd(),m_Accel,pMsg);// думаю лучше не убивать сообщения...
	
	// перехват двойного клика
	if(pMsg->message==WM_LBUTTONDBLCLK)
		{
		if(GetFocus()==&m_0_cCommands)
			OnAddCommand();
		if(GetFocus()==&m_3_cCompatibilityList)
			OnAddCompatibility();
		if(GetFocus()==&m_2_cIgnoreProgramList)
			OnAddIgnoreProgram();
		}
	return CDialog::PreTranslateMessage(pMsg);
	}

void CSettingsDlg::OnKeyAdd()
	{
	if(GetFocus()==&m_0_cTree)
		OnAddGesture();
	if(GetFocus()==&m_0_cCommands)
		OnAddCommand();
	if(GetFocus()==&m_3_cCompatibilityList)
		OnAddCompatibility();
	if(GetFocus()==&m_2_cIgnoreProgramList)
		OnAddIgnoreProgram();
	}

void CSettingsDlg::OnKeyAddGroup()
	{
	if(GetFocus()==&m_0_cTree)
		OnAddGroup();
	}

void CSettingsDlg::OnKeyDel()
	{
	if(GetFocus()==&m_0_cTree)
		OnDelGesture();
	if(GetFocus()==&m_0_cCommands)
		OnDelCommand();
	if(GetFocus()==&m_3_cCompatibilityList)
		OnDelCompatibility();
	if(GetFocus()==&m_2_cIgnoreProgramList)
		OnDelIgnoreProgram();
	}

void CSettingsDlg::OnKeyDown()
	{
	if(GetFocus()==&m_0_cCommands)
		OnCommandDown();
	}

void CSettingsDlg::OnKeyUp()
	{
	if(GetFocus()==&m_0_cCommands)
		OnCommandUp();
	}

void CSettingsDlg::OnLbnSelchange3CompatibilityList()
	{
	int number=m_3_cCompatibilityList.GetCurSel();
	if(number>=0)
		m_3_cCompatibilityEdit.SetWindowText(m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Compatibility.m_Strings[number]);
	else
		m_3_cCompatibilityEdit.SetWindowText(_T(""));
	m_3_cCompatibilityEdit.EnableWindow(m_3_cCompatibilityList.GetCount()>0);
	}

void CSettingsDlg::OnEnChange3CompatibilityEdit()
	{
	int number=m_3_cCompatibilityList.GetCurSel();
	if(number>=0)
		{
		CString s;
		m_3_cCompatibilityEdit.GetWindowText(s);
		m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Compatibility.m_Strings[number]=s;
		m_3_cCompatibilityList.DeleteString(number);
		m_3_cCompatibilityList.InsertString(number,s);
		m_3_cCompatibilityList.SetCurSel(number);
		}
	}

// [*----] обработчик изменения типа совместимости для жеста
void CSettingsDlg::OnCbnSelchange3CompatibilityType()
	{
	int type=m_3_cCompatibilityType.GetCurSel();
	if(type==0)
		{
		m_3_cCompatibilityEdit.SetWindowText(_T(""));
		m_3_cCompatibilityList.ResetContent();
		m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Compatibility.m_Strings.RemoveAll();
		m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Compatibility.m_nStrings=0;
		m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Compatibility.m_Type=0;
		}
	m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Compatibility.m_Type=type;
	m_3_cCompatibilityList.EnableWindow(type!=0);
	m_3_cCompatibilityEdit.EnableWindow((type!=0)&&(m_3_cCompatibilityList.GetCount()>0));
	}
// [*----] добавление новых программ в список (не)совеместимости
void CSettingsDlg::OnAddCompatibility()
	{
	int &nStrings=m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Compatibility.m_nStrings;
	CString s=_T("");// "Новая программа"
	m_3_cCompatibilityList.AddString(s);
	m_3_cCompatibilityList.SetCurSel(nStrings);
	m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Compatibility.m_Strings.SetAtGrow(nStrings,s);
	nStrings++;
	OnLbnSelchange3CompatibilityList();
	}

void CSettingsDlg::OnDelCompatibility()
	{
	int number=m_3_cCompatibilityList.GetCurSel();
	if(number<0)return;
	CString s;
	m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Compatibility.m_Strings.RemoveAt(number);
	m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Compatibility.m_nStrings--;
	m_3_cCompatibilityList.DeleteString(number);
	if(number>=m_3_cCompatibilityList.GetCount())
		number=m_3_cCompatibilityList.GetCount()-1;
	m_3_cCompatibilityList.SetCurSel(number);
	OnLbnSelchange3CompatibilityList();
	}

void CSettingsDlg::OnEnChange0Gesturename()
	{
	if(m_ActiveGestureNumber>=0)
		{
		CString &name=m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Name;
		m_0_cGestureName.GetWindowText(name);
		HTREEITEM hItem;
		hItem=m_0_cTree.GetSelectedItem();
		//проверка на совпадение
		//		
		//		if(m_pIdentify->m_Tunnel.GetNumberById(m_0_cTree.GetItemData(hItem))==m_ActiveGestureNumber)
		m_0_cTree.SetItemText(hItem,name);
		m_0_cTree.Sort(m_0_cTree.GetParentItem(hItem));
		}
	}

// [*----] клик по галочки "активный жест"
void CSettingsDlg::OnBnClicked0GestureEnable()
	{
	int check=m_0_cGestureEnable.GetCheck();
	if(m_ActiveGestureNumber>=0)
		{
		if((check==0)&&m_pIdentify->GestureLimit())
			{
			m_0_cGestureEnable.SetCheck(1);
			AfxMessageBox(_lng(_T("Settings-Message-GestureLimitOut")),MB_ICONASTERISK|MB_OK,0);
			return;
			}
		m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Disable=(check==1);
		m_0_cTree.SetItemImage(m_0_cTree.GetSelectedItem(),2+check,2+check);
		}
	}

void CSettingsDlg::OnEnChange0Gesturedescription()
	{
	if(m_ActiveGestureNumber>=0)
		m_0_cGestureDescription.GetWindowText(m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Description);
	}


void CSettingsDlg::MessagePause(void)
	{
	return;
	MSG message;
	while(::PeekMessage(&message,NULL,0,0,PM_REMOVE))
		{
		::TranslateMessage(&message);
		::DispatchMessage(&message);
		}
	}

void CSettingsDlg::OnBnClicked01Browse()
	{
	CFileDialog dlg(TRUE,_T("All files"),_T("*.*"));
	if(dlg.DoModal()==IDOK)
		m_0_1_cName.SetWindowText(dlg.GetPathName());
	}


void CSettingsDlg::OnCancel()
	{
	WINDOWINFO wi;
	GetWindowInfo(&wi);
	theProperties.m_WindowPosition=wi.rcWindow;
	CDialog::OnCancel();
	}

void CSettingsDlg::OnOK()
	{
	//CDialog::OnOK();
	}

void CSettingsDlg::OnBnClicked2Systemactive()
	{
	m_pServer->PostMessage(WM_SETTINGS_DLG_MESSAGE,0,m_2_cSystemActive.GetCheck());
	}

void CSettingsDlg::OnBnClicked2Showballoon()
	{theProperties.m_ShowBalloon=m_2_cShowBalloon.GetCheck();}

void CSettingsDlg::OnBnClicked2Showsplash()
	{theProperties.m_ShowSplash=m_2_cShowSplash.GetCheck();}


void CSettingsDlg::OnBnClicked2Startup()
	{theProperties.SetAutoRunKey(m_2_cStartUp.GetCheck()!=0);}


void CSettingsDlg::OnCbnSelchange2Mousebutton()
	{
	theProperties.m_MouseButton=m_2_cMouseButton.GetCurSel();
	m_pServer->PostMessage(WM_SETTINGS_DLG_MESSAGE,1,0);
	}


void CSettingsDlg::OnCbnSelchange2Disablekey()
	{
	theProperties.m_DisableKey=m_2_cDisableKey.GetCurSel();
	m_pServer->PostMessage(WM_SETTINGS_DLG_MESSAGE,1,0);
	}

void CSettingsDlg::OnLbnSelchange2IgnoreProgramList()
	{
	int number=m_2_cIgnoreProgramList.GetCurSel();
	if(number>=0)
		{
		CString s;
		m_2_cIgnoreProgramList.GetText(number,s);
		m_2_cIgnoreProgramEdit.SetWindowText(s);
		}
	else
		m_2_cIgnoreProgramEdit.SetWindowText(_T(""));
	m_2_cIgnoreProgramEdit.EnableWindow(m_2_cIgnoreProgramList.GetCount()>0);
	OnEnChange2IgnoreProgramEdit();
	}

void CSettingsDlg::OnEnChange2IgnoreProgramEdit()
	{
	int number=m_2_cIgnoreProgramList.GetCurSel();
	if(number>=0)
		{
		CString s;
		m_2_cIgnoreProgramEdit.GetWindowText(s);
		m_2_cIgnoreProgramList.DeleteString(number);
		m_2_cIgnoreProgramList.InsertString(number,s);
		m_2_cIgnoreProgramList.SetCurSel(number);

		CString &ignore=theProperties.m_IgnoreProgram;
		ignore.Empty();
		int count=m_2_cIgnoreProgramList.GetCount();
		for(int i=0;i<count;i++)
			{
			m_2_cIgnoreProgramList.GetText(i,s);
			if(s.IsEmpty())continue;
			if(i+1!=count)s+=_T("\1");
			ignore+=s;
			}
		while(1)
			{
			if(ignore.IsEmpty())
				break;
			else
				if(ignore.GetAt(ignore.GetLength()-1)==_T('\1'))
					ignore.Delete(ignore.GetLength()-1,1);
				else
					break;
			}
		}
	else
		theProperties.m_IgnoreProgram.Empty();
	m_pServer->PostMessage(WM_SETTINGS_DLG_MESSAGE,2,0);
	}

void CSettingsDlg::OnAddIgnoreProgram()
	{
	m_2_cIgnoreProgramList.AddString(_T(""));
	m_2_cIgnoreProgramList.SetCurSel(m_2_cIgnoreProgramList.GetCount()-1);
	//m_2_cIgnoreProgramEdit.SetWindowText(""));
	OnLbnSelchange2IgnoreProgramList();
	}

void CSettingsDlg::OnDelIgnoreProgram()
	{
	int number=m_2_cIgnoreProgramList.GetCurSel();
	if(number<0)return;
	m_2_cIgnoreProgramList.DeleteString(number);
	if(number>=m_2_cIgnoreProgramList.GetCount())
		number=m_2_cIgnoreProgramList.GetCount()-1;
	m_2_cIgnoreProgramList.SetCurSel(number);
	OnLbnSelchange2IgnoreProgramList();
	}

void CSettingsDlg::OnEnKillfocus2IgnoreProgramEdit()
	{
	m_pServer->PostMessage(WM_SETTINGS_DLG_MESSAGE,1,0);
	}

// [*----] 
void CSettingsDlg::OnEnChange2Username()
	{
	CString userkey,username;
	m_2_cRegistrationKey.GetWindowText(userkey);
	m_2_cUserName.GetWindowText(username);
	if((!userkey.IsEmpty())&&(!username.IsEmpty()))
		{
		theProperties.m_UserName=username;
		theProperties.m_RegKey=userkey;
		CString key=theProperties.GetKey();
		theProperties.bRegistred=(key==theProperties.m_RegKey);
		}
	if(theProperties.bRegistred)
		m_2_C_cSerialNumberStatus.SetWindowText(_lng(_T("Settings-Message-SerialStatus-Valid")));
	else
		m_2_C_cSerialNumberStatus.SetWindowText(_lng(_T("Settings-Message-SerialStatus-Invalid")));
	}

// [*----] 
void CSettingsDlg::OnEnChange2Registrationkey()
	{
	OnEnChange2Username();
	}

void CSettingsDlg::OnEnSetfocus2Registrationkey()
	{
	}

void CSettingsDlg::OnEnKillfocus2Registrationkey()
	{
	}





void CSettingsDlg::OnBnClicked2Browse()
	{
	CFileDialog dlg(TRUE,_T("Downright gesture"),_T("*.downright"));
	if(dlg.DoModal()==IDOK)
		{
		m_pIdentify->Save(theProperties.m_FileName);
		theProperties.m_FileName=dlg.GetPathName();
		m_2_cFileName.SetWindowText(theProperties.m_FileName);
		m_pIdentify->Load(theProperties.m_FileName);
		CreateTree();
		}
	}


void CSettingsDlg::OnCbnSelchange2Language()
	{
	m_2_cLanguage.GetWindowText(theProperties.m_LanguageName);
	theProperties.LoadLanguage();
	ApplyLanguage();
	m_2_cDisableKey.SetCurSel(theProperties.m_DisableKey);
	m_2_cMouseButton.SetCurSel(theProperties.m_MouseButton);
	m_cMainTab.SetCurSel(2);
	m_bDraw=1;
	OnRedrawTabContent(0,0);
	}

// [*----] дабл клик по дереву клавишь, добавление новой клавиши
void CSettingsDlg::OnNMDblclk03KeyTree(NMHDR *pNMHDR, LRESULT *pResult)
	{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	}
// [*----] правый клик по дереву клавишь, показ контекстного меню
void CSettingsDlg::OnNMRclick03KeyTree(NMHDR *pNMHDR, LRESULT *pResult)
	{
	CPoint ptMousePos;
	::GetCursorPos(&ptMousePos);
	CPoint point=ptMousePos;
	m_0_3_cKeyTree.ScreenToClient(&ptMousePos);
	UINT uFlags;
	HTREEITEM htItem=m_0_3_cKeyTree.HitTest(ptMousePos, &uFlags);
	if(htItem==NULL)return;
	m_0_3_cKeyTree.SelectItem(htItem);
	//int data=(int)m_0_3_cKeyTree.GetItemData(htItem);
	//if(data==1)return;

	if(TVHT_ONITEM & uFlags)
		{
		m_0_3_cKeyTree.SelectItem(htItem);
		CMenu menu;
		menu.LoadMenu(IDR_KEYMENU);
		CMenu* pPopup=menu.GetSubMenu(0);
		theProperties.m_Language.LocalizationMenu(pPopup->GetSafeHmenu(),IDR_KEYMENU);
		ASSERT(pPopup!=NULL);
		CWnd* pWndPopupOwner=this;

		while(pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);

		*pResult = 0;
		}
	}

// [*----] возвращает код выбранной в списке клавиши
int CSettingsDlg::GetSelectKey(void)
	{		
	HTREEITEM hKeyItem=m_0_3_cAllKeyTree.GetSelectedItem();
	if(hKeyItem==NULL)hKeyItem=m_0_3_cAllKeyTree.GetRootItem();
	int keyData=(int)m_0_3_cAllKeyTree.GetItemData(hKeyItem);
	if(keyData==-1)
		{
		hKeyItem=m_0_3_cAllKeyTree.GetChildItem(hKeyItem);
		m_0_3_cAllKeyTree.SelectItem(hKeyItem);
		keyData=(int)m_0_3_cAllKeyTree.GetItemData(hKeyItem);
		//m_0_3_cAllKeyTree.PostMessage(WM_PAINT);
		}
	return keyData;
	}
// реализация вставки клавиши
void CSettingsDlg::InsertKey(int position)
	{
	HTREEITEM hItem=m_0_3_cKeyTree.GetSelectedItem();
	if(hItem==NULL)return;
    int data=(int)m_0_3_cKeyTree.GetItemData(hItem);
	int keyData=GetSelectKey();
	if(data==-1)
		{
		// это элемент [пусто]
		m_0_3_cKeyTree.SetItemText(hItem,GetNameByCode(keyData));
		}
	else
		{
		// это обычный элемент
		if(position==0)
			{
			HTREEITEM hPrevItem=m_0_3_cKeyTree.GetPrevSiblingItem(hItem);
			if(hPrevItem==NULL)
				hItem=m_0_3_cKeyTree.InsertItem(GetNameByCode(keyData),0,0,m_0_3_cKeyTree.GetParentItem(hItem),TVI_FIRST);
			else
				hItem=m_0_3_cKeyTree.InsertItem(GetNameByCode(keyData),0,0,m_0_3_cKeyTree.GetParentItem(hItem),hPrevItem);
			}
		else
			hItem=m_0_3_cKeyTree.InsertItem(GetNameByCode(keyData),0,0,m_0_3_cKeyTree.GetParentItem(hItem),hItem);
		}
	m_0_3_cKeyTree.SetItemData(hItem,keyData);
	m_0_3_cKeyTree.SelectItem(hItem);
	KeyChanged();
	}
// [*----] пункт меню, вставка клавиши перед текущей
void CSettingsDlg::OnInsertKeyBefore()
	{
	InsertKey(0);
	}
// [*----] пункт меню, вставка клавиши после текущей
void CSettingsDlg::OnInsertKeyAfter()
	{
	InsertKey(1);
	}
// [*----] пункт меню, вставка клавиши внутрь текущей
void CSettingsDlg::OnInsertKeyInside()
	{
	HTREEITEM hItem=m_0_3_cKeyTree.GetSelectedItem();
	if(hItem==NULL)return;
    int data=(int)m_0_3_cKeyTree.GetItemData(hItem);
	if(data==-1)return;
	int keyData=GetSelectKey();
	hItem=m_0_3_cKeyTree.InsertItem(GetNameByCode(keyData),0,0,hItem,TVI_FIRST);
	m_0_3_cKeyTree.SetItemData(hItem,keyData);
	m_0_3_cKeyTree.SelectItem(hItem);
	KeyChanged();
	}

void CSettingsDlg::OnKeyDelete()
	{
	HTREEITEM hItem=m_0_3_cKeyTree.GetSelectedItem();
	if(hItem==NULL)return;
	if(m_0_3_cKeyTree.GetItemData(hItem)==-1)return;
	HTREEITEM hOtherItem=m_0_3_cKeyTree.GetPrevSiblingItem(hItem);
	if(hOtherItem==NULL)hOtherItem=m_0_3_cKeyTree.GetNextSiblingItem(hItem);
	HTREEITEM parent=m_0_3_cKeyTree.GetParentItem(hItem);
	m_0_3_cKeyTree.DeleteItem(hItem);
	if((hOtherItem==NULL)&&(parent==NULL))
		{
		hOtherItem=m_0_3_cKeyTree.InsertItem(_lng(_T("Settings-Gesture-Command-Keyboard-Empty")),1,1,NULL);
		m_0_3_cKeyTree.SetItemData(hOtherItem,-1);
		}
	m_0_3_cKeyTree.SelectItem(hOtherItem);
	KeyChanged();
	}

// [*----] изменение выделения в дереве всех клавиш
void CSettingsDlg::OnTvnSelchanged03AllKeyTree(NMHDR *pNMHDR, LRESULT *pResult)
	{
	if(pResult)*pResult=0;
	HTREEITEM hKeyItem=m_0_3_cKeyTree.GetSelectedItem();
	if(hKeyItem==NULL)return;
	HTREEITEM hItem=m_0_3_cAllKeyTree.GetSelectedItem();
	if(hItem==NULL)return;
	int data=(int)m_0_3_cAllKeyTree.GetItemData(hItem);
	if(data==-1)return;
	m_0_3_cKeyTree.SetItemData(hKeyItem,data);
	m_0_3_cKeyTree.SetItemText(hKeyItem,GetNameByCode(data));
	KeyChanged();
	}
// [*----] изменение выделения в дереве сочетания клавиш
void CSettingsDlg::OnTvnSelchanged03KeyTree(NMHDR *pNMHDR, LRESULT *pResult)
	{
	if(pResult)*pResult=0;
	HTREEITEM hKeyItem=m_0_3_cKeyTree.GetSelectedItem();
	if(hKeyItem==NULL)return;
	int data=(int)m_0_3_cKeyTree.GetItemData(hKeyItem);
	if(data==-1)return;
	int i=0;
	for(i=0;i<KeyTreeNumber;i++)
		if(KeyTree[i].code==data)break;
	if(i>=KeyTreeNumber)return;
	m_0_3_cAllKeyTree.SelectItem(KeyTree[i].hItem);
	}

// [*----] обработка ситуации когда изменилось сочетание клавишь
void CSettingsDlg::KeyChanged(void)
	{
	CString source,user;
	GetTreeItemDescription(m_0_3_cKeyTree.GetRootItem(),source,user);
	if(!user.IsEmpty())user.Delete(user.GetLength()-1,1);
	if(m_bControlSettings)return;
	int number=m_0_cCommands.GetCurSel();
	if(number==-1)return;
	m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Commands.m_Actions[number].m_Param[0]=source;
	m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Commands.m_Actions[number].m_Param[1]=user;
	m_pIdentify->m_Gestures[m_ActiveGestureNumber].m_Commands.m_Actions[number].m_Param[2]="";
	ModifyActionInfo(number);
	}

void CSettingsDlg::GetTreeItemDescription(HTREEITEM hItem, CString &source, CString &user)
	{
	source.Empty();
	user.Empty();
	HTREEITEM hChild;
	while(hItem!=NULL)
		{
		hChild=m_0_3_cKeyTree.GetChildItem(hItem);
		if(hChild!=NULL)
			{
			CString s,_source,_user;
			s.Format(_T("%i"),m_0_3_cKeyTree.GetItemData(hItem));
			GetTreeItemDescription(hChild,_source,_user);
			
			source+=_T("d(")+s+_T(")");
			source+=_source;
			source+=_T("u(")+s+_T(")");
			s=GetNameByCode(m_0_3_cKeyTree.GetItemData(hItem));
			user+=_T("[")+s+_T("] ");
			user+=_user;
			user+=_T("~[")+s+_T("] ");
			}
		else
			{
			CString s;
			s.Format(_T("%i"),m_0_3_cKeyTree.GetItemData(hItem));
			source+=_T("d(")+s+_T(")u(")+s+_T(")");
			s=GetNameByCode(m_0_3_cKeyTree.GetItemData(hItem));
			user+=_T("[")+s+_T("] ~[")+s+_T("] ");
			}
		hItem=m_0_3_cKeyTree.GetNextSiblingItem(hItem);
		}
	}

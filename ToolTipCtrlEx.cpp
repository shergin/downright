// ToolTipCtrlEx.cpp : implementation file
//

#include "stdafx.h"
#include "Downright.h"
#include "ToolTipCtrlEx.h"
#include "StringTool.h"

// CToolTipCtrlEx

IMPLEMENT_DYNAMIC(CToolTipCtrlEx, CToolTipCtrl)
CToolTipCtrlEx::CToolTipCtrlEx()
{
}

CToolTipCtrlEx::~CToolTipCtrlEx()
{
}


#define TOOLTIPSNUMBER 20
#define TOOLTIPSLENGTH 256
//#define _addToolTip(id,text) CStringToLPSTR(theProperties.m_Language.Get((CString)_T("Settings-ToolTip-")+(CString)text),buffer[number]);ctrl[number]=id;number++;

#define _addToolTip(id,text) _tcscpy_s(buffer[number],TOOLTIPSLENGTH,theProperties.m_Language.Get((CString)_T("Settings-ToolTip-")+(CString)text));ctrl[number]=id;number++;

BOOL CToolTipCtrlEx::Create(CWnd *pParentWnd, DWORD dwStyle)
{
	BOOL result=CToolTipCtrl::Create(pParentWnd,dwStyle);

	int number=0;
	static int ctrl[TOOLTIPSNUMBER];
	static TCHAR buffer[TOOLTIPSNUMBER][TOOLTIPSLENGTH];
/*	
	_addToolTip(,"");
	_addToolTip(,"");
	_addToolTip(,"");
	_addToolTip(,"");
	_addToolTip(,"");
*/
	_addToolTip(IDC_TREE,_T("Tree"));
	_addToolTip(IDC_0_COMMANDS,_T("Commands"));

	_addToolTip(IDC_0_0_COMMANDS,_T("StandartCommands"));
	_addToolTip(IDC_0_1_NAME,_T("Name"));
	_addToolTip(IDC_0_1_BROWSE,_T("Browse"));
	_addToolTip(IDC_0_1_PATH,_T("Path"));
	_addToolTip(IDC_0_1_PARAM,_T("Param"));
	_addToolTip(IDC_0_2_TEXT,_T("Text"));
	_addToolTip(IDC_0_3_KEY_TREE,_T("Key"));
	_addToolTip(IDC_0_4_NUMBER,_T("Number"));
	_addToolTip(IDC_0_4_WPARAM,_T("wParam"));
	_addToolTip(IDC_0_4_LPARAM,_T("lParam"));


	_addToolTip(IDC_3_COMPATIBILITY_TYPE,_T("CompatibilityType"));
	_addToolTip(IDC_3_COMPATIBILITY_EDIT,_T("CompatibilityEdit"));
	_addToolTip(IDC_3_COMPATIBILITY_LIST,_T("CompatibilityList"));

	_addToolTip(IDC_0_GESTURENAME,_T("GestureName"));
	_addToolTip(IDC_0_GESTUREDESCRIPTION,_T("GestureDescription"));


	for(int i=0;i<number;i++)
		AddTool(pParentWnd->GetDlgItem(ctrl[i]), buffer[i]);
	
	return result;
}


BEGIN_MESSAGE_MAP(CToolTipCtrlEx, CToolTipCtrl)
END_MESSAGE_MAP()



// CToolTipCtrlEx message handlers


// IntroDialog.cpp : implementation file
//

#include "stdafx.h"
#include "downright.h"
#include "IntroDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIntroDialog dialog


CIntroDialog::CIntroDialog(CWnd* pParent /*=NULL*/)
	: CBitmapDialog(CIntroDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIntroDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CIntroDialog::DoDataExchange(CDataExchange* pDX)
{
	CBitmapDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIntroDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIntroDialog, CBitmapDialog)
	//{{AFX_MSG_MAP(CIntroDialog)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIntroDialog message handlers

BOOL CIntroDialog::OnInitDialog() 
{
	CBitmapDialog::OnInitDialog();
	LoadBitmap (IDB_DOWNRIGHT_INTRO);
	SetTransparent (TRUE);
	SetTransColor (RGB(255,255,255));
	SetStaticTransparent (TRUE);
	SetClickAnywhereMove (TRUE);
	SetTimer(666,2000, NULL);

	RECT rect;
	SystemParametersInfo(SPI_GETWORKAREA,NULL,&rect,NULL);
	this->SetWindowPos(&wndTop,rect.right-5-398,rect.bottom-5-159,398+20,159+20,SWP_SHOWWINDOW);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CIntroDialog::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	OnOK();
	CBitmapDialog::OnLButtonDblClk(nFlags, point);
}

void CIntroDialog::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==666)OnOK();
	CBitmapDialog::OnTimer(nIDEvent);
}

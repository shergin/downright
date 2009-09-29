// TabCtrlEx.cpp : implementation file
//

#include "stdafx.h"
#include "Downright.h"
#include "TabCtrlEx.h"


// CTabCtrlEx

IMPLEMENT_DYNAMIC(CTabCtrlEx, CTabCtrl)

CTabCtrlEx::CTabCtrlEx()
{
}

CTabCtrlEx::~CTabCtrlEx()
{
}

BEGIN_MESSAGE_MAP(CTabCtrlEx, CTabCtrl)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CTabCtrlEx::OnPaint()
{
	CTabCtrl::OnPaint();
	::PostMessage(::GetParent(this->GetSafeHwnd()),WM_REDRAWTABCONTENT,0,0); 
	//CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CTabCtrl::OnPaint() for painting messages
}

#pragma once


// CTabCtrlEx
#define WM_REDRAWTABCONTENT WM_USER+5
class CTabCtrlEx : public CTabCtrl
{
	DECLARE_DYNAMIC(CTabCtrlEx)
public:
	CTabCtrlEx();
	virtual ~CTabCtrlEx();
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};



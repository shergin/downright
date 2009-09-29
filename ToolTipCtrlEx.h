#pragma once


// CToolTipCtrlEx

class CToolTipCtrlEx : public CToolTipCtrl
{
	DECLARE_DYNAMIC(CToolTipCtrlEx)

public:
	CToolTipCtrlEx();
	virtual ~CToolTipCtrlEx();
	BOOL Create(CWnd *pParentWnd, DWORD dwStyle=0);

protected:
	DECLARE_MESSAGE_MAP()
};



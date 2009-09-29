#if !defined(AFX_INTRODIALOG_H__0B006EDC_1D7B_4F26_A411_7445F79B4734__INCLUDED_)
#define AFX_INTRODIALOG_H__0B006EDC_1D7B_4F26_A411_7445F79B4734__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// IntroDialog.h : header file
//

#include "BitmapDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CIntroDialog dialog

class CIntroDialog : public CBitmapDialog
{
// Construction
public:
	CIntroDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CIntroDialog)
	enum { IDD = IDD_DOWNRIGHT_INTRO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIntroDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CIntroDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTRODIALOG_H__0B006EDC_1D7B_4F26_A411_7445F79B4734__INCLUDED_)

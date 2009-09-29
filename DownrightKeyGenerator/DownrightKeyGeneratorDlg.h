// DownrightKeyGeneratorDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CDownrightKeyGeneratorDlg dialog
class CDownrightKeyGeneratorDlg : public CDialog
{
// Construction
public:
	CDownrightKeyGeneratorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DOWNRIGHTKEYGENERATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_cUserName;
	CEdit m_cHardware;
	CEdit m_cSerialNumber;
	afx_msg void OnEnChangeUsername();
	afx_msg void OnEnChangeHardware();
	CEdit m_cInfo;
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};

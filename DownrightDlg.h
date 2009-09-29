// DownrightDlg.h : header file
//

#pragma once

#include "Identify.h"
#include "SettingsDlg.h"
#include "Mirror\Mirror.h"
#include "IntroDialog.h"

#define WM_SYSTRAY WM_USER+1
#define SYSTRAYICONID 1



// CDownrightDlg dialog
class CDownrightDlg : public CDialog
{
// Construction
public:
	CDownrightDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DOWNRIGHT_DIALOG };
	
	CIdentify* m_pIdentify;
	CSettingsDlg* m_pSettingsDlg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
public:
	int m_bHookActive;
protected:
	//HICON m_hIcon;
	HICON m_SysTrayIcon[2];


	LONG OnSysTray(UINT wParam, LONG lParam);
	LONG OnSettingsDlg(UINT wParam, LONG lParam);

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void Exit(void);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnShow();
	afx_msg void OnClose();
	afx_msg void OnSystrayExit();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnEnable();
	void ShowSysTrayBalloon(CString title, CString text, int type);
	LRESULT OnMouseMirror(WPARAM wParam, LPARAM lParam);
	BOOL SetSystemActivity(int activity);
	void CreateHookParam(unsigned int &up, unsigned int &down, unsigned int &key);
	void SetHookOutcast();
	LRESULT OnIdentify(WPARAM wParam, LPARAM lParam);
};

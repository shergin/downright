#pragma once
#include "Graph.h"
#include "Splitter.h"
#include "Identify.h"
#include "TabCtrlEx.h"
#include "TreeCtrlEx.h"
#include "ToolTipCtrlEx.h"
#include "afxcmn.h"
#include "afxwin.h"

#include "explorer.h"

//#include "key.h"

#define WM_SETTINGS_DLG_MESSAGE WM_USER+8

// CSettingsDlg dialog

class CSettingsDlg : public CDialog
{
	DECLARE_DYNAMIC(CSettingsDlg)

public:
	CSettingsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSettingsDlg();

// Dialog Data
	enum { IDD = IDD_SETTINGS };

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	LRESULT OnRedrawTabContent(WPARAM wParam, LPARAM lParam);
public:
	CGraph m_Graph;
	CSplitter m_Splitter;
	CPoint m_Size;
	CIdentify* m_pIdentify;
	CWnd* m_pServer;

	CToolTipCtrlEx m_cToolTip;

	int m_ActiveGestureNumber;
	bool m_bControlSettings;

	int m_Position[4];
	bool m_bDraw;
	int m_ActiveSystemInFirstMoment;

	HACCEL m_Accel;

	int m_AddSymbolState;

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	virtual BOOL OnInitDialog();

	CExplorer *m_2_pExplorer;

	void MoveElements(int cx, int cy);
	afx_msg void OnPaint();
	CImageList m_ImageList;
	CTreeCtrlEx m_0_cTree;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	CTabCtrl m_0_cGestureTab;
	CTabCtrl m_0_cCommandTab;
	CTabCtrlEx m_cMainTab;
	CListBox m_0_0_cCommands;
	CEdit m_0_2_cText;
	void SetPosition(int a, int b, int c, int d);
	void SetVisibilityGroup(int a, int b, int c, int d, bool visibility, int level);
	afx_msg void OnTcnSelchangeMaintab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchange0Gesturetab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchange0Commandtab(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnNMRclickTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDelGesture();
	afx_msg void OnAddGesture();
	afx_msg void OnAddGroup();
	CStatic m_0_1_cCName;
	CStatic m_0_1_cCPath;
	CStatic m_0_1_cCParam;
	CEdit m_0_1_cName;
	CButton m_0_1_cBrowse;
	CEdit m_0_1_cPath;
	CEdit m_0_1_cParam;
	CListBox m_0_cCommands;
	void SetGestureTabState(int state);
	afx_msg void OnLbnSelchange0Commands();
	CStatic m_0_4_cCNumber;
	CStatic m_0_4_cCWParam;
	CStatic m_0_4_cCLParam;
	CEdit m_0_4_cNumber;
	CEdit m_0_4_cWParam;
	CEdit m_0_4_cLParam;
	void SetActionControls(CAction* pAction);
	afx_msg void OnAddCommand();
	afx_msg void OnDelCommand();
	afx_msg void OnCommandUp();
	afx_msg void OnCommandDown();
	afx_msg void OnLbnSelchange00Commands();
	void ModifyActionInfo(int number);
	afx_msg void OnEnChange01Name();
	afx_msg void OnEnChange01Path();
	afx_msg void OnEnChange01Param();
	afx_msg void OnEnChange02Text();
	afx_msg void OnEnChange04Number();
	afx_msg void OnEnChange04Wparam();
	afx_msg void OnEnChange04Lparam();
	void SetCommandTabState(int state);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnKeyAdd();
	afx_msg void OnKeyAddGroup();
	afx_msg void OnKeyDel();
	afx_msg void OnKeyDown();
	afx_msg void OnKeyUp();
	void InsertGesture(int type);
	CComboBox m_3_cCompatibilityType;
	CListBox m_3_cCompatibilityList;
	CEdit m_3_cCompatibilityEdit;
	afx_msg void OnLbnSelchange3CompatibilityList();
	afx_msg void OnEnChange3CompatibilityEdit();
	afx_msg void OnCbnSelchange3CompatibilityType();
	afx_msg void OnAddCompatibility();
	afx_msg void OnDelCompatibility();
	CEdit m_0_cGestureName;
	afx_msg void OnEnChange0Gesturename();
	afx_msg void OnEnChange0Gesturedescription();
	CEdit m_0_cGestureDescription;
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	void MessagePause(void);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	//CScrollBar m_0_cGesturePreviewScroll;
	afx_msg void OnBnClicked01Browse();
	CButton m_0_cGestureEnable;
	afx_msg void OnBnClicked0GestureEnable();
public:
	virtual void OnCancel();
	virtual void OnOK();
private:
	int m_static[5];
public:
	CTabCtrl m_2_cSettingsTab;
	CButton m_2_cSystemActive;
	CButton m_2_cShowBalloon;
	CButton m_2_cShowSplash;
	CButton m_2_cStartUp;
	CComboBox m_2_cMouseButton;
	CStatic m_2_C_cMouseButton;
	CComboBox m_2_cDisableKey;
	CStatic m_2_C_cDisableKey;
	afx_msg void OnBnClicked2Systemactive();
	afx_msg void OnBnClicked2Showballoon();
	afx_msg void OnBnClicked2Showsplash();
	afx_msg void OnBnClicked2Startup();
	afx_msg void OnCbnSelchange2Mousebutton();
	afx_msg void OnCbnSelchange2Disablekey();
	afx_msg void OnTcnSelchange2Settingstab(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox m_2_cLanguage;
	CStatic m_2_C_cLanguage;
	CEdit m_2_cIgnoreProgramEdit;
	CListBox m_2_cIgnoreProgramList;
	afx_msg void OnLbnSelchange2IgnoreProgramList();
	afx_msg void OnEnChange2IgnoreProgramEdit();
	afx_msg void OnAddIgnoreProgram();
	afx_msg void OnDelIgnoreProgram();
	afx_msg void OnEnKillfocus2IgnoreProgramEdit();
	void ApplyLanguage(void);
	CEdit m_2_cUserName;
	CEdit m_2_cHardwareID;
	CEdit m_2_cRegistrationKey;

	CStatic m_2_C_cUserName;
	CStatic m_2_C_cHardwareID;
	CStatic m_2_C_cRegistrationKey;

	afx_msg void OnEnChange2Username();
	afx_msg void OnEnChange2Registrationkey();
	afx_msg void OnEnSetfocus2Registrationkey();
	afx_msg void OnEnKillfocus2Registrationkey();
	CStatic m_2_C_cSerialNumberStatus;
	afx_msg void OnNMDblclkTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	CStatic m_2_C_cFileName;
	CEdit m_2_cFileName;
	CButton m_2_cBrowse;
	afx_msg void OnBnClicked2Browse();
	void CreateTree(void);
	afx_msg void OnCbnSelchange2Language();
	CTreeCtrl m_0_3_cKeyTree;
	void KeyEvent(MSG* pMsg);
	//
	HTREEITEM m_hKeyTreeLevel;
	CTreeCtrl m_0_3_cAllKeyTree;
	afx_msg void OnNMDblclk03KeyTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclick03KeyTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnInsertKeyBefore();
	afx_msg void OnInsertKeyInside();
	afx_msg void OnInsertKeyAfter();
	afx_msg void OnKeyDelete();
	int GetSelectKey(void);
	afx_msg void OnTvnSelchanged03AllKeyTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchanged03KeyTree(NMHDR *pNMHDR, LRESULT *pResult);
	void InsertKey(int position);
	void KeyChanged(void);
	void CSettingsDlg::GetTreeItemDescription(HTREEITEM hItem, CString &source, CString &user);
};

#define move(e,x1,y1,x2,y2) r.left=x1;r.top=y1;r.right=x2;r.bottom=y2;e.MoveWindow(&r); 

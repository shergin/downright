#pragma once


// CXTreeCtrl

class CXTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CXTreeCtrl)

public:
	CXTreeCtrl();
	virtual ~CXTreeCtrl();

protected:
	DECLARE_MESSAGE_MAP()


	UINT m_TimerTicks;
	UINT m_nScrollTimerID;
	CPoint m_HoverPoint;
	UINT m_nHoverTimerID;
	DWORD m_dwDragStart;
	BOOL m_bDragging;
	CImageList* m_pDragImage;
	HTREEITEM m_hItemDragS;
	HTREEITEM m_hItemDragD;

public:
	afx_msg void OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);


	HTREEITEM CopyItem(HTREEITEM hItem, HTREEITEM htiNewParent, HTREEITEM htiAfter);
	HTREEITEM CopyBranch(HTREEITEM htiBranch, HTREEITEM htiNewParent, HTREEITEM htiAfter);
};



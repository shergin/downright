#pragma once

#include "Identify.h"
// CTreeCtrlEx
class CTreeCtrlEx : public CTreeCtrl
{
	DECLARE_DYNAMIC(CTreeCtrlEx)

public:
	CTreeCtrlEx();
	virtual ~CTreeCtrlEx();

protected:
	DECLARE_MESSAGE_MAP()

	CImageList* m_pDragImage;
	BOOL m_bLDragging;
	HTREEITEM m_hitemDrag, m_hitemDrop;
public:
	CIdentify *m_pIdentify;
	afx_msg void OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTvnItemexpanded(NMHDR *pNMHDR, LRESULT *pResult);

	HTREEITEM CopyItem(HTREEITEM hItem, HTREEITEM htiNewParent, HTREEITEM htiAfter);
	HTREEITEM CopyBranch(HTREEITEM htiBranch, HTREEITEM htiNewParent, HTREEITEM htiAfter);
	void Init(CIdentify *pIdentify);
	void Sort(HTREEITEM parent=TVI_ROOT);
	//HTREEITEM InsertItem(LPTVINSERTSTRUCT lpInsertStruct);

	CImageList *CreateDragImageEx(HTREEITEM hItem);
};



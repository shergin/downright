// TreeCtrlEx.cpp : implementation file
//

#include "stdafx.h"
#include "Downright.h"
#include "TreeCtrlEx.h"





// CTreeCtrlEx

IMPLEMENT_DYNAMIC(CTreeCtrlEx, CTreeCtrl)
CTreeCtrlEx::CTreeCtrlEx()
{
	m_bLDragging=false;
}

CTreeCtrlEx::~CTreeCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CTreeCtrlEx, CTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnTvnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnTvnItemexpanded)
END_MESSAGE_MAP()



// CTreeCtrlEx message handlers

CImageList *CTreeCtrlEx::CreateDragImageEx(HTREEITEM hItem)
{
	CRect	rect;	
	GetItemRect(hItem, rect, true );
	rect.left-=16+3;
	//
	// Create bitmap in memory DC
	//
	CClientDC	cDc(this);	
	CDC			cMemDC;	
	CBitmap		cBitmap;

	if(!cMemDC.CreateCompatibleDC(&cDc))		
		return NULL;	

	if(!cBitmap.CreateCompatibleBitmap(&cDc, rect.Width(),rect.Height()))
		return NULL;
	
	CBitmap* pOldMemDCBitmap=cMemDC.SelectObject( &cBitmap );

    cMemDC.BitBlt(
		0,
		0,
		rect.Width(),
        rect.Height(),
		&cDc, rect.left, rect.top, SRCCOPY);

	cMemDC.SelectObject( pOldMemDCBitmap );
	//
	// Create the imagelist	with the merged drag images
	//
	CImageList* pCompleteImageList = new CImageList;
	
	pCompleteImageList->Create(
		rect.Width(), 
		rect.Height(), 
		ILC_COLOR24 | ILC_MASK,0,1);

	pCompleteImageList->Add(&cBitmap,GetSysColor(COLOR_WINDOW)); 
	cBitmap.DeleteObject();

	return pCompleteImageList;
}


void CTreeCtrlEx::OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult)
{
	TRACE("OnTvnBeginrdrag\n");

	NM_TREEVIEW* pNMTreeView=(NM_TREEVIEW*)pNMHDR;
	*pResult=0;

	m_hitemDrag=pNMTreeView->itemNew.hItem;

	m_hitemDrop=NULL;
	// моё ограничение на драг&дроп
	if(GetItemData(m_hitemDrag)<1000)
		return;

	m_pDragImage=CreateDragImageEx(m_hitemDrag);
	if(!m_pDragImage)
		return;

	m_bLDragging = TRUE;
	m_pDragImage->BeginDrag(0, CPoint(-15,-15));
	POINT pt=pNMTreeView->ptDrag;
	ClientToScreen(&pt);
	m_pDragImage->DragEnter(NULL, pt);
	SetCapture();
}

void CTreeCtrlEx::OnMouseMove(UINT nFlags, CPoint point)
{
	HTREEITEM hitem;
	UINT flags;
	if(m_bLDragging)
	{
		if(nFlags==0)
		{
			m_bLDragging=FALSE;
		}
		else
		{
			POINT pt = point;
			ClientToScreen( &pt );
			CImageList::DragMove(pt);
			if ((hitem = HitTest(point, &flags)) != NULL)
			{
				CImageList::DragShowNolock(FALSE);
				SelectDropTarget(hitem);
				m_hitemDrop = hitem;
				if(GetItemData(hitem)>=1000 || GetItemData(hitem)==0)
					CImageList::DragShowNolock(TRUE);
				else
					m_hitemDrop=NULL;
			}
		}
	}
	CTreeCtrl::OnMouseMove(nFlags, point);
}

void CTreeCtrlEx::OnLButtonUp(UINT nFlags, CPoint point)
{
	CTreeCtrl::OnLButtonUp(nFlags, point);

	if(m_bLDragging)
	{
		m_bLDragging=FALSE;
		CImageList::DragLeave(this);
		CImageList::EndDrag();
		ReleaseCapture();
		delete m_pDragImage;
		SelectDropTarget(NULL);

		if(m_hitemDrop!=NULL && m_hitemDrag!=NULL)
		{
			if(GetItemData(m_hitemDrop)!=0)
			{
				if(m_pIdentify->GetGestureById((int)GetItemData(m_hitemDrop))->m_GroupStatus!=1)
				{
					m_hitemDrop=GetParentItem(m_hitemDrop);
				}
				if( (m_hitemDrag==m_hitemDrop) || (m_hitemDrop==NULL) || (GetParentItem(m_hitemDrag)==m_hitemDrop) )
				{
					SelectItem(m_hitemDrag);
					return;
				}
			}

			HTREEITEM htiParent = m_hitemDrop;
			while( (htiParent = GetParentItem( htiParent )) != NULL )
			{
				if( htiParent == m_hitemDrag ) return;
			}
			
			Expand(m_hitemDrop, TVE_EXPAND);
			
			int dataDrag=(int)GetItemData(m_hitemDrag);
			int dataDrop=(int)GetItemData(m_hitemDrop);
			// перемещаем жесты в основном массиве, там внутри модифицируется тунель
			m_pIdentify->Move(
				m_pIdentify->m_Tunnel.GetNumberById(dataDrag),
				m_pIdentify->m_Tunnel.GetNumberById(dataDrop)
				);

			HTREEITEM htiNew=CopyBranch(m_hitemDrag,m_hitemDrop,TVI_SORT);
			DeleteItem(m_hitemDrag);
			SelectItem(htiNew);
		}
	}
}

void CTreeCtrlEx::OnTvnItemexpanded(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    HTREEITEM hti=pNMTreeView->itemNew.hItem;
    int y1=0,y2=0;

	UINT state=GetItemState(hti,TVIS_EXPANDED);
    GetItemImage(hti,y1,y2);
    if (/*y1==0*/state&TVIS_EXPANDED) CTreeCtrl::SetItemImage(hti,1,1); else CTreeCtrl::SetItemImage(hti,0,0);
    *pResult = 0;
}

HTREEITEM CTreeCtrlEx::CopyItem(HTREEITEM hItem, HTREEITEM htiNewParent, HTREEITEM htiAfter)
{
	TV_INSERTSTRUCT tvstruct;
	HTREEITEM hNewItem;
	CString sText;

	tvstruct.item.hItem = hItem;
	tvstruct.item.mask = TVIF_CHILDREN|TVIF_HANDLE|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	GetItem( &tvstruct.item );
	sText = GetItemText( hItem );
	tvstruct.item.cchTextMax = sText.GetLength ();
	tvstruct.item.pszText = sText.LockBuffer ();

	tvstruct.hParent = htiNewParent;
	tvstruct.hInsertAfter = htiAfter;
	tvstruct.item.mask = TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT;
	hNewItem = InsertItem( &tvstruct );
	sText.ReleaseBuffer ();

	SetItemData( hNewItem,GetItemData(hItem) );
	SetItemState( hNewItem,GetItemState(hItem,TVIS_STATEIMAGEMASK),TVIS_STATEIMAGEMASK);
	Sort(htiNewParent);
	return hNewItem;
}

HTREEITEM CTreeCtrlEx::CopyBranch(HTREEITEM htiBranch, HTREEITEM htiNewParent, HTREEITEM htiAfter)
{
	HTREEITEM hChild;
	HTREEITEM hNewItem = CopyItem( htiBranch,htiNewParent,htiAfter );
	hChild = GetChildItem( htiBranch );

	while( hChild != NULL )
	{
		CopyBranch( hChild,hNewItem,htiAfter );
		hChild = GetNextSiblingItem( hChild );
	}

	return hNewItem;
}

void CTreeCtrlEx::Init(CIdentify *pIdentify)
{
	m_pIdentify=pIdentify;
}


/*static*/ int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	// lParamSort contains a pointer to the tree control.
	// The lParam of an item is just its handle, 
	// as specified with SetItemData
	int result=0;
	if( (lParam1!=0) && (lParam2!=0) && (lParamSort!=0))
	{
		CTreeCtrlEx* pmyTreeCtrl = (CTreeCtrlEx*) lParamSort;
		int status1=pmyTreeCtrl->m_pIdentify->GetGestureById((int)lParam1)->m_GroupStatus;
		int status2=pmyTreeCtrl->m_pIdentify->GetGestureById((int)lParam2)->m_GroupStatus;
		 
		if(status1==status2)			
			result=0;
		else
			if(status1<status2)
				result=1;
			else
				result=-1;
		if(result==0)
		{
			CString &s1=pmyTreeCtrl->m_pIdentify->GetGestureById((int)lParam1)->m_Name;
			CString &s2=pmyTreeCtrl->m_pIdentify->GetGestureById((int)lParam2)->m_Name;
			result=s1.Compare(s2);
		}
		//int data1=(int)pmyTreeCtrl->GetItemData((HTREEITEM)lParam1);
		//int data2=(int)pmyTreeCtrl->GetItemData((HTREEITEM)lParam2);
		//CString    strItem1 = pmyTreeCtrl->GetItemText((HTREEITEM) lParam1);
		//CString    strItem2 = pmyTreeCtrl->GetItemText((HTREEITEM) lParam2);
		return result;//strcmp(strItem2, strItem1);
	}
	else
	{
		Beep(100,100);
		return 0;
	}
}
void CTreeCtrlEx::Sort(HTREEITEM parent)
{
   TVSORTCB tvs;
   tvs.hParent=parent;
   tvs.lpfnCompare=MyCompareProc;
   tvs.lParam=(LPARAM)this;
   SortChildrenCB(&tvs);
}


/*
/// нахер удалить эту хрень!!!
HTREEITEM CTreeCtrlEx::InsertItem(LPTVINSERTSTRUCT lpInsertStruct)
{
	TRACE("z");
	if(lpInsertStruct!=NULL)
		lpInsertStruct->hInsertAfter=0;
	HTREEITEM x=CTreeCtrl::InsertItem(lpInsertStruct);
//	if(lpInsertStruct!=NULL)
//		Sort(lpInsertStruct->hParent);
	return x;
}
*/
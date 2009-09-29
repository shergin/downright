/*
// XTreeCtrl.h

protected:
	UINT m_TimerTicks;
	UINT m_nScrollTimerID;
	CPoint m_HoverPoint;
	UINT m_nHoverTimerID;
	DWORD m_dwDragStart;
	BOOL m_bDragging;
	CImageList* m_pDragImage;
	HTREEITEM m_hItemDragS;
	HTREEITEM m_hItemDragD;

	// XTreeCtrl.cpp
	#define DRAG_DELAY 60
	void CXTreeCtrl::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
	{
		NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
		*pResult = 0;

		if( (GetTickCount() - m_dwDragStart) < DRAG_DELAY )
			return;

		m_hItemDragS = pNMTreeView->itemNew.hItem;
		m_hItemDragD = NULL;

		m_pDragImage = CreateDragImage( m_hItemDragS );
		if( !m_pDragImage )
			return;

		m_bDragging = true;
		m_pDragImage->BeginDrag ( 0,CPoint(8,8) );
		CPoint pt = pNMTreeView->ptDrag;
		ClientToScreen( &pt );
		m_pDragImage->DragEnter ( this,pt );
		SetCapture();

		m_nScrollTimerID = SetTimer( 2,40,NULL );
	}

	void CXTreeCtrl::OnMouseMove(UINT nFlags, CPoint point) 
	{
		HTREEITEM hItem;
		UINT flags;

		if( m_nHoverTimerID )
		{
			KillTimer( m_nHoverTimerID );
			m_nHoverTimerID = 0;
		}
		m_nHoverTimerID = SetTimer( 1,800,NULL ); //定时为 0.8 秒则自动展开
		m_HoverPoint = point;

		if( m_bDragging )
		{
			CPoint pt = point;
			CImageList::DragMove( pt );

			CImageList::DragShowNolock( false );
			if( (hItem = HitTest(point,&flags)) != NULL )
			{
				SelectDropTarget( hItem );
				m_hItemDragD = hItem;
			}
			CImageList::DragShowNolock( true );

			CRect rect;
			GetClientRect( &rect );
			if( point.x < rect.left + 20 )
				m_hItemDragD = NULL;
		}

		CTreeCtrl::OnMouseMove(nFlags, point);
	}

	void CXTreeCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
	{
		CTreeCtrl::OnLButtonUp(nFlags, point);

		if( m_bDragging )
		{
			m_bDragging = FALSE;
			CImageList::DragLeave( this );
			CImageList::EndDrag();
			ReleaseCapture();
			delete m_pDragImage;

			SelectDropTarget( NULL );

			if( m_hItemDragS == m_hItemDragD )
			{
				KillTimer( m_nScrollTimerID );
				return;
			}

			Expand( m_hItemDragD,TVE_EXPAND );
			HTREEITEM htiParent = m_hItemDragD;

			while( (htiParent = GetParentItem(htiParent)) != NULL )
			{
				if( htiParent == m_hItemDragS )
				{
					HTREEITEM htiNewTemp = CopyBranch( m_hItemDragS,NULL,TVI_LAST );
					HTREEITEM htiNew = CopyBranch( htiNewTemp,m_hItemDragD,TVI_LAST );
					DeleteItem( htiNewTemp );
					SelectItem( htiNew );
					KillTimer( m_nScrollTimerID );
					return;
				}
			}

			HTREEITEM htiNew = CopyBranch( m_hItemDragS,m_hItemDragD,TVI_LAST );
			DeleteItem( m_hItemDragS );
			SelectItem( htiNew );
			KillTimer( m_nScrollTimerID );
		}
	}

	HTREEITEM CXTreeCtrl::CopyItem(HTREEITEM hItem, HTREEITEM htiNewParent, HTREEITEM htiAfter)
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

		return hNewItem;
	}

	HTREEITEM CXTreeCtrl::CopyBranch(HTREEITEM htiBranch, HTREEITEM htiNewParent, HTREEITEM htiAfter)
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

	void CXTreeCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
	{
		m_dwDragStart = GetTickCount();

		CTreeCtrl::OnLButtonDown(nFlags, point);
	}

	void CXTreeCtrl::OnTimer(UINT nIDEvent) 
	{
		if( nIDEvent == m_nHoverTimerID )
		{
			KillTimer( m_nHoverTimerID );
			m_nHoverTimerID = 0;
			HTREEITEM trItem = 0;
			UINT uFlag = 0;
			trItem = HitTest( m_HoverPoint,&uFlag );
			if( trItem && m_bDragging )
			{
				SelectItem( trItem );
				Expand( trItem,TVE_EXPAND );
			}
		}
		else if( nIDEvent == m_nScrollTimerID )
		{
			m_TimerTicks++;
			CPoint pt;
			GetCursorPos( &pt );
			CRect rect;
			GetClientRect( &rect );
			ClientToScreen( &rect );

			HTREEITEM hItem = GetFirstVisibleItem();

			if( pt.y < rect.top +10 )
			{
				int slowscroll = 6 - (rect.top + 10 - pt.y )/20;
				if( 0 == (m_TimerTicks % ((slowscroll > 0) ? slowscroll : 1)) )
				{
					CImageList::DragShowNolock ( false );
					SendMessage( WM_VSCROLL,SB_LINEUP );
					SelectDropTarget( hItem );
					m_hItemDragD = hItem;
					CImageList::DragShowNolock ( true );
				}
			}
			else if( pt.y > rect.bottom - 10 )
			{
				int slowscroll = 6 - (pt.y - rect.bottom + 10)/20;
				if( 0 == (m_TimerTicks % ((slowscroll > 0) ? slowscroll : 1)) )
				{
					CImageList::DragShowNolock ( false );
					SendMessage( WM_VSCROLL,SB_LINEDOWN );
					int nCount = GetVisibleCount();
					for( int i=0 ; i<nCount-1 ; i++ )
						hItem = GetNextVisibleItem( hItem );
					if( hItem )
						SelectDropTarget( hItem );
					m_hItemDragD = hItem;
					CImageList::DragShowNolock ( true );
				}
			}
		}
		else
			CTreeCtrl::OnTimer(nIDEvent);
	}

*/
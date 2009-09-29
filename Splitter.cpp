#include "StdAfx.h"
#include "splitter.h"


void CSplitter::Init(CGraph *pGraph)
{
	m_pGraph=pGraph;
	m_Status=0;
	m_Position=m_pGraph->m_SplitterPosition;
}

void CSplitter::MouseMove(CPoint &mouse)
{
	if((mouse.x-dx < m_Position+3) && (mouse.x-dx > m_Position-3))
		::SetCursor(AfxGetApp()->LoadStandardCursor((LPCTSTR)IDC_SIZEWE));
	if(m_Status==1 && CorrectPosition(m_Position)!=CorrectPosition(mouse.x-dx))
	{
		m_pGraph->DrawSplitterBar(CorrectPosition(m_Position));
		m_Position=mouse.x-dx;
		m_pGraph->DrawSplitterBar(CorrectPosition(m_Position));
	}
}

void CSplitter::MouseDown(CPoint &mouse)
{
    if((mouse.x-dx < m_Position+3) && (mouse.x-dx > m_Position-3))
	{
		::SetCursor(AfxGetApp()->LoadStandardCursor((LPCTSTR)IDC_SIZEWE));
		m_Status=1;
		m_Position=mouse.x-dx;
		m_pGraph->DrawSplitterBar(CorrectPosition(m_Position));
		m_pGraph->m_pMainWnd->SetCapture();
	}
}

#define min_left_space 200
#define min_right_space 200
bool CSplitter::MouseUp(CPoint &mouse)
{
	if(m_Status==1)
	{
		m_Status=0;
		m_pGraph->DrawSplitterBar(CorrectPosition(m_Position));
		if(m_Position<min_left_space)m_Position=min_left_space;

		if(m_Position>m_pGraph->m_pSize->x-min_left_space)m_Position=m_pGraph->m_pSize->x-min_left_space;
		ReleaseCapture();
		return true;
	}
	return false;
}
int CSplitter::CorrectPosition(int position)
{
	if(position<min_left_space)position=min_left_space;
	if(position>m_pGraph->m_pSize->x-min_left_space)position=m_pGraph->m_pSize->x-min_left_space;
	return position;
}

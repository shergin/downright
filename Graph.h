#pragma once

#include "Identify.h"

class CGraph
{
public:
	CWnd *m_pMainWnd;
	CIdentify *m_pIdentify;
	HBRUSH *m_pHBRUSH;
	COLORREF Color[7];
	int m_SplitterPosition;
	bool m_bShowSplitter;
	CPoint *m_pSize;

	CPoint m_GesturePreviewSize;
	CDC m_GesturePreviewDC;
	CBitmap m_GesturePreviewBitmap;
	bool m_GesturePreviewCreate;
	int m_ScrollPos;

	CGraph();
	~CGraph();
	void Init(CWnd *pMainWnd, CPoint *pSize, HBRUSH *pHBRUSH, CIdentify *pIdentify);
	void Draw(int param, int activeGesture);
	void DrawSplitterBar(int position);
	void DrawSymbol(CDC* pDC, CPoint point, CSymbol* pSymbol, int style);
	void CreateGesturePreview(void);
	void DrawLogo(CDC* pDC, int x, int y, int k, COLORREF color);
	void DrawBigLogoSpace(CDC* pDC, int x1, int y1, int x2, int y2);
};

#pragma once

#include "Graph.h"

#define dx 2
class CSplitter
{
public:
	int m_Position;
	int m_Status;
	CGraph *m_pGraph;
	void Init(CGraph *pGraph);
	void MouseMove(CPoint &mouse);
	void MouseDown(CPoint &mouse);
	bool MouseUp(CPoint &mouse);
	inline int CorrectPosition(int position);
};

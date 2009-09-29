#pragma once

#include "StringTool.h"
#include "Gesture.h"
#include "Tunnel.h"

#define UNREGISTRED_VERSION_GESTURE_LIMIT 5
class CIdentify
{
public:
	CIdentify(void);
	~CIdentify(void);
	
	CTunnel m_Tunnel; // тунель в дерево

	CArray<CGesture/*,CGesture*/> m_Gestures; // массив жестов
	int m_nGestures; // их количество

	HWND m_hServerWnd;
	CSymbol theSymbol;


	void AddGesture(unsigned char groupStatus, CString &name, CString &description, CString &commands, CString &symbols, CString &compatibility, bool &disable);
	bool Load(CString filename);
	bool Save(CString filename);
	CGesture* GetGestureById(int id);
	void Move(int element, int parent);
	void NextPoint(WPARAM wParam, LPARAM lParam);
	bool GestureLimit(void);
};

#define _point_to_int(p) ((p).x+(p).y*0xffff)
#define _int_to_point(i,p) {(p).x=i%0xffff;(p).y=i/0xffff;}
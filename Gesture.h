#pragma once

#include "Commands.h"
#include "Compatibility.h"
#include "Symbols.h"

#define WM_IDENTIFY WM_USER+2

class CGesture
{
public:
	CGesture(void);
	CGesture(CGesture &obj);
	~CGesture(void);
	CGesture& operator = (const CGesture &obj);

	unsigned char m_GroupStatus; // 0 - просто жест, 1 - открытие группы, 2 - закрытие группы
	CString m_Name;
	CString m_Description;
	CCommands m_Commands;
	CCompatibility m_Compatibility;
	CSymbols m_Symbols;
	bool m_Disable;
	bool Compare(CSymbol* pSymbol);
	BOOL Execute(HWND hServer, HWND hTarget);
};

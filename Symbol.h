#pragma once

#include "Direction.h"

#define MAXSYMBOLELEMENT 512
class CSymbol
{
public:
	CDirection m_Direction[MAXSYMBOLELEMENT];
	void operator = (CString &s);
	operator CString();
	int m_nDirection;
	CSymbol(void);
	~CSymbol(void);
	bool Compare(CSymbol* pSymbol);
};

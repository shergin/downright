#pragma once
#include "afxtempl.h"
#include "Symbol.h"
class CSymbols
{
public:
	CSymbols(void);
	~CSymbols(void);
	CArray<CSymbol> m_Symbol;
	int m_nSymbol;
	CSymbols& operator = (const CSymbols &obj);
	void operator = (const CString &s);
	operator CString();
};

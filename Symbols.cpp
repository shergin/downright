#include "StdAfx.h"
#include "symbols.h"

CSymbols::CSymbols(void)
{
	m_nSymbol=0;
}

CSymbols::~CSymbols(void)
{
}

CSymbols& CSymbols::operator = (const CSymbols &obj)
{
	m_nSymbol=obj.m_nSymbol;
	// implementation m_Symbols=obj.m_Symbols;
	m_Symbol.RemoveAll();
	m_Symbol.SetSize(m_nSymbol);
	for(int i=0;i<m_nSymbol;i++)
	{
		m_Symbol.SetAtGrow(i,const_cast<CSymbol&>(obj.m_Symbol[i]));
	}
	// end of implementation
	return *this;
}

void CSymbols::operator = (const CString &s)
{
	m_nSymbol=0;
	m_Symbol.RemoveAll();
	m_Symbol.SetSize(1,3);
	CSymbol symbol;
	CString str;
	TCHAR ch=0;
	for(int i=0;i<s.GetLength();i++)
	{
		ch=s.GetAt(i);
		if((ch=='|')||(i+1==s.GetLength()))
		{
			if(i+1==s.GetLength())str+=ch;
			symbol=str;
			m_Symbol.SetAtGrow(m_nSymbol,symbol);
			m_nSymbol++;
			str.Empty();
		}
		else
			str+=ch;
	}
}

CSymbols::operator CString()
{
	CString result;
	for(int i=0;i<m_nSymbol;i++)
	{
		result+=(CString)m_Symbol[i];
		if(i+1!=m_nSymbol)result+="|";
	}
	return result;
}
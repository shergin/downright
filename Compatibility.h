#pragma once
#include "afxtempl.h"

class CCompatibility
{
public:
	CCompatibility(void);
	~CCompatibility(void);

	void operator = (CString s);
	operator CString();
	CCompatibility& operator = (const CCompatibility &obj);
	int m_nStrings;
	CArray<CString,CString&> m_Strings;
	int m_Type; // 0 - �� �����, 1 - ������ � �����, 2 - ����� ����
};

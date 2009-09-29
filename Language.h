#pragma once
#include "afxtempl.h"
class CLanguageElement
{
public:
	CString key;
	CString str;
};
class CLanguage
{
	CArray<CLanguageElement> m_Array;
	int m_nArray;
public:
	CLanguage(void);
	~CLanguage(void);
	void AddStr(CString left, CString right, bool safe=false);
	bool Load(CString filename);
	CString Get(CString key);
	void LocalizationMenu(HMENU hMenu, int menuId);
};

#pragma once
#include "Language.h"

class CProperties
{
public:
	CLanguage m_Language;
	
	CString m_UserName;
	CString m_RegKey;
	CString m_ProgramDirectory;
	CString m_FileName;
	CString m_LanguageName;
	CString m_IgnoreProgram;
	CRect m_WindowPosition;
	int m_ShowBalloon;
	int m_ShowSplash;
	int m_DisableKey;
	int m_MouseButton;

	bool bRegistred;

	CProperties(void);
	~CProperties(void);
	void Load(void);
	void Save(void);

	bool IsAutoRunKey(void);
	void SetAutoRunKey(bool b);
	CString GetKey(void);
	CString GetKeyEx(CString hardware, CString username);
	void LoadLanguage(void);
};
extern CProperties theProperties;
#define _lng(x) theProperties.m_Language.Get(x)

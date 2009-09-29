#include "StdAfx.h"
#include "Properties.h"

#include "atlbase.h"
#include "math.h"

#include "StringTool.h"
#include ".\properties.h"

#pragma warning(disable:4996)

CProperties::CProperties(void)
{
	bRegistred=false;
}

CProperties::~CProperties(void)
{
}

CProperties theProperties;

void CProperties::Load(void)
{
	CWinApp* pApp=AfxGetApp();
	m_ProgramDirectory		=pApp->GetProfileString	(_T("General"),_T("ProgramDirectory"));
	m_FileName				=pApp->GetProfileString	(_T("General"),_T("FileName"));
	m_LanguageName			=pApp->GetProfileString	(_T("General"),_T("Language"));
	m_IgnoreProgram			=pApp->GetProfileString	(_T("General"),_T("IgnoreProgram"));
	m_UserName				=pApp->GetProfileString	(_T("General"),_T("UserName"));
	m_RegKey				=pApp->GetProfileString	(_T("General"),_T("RegKey"));
	m_ShowBalloon			=pApp->GetProfileInt	(_T("General"),_T("ShowBalloon"),		0);
	m_ShowSplash			=pApp->GetProfileInt	(_T("General"),_T("ShowSpalsh"),		1);
	m_DisableKey			=pApp->GetProfileInt	(_T("General"),_T("DisableKey"),		1);
	m_MouseButton			=pApp->GetProfileInt	(_T("General"),_T("MouseButton"),		0);
	// положение окна
	m_WindowPosition.left	=pApp->GetProfileInt	(_T("General"),_T("PositionLeft"),		0);
	m_WindowPosition.top	=pApp->GetProfileInt	(_T("General"),_T("PositionTop"),		0);
	m_WindowPosition.right	=pApp->GetProfileInt	(_T("General"),_T("PositionRight"),		0);
	m_WindowPosition.bottom	=pApp->GetProfileInt	(_T("General"),_T("PositionBottom"),	0);

	if(m_RegKey==GetKey())bRegistred=true;
	LoadLanguage();
}

void CProperties::Save(void)
{
	CWinApp* pApp=AfxGetApp();
	pApp->WriteProfileString(_T("General"),_T("ProgramDirectory"),	m_ProgramDirectory		);
	pApp->WriteProfileString(_T("General"),_T("FileName"),			m_FileName				);
	pApp->WriteProfileString(_T("General"),_T("Language"),			m_LanguageName			);
	pApp->WriteProfileString(_T("General"),_T("IgnoreProgram"),		m_IgnoreProgram			);
	pApp->WriteProfileString(_T("General"),_T("UserName"),			m_UserName				);
	pApp->WriteProfileString(_T("General"),_T("RegKey"),			m_RegKey				);
	pApp->WriteProfileInt   (_T("General"),_T("ShowBalloon"),		m_ShowBalloon			);
	pApp->WriteProfileInt   (_T("General"),_T("ShowSpalsh"),		m_ShowSplash			);
	pApp->WriteProfileInt   (_T("General"),_T("DisableKey"),		m_DisableKey			);
	pApp->WriteProfileInt   (_T("General"),_T("MouseButton"),		m_MouseButton			);
	// положение окна
	pApp->WriteProfileInt   (_T("General"),_T("PositionLeft"),		m_WindowPosition.left	);
	pApp->WriteProfileInt   (_T("General"),_T("PositionTop"),		m_WindowPosition.top	);
	pApp->WriteProfileInt   (_T("General"),_T("PositionRight"),		m_WindowPosition.right	);
	pApp->WriteProfileInt   (_T("General"),_T("PositionBottom"),	m_WindowPosition.bottom	);
}


bool CProperties::IsAutoRunKey(void)
{
	bool b=false;
	CRegKey key;
	LONG status=key.Open(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"));
	if(status==ERROR_SUCCESS)
	{
		TCHAR setting[256];
		DWORD settingSize=sizeof(setting);
		status=key.QueryValue(setting,_T("Downright"), &settingSize);
		if(status==ERROR_SUCCESS)
			b=true;
	}
	key.Close();
	return b;
}

void CProperties::SetAutoRunKey(bool b)
{
	CRegKey key;
	if(b)
		key.SetValue(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),m_ProgramDirectory+_T("\\Downright.exe"),_T("Downright"));
	else
	{
		LONG status=key.Open(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"));
		if(status==ERROR_SUCCESS)
			key.DeleteValue(_T("Downright"));
		key.Close();
	}
}

CString CProperties::GetKey(void)
	{
	DWORD serial=0;
	GetVolumeInformation(_T("c:\\"),NULL,NULL,&serial,NULL,NULL,NULL,NULL);
	return GetKeyEx(UnsignedLongToString(serial),m_UserName);
	}

CString CProperties::GetKeyEx(CString hardware, CString username)
	{
	CString s;
	double key=-3.14159;
	TCHAR ch=0;
	for(int i=0;i<hardware.GetLength();i++)
		{
		ch=hardware.GetAt(i);
		key+=sin((double)ch);
		}
	for(int i=0;i<username.GetLength();i++)
		{
		ch=username.GetAt(i);
		key+=cos((double)ch);
		}
	if(key<0)key=-key;
	key-=floor(key);
	// в строку
	unsigned char x=0;
	for(int i=0;i<12;i++)
		{
		x=(unsigned char)(key*16);
		key*=16;
		key-=floor(key);
		if(x<10)
			ch=(unsigned char)'0'+(unsigned char)(x);
		else
			ch=(unsigned char)'a'+(unsigned char)(x-10);
		s+=ch;
		}
	return s;
	}

void CProperties::LoadLanguage(void)
	{
	m_Language.Load(m_ProgramDirectory+_T("\\Languages\\")+m_LanguageName+_T(".lng"));
	}

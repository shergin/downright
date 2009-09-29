#include "StdAfx.h"
#include "compatibility.h"
#include "StringTool.h"
CCompatibility::CCompatibility(void)
{
	m_nStrings=0;
	m_Type=0;
}

CCompatibility::~CCompatibility(void)
{
}



CCompatibility& CCompatibility::operator = (const CCompatibility &obj)
{
	m_nStrings=obj.m_nStrings;
	m_Type=obj.m_Type;
	// implementation m_Actions=obj.m_Actions;
	m_Strings.RemoveAll();
	m_Strings.SetSize(m_nStrings);
	for(int i=0;i<m_nStrings;i++)
	{
		m_Strings.SetAtGrow(i,const_cast<CString&>(obj.m_Strings[i]));
	}
	// end of implementation
	return *this;
}

void CCompatibility::operator = (CString s)
{
	m_nStrings=0;
	long length=s.GetLength();
	// определяем тип
	if(length<3)return;
	if(s.GetAt(1)!='|')return;
	switch(s.GetAt(0))
	{
		case '1':m_Type=1;break;
		case '2':m_Type=2;break;
		default:return;
	}
	s.Delete(0,2);
	length-=2;

	CString temp;
	TCHAR ch=0;
	int p=0;
	for(int i=0;i<length;i++)
	{
		ch=s.GetAt(i);
		if((ch=='|')||(i+1==length))
		{
			if(ch!='|')temp+=ch;
			m_Strings.SetAtGrow(m_nStrings,FromSafe(temp));
			TRACE(temp+_T(" %i \n"),m_nStrings);
			m_nStrings++;
			temp.Empty();
		}
		else
			temp+=ch;
	}
}

CCompatibility::operator CString()
{
	if( m_Type<1 || m_Type>2 )return _T("");
	if(m_nStrings<=0)return _T("");
	CString result;
	if(m_Type==1)result=_T("1|");
	if(m_Type==2)result=_T("2|");
	for(int i=0;i<m_nStrings;i++)
	{
		result+=ToSafe(m_Strings[i]);
		if(i+1!=m_nStrings)result+=_T("|");
	}
	return result;
}
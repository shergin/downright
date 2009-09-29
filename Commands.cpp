#include "StdAfx.h"
#include "commands.h"

CCommands::CCommands(void)
{
	m_nActions=0;
}

CCommands::~CCommands(void)
{
}



CCommands& CCommands::operator = (const CCommands &obj)
{
	m_nActions=obj.m_nActions;
	// implementation m_Actions=obj.m_Actions;
	m_Actions.RemoveAll();
	m_Actions.SetSize(m_nActions);
	//CAction action;
	for(int i=0;i<m_nActions;i++)
	{
		//action=obj.m_Actions[i];
		//m_Actions.SetAtGrow(i,action);
		m_Actions.SetAtGrow(i,const_cast<CAction&>(obj.m_Actions[i]));
	}
	// end of implementation
	return *this;
}

void CCommands::operator = (CString s)
{
	m_Actions.RemoveAll();
	m_Actions.SetSize(1,5);
	m_nActions=0;
	long length=s.GetLength();
	CString temp;
	TCHAR ch=0;
	int p=0;
	CAction action;
	for(int i=0;i<length;i++)
	{
		ch=s.GetAt(i);
		if((ch=='|')||(i+1==length))
		{
			if(ch!='|')temp+=ch;
			action=temp;
			m_Actions.SetAtGrow(m_nActions,action);
			m_nActions++;
			temp.Empty();
		}
		else
			temp+=ch;
	}
}

CCommands::operator CString()
{
	CString result;
	for(int i=0;i<m_nActions;i++)
	{
		result+=(CString)m_Actions[i];
		if(i+1!=m_nActions)result+="|";
	}
	return result;
}
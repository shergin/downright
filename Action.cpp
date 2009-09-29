#include "StdAfx.h"
#include "action.h"

void CAction::GetKeyElement(CString &s,int &type,int &key)
	{
	// формат примерно такой "d(ff)u(ff)"
	if(s.GetLength()<4){s.Empty();return;}
	if(s.GetAt(1)!=_T('(')){s.Empty();return;}
	type=-1;
	if(s.GetAt(0)==_T('d'))type=0;
	if(s.GetAt(0)==_T('u'))type=1;
	if(type==-1){s.Empty();return;}
	int end=s.Find(_T(")"));
	if(end==-1){s.Empty();return;}
	key=_tstoi(s.Mid(2,end-2));
	s.Delete(0,end+1);
	}

CString CAction::GetDescription()
{
	CString description;
			CString s;
	switch(m_Type)
	{
		case 0:
			description=_lng(_T("Settings-Gesture-Command-Standart-Title"));//"Выполнить: ";
			for(int i=0;i<StandartActionCount;i++)
				if(m_Param[0]==StandartAction[i])
				{
					description+=_lng(_T("Settings-Gesture-Command-Standart-")+StandartAction[i]);
					break;
				}
		break;
		case 1:
			description.Format(_lng(_T("Settings-Gesture-Command-Start-Title")),m_Param[0]);
			if(!m_Param[1].IsEmpty()){s.Format(_lng(_T("Settings-Gesture-Command-Start-Title-Path")),m_Param[1]);description+=s;}
			if(!m_Param[2].IsEmpty()){s.Format(_lng(_T("Settings-Gesture-Command-Start-Title-Parameters")),m_Param[2]);description+=s;}
			break;
		case 2:
			description.Format(_lng(_T("Settings-Gesture-Command-Text-Title")),m_Param[0]);
		break;
		case 3:
			description.Format(_lng(_T("Settings-Gesture-Command-Keyboard-Title")),m_Param[1]);
		break;
		case 4:
			description.Format(_lng(_T("Settings-Gesture-Command-Message-Title")),m_Param[0],m_Param[1],m_Param[2]);
		break;
	}
	return description;
}

void CAction::operator = (CString action)
{
	if(action.Find(_T("standart("))==0)	{m_Type=0; goto next;}
	if(action.Find(_T("start("))==0)	{m_Type=1; goto next;}
	if(action.Find(_T("text("))==0)		{m_Type=2; goto next;}
	if(action.Find(_T("key("))==0)		{m_Type=3; goto next;}
	if(action.Find(_T("message("))==0)	{m_Type=4; goto next;}
next:
	int i=0;
	for(i=0;i<3;i++)
		m_Param[i].Empty();

	int start=action.Find(_T("("));
	if(start==-1)return;
	action.Delete(0,start+1);
	if(action.GetLength()<=0)return;
	if(action.GetAt(action.GetLength()-1)==_T(')'))
		action.SetAt(action.GetLength()-1,_T(','));
	else
		return;
	for(i=0;i<3;i++)
	{
		int end=action.Find(_T(","));
		if(end==-1)break;
		m_Param[i]=FromSafe(action.Left(end));
		action.Delete(0,end+1);
	}
	
	TRACE(_T("[0] ")+m_Param[0]+_T("\n"));
	TRACE(_T("[1] ")+m_Param[1]+_T("\n"));
	TRACE(_T("[2] ")+m_Param[2]+_T("\n"));
}

CAction::operator CString()
{
	CString result;
	switch(m_Type)
	{
		case 0:	result=_T("standart(");	break;
		case 1:	result=_T("start(");	break;
		case 2:	result=_T("text(");	break;
		case 3:	result=_T("key(");	break;
		case 4:	result=_T("message(");	break;
		default: return _T("");
	}
	result+=ToSafe(m_Param[0])+_T(",")+ToSafe(m_Param[1])+_T(",")+ToSafe(m_Param[2])+_T(")");
	return result;
}

void CAction::SetActionType(int type)
{
	TRACE(_T("SetActionType type=%i, m_Type=%i\n"),type,m_Type);
	if(m_Type!=type)
	{		
		m_Param[0].Empty();
		m_Param[1].Empty();
		m_Param[2].Empty();
		switch(type)
		{
			case 0:
				m_Param[0]=_T("minimize");
			break;
			break;
			case 3:
			break;
			case 4:
				m_Param[0]=_T("0");
				m_Param[1]=_T("0");
				m_Param[2]=_T("0");
			break;
		}
		m_Type=type;
	}
}

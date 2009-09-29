#include "StdAfx.h"
#include "identify.h"

CIdentify::CIdentify(void)
{
	m_hServerWnd=NULL;
}

CIdentify::~CIdentify(void)
{
}

void CIdentify::AddGesture(unsigned char m_GroupStatus, CString &name, CString &description, CString &commands, CString &symbols, CString &compatibility, bool &disable)
{
	if(m_GroupStatus!=0)
	{
		if(m_GroupStatus!=1)name.Empty();
		commands.Empty();
		symbols.Empty();
		compatibility.Empty();
		disable=false;
	}
	CGesture gesture;
	gesture.m_GroupStatus=m_GroupStatus;
	gesture.m_Name=FromSafe(name);
	gesture.m_Description=FromSafe(description);
	gesture.m_Commands=commands;
	gesture.m_Symbols=symbols;
	gesture.m_Compatibility=compatibility;
	gesture.m_Disable=disable;
	m_Gestures.SetAtGrow(m_nGestures,gesture);
	m_nGestures++;
	description.Empty();
	commands.Empty();
	symbols.Empty();
	compatibility.Empty();
	disable=false;
}


bool CIdentify::Load(CString filename)
{
	CFile f;
	CString image,str,name,description,commands,symbols,compatibility;
	bool disable=false;
	int nEnableGesture=0;
	int i=0;
	if(!f.Open(filename,CFile::modeRead))return false;
	int length=(int)f.GetLength();
	f.Read(image.GetBuffer(length),length);
	f.Close();
	image.ReleaseBuffer(length);
	TCHAR ch=0;
	m_nGestures=0;
	m_Gestures.RemoveAll();
	m_Gestures.SetSize(100,50);
	for(i=0;i<length;i++)
	{
		ch=image.GetAt(i);
		if((ch==13)||(ch==10)||(i+1==length))
		{
			if(!str.IsEmpty())
			{

				long p=0;
				if(p=str.Find(_T("description["))==0)
				{
					description=str.Mid(12,str.GetLength()-12-1);
				}
				if(p=str.Find(_T("name["))==0)
				{
					name=str.Mid(5,str.GetLength()-5-1);
				}
				if(p=str.Find(_T("commands["))==0)
				{
					commands=str.Mid(9,str.GetLength()-9-1);
				}
				if(p=str.Find(_T("compatibility["))==0)
				{
					compatibility=str.Mid(14,str.GetLength()-14-1);
				}
				if(p=str.Find(_T("disable["))==0)
				{
					disable=true;
				}
				if(p=str.Find(_T("symbols["))==0)
				{
					symbols=str.Mid(8,str.GetLength()-8-1);
					if(!disable)nEnableGesture++;
					if((!theProperties.bRegistred)&&(nEnableGesture>UNREGISTRED_VERSION_GESTURE_LIMIT))disable=true;
					AddGesture(0,name,description,commands,symbols,compatibility,disable);
				}
				if(p=str.Find(_T("opengroup["))==0)
				{
					name=str.Mid(10,str.GetLength()-10-1);
					AddGesture(1,name,description,commands,symbols,compatibility,disable);					
				}
				if(p=str.Find(_T("closegroup["))==0)
				{
					AddGesture(2,name,description,commands,symbols,compatibility,disable);					
				}
				str.Empty();
			}
		}
		else
			str+=ch;
	}
	return true;
}

bool CIdentify::Save(CString filename)
{
	CString image;
	long i=0;
	for(i=0;i<m_nGestures;i++)
	{
		switch(m_Gestures[i].m_GroupStatus)
		{
			case 0:
				if(!m_Gestures[i].m_Description.IsEmpty())
					image+=_T("description[")+ToSafe(m_Gestures[i].m_Description)+_T("]\n");
				image+=_T("name[")+ToSafe(m_Gestures[i].m_Name)+_T("]\n");
				image+=_T("commands[")+(CString)m_Gestures[i].m_Commands+_T("]\n");
				if(m_Gestures[i].m_Compatibility.m_Type!=0)
					image+=_T("compatibility[")+(CString)m_Gestures[i].m_Compatibility+_T("]\n");// no convert!
				if(m_Gestures[i].m_Disable==true)
					image+=_T("disable[]\n");
				image+=_T("symbols[")+(CString)m_Gestures[i].m_Symbols+_T("]\n");
			break;
			case 1:
				if(!m_Gestures[i].m_Description.IsEmpty())
					image+=_T("description[")+ToSafe(m_Gestures[i].m_Description)+_T("]\n");
				image+=_T("opengroup[")+ToSafe(m_Gestures[i].m_Name)+_T("]\n");
			break;
			case 2:
				if(!m_Gestures[i].m_Description.IsEmpty())
					image+=_T("description[")+ToSafe(m_Gestures[i].m_Description)+_T("]\n");
				image+=_T("closegroup[")+ToSafe(m_Gestures[i].m_Name)+_T("]\n");
			break;
		}
		image+=_T("\n");
	}
	long length=image.GetLength();

	CFile file;
	if(!file.Open(filename,CFile::modeWrite|CFile::modeCreate))
		return false;
	file.SeekToBegin();
	file.Write(image.GetBuffer(length),length);
	file.Close();

	return true;
}





CGesture* CIdentify::GetGestureById(int id)
{
	int number=m_Tunnel.GetNumberById(id);
	if((number<0)||(number>=m_nGestures)) return NULL;
	return &m_Gestures[number];
}

template<typename T>
void printArray(CArray<T> &array, int length)
{
	for(int i=0;i<length;i++)
	{
		TRACE(_T("array[%i]="),i);
		TRACE(array[i].m_Description);
		TRACE(_T("\n"));
	}
	TRACE(_T("\n"));
}

// [*] перемещает жест или элемент списка жестов element на родительский уровень parent
void CIdentify::Move(int element, int parent)
{
	switch(m_Gestures[element].m_GroupStatus)
	{
	case 0:// простой жест
		{
			printArray(m_Gestures,m_nGestures);
			CGesture gesture;
			gesture=m_Gestures[element];
			TRACE(gesture.m_Description);

			m_Gestures.InsertAt(parent+1,gesture);

			printArray(m_Gestures,m_nGestures);

			if(parent>element)
				m_Gestures.RemoveAt(element);
			else
				m_Gestures.RemoveAt(element+1);
			printArray(m_Gestures,m_nGestures);
			// модифицируем тунель
			m_Tunnel.Move(element,1,parent+1);

		}
	break;
	case 1: // группа жестов
		{
			printArray(m_Gestures,m_nGestures);
			int level=0,count=0,i=element;
			do
			{
				switch(m_Gestures[i++].m_GroupStatus)
				{
					case 0:

					break;
					case 1:
						level++;
					break;
					case 2:
						level--;
					break;
				}
				count++;
			}
			while(level>0);
			CArray<CGesture> group;
			group.SetSize(count);
			for(i=0;i<count;i++)
				group.SetAt(i,m_Gestures[element+i]);
			printArray(group,count);
			m_Gestures.InsertAt(parent+1,&group);
			printArray(m_Gestures,m_nGestures);
			if(parent>element)
				m_Gestures.RemoveAt(element,count);
			else
				m_Gestures.RemoveAt(element+count,count);
			printArray(m_Gestures,m_nGestures);
			// модифицируем тунель
			m_Tunnel.Move(element,count,parent+1);
		}
	break;
	default:
		ASSERT(FALSE);
	}
}

#define _point_to_int(p) ((p).x+(p).y*0xffff)
#define _int_to_point(i,p) {(p).x=i%0xffff;(p).y=i/0xffff;}

void CIdentify::NextPoint(WPARAM wParam, LPARAM lParam)
{
	static POINT old;
	POINT pt;
	_int_to_point((LONG)lParam,pt);
	// начинаем распозновать
	if(wParam==0)
	{
		theSymbol.m_nDirection=0;
		old=pt;
		return;
	}

	// продолжаем распозновать
	if(wParam==1) 
	{
		if(theSymbol.m_nDirection+1>=MAXSYMBOLELEMENT)
			return;
		int dx=pt.x-old.x, dy=pt.y-old.y;
		#define MINSTEP 10
		if(!((abs(dx)>MINSTEP)||(abs(dy)>MINSTEP)))return;
		old=pt;
		theSymbol.m_Direction[theSymbol.m_nDirection].x=dx;
		theSymbol.m_Direction[theSymbol.m_nDirection].y=dy;
        theSymbol.m_nDirection++;
		return;
	}

	// заканчиваем распозновать
	if(wParam==2)
	{
		if(theSymbol.m_nDirection<=4)return;
		int a=0;
		if((HWND)lParam!=NULL)
			for(a=0;a<m_nGestures;a++)
				if(m_Gestures[a].Compare(&theSymbol))
				{
					if(m_Gestures[a].Execute(m_hServerWnd,(HWND)lParam))
                        break;
				}
		return;
	}
}

// возвращает true если привышен лимит активных жестов для этой версии программы
bool CIdentify::GestureLimit(void)
{
	if(theProperties.bRegistred)return false;
	int number=0;
	for(int i=0;i<m_nGestures;i++)
		if((m_Gestures[i].m_GroupStatus==0)&&(m_Gestures[i].m_Disable==0))number++;
	return number>=UNREGISTRED_VERSION_GESTURE_LIMIT;
}

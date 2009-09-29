#include "StdAfx.h"
#include "gesture.h"

CGesture::CGesture(void)
{
	m_Disable=false;
}


CGesture::~CGesture(void)
{
}

CGesture::CGesture(CGesture &obj)
{
	*this=obj;
}

CGesture& CGesture::operator = (const CGesture &obj)
{
	this->m_Name=obj.m_Name;
	this->m_Description=obj.m_Description;
	this->m_GroupStatus=obj.m_GroupStatus;
	this->m_Symbols=obj.m_Symbols;
	this->m_Commands=obj.m_Commands;
	this->m_Compatibility=obj.m_Compatibility;
	this->m_Disable=obj.m_Disable;
	return *this;
}

bool CGesture::Compare(CSymbol* pSymbol)
{
	if(m_GroupStatus!=0)return false;
	if(m_Disable)return false;
	for(int i=0;i<m_Symbols.m_nSymbol;i++)
		if(m_Symbols.m_Symbol[i].Compare(pSymbol))
		{
			TRACE(_T(" !!! %s \n"),m_Name);
			return true;
		}
	return false;
}

//
void PressHotKey(BYTE key, BYTE mod)
{
	keybd_event(mod, 0, 0, 0);
	keybd_event(key, 0, 0, 0);
	keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(mod, 0, KEYEVENTF_KEYUP, 0);
}


HWND hServer_;
HWND hTarget_;
CGesture* pGesture_;

// поток на выполнение...
UINT ExecuteThread(LPVOID pParam)
{
	HWND hServer=hServer_;
	HWND hTarget=hTarget_;
	CGesture* pGesture=pGesture_;

	// *** выпоняем
	// сообщаяем главному окну
	PostMessage(hServer,WM_IDENTIFY,(WPARAM)1,(LPARAM)pGesture);
	CAction* pAction;
	for(int i=0;i<pGesture->m_Commands.m_nActions;i++)
	{
		pAction=&pGesture->m_Commands.m_Actions[i];
		switch(pAction->m_Type)
		{
			case 0:
			{
				CString &s=pAction->m_Param[0];
				if(s==_T("Close"))
				{
					PressHotKey(VK_F4,VK_MENU);
					//PostMessage(m_hClientWnd,WM_CLOSE,0,0);
				}
				if(s==_T("Maximize"))	PostMessage(hTarget, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
				if(s==_T("Minimize"))	PostMessage(hTarget, WM_SYSCOMMAND, SC_MINIMIZE, 0);
				if(s==_T("MinimizeAll"))
				{
					PressHotKey('D',VK_LWIN);
					//SendMessage(FindWindow("Shell_TrayWnd",NULL),WM_COMMAND,0x019F,0);
				}
				if(s==_T("Copy"))	PressHotKey('C',VK_CONTROL);
				if(s==_T("Paste"))	PressHotKey('V',VK_CONTROL);
				if(s==_T("Cut"))	PressHotKey('X',VK_CONTROL);
				if(s==_T("Open"))	PressHotKey('O',VK_CONTROL);
				if(s==_T("Save"))	PressHotKey('S',VK_CONTROL);
				if(s==_T("Print"))	PressHotKey('P',VK_CONTROL);
				if(s==_T("Next"))	PressHotKey(VK_RIGHT,VK_MENU);
				if(s==_T("Back"))	PressHotKey(VK_LEFT,VK_MENU);
				if(s==_T("Shutdown"))
				{
					ExitWindowsEx(EWX_POWEROFF|EWX_SHUTDOWN,0);
				}

				if(s==_T("NextWindow"))	PressHotKey(VK_ESCAPE,VK_MENU);
				if(s==_T("PrevWindow"))
				{
					keybd_event(VK_MENU, 0, 0, 0);
					keybd_event(VK_SHIFT, 0, 0, 0);
					keybd_event(VK_ESCAPE, 0, 0, 0);
					keybd_event(VK_ESCAPE, 0, KEYEVENTF_KEYUP, 0);
					keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
					keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
				}
				if(s==_T("Undo"))	PressHotKey('Z',VK_CONTROL);
				if(s==_T("Redo"))	PressHotKey('Y',VK_CONTROL);
				if(s==_T("SelectAll"))	PressHotKey('A',VK_CONTROL);
				if(s==_T("CloseDocument"))	PressHotKey(VK_F4,VK_CONTROL);
			}
			break;
			case 1:
				{
				//if(pAction->m_Param[0].Mid(pAction->m_Param[0].GetLength()-1,4)==".lnk")
                    ShellExecute(NULL,_T("open"),pAction->m_Param[0],pAction->m_Param[1],pAction->m_Param[2],SW_SHOWNORMAL);
				//else
                //    ShellExecute(NULL,"open","start "+pAction->m_Param[0],pAction->m_Param[1],pAction->m_Param[2],SW_SHOWNORMAL);
				}
			break;
			case 2:
				TypeText(pAction->m_Param[0],hTarget);
			break;
			case 3:
				{
				int type=0,key=0;
				CString s=pAction->m_Param[0];
				while(!s.IsEmpty())
					{
					pAction->GetKeyElement(s,type,key);
					if(type==0)
						keybd_event(key,0,0,0);
					else
						keybd_event(key,0,KEYEVENTF_KEYUP,0);
					Sleep(100);
					}
				/*	//old
					long i=0,m=0;
					i=atol(pAction->m_Param[0]);
					m=atol(pAction->m_Param[1]);
					
					if((m & HOTKEYF_SHIFT)==HOTKEYF_SHIFT)		keybd_event(VK_SHIFT,0,0,0);
					if((m & HOTKEYF_CONTROL)==HOTKEYF_CONTROL)	keybd_event(VK_CONTROL,0,0,0);
					if((m & HOTKEYF_ALT)==HOTKEYF_ALT)			keybd_event(VK_MENU,0,0,0);
					keybd_event((BYTE)i, 0, 0, 0);
					keybd_event((BYTE)i, 0, KEYEVENTF_KEYUP, 0);
					if((m & HOTKEYF_SHIFT)==HOTKEYF_SHIFT)		keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
					if((m & HOTKEYF_CONTROL)==HOTKEYF_CONTROL)	keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP,0);
					if((m & HOTKEYF_ALT)==HOTKEYF_ALT)			keybd_event(VK_MENU,0,KEYEVENTF_KEYUP,0);
				*/
				}
			break;
			case 4:
				PostMessage(hTarget,StringToLong(pAction->m_Param[0]),StringToLong(pAction->m_Param[1]),StringToLong(pAction->m_Param[2]));
			break;	
		}

	}
	return 0;
}

BOOL CGesture::Execute(HWND hServer, HWND hTarget)
{
	if((hServer==NULL)||(hTarget==NULL))return FALSE;
	// *** тест на пригодность жеста
	// *** получаем hwnd родителя
	HWND hWnd=NULL;
	while((hWnd=GetParent(hTarget))!=NULL)
		hTarget=hWnd;
	// *** тест на совместимость
	// получаем заголовок окна
	CString title;
	LPTSTR lpStr=title.GetBuffer(512);
	GetWindowText(hTarget,lpStr,512);
	title.ReleaseBuffer(512);
	TRACE(title);
	// получаем тип совместимости...
	int compatibilityType=m_Compatibility.m_Type;
	// построчня проверка...
	if(compatibilityType>0)
	{
		for(long i=0;i<m_Compatibility.m_nStrings;i++)
			if(title.Find(m_Compatibility.m_Strings[i])!=-1)
			{
				if(compatibilityType==1)
					return FALSE;
				if(compatibilityType==2)
					goto next;
			}
		if(compatibilityType==2)return FALSE;
	}
next:
	// *** передаем параметры
	hServer_=hServer;
	hTarget_=hTarget;
	pGesture_=this;
	// поехали!
	AfxBeginThread(ExecuteThread,this,THREAD_PRIORITY_NORMAL);
	return TRUE;
}

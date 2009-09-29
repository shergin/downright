#include "stdafx.h"

#define _COMPILING_44E531B1_14D3_11d5_A025_006067718D04
#include "Mirror.h"

// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ||| дефайны |||||||||||||||||||||||||||||||||||||||||||||||||||||||
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

// размер истории сообщений
#define MESSAGE_BUFFER_SIZE 8
// макрос для простого доступа к истории
#define _history(n) history[(begin+n)%MESSAGE_BUFFER_SIZE]
// константы типа уведомления о мышы
#define MIRROR_BEGIN	0
#define MIRROR_NEXT_DOT	1
#define MIRROR_END		2
#define MIRROR_ERROR	3
// максимальная длина дрейфа
#define LEEWAY_LENGTH 30 
// ген иммунитета для сообщений
#define IMMUNITY 0x80
// тривиальная математика
#define _abs(x) (((x)<0)?(-(x)):(x))
#define _max(a,b) (((a)>(b))?(a):(b))

#define DeleteMessage() {theCorpse.message=pMsg->message; theCorpse.time=pMsg->time; pMsg->message=WM_NULL; return 0;}

#define OUTCAST_BUFFER_LENGTH 1024*5
#define MAX_TITLE_LENGTH 256
#define _point_to_int(p) ((p).x+(p).y*0xffff)
#define _int_to_point(i,p) {(p).x=i%0xffff;(p).y=i/0xffff;}
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ||| межпроцессорная зона памяти |||||||||||||||||||||||||||||||||||
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
#pragma data_seg(".Downright")
// хёдер окна сервера
HWND hWndServer=NULL;
// хёдер окна на котором начали рисовать
HWND targetHwnd=NULL;
// - [*] история сообщений
//    - [*] струкура одного экземпляра истории
struct msg
{
// -  -  - [ ] сообщение
	unsigned int message;
// -  -  - [ ] количество одинаковых
	unsigned int number;
// -  -  - [ ] время создания
	unsigned int time;
// -  -  - [ ] общее смещение
	int offset;
};
// -  - [ ] плавающий указатель на начало
int begin=MESSAGE_BUFFER_SIZE-1;
// -  - [ ] массив данных о истории
__declspec(allocate(".Downright")) msg history[MESSAGE_BUFFER_SIZE];
// -  - [ ] pпеременные для учета общего смещения
int lastX=0;
int lastY=0;


struct corpse
{
	unsigned int message;
	unsigned int time;
};
corpse theCorpse;


// -  [*] флаги состояний
int passMessage=0;
MSG leewayMsg;

__declspec(allocate(".Downright")) TCHAR outcast[OUTCAST_BUFFER_LENGTH];
unsigned int outcastVersion=1;

unsigned int DisableKey=0x08;
unsigned int DrawingButtonDown=WM_RBUTTONDOWN;
unsigned int DrawingButtonUp=WM_RBUTTONUP;
#pragma data_seg()
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

#pragma comment(linker, "/section:.Downright,rws")

HINSTANCE hInst;
UINT UWM_MOUSEMOVE;
HHOOK hook;
static LRESULT CALLBACK msghook(UINT nCode, WPARAM wParam, LPARAM lParam);

unsigned int outcastTestVersion=0;
bool bNoSupportWindow=false;


void stringcopy(TCHAR* a, TCHAR* b) // a=b
{
	if(!b)
	{
		a[0]=0;
		return;
	}
	unsigned int i=0;
	do
	{
		a[i]=b[i];
		i++;
	}
	while(b[i]!=0);
}

bool findstr(TCHAR *a, TCHAR *b)// в строке a ищет строку b
{
	if(!a)return false;
	if(b[0]<2)return false;
	long i=0,p=0;
	bool succes;
	while(a[i]>1)
	{
		p=0;
		succes=true;
		if((a[p+i]>1)&&(b[p]>1))
			while((a[p+i]>1)&&(b[p]>1))
			{
				if(a[p+i]!=b[p]){succes=false;break;}
				p++;
			}
		else
			succes=false;
		if(succes)return true;
		i++;
	}
	return false;
}

bool isoutcast(TCHAR* title)
{
	unsigned int i=0;
	if(findstr(title,outcast))
		return true;
	while(outcast[i]!=0)
	{
		if(outcast[i]==1)
			if(findstr(title,outcast+i+1))
				return true;
		i++;
	}
	return false;
}



BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD  Reason, LPVOID Reserved)
{
	switch(Reason)
	{
	case DLL_PROCESS_ATTACH:
		hInst = hInstance;
		UWM_MOUSEMOVE = RegisterWindowMessage(UWM_MOUSEMOVE_MSG);
		return TRUE;
	case DLL_PROCESS_DETACH:
		if(hWndServer != NULL)
			clearMyHook(hWndServer);
		return TRUE;
	}
	return TRUE;
}


__declspec(dllexport) BOOL setMyHook(HWND hWnd, unsigned int down, unsigned int up, unsigned int key)
{
	if(hWndServer != NULL)
		return FALSE; // already hooked!

	DrawingButtonDown=down;
	DrawingButtonUp=up;
	DisableKey=key;

	hook = SetWindowsHookEx(/*WH_MOUSE*//*WH_GETMESSAGE*/WH_SYSMSGFILTER,
		(HOOKPROC)msghook,
		hInst,
		0);
	if(hook != NULL)
	{
		hWndServer = hWnd;
		return TRUE;
	}
	return FALSE;
}

__declspec(dllexport) void setHookParam(unsigned int down, unsigned int up, unsigned int key)
{
	DrawingButtonDown=down;
	DrawingButtonUp=up;
	DisableKey=key;
}

__declspec(dllexport) void setOutcast(TCHAR* buffer)
{
	outcastVersion++;
	stringcopy(outcast,buffer);
}

__declspec(dllexport) BOOL clearMyHook(HWND hWnd)
{
	if(hWnd != hWndServer || hWnd == NULL)
		return FALSE;
	BOOL unhooked = UnhookWindowsHookEx(hook);
	if(unhooked)
		hWndServer = NULL;
	return unhooked;
}


// главная функция
static LRESULT CALLBACK msghook(UINT nCode, WPARAM wParam, LPARAM lParam)
{
/*
	if(((LPMSG)lParam)->message==WM_MOVE){Beep(1000,100);}
	if(((LPMSG)lParam)->message==WM_SIZE){Beep(2000,100);}
	if(((LPMSG)lParam)->message==WM_WINDOWPOSCHANGING){Beep(3000,100);}
	if(((LPMSG)lParam)->message==WM_MOVING){Beep(4000,100);}*/

	if(((LPMSG)lParam)->message==WM_MOVING){Beep(4000,100);}
	if(((LPMSG)lParam)->message==WM_SIZING){Beep(4000,100);}
	if(((LPMSG)lParam)->message==WM_LBUTTONDOWN){Beep(4000,100);}


	// *** предварительные действия
	// не знаю что это... наверно нужная штука... Так делать реккомендуется, но никто не знает зачем... =)
	if(nCode<0)
	{
		CallNextHookEx(hook, nCode, wParam, lParam);
		return 0;
	}
	// наше сообщение, чтоб проще было обращаться...
	LPMSG pMsg=(LPMSG)lParam;

	// *** отфильтровываем ненужные сообщения
	if(pMsg->message==WM_MOUSEMOVE)goto next;
	if(pMsg->message==WM_LBUTTONDOWN)goto next;
	if(pMsg->message==WM_LBUTTONUP)goto next;
	if(pMsg->message==DrawingButtonDown)goto next;
	if(pMsg->message==DrawingButtonUp)goto next;
	
	return CallNextHookEx(hook, nCode, wParam, lParam);
next:

	// *** отфильтровываем неприкосновенные сообщения
	if(((pMsg->wParam & IMMUNITY)>0)||((pMsg->wParam & DisableKey)>0))
		return CallNextHookEx(hook,nCode,wParam,lParam);
	// *** убиваем тех, что и так уже трупы... зомби...
	if((pMsg->message==theCorpse.message)&&(pMsg->time==theCorpse.time))
		DeleteMessage();

	// *** пропуск сообщений окнам, умеющим распозновать жесты сами
	if(outcastVersion>outcastTestVersion)
	{
		// получаем родителя
		HWND nextWnd=NULL,parentWnd=pMsg->hwnd;
		while((nextWnd=GetParent(parentWnd))!=NULL)
			parentWnd=nextWnd;
		TCHAR title[MAX_TITLE_LENGTH];	//место под строку
		GetWindowText(parentWnd,title,MAX_TITLE_LENGTH);	// получаем
		bNoSupportWindow=isoutcast(title); // тестируем
		//if(bNoSupportWindow)Beep(100,100);
		outcastTestVersion=outcastVersion;
	}
	// если оно и само с усами...
	if(bNoSupportWindow)
		return CallNextHookEx(hook,nCode,wParam,lParam);


	// *** делаем прививку, MM прививку может не пережить
	pMsg->wParam|=IMMUNITY;


	// *** обновляем буфер
	if(_history(0).message==pMsg->message)
	{
		_history(0).number++;
		if(pMsg->message==WM_MOUSEMOVE)
		{
			_history(0).offset+=_max(_abs(pMsg->pt.x-lastX),_abs(pMsg->pt.y-lastY));
			lastX=pMsg->pt.x;
			lastY=pMsg->pt.y;
		}
		else
		{
			// ситуация теориетически не возможная, но встречающаяся...
			// наверно нашь хук вызывается дважды на одно сообщение...
			// остается вопрос: если на первом вызове мы его убили, дойдет ли оно до второго этапа...
			return CallNextHookEx(hook,nCode,wParam,lParam);
		}
	}
	else
	{
		// обновляем begin
		begin--;
		if(begin<0)begin=MESSAGE_BUFFER_SIZE-1;
		// дописываем сообщение
		_history(0).message=pMsg->message;
		_history(0).number=1;
		_history(0).offset=0;
		_history(0).time=pMsg->time;
		lastX=pMsg->pt.x;
		lastY=pMsg->pt.y;
	}

	// *** распознаем ситуации

	// установка признака passMessage (был левый клик)
	if
		(
			(
				(_history(0).message==WM_LBUTTONUP)
			)
			&&
			(
				(
					(_history(1).message==WM_MOUSEMOVE)&&
					(_history(1).offset<LEEWAY_LENGTH)&&
					(_history(2).message==WM_LBUTTONDOWN)	
				)
				||
				(
					(_history(1).message==WM_LBUTTONDOWN)	
				)
			)
		)
	{
		//устанавливаем испытательный срок
		passMessage=1;
	}

	// следим за испытательным сроком
	if
		(
			(passMessage==1)&&
			(_history(0).message==WM_MOUSEMOVE)&&
			(_history(0).offset>LEEWAY_LENGTH)
		)
		passMessage=0;

	// если испытательный срок прощел успешно, разрешаем
	if
		(
			(passMessage==1)
			&&
			(
				(_history(0).message==WM_LBUTTONDOWN)
				||
				(_history(0).message==DrawingButtonDown)
			)
		)
		passMessage=2;

	// если прошлое сообщение было UP во время халявы, то халява кончилась
	if
		(
			(passMessage==2)
			&&
			(
				(_history(1).message==WM_LBUTTONUP)
				||
				(_history(1).message==DrawingButtonUp)
			)
		)
		passMessage=0;

	// если мы добрые, то пусть идут дальше
	if(passMessage==2)
		return CallNextHookEx(hook, nCode, wParam, lParam);


	if(_history(0).message==DrawingButtonDown)
	{
		// сообщаем серверу
		targetHwnd=pMsg->hwnd;
		PostMessage(hWndServer, UWM_MOUSEMOVE, (WPARAM)MIRROR_BEGIN, (LPARAM)_point_to_int(pMsg->pt));
		// сохраняем
		leewayMsg=*pMsg;
		// убиваем
		DeleteMessage();
	}
	
	// посылаем координаты серверу
	if	(
			(_history(0).message==WM_MOUSEMOVE)&&
			(_history(1).message==DrawingButtonDown)
		)
	{
		// сообщаем серверу
		PostMessage(hWndServer, UWM_MOUSEMOVE, (WPARAM)MIRROR_NEXT_DOT, (LPARAM)_point_to_int(pMsg->pt));
	}


	if(_history(0).message==DrawingButtonUp)
	{
		if(_history(1).message==DrawingButtonDown)
		{
			goto rightClick;
		}
		else if
				(
					(_history(1).message==WM_MOUSEMOVE)&&
					(_history(2).message==DrawingButtonDown)
				)
				if(_history(1).offset>LEEWAY_LENGTH)
				{
					// * жест
					// сообщаем серверу
					PostMessage(hWndServer, UWM_MOUSEMOVE, (WPARAM)MIRROR_NEXT_DOT, (LPARAM)_point_to_int(pMsg->pt));
					PostMessage(hWndServer, UWM_MOUSEMOVE, (WPARAM)MIRROR_END, (LPARAM)targetHwnd);
					// убиваем текущее
					DeleteMessage();
				}
				else
				{
					// * пьяный райтклик
rightClick:
					// сообщаем серверу
					PostMessage(hWndServer, UWM_MOUSEMOVE, (WPARAM)MIRROR_ERROR, (LPARAM)0);
					// делаем смущенное лицо и возвращем, то что отняли...
					PostMessage(leewayMsg.hwnd	,leewayMsg.message	,leewayMsg.wParam | IMMUNITY	,leewayMsg.lParam	);
					PostMessage(leewayMsg.hwnd	,pMsg->message		,pMsg->wParam | IMMUNITY		,leewayMsg.lParam	);
					// убиваем текущее
					DeleteMessage();
				}
	}











	// *** если мы не придумали что с тобой сделать, так уж и быть, иди с миром...
	return CallNextHookEx(hook, nCode, wParam, lParam);
}

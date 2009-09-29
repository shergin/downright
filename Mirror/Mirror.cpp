#include "stdafx.h"

#define _COMPILING_DOWNRIGHT_MIRROR
#include "Mirror.h"

// [+] раздел€ема€ область пам€ти
#pragma data_seg(".Downright")
HWND hWndServer=NULL;

#pragma data_seg()
// [-] раздел€ема€ область пам€ти
// дополнительный параметр компоновщика
#pragma comment(linker,"/section:.Downright,rws")

HINSTANCE hInst;
UINT UWM_DOWNRIGHT_MIRROR;
HHOOK hookMouse, hookStick;

static LRESULT CALLBACK msgMouseHook(UINT nCode, WPARAM wParam, LPARAM lParam);
static LRESULT CALLBACK msgStickHook(UINT nCode, WPARAM wParam, LPARAM lParam);


BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD  reason, LPVOID reserved)
{
	switch(reason)
	{
		case DLL_PROCESS_ATTACH:
			hInst = hInstance;
			UWM_DOWNRIGHT_MIRROR = RegisterWindowMessage(UWM_DOWNRIGHT_MIRROR_MSG);
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
		return FALSE;

	hookMouse = SetWindowsHookEx(WH_MOUSE,	(HOOKPROC)msgMouseHook, hInst, 0);
	hookStick = SetWindowsHookEx(/*WH_GETMESSAGE*/ WH_SYSMSGFILTER,	(HOOKPROC)msgStickHook, hInst, 0);
	
	if(hookMouse && hookStick)
	{
		hWndServer = hWnd;
		return TRUE;
	}
	else
	{
		if(hookMouse)UnhookWindowsHookEx(hookMouse);
		if(hookStick)UnhookWindowsHookEx(hookStick);
		return FALSE;
	}
}

__declspec(dllexport) BOOL clearMyHook(HWND hWnd)
{
	if((hWnd != hWndServer) || (hWnd == NULL))
		return FALSE;
	BOOL unhookedMouse = UnhookWindowsHookEx(hookMouse);
	BOOL unhookedStick = UnhookWindowsHookEx(hookStick);
	if(unhookedMouse && unhookedStick)
		hWndServer = NULL;
	return unhookedMouse && unhookedStick;
}

__declspec(dllexport) void setHookParam(unsigned int down, unsigned int up, unsigned int key)
{
}

__declspec(dllexport) void setOutcast(TCHAR* buffer)
{
}

static LRESULT CALLBACK msgMouseHook(UINT nCode, WPARAM wParam, LPARAM lParam)
{
	return CallNextHookEx(hookMouse, nCode, wParam, lParam);
}

static LRESULT CALLBACK msgStickHook(UINT nCode, WPARAM wParam, LPARAM lParam)
{
	LPMSG pMsg=(LPMSG)lParam;
	
	if(pMsg->message==WM_WINDOWPOSCHANGING)
		Beep(1000,100);
	return CallNextHookEx(hookStick, nCode, wParam, lParam);
}

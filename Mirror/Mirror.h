#ifndef _DEFINED_DOWNRIGHT_MIRROR
	#define _DEFINED_DOWNRIGHT_MIRROR
	#if _MSC_VER > 1000
		#pragma once
	#endif
	#ifdef __cplusplus
		extern "C"
		{
	#endif // __cplusplus

		#ifdef _COMPILING_DOWNRIGHT_MIRROR
		#define LIBSPEC __declspec(dllexport)
		#else
		#define LIBSPEC __declspec(dllimport)
		#endif // _COMPILING_DOWNRIGHT_MIRROR
			LIBSPEC BOOL setMyHook(HWND hWnd, unsigned int down, unsigned int up, unsigned int key);
			LIBSPEC void setHookParam(unsigned int down, unsigned int up, unsigned int key);
			LIBSPEC void setOutcast(TCHAR* buffer);
			LIBSPEC BOOL clearMyHook(HWND hWnd);
		#undef LIBSPEC

	#ifdef __cplusplus
		}
	#endif // __cplusplus

	#define UWM_DOWNRIGHT_MIRROR_MSG _T("UWM_DOWNRIGHT_MIRROR_MSG-{44E531B1_14D3_11d5_A025_006067718D04}")

	#ifndef GET_X_LPARAM
	#define GET_X_LPARAM(p) ((int)(short)LOWORD(p))
	#define GET_Y_LPARAM(p) ((int)(short)HIWORD(p))
	#endif

#endif // _DEFINED_DOWNRIGHT_MIRROR


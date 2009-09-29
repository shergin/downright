#pragma once
#include "StringTool.h"
class CAction
{
public:
	int m_Type;
	CString m_Param[3];
	void operator = (CString s);
	operator CString();
	CString GetDescription(void);
	void SetActionType(int type);
	static void GetKeyElement(CString &s,int &type,int &key);
};

const CString StandartAction[]=
	{
	_T("Close"),
	_T("Maximize"),
	_T("Minimize"),
	_T("MinimizeAll"),
	_T("Copy"),
	_T("Paste"),
	_T("Cut"),
	_T("Open"),
	_T("Save"),
	_T("Print"),
	_T("Next"),
	_T("Back")
	_T("NextWindow"),
	_T("PrevWindow"),
	_T("Undo"),
	_T("Redo"),
	_T("SelectAll"),
	_T("CloseDocument"),
	_T("Shutdown")
	};
#define StandartActionCount (sizeof(StandartAction)/sizeof(StandartAction[0]))

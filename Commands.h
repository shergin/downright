#pragma once

#include "Action.h"
#include "afxtempl.h"

// implementation


class CCommands
{
public:
	CCommands(void);
	~CCommands(void);
	void operator = (CString s);
	CCommands& operator = (const CCommands &obj);
	operator CString();
	int m_nActions;
	CArray<CAction,CAction&> m_Actions;
};

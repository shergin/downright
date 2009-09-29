#pragma once
#include "Sleeper.h"
#include "afxtempl.h"

class CTunnel
{
public:
	CTunnel(void);
	~CTunnel(void);	
	int Add(int number);
	int GetNumberById(int id);

	CArray<CSleeper> m_Tunnel;
	int m_nTunnel;
	int m_Index;
	void Delete(int number, int count=1);
	void Move(int begin, int count, int position);
	void InsertSpace(int position, int count);
};

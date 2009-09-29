#include "StdAfx.h"
#include "Tunnel.h"

CTunnel::CTunnel(void)
{
	m_Tunnel.RemoveAll();
	m_Tunnel.SetSize(100,50);
	m_nTunnel=0;
	m_Index=999;
}

CTunnel::~CTunnel(void)
{
}

int CTunnel::Add(int number)
{
	m_Index++;
	CSleeper sleeper;
	sleeper.id=m_Index;
	sleeper.number=number;
	m_Tunnel.SetAtGrow(m_nTunnel,sleeper);
	m_nTunnel++;
	return m_Index;
}

int CTunnel::GetNumberById(int id)
{
	for(int i=0;i<m_nTunnel;i++)
		if(m_Tunnel[i].id==id)
			return m_Tunnel[i].number;
	return -1;
}

void CTunnel::Delete(int number, int count)
{
	for(int i=0;i<m_nTunnel;i++)
	{
		if(m_Tunnel[i].number>=number && m_Tunnel[i].number<number+count)
		{
			m_Tunnel.RemoveAt(i);
			i--;
			m_nTunnel--;
			continue;
		}
		if(m_Tunnel[i].number>=number+count)
			m_Tunnel[i].number-=count;
	}
}

//перемещает данные по номеру
void CTunnel::Move(int begin, int count, int position)
{
	if( (position>=begin) && (position<begin+count) )
		return;
	if(position<begin)
	{
		for(int i=0;i<m_nTunnel;i++)
		{
			if( (m_Tunnel[i].number>=position) && (m_Tunnel[i].number<begin) )
			{
				m_Tunnel[i].number+=count;
				continue;
			}
			if( (m_Tunnel[i].number>=begin) && (m_Tunnel[i].number<begin+count) )
			{
				m_Tunnel[i].number=position+(m_Tunnel[i].number-begin);
				continue;
			}
		}
	}
	else
	{
		for(int i=0;i<m_nTunnel;i++)
		{
			if( (m_Tunnel[i].number>=begin) && (m_Tunnel[i].number<begin+count) )
			{
				m_Tunnel[i].number=position-count+(m_Tunnel[i].number-begin);
				continue;
			}
			if( (m_Tunnel[i].number>=begin+count) && (m_Tunnel[i].number<position) )
			{
				m_Tunnel[i].number-=count;
				continue;
			}
		}
	}
}

void CTunnel::InsertSpace(int position, int count)
{
	for(int i=0;i<m_nTunnel;i++)
	{
		if(m_Tunnel[i].number>=position)
			m_Tunnel[i].number+=count;
	}
}


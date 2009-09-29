#include "StdAfx.h"
#include "symbol.h"

CSymbol::CSymbol(void)
{
	m_nDirection=0;
}

CSymbol::~CSymbol(void)
{
}

void CSymbol::operator = (CString &s)
{
	if(s.GetLength()>MAXSYMBOLELEMENT*4)
		s=s.Left(MAXSYMBOLELEMENT*4);
	int p=0;
	for(p=0;p+3<s.GetLength();p+=4)
	{
		m_Direction[p/4].x=((unsigned char)s.GetAt(p+0)-48)*10;
		m_Direction[p/4].x+=((unsigned char)s.GetAt(p+1)-48);
		m_Direction[p/4].x-=50;
		m_Direction[p/4].y=((unsigned char)s.GetAt(p+2)-48)*10;
		m_Direction[p/4].y+=((unsigned char)s.GetAt(p+3)-48);
		m_Direction[p/4].y-=50;
	}
	m_nDirection=p/4;
}
#define _normalize(x) {if(x<-49)x=-49;if(x>49)x=49;}
CSymbol::operator CString()
{
	CString result;
	for(int i=0;i<m_nDirection;i++)
	{
		_normalize(m_Direction[i].x);
		_normalize(m_Direction[i].y);
		int x=m_Direction[i].x+50;
		int y=m_Direction[i].y+50;
		result+=(CString)((char)((x/10)+48));
		result+=(CString)((char)((x%10)+48));
		result+=(CString)((char)((y/10)+48));
		result+=(CString)((char)((y%10)+48));
	}
	return result;
}

long nMin(double x, double y, double z)
{
	if((x<=y)&&(x<=z))return 0;
	if((y<=x)&&(y<=z))return 1;
	if((z<=x)&&(z<=y))return 2;
	return -1;
}
bool CSymbol::Compare(CSymbol* pSymbol)
{
	double epsilon=30.+((m_nDirection>15)?(15.):(0.));

	if(m_nDirection<=0)return false;
	int a=0,b=0;
	double r1=0,r2=0,r3;
	bool succes=false;
	while(1)
	{
		// a+1
		if(a+1<m_nDirection)
			r1=(m_Direction[a+1]==pSymbol->m_Direction[b]);
		else
			r1=777;

		// b+1
		if(b+1<pSymbol->m_nDirection)
			r2=(m_Direction[a]==pSymbol->m_Direction[b+1]);
		else
			r2=777;

		// a+1, b+1
		if((b+1<pSymbol->m_nDirection)&&(a+1<m_nDirection))
			r3=(m_Direction[a+1]==pSymbol->m_Direction[b+1]);
		else
			r3=777;
		

		if((r1==777)&&(r2==777))
		{
			succes=true;			
			break;
		}
		if(min(r1,r2)>epsilon)
			if(r3>epsilon*1.8)
			{
				succes=false;
				break;
			}
		switch(nMin(r1,r2,r3))
		{
			case 0:a++;break;
			case 1:b++;break;
			case 2:a++;b++;break;
			default:
				ASSERT(1);
		}
	} // while
	return succes;
}


/*

bool Gesture::Compare(CIdentify* pMain)
{
	const double epsilon=40.;
	Symbol symbol;
	long a=0,b=0;
	for(a=0;a<SymbolCount;a++)
	{
		symbol=GetSymbol(a);
		if(symbol.nElements<=0)continue;
		long a=0,b=0;
		double r1=0,r2=0,r3;
		bool succes=false;
		while(1)
		{
			// a+1
			if(a+1<symbol.nElements)
				r1=(symbol.Elements[a+1]==pMain->m_Elements[b]);
			else
				r1=777;
			// b+1
			if(b+1<pMain->m_nElements)
				r2=(symbol.Elements[a]==pMain->m_Elements[b+1]);
			else
				r2=777;
			// a+1, b+1
			if((b+1<pMain->m_nElements)&&(a+1<symbol.nElements))
				r3=(symbol.Elements[a+1]==pMain->m_Elements[b+1]);
			else
				r3=777;
			//

			if((r1==777)&&(r2==777))
			{
				succes=true;			
				break;
			}
			if(min(r1,r2)>epsilon)
				if(r3>epsilon*1.8)
				{
					succes=false;
					break;
				}
			switch(nMin(r1,r2,r3))
			{
				case 0:a++;break;
				case 1:b++;break;
				case 2:a++;b++;break;
				default:
					ASSERT(1);
			}
		}
		if(succes)
		{
			TRACE(" ==== "+Description+"\n");
			return true;
		}
	}
	return false;
};

*/
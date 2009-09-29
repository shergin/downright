#include "StdAfx.h"
#include "graph.h"
//#include "math.h"
#define Abs(x) ((x<0)?(-x):(x)) 


union rgb
{
	unsigned __int8 element[3];
	COLORREF color;
};

void MultiplyColor(COLORREF &color, double k)
{
	rgb x;
	x.color=color;
	x.element[0]=(unsigned __int8)((double)x.element[0]*k);
	x.element[1]=(unsigned __int8)((double)x.element[1]*k);
	x.element[2]=(unsigned __int8)((double)x.element[2]*k);
	color=x.color;
}


CGraph::CGraph(void)
: m_bShowSplitter(false)
{
	m_GesturePreviewCreate=false;
	m_bShowSplitter=false;
	m_ScrollPos=0;
}

CGraph::~CGraph(void)
{
	if((HDC)m_GesturePreviewDC!=0)
	{
		//m_Bitmap.Detach();
		m_GesturePreviewDC.Detach();	
		m_GesturePreviewBitmap.DeleteObject();
		m_GesturePreviewDC.DeleteDC();
	}
}

#define line(p,x1,y1,x2,y2) (p)->MoveTo(x1,y1);(p)->LineTo(x2,y2); // Линия
#define rectangle(p,x1,y1,x2,y2) line(p,x1,y1,x2,y1);line(p,x1,y2,x2,y2);line(p,x1,y1,x1,y2);line(p,x2,y1,x2,y2);
#define rect(r,x1,y1,x2,y2); r.left=(x1);r.top=(y1);r.right=(x2);r.bottom=(y2);

// инициализируем
void CGraph::Init(CWnd *pMainWnd, CPoint *pSize, HBRUSH *pHBRUSH, CIdentify *pIdentify)
{
	m_pIdentify=pIdentify;
	m_pHBRUSH=pHBRUSH;
	m_pMainWnd=pMainWnd;
	m_pSize=pSize;
	m_SplitterPosition=300;
	Color[0]=(COLORREF)GetSysColor(COLOR_BTNFACE); // фон окна диалога
	Color[1]=(COLORREF)GetSysColor(COLOR_HIGHLIGHTTEXT/*COLOR_WINDOW*/); // фон окна (~белый)
	Color[3]=(COLORREF)GetSysColor(COLOR_INACTIVECAPTION);
	Color[2]=Color[3];
	MultiplyColor(Color[2],0.6);
	Color[4]=Color[2];
	MultiplyColor(Color[4],0.9);
	//Color[2]=(COLORREF)GetSysColor(COLOR_HIGHLIGHT);
	Color[5]=(COLORREF)RGB(0,0,0);
	Color[6]=(COLORREF)RGB(255,255,255);
}

void CGraph::Draw(int param, int activeGesture)
{
	TRACE("Draw\n");
	CClientDC DC(m_pMainWnd);
	CBrush *background=NULL;
	if(m_pHBRUSH!=0)
	{
		background=background->FromHandle(*m_pHBRUSH);
		DC.SetBrushOrg(100,5);
	}
	CBrush brush,brush1;
	brush.CreateSolidBrush(Color[6]);
	CBrush* pOldBrush=DC.SelectObject(&brush);

	CPen pen;
	pen.CreatePen(PS_SOLID,1,Color[3]);
	CPen* pOldPen=DC.SelectObject(&pen);
	int k=5,s=7; // коэфициент пропорций логотипа
	RECT r;
	rect(r	,s+0		,-s+m_pSize->y-k*10		,s+k		,-s+m_pSize->y		);	DC.FillSolidRect(&r,Color[2]);
	rect(r	,s+k*9		,-s+m_pSize->y-k*10		,s+k*10		,-s+m_pSize->y		);	DC.FillSolidRect(&r,Color[2]);
	rect(r	,s+k		,-s+m_pSize->y-k*10		,s+k*9		,-s+m_pSize->y-k*9	);	DC.FillSolidRect(&r,Color[2]);
	rect(r	,s+k		,-s+m_pSize->y-k		,s+k*9		,-s+m_pSize->y		);	DC.FillSolidRect(&r,Color[2]);
	rect(r	,s+k*6		,-s+m_pSize->y-k*9		,s+k*9		,-s+m_pSize->y-k*6	);	DC.FillSolidRect(&r,Color[2]);
	rect(r	,s+k*11-2	,27						,s+k*12-2	,s+m_pSize->y-s*2	);	DC.FillSolidRect(&r,Color[2]);
	

	// [-] сплеш
	if(param==2)
	{
		int x1=68;
		int y1=27;
		int x2=m_pSize->x-7;
		int y2=m_pSize->y-7;
		DrawBigLogoSpace(&DC,x1,y1,x2,y2);

		// подготовка шрифтов
		LOGFONT logFont;
		logFont.lfHeight=26;
		logFont.lfWidth=0;
		logFont.lfEscapement=0;
		logFont.lfOrientation=0;
		logFont.lfWeight=0;
		logFont.lfItalic=0;
		logFont.lfUnderline=0;
		logFont.lfStrikeOut=0;
		logFont.lfCharSet=1;
		logFont.lfOutPrecision=OUT_DEFAULT_PRECIS;
		logFont.lfClipPrecision=CLIP_DEFAULT_PRECIS;
		logFont.lfQuality=ANTIALIASED_QUALITY;
		logFont.lfPitchAndFamily=VARIABLE_PITCH|FF_SWISS;
		_tcscpy_s(logFont.lfFaceName,_T("Tahoma"));
		DC.SetBkMode(TRANSPARENT);
		//нормальный
		CFont NormalFont;
		NormalFont.CreateFontIndirect(&logFont);
		//вертикальный
		logFont.lfEscapement=2700;
		logFont.lfHeight=22;
		CFont VertFont;
		VertFont.CreateFontIndirect(&logFont);
		//маленький
		logFont.lfEscapement=0;
		logFont.lfHeight=11;
		CFont SmallFont;
		SmallFont.CreateFontIndirect(&logFont);
		//правый
		logFont.lfOrientation=16;
		logFont.lfHeight=26;
		CFont RightFont;
		RightFont.CreateFontIndirect(&logFont);


		CFont* oldFont=DC.SelectObject(&NormalFont);
		
		DC.SetTextColor(Color[3]);
		DC.TextOut(x1+10,y2-55,_T("downright blackrain, generation three, version eight"));
		DC.SetTextColor(Color[4]);
		DC.TextOut(x2-280,y2-72,_T("http://downright.shergin.com"));
		DC.SetTextColor(Color[3]);
		DC.SelectObject(&VertFont);
		int i=0;
/*		DC.TextOut(x2-73+i++*18,y1+10,"pr.shergin");
		DC.TextOut(x2-73+i++*18,y1+10,"web.shergin");
		DC.TextOut(x2-73+i++*18,y1+10,"design.shergin");
		DC.TextOut(x2-73+i++*18,y1+10,"programming.shergin");
		DC.TextOut(x2-73+i++*18,y1+10,"research.shergin");
*/		
		DC.TextOut(x2-2,y1+11,_T("copyright © shergin research lab, 2003-05"));

	//	DC.SelectObject(&RightFont);
	//	DC.TextOut(x2-10,y2-70,"http://downright.shergin.net");




		DC.SelectObject(&SmallFont);
		DC.TextOut(x2-570,y2-27,_T("This computer program is protected by copyright law and international treaties. Unauthorized reproduction or distribution of this program,"));
		DC.TextOut(x2-570,y2-18,_T("or any portion of it, may result in severe civil and penalties, and will be prosecuted to the maximum extent possible under the law."));
		goto label_return;
	}


	// [-] разделитель
	if(m_bShowSplitter)
	{
		static int oldPos=-1;
		//   [-] стираем 
		if(oldPos!=-1)
		{
			rect(r,oldPos,27,oldPos+k,m_pSize->y-s);	DC.FillSolidRect(&r,Color[0]);
		}
		oldPos=m_SplitterPosition;
		//   [-] рисуем
		rect(r,m_SplitterPosition,27,m_SplitterPosition+k,m_pSize->y-s);	DC.FillSolidRect(&r,Color[2]);
	}

	if(param==3)
	{
		int x1=m_SplitterPosition+12;
		int y1=51;
		int x2=m_pSize->x-11;
		int y2=m_pSize->y-11;
		DrawBigLogoSpace(&DC,x1,y1,x2,y2);
	}
	if(param==1)//рисуем панель символов
	{
		int x1=m_SplitterPosition+12;
		int y1=51;
		int x2=m_pSize->x-11;
		int y2=m_pSize->y-11;

		DrawBigLogoSpace(&DC,x1,y1,x2,y2);

		CRgn rgn;
		rgn.CreateRectRgn(x1+5*2,y1+5*2,x2-5*2,y2-5*2);
		DC.SelectClipRgn(&rgn);

		CPoint point;

		int n=10;
		int level=0,i=0;
		int x=0, y=0;
		CSymbols &symbols=m_pIdentify->m_Gestures[activeGesture].m_Symbols;
		for(i=0;i<symbols.m_nSymbol;i++)
		{
			point.x=x2-57-x*53;
			point.y=y2-57-y*53;
		
			DrawSymbol(&DC,point,&symbols.m_Symbol[i],0);


			// x, y

			x++;y--;
			if((y<0)/*||(m_SplitterPosition+x*61+100>m_pSize->x)*/){level++;y=level;x=0;}
		}

		rgn.DeleteObject();
	}
label_return:
	DC.SelectObject(pOldBrush);
	DC.SelectObject(pOldPen);
}

void CGraph::DrawSplitterBar(int position)
{
	m_SplitterPosition=position;
	CClientDC dc(m_pMainWnd);
	CBrush brush(Color[2]);
	CBrush* pOldBrush = dc.SelectObject(&brush);
	dc.PatBlt(
		position, 
		27, 
		5, 
		m_pSize->y-34,
		PATINVERT
	);
	dc.SelectObject(pOldBrush);
}



void CGraph::DrawSymbol(CDC* pDC, CPoint point, CSymbol* pSymbol, int style)
{
	int size=0;
	rgb c0,c1;
	if(style==0)
	{
		size=40;
//		pDC->FillSolidRect(point.x,point.y,size+6,size+6,Color[2]);
//		line(pDC,point.x-3,point.y-3,point.x-3,point.y+size+9);
//		line(pDC,point.x-3,point.y-3,point.x+size+9,point.y-3);
		COLORREF color=Color[2];
		MultiplyColor(color,0.7);
		DrawLogo(pDC,point.x-3,point.y-3,5,color);
		c0.color=Color[1];//1
		c1.color=Color[2];//2
	}
	if(style==1)
	{
		size=30;
		CPen pen;
		pen.CreatePen(PS_SOLID,1,Color[3]);
		CPen* pOldPen=pDC->SelectObject(&pen);
		//pDC->FillSolidRect(point.x,point.y,size+6,size+6,Color[0]);
		rectangle(pDC,point.x,point.y,point.x+size+6,point.y+size+6);
		pDC->SelectObject(pOldPen);
		c0.color=Color[2];//1
		c1.color=Color[0];//2
	}


	// символ не символ... то нахуй нам нужен такой символ?!
	if(pSymbol->m_nDirection==0)return;

	int i=0;

	int minx=0, miny=0, maxx=0, maxy=0;
	int px=0, py=0, ox=0, oy=0;
	int gx=0,gy=0;
	
	double len=0;
	for(i=0;i<pSymbol->m_nDirection;i++)
	{
		gx=pSymbol->m_Direction[i].x;
		gy=pSymbol->m_Direction[i].y;
		len+=max(Abs(gx),Abs(gy));
		px+=gx;
		py+=gy;
		if(minx>px)minx=px;
		if(miny>py)miny=py;
		if(maxx<px)maxx=px;
		if(maxy<py)maxy=py;
	}
	ox=maxx-minx;//по идее minx <= 0 (miny <= 0)
	oy=maxy-miny;
	if((ox==0)&&(oy==0))return;

	double sx=(double)size/((double)ox+0.01),sy=(double)size/((double)oy+0.01);
	double scale=min(sx,sy);

	long dx=0,dy=0;
	if(ox<oy)
		dx=(long)(((double)(size-(double)scale*ox))/2.);
	else
		dy=(long)(((double)(size-(double)scale*oy))/2.);
	px=0;
	py=0;
	point.x+=dx+3-1;
	point.y+=dy+3-1;

	long d=pSymbol->m_nDirection;


	len*=scale;

	long iColor=0;
	
	float dr=(float)(c0.element[0]-c1.element[0])/(float)len;
	float dg=(float)(c0.element[1]-c1.element[1])/(float)len;
	float db=(float)(c0.element[2]-c1.element[2])/(float)len;
	
	unsigned __int8 rr;
	unsigned __int8 gg;
	unsigned __int8 bb;

	long x1=0,y1=0,x2=0,y2=0;
	x1=point.x-(long)((minx)*scale);
	y1=point.y-(long)((miny)*scale);
	for(i=0;i<d;i++)
	{
		px+=pSymbol->m_Direction[i].x;
		py+=pSymbol->m_Direction[i].y;
		x2=point.x+(long)((px-minx)*scale);
		y2=point.y+(long)((py-miny)*scale);
		{
			long dx=x2-x1;
			long dy=y2-y1;
			long length=max(Abs(dx),Abs(dy));
			
			double ldx=(double)dx/(double)length;
			double ldy=(double)dy/(double)length;
			long x=0,y=0;
			double i;
			for(i=0;i<length;i++)
			{
				x=x1+(long)(ldx*i);
				y=y1+(long)(ldy*i);
				rr=(unsigned __int8)((long)c0.element[0]-(long)(dr*iColor));
				gg=(unsigned __int8)((long)c0.element[1]-(long)(dg*iColor));
				bb=(unsigned __int8)((long)c0.element[2]-(long)(db*iColor));
				iColor++;
				pDC->SetPixelV(x  ,y  ,RGB(rr,gg,bb));
				pDC->SetPixelV(x  ,y-1,RGB(rr,gg,bb));
				pDC->SetPixelV(x  ,y+1,RGB(rr,gg,bb));
				pDC->SetPixelV(x-1,y  ,RGB(rr,gg,bb));
				pDC->SetPixelV(x+1 ,y  ,RGB(rr,gg,bb));
/*				
				if(Abs(ldx)<Abs(ldy))
					pDC->SetPixelV(x-1,y,RGB(rr,gg,bb));
				else
					pDC->SetPixelV(x,y-1,RGB(rr,gg,bb));
*/				
			}
			iColor--;
		}
		x1=x2;
		y1=y2;
	}


}

#define GesturePreviewWidth 1000
void CGraph::CreateGesturePreview(void)
{
	m_GesturePreviewCreate=true;
	m_GesturePreviewSize.SetPoint(600,1000);
	if((HDC)m_GesturePreviewDC!=0)
	{
		m_GesturePreviewBitmap.Detach();
		m_GesturePreviewDC.Detach();
	}
	CClientDC dc(m_pMainWnd);
	m_GesturePreviewDC.CreateCompatibleDC(&dc);
	m_GesturePreviewBitmap.CreateCompatibleBitmap(&dc,m_GesturePreviewSize.x,m_GesturePreviewSize.y);
	m_GesturePreviewDC.SelectObject(m_GesturePreviewBitmap);
	m_GesturePreviewDC.FillSolidRect(0,0,600,600,Color[2]);



	// подготовка шрифтов

	LOGFONT logFont;
	logFont.lfHeight=18;
	logFont.lfWidth=0;
	logFont.lfEscapement=0;
	logFont.lfOrientation=0;
	logFont.lfWeight=0;
	logFont.lfItalic=0;
	logFont.lfUnderline=0;
	logFont.lfStrikeOut=0;
	logFont.lfCharSet=1;
	logFont.lfOutPrecision=OUT_DEFAULT_PRECIS;
	logFont.lfClipPrecision=CLIP_DEFAULT_PRECIS;
	logFont.lfQuality=DRAFT_QUALITY;
	logFont.lfPitchAndFamily=VARIABLE_PITCH|FF_SWISS;
	_tcscpy_s(logFont.lfFaceName,_T("Tahoma"));
	m_GesturePreviewDC.SetBkMode(TRANSPARENT);
	//нормальный
	CFont NormalFont;
	NormalFont.CreateFontIndirect(&logFont);
	//вертикальный
	logFont.lfEscapement=900;
	CFont VertFont;
	VertFont.CreateFontIndirect(&logFont);
	
	CFont* oldFont=m_GesturePreviewDC.SelectObject(&NormalFont);
	
	m_GesturePreviewDC.SetTextColor(Color[3]);
	


	// начинаем рисовать
	CPoint point;
	#define offset 20
	int i=0,p=0,level=0,minus=0;
	for(i=0;i<m_pIdentify->m_nGestures;i++)
	{
		//m_GesturePreviewDC.FillSolidRect(5+level*offset,5+i*41+20,600,20,Color[0]);
		switch(m_pIdentify->m_Gestures[i].m_GroupStatus)
		{
		case 0:
			for(p=0;p<m_pIdentify->m_Gestures[i].m_Symbols.m_nSymbol;p++)
			{
				point.x=5+p*41+level*offset;
				point.y=5+i*41;
				DrawSymbol(&m_GesturePreviewDC, point, &m_pIdentify->m_Gestures[i].m_Symbols.m_Symbol[p],1);
			}
		break;
		case 1:
			level++;
		break;
		case 2:
			level--;
			minus++;
		break;
		}
		m_GesturePreviewDC.TextOut(7+level*offset,22+i*41,m_pIdentify->m_Gestures[i].m_Name);
	}

//	for(int g=0;g<20;g++)
//		m_GesturePreviewDC.FillSolidRect(10,g*30,600,g*30+30,(COLORREF)GetSysColor(g));
	

	m_GesturePreviewCreate=false;
}

void CGraph::DrawLogo(CDC* pDC, int x, int y, int k, COLORREF color)
{
	RECT r;
	rect(r	,x+0	,y+0	,x+k	,y+k*10	);	pDC->FillSolidRect(&r,color);
	rect(r	,x+k*9	,y+0	,x+k*10	,y+k*10	);	pDC->FillSolidRect(&r,color);
	rect(r	,x+k	,y+0	,x+k*9	,y+k*1	);	pDC->FillSolidRect(&r,color);
	rect(r	,x+k	,y+k*9	,x+k*9	,y+k*10	);	pDC->FillSolidRect(&r,color);
	rect(r	,x+k*6	,y+k*1	,x+k*9	,y+k*4	);	pDC->FillSolidRect(&r,color);
}

void CGraph::DrawBigLogoSpace(CDC* pDC, int x1, int y1, int x2, int y2)
{
	CRect r;
	rect(r,x1,y1,x2,y2);pDC->FillSolidRect(&r,Color[2]);

	COLORREF color=Color[2];
	MultiplyColor(color,0.9);
	DrawLogo(pDC,x1+(x2-x1)/2-60,y1+(y2-y1)/2-60,12,color);

	#define space 5
	#define thickness 40

	rect(r,x1+space,y1+space,x2-space,y1+space+thickness);pDC->FillSolidRect(&r,color);
	rect(r,x1+space,y2-space-thickness,x2-space,y2-space);pDC->FillSolidRect(&r,color);
}

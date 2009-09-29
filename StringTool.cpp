#include "StdAfx.h"
#include "stringtool.h"


/*
void CStringToLPSTR(CString &s, LPTSTR lpStr)
{
	int i=0;
	for(i=0;i<s.GetLength();i++)
	{
		lpStr[i]=s.GetAt(i);
	}
	lpStr[i]=0;
}
*/
#define getSymbol(x) (((x)<10)?((x)+'0'):((x)+'a'-10))
CString ToSafe(CString s)
{
	CString result;
	TCHAR ch=0,a=0;
	for(long i=0;i<s.GetLength();i++)
	{
		ch=s.GetAt(i);
		a=ch/16;a=getSymbol(a);
		result+=(CString)(char)a;
		a=ch%16;a=getSymbol(a);
		result+=(CString)(char)a;
	}
	return result;
}
#define isHexSymbol(x) ((((x)>='0')&&((x)<='9'))||(((x)>='a')&&((x)<='f')))
#define isDecSymbol(x) (((x)>='0')&&((x)<='9'))
CString FromSafe(CString s)
{
	//return s;////////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11
	CString error=_T("Internal error. (StringTool.cpp)");
	CString result;
	TCHAR ch=0,newch=0;
	if(s.GetLength()%2==1)return error;
	for(long i=0;i+1<s.GetLength();i+=2)
	{
		ch=s.GetAt(i);
		if(!isHexSymbol(ch))
			return error;
		ch-=(TCHAR)_T('0');
		if(ch>10)ch-=(TCHAR)_T('a')-(TCHAR)_T('0')-10;
		newch=ch*16;
		//
		ch=s.GetAt(i+1);
		if(!isHexSymbol(ch))
			return error;
		ch-=(TCHAR)_T('0');
		if(ch>10)ch-=(TCHAR)_T('a')-(TCHAR)_T('0')-10;
		newch+=ch;
		result+=newch;
	}
	return result;
}

///
unsigned long StringToLong(CString s)
{
	if(s.IsEmpty())return 0;
	s.MakeLower();
	long base=10,result=0;
	TCHAR ch=0;
	if(s.Find(_T("0x"))==0)
	{
		base=16;
		s.Delete(0,2);
	}
	if(s.GetAt(s.GetLength()-1)==_T('h'))
	{
		base=16;
		s.Delete(s.GetLength()-1,1);
	}
	s.MakeReverse();
	long b=1;
	for(long i=0;i<s.GetLength();i++)
	{
		ch=s.GetAt(i);
		ch-=(TCHAR)_T('0');
		if(ch>10)ch-=(TCHAR)_T('a')-(TCHAR)_T('0')-10;
		result+=ch*b;
		b*=base;
	}
	return result;
}

CString UnsignedLongToString(unsigned long number)
{
	CString s;
	unsigned char ch=0;
	unsigned char x=0;
	for(int i=0;i<8;i++)
	{
		x=(unsigned char)(number%16);
		if(x<10)
			ch=(unsigned char)_T('0')+(unsigned char)(x);
		else
			ch=(unsigned char)_T('a')+(unsigned char)(x-10);
		s+=ch;
		number/=16;
	}
	return s;
}

bool CorrectNumber(CString &s)
{
	TCHAR ch;
	long i;
	s.MakeLower();
	bool hex=false;
	bool b=true;
	if(s.Find(_T("0x"))==0)
	{
		hex=true;
		s.Delete(0,2);
	}
	if(!s.IsEmpty())
		if(s.GetAt(s.GetLength()-1)==_T('h'))
		{
			hex=true;
			s.Delete(s.GetLength()-1,1);
		}
	if(hex)
		for(i=0;i<s.GetLength();i++)
		{
			ch=s.GetAt(i);
			if(!isHexSymbol(ch))
			{
				b=false;
				s.Delete(i,1);
				i--;
			}
		}
	else
		for(i=0;i<s.GetLength();i++)
		{
			ch=s.GetAt(i);
			if(!isDecSymbol(ch))
			{
				b=false;
				s.Delete(i,1);
				i--;
			}
		}
	if(hex)s=_T("0x")+s;
	return b;
}


/// typing text
bool CopyTextToClipboard (CString text, HWND hwnd)
{
	/*
    if (!OpenClipboard(hwnd) )
		return false;
	EmptyClipboard();
	
	//if (!EmptyClipboard() )
    //    return false;
    
	size_t strLen =  strlen(lpszText);
    HGLOBAL hnd = GlobalAlloc(GMEM_FIXED, strLen+1); 
	if (hnd == NULL) 
    { 
        CloseClipboard(); 
        return false; 
    }
	LPTSTR lptstrCopy = (LPTSTR)GlobalLock(hnd); 
    strcpy(lptstrCopy, lpszText);
    GlobalUnlock(hnd); 
    SetClipboardData(CF_TEXT, lptstrCopy);
    
    long wlen = MultiByteToWideChar(CP_ACP, 0, lptstrCopy, -1, 0, 0);
    
    HGLOBAL hnd2 = GlobalAlloc(GMEM_FIXED, wlen*2); 
    LPWSTR wbuf = (LPWSTR)GlobalLock(hnd2); 
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, lptstrCopy, -1, wbuf, wlen);
    SetClipboardData(CF_UNICODETEXT, wbuf);
    GlobalUnlock(hnd2);
    
    HGLOBAL hnd3 = GlobalAlloc(GMEM_FIXED, strLen+1); 
    LPSTR lptstrCopy3 = (LPSTR)GlobalLock(hnd3); 
    CharToOem(lptstrCopy, lptstrCopy3);
    SetClipboardData(CF_OEMTEXT, lptstrCopy3);
    GlobalUnlock(hnd3);
    
    CloseClipboard(); 
	*/
    return true;

}

bool TypeText(CString &s,HWND hwnd)
{
	if(!CopyTextToClipboard(s,hwnd))
		return false;

	keybd_event(VK_CONTROL, 0, 0, 0);
	keybd_event('V', 0, 0, 0);
	keybd_event('V', 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
	
	Sleep(500);
	OpenClipboard(0);
	EmptyClipboard();
	CloseClipboard();
	return true;
}

/*

// полный исходник ... а может где ошибка ??

if ( OpenClipboard( 0 ) )
{ 

HBITMAP hbp; 
HANDLE hGlb;

UINT PriList[18] = {CF_TEXT, CF_DIB, CF_DIF, CF_DSPBITMAP, CF_DSPENHMETAFILE ,
CF_DSPMETAFILEPICT,
CF_DSPTEXT , CF_ENHMETAFILE , CF_METAFILEPICT , CF_OEMTEXT , 
CF_OWNERDISPLAY , CF_PALETTE , CF_RIFF , CF_TEXT , CF_WAVE ,
CF_TIFF , CF_UNICODETEXT };


DWORD sz; 

hGlbnew = NULL;
format = NULL;

// пытаемся понять что лежит в буфере, и сохраним это
format = GetPriorityClipboardFormat(PriList, 17 );
if ( format > 0 ) 
{
void *p, *pnew;
char str[100];

hGlb = GetClipboardData( format);
sz = GlobalSize(hGlb); 

sprintf(str, "clipp data len %X %d", sz, format);
MessageBox(0, str, "22",0);

hGlbnew = GlobalAlloc( GMEM_MOVEABLE | GMEM_DDESHARE, sz+1 );

p = GlobalLock(hGlb);
pnew = GlobalLock(hGlbnew);

if ( pnew && p)
{
memcpy(pnew, p, sz);
GlobalUnlock(hGlb);
GlobalUnlock(hGlbnew);
}
else
{
if ( hGlbnew ) GlobalFree( hGlbnew);
format=0;
}


}
// прога начинает юзать буфер

hbp = (HBITMAP)LoadImage(g_hModule, MAKEINTRESOURCE(IDB_BITMAP2),IMAGE_BITMAP, 0, 0, LR_LOADMAP3DCOLORS ); 
EmptyClipboard();
SetClipboardData(CF_BITMAP, hbp );
Sleep(1000);
EmptyClipboard();

hbp = (HBITMAP)LoadImage(g_hModule, MAKEINTRESOURCE(IDB_BITMAP1),IMAGE_BITMAP, 0, 0, LR_LOADMAP3DCOLORS );

SetClipboardData(CF_BITMAP, hbp); 

hr = CallMethod(vtButtonOpen.pdispVal, L"PasteFace", &vtParam, 0, NULL);
VariantClear(&vtParam);

if ( hGlbnew && format > 0)// востанавливаем старое содержимое буфера
{
MessageBox(0, "Set data ...", "2233",0);
if ( !SetClipboardData(format, hGlbnew ) )
MessageBox(0, "Err", "2233",0);
}
CloseClipboard();



*/







/*
const unsigned char rus[]={
	'Й','й','Q',
	'Ц','ц','W',
	'У','у','E',
	'К','к','R',
	'Е','е','T',
	'Н','н','Y',
	'Г','г','U',
	'Ш','ш','I',
	'Щ','щ','O',
	'З','з','P',
	'Х','х','[',
	'Ъ','ъ',']',
	'Ф','ф','A',
	'Ы','ы','S',
	'В','в','D',
	'А','а','F',
	'П','п','G',
	'Р','р','H',
	'О','о','J',
	'Л','л','K',
	'Д','д','L',
	'Ж','ж',';',
	'Э','э','\'',
	'Я','я','Z',
	'Ч','ч','X',
	'С','с','C',
	'М','м','V',
	'И','и','B',
	'Т','т','N',
	'Ь','ь','M',
	'Б','б',',',
	'Ю','ю','.',
	'Ё','ё','`'
};
void TypeText(CString &s)
{
	//OpenClipboard(hwnd);
	//HANDLE hMem;
	//GetClipboardData(
	SetClipboardData(CF_TEXT,"text");
	
	bool keyboardCapital=(GetKeyState(VK_CAPITAL)==1);
	bool symbolCapital=false;
	bool shift=false;
	bool rusLayer=false;
	unsigned char ch=0,key=0;
	for(long i=0;i<s.GetLength();i++)
	{
		ch=s.GetAt(i);
		if((ch>='a')&&(ch<='z'))
		{
			symbolCapital=false;
			rusLayer=false;
			key=ch-'a'+'A';
			goto go;
		}
		if((ch>='A')&&(ch<='Z'))
		{
			symbolCapital=true;
			rusLayer=false;
			key=ch;
			goto go;
		}
		for(i=0;i<sizeof(rus);i+=3)
		{
			if(ch==rus[i])
			{
				rusLayer=true;
				symbolCapital=true;
				key=rus[i+2];
				break;
			}
			if(ch==rus[i+1])
			{
				rusLayer=true;
				symbolCapital=false;
				key=rus[i+2];
				break;
			}
		}
go:
		if(rusLayer)
			LoadKeyboardLayout("00000419", KLF_ACTIVATE);
		else
			LoadKeyboardLayout("00000409", KLF_ACTIVATE);
		shift=(symbolCapital&&(!keyboardCapital))||((!symbolCapital)&&keyboardCapital);
		if(shift)keybd_event(VK_SHIFT, 0, 0, 0);
		keybd_event(key, 0, 0, 0);
		keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
		if(shift)keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
	}
}
*/
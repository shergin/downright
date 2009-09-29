#pragma once

#define StringCopy(_source,_target) _tcscpy_s(_target,1024*1024,_source)

//void CStringToLPSTR(CString &s, LPSTR lpStr);

CString ToSafe(CString s);
CString FromSafe(CString s);
unsigned long StringToLong(CString s);
bool CorrectNumber(CString &s);

bool TypeText(CString &s, HWND hwnd);

CString UnsignedLongToString(unsigned long number);
#include "StdAfx.h"
#include "language.h"
#include "Resource.h"
#include "StringTool.h"
#define add(a,b) element.key=a; element.str=b; m_Array.SetAtGrow(m_nArray,element); m_nArray++;
CLanguage::CLanguage(void)
{
	CLanguageElement element;
	m_nArray=0;
	m_Array.SetSize(100,100);
	// главные вкладки
	AddStr(_T("Settings-Title"),_T("Downright blackrain"));
	AddStr(_T("Settings-MainTab-Logo"),_T("Logo"));
	AddStr(_T("Settings-MainTab-Gestures"),_T("Gestures"));
	AddStr(_T("Settings-MainTab-Settings"),_T("Settings"));
	AddStr(_T("Settings-MainTab-Help"),_T("Help"));
	// корневые элементы дерева
	AddStr(_T("Settings-Tree-Gestures"),_T("Gestures"));
	
	AddStr(_T("Settings-GestureTab-Description"),_T("Description"));
	AddStr(_T("Settings-GestureTab-Commands"),_T("Commands"));
	AddStr(_T("Settings-GestureTab-Symbols"),_T("Symbols"));
	AddStr(_T("Settings-GestureTab-Compatibility"),_T("Compatibility"));


	AddStr(_T("Settings-CommandTab-Simply"),_T("Simply"));
	AddStr(_T("Settings-CommandTab-Start"),_T("Start"));
	AddStr(_T("Settings-CommandTab-Text"),_T("Text"));
	AddStr(_T("Settings-CommandTab-Keyboard"),_T("Keyboard"));
	AddStr(_T("Settings-CommandTab-Message"),_T("Message"));
	AddStr(_T("Settings-CommandTab-NoSelect"),_T("No command selected"));

	AddStr(_T("Settings-SettingsTab-General"),_T("General"));
	AddStr(_T("Settings-SettingsTab-IngnoreProgram"),_T("Ignore Program"));
	AddStr(_T("Settings-SettingsTab-Registration"),_T("Registration"));





	AddStr(_T("Settings-Message-DeleteGroupQuestion"),_T("Delete this gesture group?"));
	AddStr(_T("Settings-Message-GestureLimitOut"),_T("Вы исчерпали лимит активных жестов демонстрационной версии программы.\nИнформацию о процедуре преобретения полной версии можно получить на официальном сайте: http://downright.shergin.com"));

	AddStr(_T("Settings-Registration-UserName"),_T("Name:"));
	AddStr(_T("Settings-Registration-HardwareID"),_T("Hardware ID:"));
	AddStr(_T("Settings-Registration-SerialNumber"),_T("Serial number:"));



	AddStr(_T("Settings-Message-SerialStatus-Valid"),_T("Serial key is valid."));
	AddStr(_T("Settings-Message-SerialStatus-Invalid"),_T("Serial key is invalid."));


	AddStr(_T("Settings-Other-NewGesture"),_T("My new gesture"));
	AddStr(_T("Settings-Other-NewGroup"),_T("My new group"));



	// список типов совместимости
	AddStr(_T("Settings-CompatibilityType-All"),_T("Full compatibility"));
	AddStr(_T("Settings-CompatibilityType-Except"),_T("Except"));
	AddStr(_T("Settings-CompatibilityType-Only"),_T("Only"));

	AddStr(_T("Settings-Gesture-Description-Disable"),_T("Disable gesture"));

	AddStr(_T("Settings-Gesture-Command-Standart-Title"),_T("Execute: "));
	AddStr(_T("Settings-Gesture-Command-Standart-Close"),_T("Close"));
	AddStr(_T("Settings-Gesture-Command-Standart-Maximize"),_T("Maximize"));
	AddStr(_T("Settings-Gesture-Command-Standart-Minimize"),_T("Minimize"));
	AddStr(_T("Settings-Gesture-Command-Standart-MinimizeAll"),_T("Minimize all"));
	AddStr(_T("Settings-Gesture-Command-Standart-Copy"),_T("Copy"));
	AddStr(_T("Settings-Gesture-Command-Standart-Paste"),_T("Paste"));
	AddStr(_T("Settings-Gesture-Command-Standart-Cut"),_T("Cut"));
	AddStr(_T("Settings-Gesture-Command-Standart-Open"),_T("Open"));
	AddStr(_T("Settings-Gesture-Command-Standart-Save"),_T("Save"));
	AddStr(_T("Settings-Gesture-Command-Standart-Print"),_T("Print"));
	AddStr(_T("Settings-Gesture-Command-Standart-Next"),_T("Next"));
	AddStr(_T("Settings-Gesture-Command-Standart-Back"),_T("Back"));
	AddStr(_T("Settings-Gesture-Command-Standart-NextWindow"),_T("Next window"));
	AddStr(_T("Settings-Gesture-Command-Standart-PrevWindow"),_T("Previous window"));
	AddStr(_T("Settings-Gesture-Command-Standart-Undo"),_T("Undo"));
	AddStr(_T("Settings-Gesture-Command-Standart-Redo"),_T("Redo"));
	AddStr(_T("Settings-Gesture-Command-Standart-SelectAll"),_T("Select all"));
	AddStr(_T("Settings-Gesture-Command-Standart-CloseDocument"),_T("Close document"));
	AddStr(_T("Settings-Gesture-Command-Standart-Shutdown"),_T("Shutdown"));

	AddStr(_T("Settings-Gesture-Command-Text-Title"),_T("Insert text: «%s»"));
	
	AddStr(_T("Settings-Gesture-Command-Start-Title"),_T("Start «%s»"));
	AddStr(_T("Settings-Gesture-Command-Start-Title-Path"),_T(", by path «%s»"));
	AddStr(_T("Settings-Gesture-Command-Start-Title-Parameters"),_T(", with parameters «%s»"));
	
	AddStr(_T("Settings-Gesture-Command-Keyboard-Title"),_T("Keyboard: «%s»"));
	AddStr(_T("Settings-Gesture-Command-Keyboard-Empty"),_T("<empty>"));

	AddStr(_T("Settings-Gesture-Command-Message-Title"),_T("Message: number: %s, lParam: %s, wParam: %s"));


	AddStr(_T("Settings-Gesture-Command-Execute-Name"),_T("Name:"));
	AddStr(_T("Settings-Gesture-Command-Execute-Browse"),_T("Browse"));
	AddStr(_T("Settings-Gesture-Command-Execute-Path"),_T("Path:"));
	AddStr(_T("Settings-Gesture-Command-Execute-Param"),_T("Parameters:"));

	AddStr(_T("Settings-Gesture-Command-Message-Number"),_T("Number:"));
	AddStr(_T("Settings-Gesture-Command-Message-LParam"),_T("lParam:"));
	AddStr(_T("Settings-Gesture-Command-Message-WParam"),_T("wParam:"));


	// menu
	AddStr(_T("Settings-Menu-Keyboard-Insert-Before"),_T("Insert before"));
	AddStr(_T("Settings-Menu-Keyboard-Insert-Inside"),_T("Insert inside"));
	AddStr(_T("Settings-Menu-Keyboard-Insert-After"),_T("Insert after"));
	AddStr(_T("Settings-Menu-Keyboard-Delete"),_T("Delete"));


	AddStr(_T("Settings-Menu-Gesture-Insert"),_T("Insert gesture\tIns"));
	AddStr(_T("Settings-Menu-Gesture-InsertGroup"),_T("Insert group\tCtrl-Ins"));
	AddStr(_T("Settings-Menu-Gesture-Delete"),_T("Delete\tDel"));
	AddStr(_T("Settings-Menu-Command-Insert"),_T("Insert command\tIns"));
	AddStr(_T("Settings-Menu-Command-Delete"),_T("Delete command\tDel"));
	AddStr(_T("Settings-Menu-Command-Up"),_T("Up\tCtrl-Up"));
	AddStr(_T("Settings-Menu-Command-Down"),_T("Down\tCtrl-Down"));
	AddStr(_T("Settings-Menu-Compatibility-Add"),_T("Add\tIns"));
	AddStr(_T("Settings-Menu-Compatibility-Delete"),_T("Delete\tDel"));
	AddStr(_T("Settings-Menu-SysTray-Open"),_T("Open"));
	AddStr(_T("Settings-Menu-SysTray-Enable"),_T("Enable"));
	AddStr(_T("Settings-Menu-SysTray-Exit"),_T("Shutdown"));
	AddStr(_T("Settings-Menu-IgnoreProgram-Add"),_T("Add\tIns"));
	AddStr(_T("Settings-Menu-IgnoreProgram-Delete"),_T("Delete\tDel"));
	
	// settings
	AddStr(_T("Settings-Stiings-DisableKey-None"),_T("None"));
	AddStr(_T("Settings-Stiings-DisableKey-Ctrl"),_T("Ctrl"));
	AddStr(_T("Settings-Stiings-DisableKey-Shift"),_T("Shift"));


	AddStr(_T("Settings-Stiings-MouseButton-Left"),_T("Left"));
	AddStr(_T("Settings-Stiings-MouseButton-Right"),_T("Right"));
	AddStr(_T("Settings-Stiings-MouseButton-Middle"),_T("Middle"));
	
	AddStr(_T("Settings-Stiings-SystemActive"),_T("System active"));
	AddStr(_T("Settings-Stiings-ShowBalloons"),_T("Show balloons"));
	AddStr(_T("Settings-Stiings-ShowSplash"),_T("Show splash"));
	AddStr(_T("Settings-Stiings-StartUp"),_T("Start program with windows"));
	AddStr(_T("Settings-Stiings-DisableKey"),_T("Disable system key:"));
	AddStr(_T("Settings-Stiings-MouseButton"),_T("Drawing mouse button:"));

	AddStr(_T("Settings-Stiings-FileName"),_T("Gesture's database file name:"));
	AddStr(_T("Settings-Stiings-Browse"),_T("Browse..."));

	// tray
	AddStr(_T("SystemTray-Error-Title"),_T("Downright blackrain. Error."));
	AddStr(_T("SystemTray-Error-Hook"),_T("Error in the hook intialization."));

	AddStr(_T("SystemTray-Identify-Title"),_T("Downright blackrain. Identify. Executing."));


	// ToolTips
	AddStr(_T("Settings-ToolTip-Tree"),_T("Для добавления и удаления элементов дерева используйте контекстное меню, вызываемое щелчком правой кнопки мыши."));
	AddStr(_T("Settings-ToolTip-Commands"),_T("Список команд. Для добавления, удаления и изменения порядка используйте контекстное меню, вызываемое щелчком правой кнопки мыши."));
	AddStr(_T("Settings-ToolTip-StandartCommands"),_T("Список простых команд, выберете одну."));
	AddStr(_T("Settings-ToolTip-Name"),_T("Имя программы или документа. Может содержать полный или относительный путь."));
	AddStr(_T("Settings-ToolTip-Browse"),_T("Обзор файлов для выбора."));
	AddStr(_T("Settings-ToolTip-Path"),_T("Папка, содержащая объект или связанные с ним файлы."));
	AddStr(_T("Settings-ToolTip-Param"),_T("Дополнительные параметры программы, например имя документа."));
	AddStr(_T("Settings-ToolTip-Text"),_T("Произвольный текст, который будет автоматически печататься при активизации жеста."));
	AddStr(_T("Settings-ToolTip-Key"),_T("Сочетание клавиш. Для добавления или удаления используйте контекстное меню, вызываемое щелчком правой кнопки мыши."));
	AddStr(_T("Settings-ToolTip-Number"),_T("Номер системного сообщения Windows. Может быть записано в виде: 0x0301 (шестнадцатеричное), 0301h (шестнадцатеричное) или 769 (десятичное)."));
	AddStr(_T("Settings-ToolTip-wParam"),_T("Первый параметр сообщения."));
	AddStr(_T("Settings-ToolTip-lParam"),_T("Второй параметр сообщения."));
	AddStr(_T("Settings-ToolTip-CompatibilityType"),_T("Тип совместимости жеста."));
	AddStr(_T("Settings-ToolTip-CompatibilityEdit"),_T("Фрагмент заголовка окна приложения."));
	AddStr(_T("Settings-ToolTip-CompatibilityList"),_T("Список фрагментов заголовков приложений. Для добавления и удаления используйте контекстное меню, вызываемое щелчком правой кнопки мыши."));
	AddStr(_T("Settings-ToolTip-GestureName"),_T("Имя жеста, короткое и ясное."));
	AddStr(_T("Settings-ToolTip-GestureDescription"),_T("Описание жеста, полное и развернутое, если необходимо."));

}

CLanguage::~CLanguage(void)
{
	m_Array.RemoveAll();
}

void CLanguage::AddStr(CString left, CString right, bool safe)
{
	if(left.IsEmpty())return;
	if(safe)
	{
		right.Replace(_T("\\t"),_T("\t"));
		right.Replace(_T("\\n"),_T("\n"));
		right.Replace(_T("\\r"),_T("\r"));
	}
	if(safe)
	{
		for(int i=0;i<m_nArray;i++)
			if(m_Array[i].key==left)
			{
				m_Array[i].str=right;
				return;
			}
	}
	CLanguageElement element;
	element.key=left;
	element.str=right;
	m_Array.SetAtGrow(m_nArray,element);
	m_nArray++;
}


bool CLanguage::Load(CString filename)
{
	CFile file;
	CString image,str,left,right;
	int i=0;
	if(!file.Open(filename,CFile::modeRead))return false;
	int length=(int)file.GetLength();
	file.Read(image.GetBuffer(length),length);
	image.ReleaseBufferSetLength(length);
	file.Close();
	TCHAR ch=0;
	for(i=0;i<length;i++)
	{
		ch=image.GetAt(i);
		if((ch==13)||(ch==10)||(i+1==length))
		{
			if(i+1==length)str+=ch;
			if(!str.IsEmpty())
			{
				int eq=str.Find(_T("="));
				if(eq!=-1)
				{
					left=str.Left(eq);
					right=str.Right(str.GetLength()-eq-1);
					AddStr(left,right,true);
				}
				str.Empty();
			}
		}
		else
			str+=ch;
	}

	return false;
}

CString CLanguage::Get(CString key)
{
	CString s;
	for(int i=0;i<m_nArray;i++)
		if(key==m_Array[i].key)
			return m_Array[i].str;
	return _T("[Language.cpp]: Internal error.");
}

#define _localMenuItem(id,name) mii.wID=id;StringCopy(Get(name),buffer);SetMenuItemInfo(hMenu, id, FALSE, &mii);
void CLanguage::LocalizationMenu(HMENU hMenu, int menuId)
{

	TCHAR buffer[1024];
	MENUITEMINFO mii=
		{
			sizeof(MENUITEMINFO),
			MIIM_TYPE | MIIM_ID | MIIM_STATE,
			MFT_STRING,
			MFS_UNCHECKED,
			777,// потом надо изменить!
			0,0,0,0,
			buffer,
			sizeof(buffer)/sizeof(buffer[0])
		};
	switch(menuId)
	{
		case IDR_GESTUREMENU:
			_localMenuItem(IDM_ADDGESTURE,_T("Settings-Menu-Gesture-Insert"));
			_localMenuItem(IDM_ADDGROUP,_T("Settings-Menu-Gesture-InsertGroup"));
			_localMenuItem(IDM_DELGESTURE,_T("Settings-Menu-Gesture-Delete"));
		break;
		case IDR_COMMANDMENU:
			_localMenuItem(IDM_ADDCOMMAND,_T("Settings-Menu-Command-Insert"));
			_localMenuItem(IDM_DELCOMMAND,_T("Settings-Menu-Command-Delete"));
			_localMenuItem(IDM_COMMANDUP,_T("Settings-Menu-Command-Up"));
			_localMenuItem(IDM_COMMANDDOWN,_T("Settings-Menu-Command-Down"));
		break;
		case IDR_COMPATIBILITYMENU:
			_localMenuItem(IDM_ADDCOMPATIBILITY,_T("Settings-Menu-Compatibility-Add"));
			_localMenuItem(IDM_DELCOMPATIBILITY,_T("Settings-Menu-Compatibility-Delete"));
		break;
		case IDR_IGNOREPROGRAMMENU:
			_localMenuItem(IDM_ADDIGNOREPROGRAM,_T("Settings-Menu-IgnoreProgram-Add"));
			_localMenuItem(IDM_DELIGNOREPROGRAM,_T("Settings-Menu-IgnoreProgram-Delete"));
		break;
		case IDR_SYSTRAYMENU:
			_localMenuItem(IDM_SYSTRAY_SHOW,_T("Settings-Menu-SysTray-Open"));
			_localMenuItem(IDM_SYSTRAY_ENABLE,_T("Settings-Menu-SysTray-Enable"));
			_localMenuItem(IDM_SYSTRAY_EXIT,_T("Settings-Menu-SysTray-Exit"));
		break;
		case IDR_KEYMENU:
			_localMenuItem(IDM_INSERTKEYBEFORE,_T("Settings-Menu-Keyboard-Insert-Before"));
			_localMenuItem(IDM_INSERTKEYINSIDE,_T("Settings-Menu-Keyboard-Insert-Inside"));
			_localMenuItem(IDM_INSERTKEYAFTER,_T("Settings-Menu-Keyboard-Insert-After"));
			_localMenuItem(IDM_KEYDELETE,_T("Settings-Menu-Keyboard-Delete"));
		break;
	}
}

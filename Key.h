class CKey;

class CKey
	{
public:
	int code;
	CString name;
	HTREEITEM hItem;
	};

CKey KeyTree[]=
	{
	// Number
	-1,				_T("Number"),	NULL,
	'0',			_T("0"),	NULL,
	'1',			_T("1"),	NULL,
	'2',			_T("2"),	NULL,
	'3',			_T("3"),	NULL,
	'4',			_T("4"),	NULL,
	'5',			_T("5"),	NULL,
	'6',			_T("6"),	NULL,
	'7',			_T("7"),	NULL,
	'8',			_T("8"),	NULL,
	'9',			_T("9"),	NULL,
	// Letter
	-1,				_T("Letter"),	NULL,
	VK_SPACE,		_T("Space"),	NULL,
	'A',			_T("A"),	NULL,
	'B',			_T("B"),	NULL,
	'C',			_T("C"),	NULL,
	'D',			_T("D"),	NULL,
	'E',			_T("E"),	NULL,
	'F',			_T("F"),	NULL,
	'G',			_T("G"),	NULL,
	'H',			_T("H"),	NULL,
	'I',			_T("I"),	NULL,
	'J',			_T("J"),	NULL,
	'K',			_T("K"),	NULL,
	'L',			_T("L"),	NULL,
	'M',			_T("M"),	NULL,
	'N',			_T("N"),	NULL,
	'O',			_T("O"),	NULL,
	'P',			_T("P"),	NULL,
	'Q',			_T("Q"),	NULL,
	'R',			_T("R"),	NULL,
	'S',			_T("S"),	NULL,
	'T',			_T("T"),	NULL,
	'U',			_T("U"),	NULL,
	'V',			_T("V"),	NULL,
	'W',			_T("W"),	NULL,
	'X',			_T("X"),	NULL,
	'Y',			_T("Y"),	NULL,
	'Z',			_T("Z"),	NULL,
	// Mode
	-1,				_T("Mode"),	NULL,
	VK_SHIFT,		_T("Shift"),	NULL,
	VK_CONTROL,		_T("Ctrl"),	NULL,
	VK_MENU,		_T("Alt"),	NULL,
	// Action
	-1,				_T("Action"),	NULL,
	VK_BACK,		_T("Backspace"),	NULL,
	VK_RETURN,		_T("Enter"),	NULL,
	VK_PAUSE,		_T("Pause"),	NULL,
	VK_ESCAPE,		_T("Esc"),	NULL,
	VK_TAB,			_T("Tab"),	NULL,
	VK_INSERT,		_T("Insert"),	NULL,
	VK_DELETE,		_T("Delete"),	NULL,
	// Arrow
	-1,				_T("Arrow"),	NULL,
	VK_LEFT,		_T("Left"),	NULL,
	VK_RIGHT,		_T("Rigth"),	NULL,
	VK_UP,			_T("Up"),	NULL,
	VK_DOWN,		_T("Down"),	NULL,
	VK_PRIOR,		_T("Page Up"),	NULL,
	VK_NEXT,		_T("Page Down"),	NULL,
	VK_END,			_T("End"),	NULL,
	VK_HOME,		_T("Home"),	NULL,
	// Oem
	-1,				_T("Oem"),	NULL,
	VK_OEM_PLUS,	_T("Oem Plus [+]"),	NULL,
	VK_OEM_COMMA,	_T("Oem Comma [,]"),	NULL,
	VK_OEM_MINUS,	_T("Oem Minus [-]"),	NULL,
	VK_OEM_PERIOD,	_T("Oem Period [.]"),	NULL,
	VK_OEM_AX,		_T("Oem AX"),	NULL,
	VK_OEM_1,		_T("Oem 1 [;:]"),	NULL,
	VK_OEM_2,		_T("Oem 2 [/?]"),	NULL,
	VK_OEM_3,		_T("Oem 3 [`~]"),	NULL,
	VK_OEM_4,		_T("Oem 4 [[{]"),	NULL,
	VK_OEM_5,		_T("Oem 5 [\\|]"),	NULL,
	VK_OEM_6,		_T("Oem 6 []}]"),	NULL,
	VK_OEM_7,		_T("Oem 7 ['\"]"),	NULL,
	VK_OEM_8,		_T("Oem 8"),	NULL,
	VK_OEM_102,		_T("Oem 102 [<>] or [\\|]"),	NULL,
	// System
	-1,				_T("System"),	NULL,
	VK_SNAPSHOT,	_T("Print Screen"),	NULL,
	VK_NUMLOCK,		_T("Num Lock"),	NULL,
	VK_SCROLL,		_T("Scroll Lock"),	NULL,
	// Windows
	-1,				_T("Windows"),	NULL,
	VK_LWIN,		_T("Left Win"),	NULL,
	VK_RWIN,		_T("Right Win"),	NULL,
	VK_APPS,		_T("Applications"),	NULL,
	// Num Pad
	-1,				_T("Num Pad"),	NULL,
	VK_NUMPAD0,		_T("Num Pad 0"),	NULL,
	VK_NUMPAD1,		_T("Num Pad 1"),	NULL,
	VK_NUMPAD2,		_T("Num Pad 2"),	NULL,
	VK_NUMPAD3,		_T("Num Pad 3"),	NULL,
	VK_NUMPAD4,		_T("Num Pad 4"),	NULL,
	VK_NUMPAD5,		_T("Num Pad 5"),	NULL,
	VK_NUMPAD6,		_T("Num Pad 6"),	NULL,
	VK_NUMPAD7,		_T("Num Pad 7"),	NULL,
	VK_NUMPAD8,		_T("Num Pad 8"),	NULL,
	VK_NUMPAD9,		_T("Num Pad 9"),	NULL,
	VK_MULTIPLY,	_T("Multiply [*]"),	NULL,
	VK_ADD,			_T("Add [+]"),	NULL,
	VK_SUBTRACT,	_T("Subtract [-]"),	NULL,
	VK_DIVIDE,		_T("Divide [/]"),	NULL,
	VK_SEPARATOR,	_T("Separator"),	NULL,
	VK_DECIMAL,		_T("Decimal"),	NULL,
	// F-key
	-1,				_T("F-key"),	NULL,
	VK_F1,			_T("F1"),	NULL,
	VK_F2,			_T("F2"),	NULL,
	VK_F3,			_T("F3"),	NULL,
	VK_F4,			_T("F4"),	NULL,
	VK_F5,			_T("F5"),	NULL,
	VK_F6,			_T("F6"),	NULL,
	VK_F7,			_T("F7"),	NULL,
	VK_F8,			_T("F8"),	NULL,
	VK_F9,			_T("F9"),	NULL,
	VK_F10,			_T("F10"),	NULL,
	VK_F11,			_T("F11"),	NULL,
	VK_F12,			_T("F12"),	NULL,
	VK_F13,			_T("F13"),	NULL,
	VK_F14,			_T("F14"),	NULL,
	VK_F15,			_T("F15"),	NULL,
	VK_F16,			_T("F16"),	NULL,
	VK_F17,			_T("F17"),	NULL,
	VK_F18,			_T("F18"),	NULL,
	VK_F19,			_T("F19"),	NULL,
	VK_F20,			_T("F20"),	NULL,
	VK_F21,			_T("F21"),	NULL,
	VK_F22,			_T("F22"),	NULL,
	VK_F23,			_T("F23"),	NULL,
	VK_F24,			_T("F24"),	NULL,
	// Browser
	-1,						_T("Browser"),	NULL,
	VK_BROWSER_BACK,		_T("Browser Back"),	NULL,
	VK_BROWSER_FORWARD,		_T("Browser Forward"),	NULL,
	VK_BROWSER_REFRESH,		_T("Browser Refresh"),	NULL,
	VK_BROWSER_STOP,		_T("Browser Stop"),	NULL,
	VK_BROWSER_SEARCH,		_T("Browser Search"),	NULL,
	VK_BROWSER_FAVORITES,	_T("Browser Favorites"),	NULL,
	VK_BROWSER_HOME,		_T("Browser Home"),	NULL,
	// Media
	-1,						_T("Media"),	NULL,
	VK_VOLUME_MUTE,			_T("Volume Mute"),	NULL,
	VK_VOLUME_DOWN,			_T("Volume Down"),	NULL,
	VK_VOLUME_UP,			_T("Volume Up"),	NULL,
	VK_MEDIA_NEXT_TRACK,	_T("Media Next Track"),	NULL,
	VK_MEDIA_PREV_TRACK,	_T("Media Prev Track"),	NULL,
	VK_MEDIA_STOP,			_T("Media Stop"),	NULL,
	VK_MEDIA_PLAY_PAUSE,	_T("Media Play Track"),	NULL,
	VK_LAUNCH_MAIL,			_T("Launch Mail"),	NULL,
	VK_LAUNCH_MEDIA_SELECT,	_T("Launch Media Select"),	NULL,
	VK_LAUNCH_APP1,			_T("Launch App One"),	NULL,
	VK_LAUNCH_APP2,			_T("Launch App Two"),	NULL,
	// Mouse
	-1,				_T("Mouse"),	NULL,
	VK_LBUTTON,		_T("Left Mouse Button"),	NULL,
	VK_RBUTTON,		_T("Right Mouse Button"),	NULL,
	VK_MBUTTON,		_T("Middle Mouse Button"),	NULL,
	VK_XBUTTON1,	_T("X One Mouse Button"),	NULL,
	VK_XBUTTON2,	_T("X Two Mouse Button"),	NULL,
	// Other
	-1,				_T("Other"),	NULL,
	VK_CANCEL,		_T("Cancel"),	NULL,
	VK_CLEAR,		_T("Clear"),	NULL,
	VK_KANA,		_T("Kana"),	NULL,
	VK_HANGUL,		_T("Hangul"),	NULL,
	VK_JUNJA,		_T("Junja"),	NULL,
	VK_FINAL,		_T("Final"),	NULL,
	VK_HANJA,		_T("Nanja"),	NULL,
	VK_KANJI,		_T("Kanji"),	NULL,
	VK_CONVERT,		_T("Convert"),	NULL,
	VK_NONCONVERT,	_T("Non Convert"),	NULL,
	VK_ACCEPT,		_T("Accept"),	NULL,
	VK_MODECHANGE,	_T("Mode Change"),	NULL,
	VK_SELECT,		_T("Select"),	NULL,
	VK_PRINT,		_T("Print"),	NULL,
	VK_EXECUTE,		_T("Execute"),	NULL,
	VK_HELP,		_T("Help"),	NULL,
	VK_SLEEP,		_T("Sleep"),	NULL,
	VK_OEM_NEC_EQUAL,		_T("Oem Nec Equal [=]"),	NULL,
	VK_OEM_FJ_JISHO,		_T("Oem Fj Jisho"),	NULL,
	VK_OEM_FJ_MASSHOU,		_T("Oem Fj Masshou"),	NULL,
	VK_OEM_FJ_TOUROKU,		_T("Oem Fj Touroku"),	NULL,
	VK_OEM_FJ_LOYA,			_T("Oem Fj Loya"),	NULL,
	VK_OEM_FJ_ROYA,			_T("Oem Fj Roya"),	NULL,
	VK_ICO_HELP,	_T("Ico Help"),	NULL,
	VK_ICO_00,		_T("Ico 00"),	NULL,
	VK_PROCESSKEY,	_T("Precess Key"),	NULL,
	VK_ICO_CLEAR,	_T("Ico Clear"),	NULL,
	VK_PACKET,		_T("Packet"),	NULL,
	VK_OEM_RESET,	_T("Oem Reset"),	NULL,
	VK_OEM_JUMP,	_T("Oem Jump"),	NULL,
	VK_OEM_PA1,		_T("Oem Pa 1"),	NULL,
	VK_OEM_PA2,		_T("Oem Pa 2"),	NULL,
	VK_OEM_PA3,		_T("Oem Pa 3"),	NULL,
	VK_OEM_WSCTRL,	_T("Oem Ws Ctrl"),	NULL,
	VK_OEM_CUSEL,	_T("Oem Cusel"),	NULL,
	VK_OEM_ATTN,	_T("Oem Attn"),	NULL,
	VK_OEM_FINISH,	_T("Oem Finish"),	NULL,
	VK_OEM_COPY,	_T("Oem Copy"),	NULL,
	VK_OEM_AUTO,	_T("Oem Auto"),	NULL,
	VK_OEM_ENLW,	_T("Oem Enlw"),	NULL,
	VK_OEM_BACKTAB,	_T("Oem Back Tab"),	NULL,
	VK_ATTN,		_T("Attn"),	NULL,
	VK_CRSEL,		_T("CrSel"),	NULL,
	VK_EXSEL,		_T("ExSel"),	NULL,
	VK_EREOF,		_T("EreOf"),	NULL,
	VK_PLAY,		_T("Play"),	NULL,
	VK_ZOOM,		_T("Zoom"),	NULL,
	VK_NONAME,		_T("No Name"),	NULL,
	VK_PA1,			_T("Pa 1"),	NULL,
	VK_OEM_CLEAR,	_T("Oem Clear"),	NULL
};
#define KeyTreeNumber (sizeof(KeyTree)/sizeof(KeyTree[0]))
 
CString GetNameByCode(UINT_PTR code)
	{
/*	if((code>='0')&&(code<='9'))
		return "Cifra";
	if((code>='A')&&(code<='Z'))
		return "Bukva";
*/
	UINT_PTR i=0;
	for(i=0;i<KeyTreeNumber;i++)
		if(KeyTree[i].code==code)break;
	if(i!=KeyTreeNumber)
		return KeyTree[i].name;
	return _T("?");
	}
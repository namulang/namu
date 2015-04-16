#pragma once

namespace LG
{
	enum COLOR
	{		
		BLACK=0, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE, UNKNOWN
	};
	enum SPECIAL_KEY
	{
		//	입력용 키:
		ENTER		= 13,
		SPACE		= 32,
		BACKSPACE	= 8,
		TAB			= 9,
		ESCAPE		= 27,
		UP			= 0xe048,
		DOWN		= 0xe050,
		LEFT		= 0xe04b,
		RIGHT		= 0xe04d,
		INSERT		= 0xe052,
		DEL			= 0xe053,
		CTRL_D		= 4,
		CTRL_V		= 22,
		CTRL_X		= 24,
		HOME		= 0xe047,		
		F1			= 0x3b,
		F2			= 0xe03c,
		F3			= 0xe03d,
		F4			= 0xe03e,
		F5			= 0xe03f,
		F6			= 0xe040,
		F7			= 0xe041,
		F8			= 0xe042,
		F9			= 0xe043,
		F10			= 0xe044,
		F11			= 0xe085,
		F12			= 0xe086,
		//	필수 키:		
		CONFIRM		= ENTER,	//	확인
		CANCEL		= BACKSPACE,	//	취소 / 메뉴키
		//	선택 키:
		//		단축키:
		CLOSE		= ESCAPE,
		MAP			= HOME,	
		ADD			= INSERT,
		REMOVE		= DEL,
		COPY		= CTRL_D,
		PASTE		= CTRL_V,
		CUT			= CTRL_X,
		RENAME		= F2,
		HELP		= '?',
		//		추가키:
		COMMAND		= '~'
	};
}
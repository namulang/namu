#pragma once

namespace LG
{
	enum COLOR
	{		
		BLACK=0, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE, UNKNOWN
	};
	enum SPECIAL_KEY
	{
		//	필수 키:
		UP			= 72,
		DOWN		= 80,
		LEFT		= 75,
		RIGHT		= 77,
		CONFIRM		= 13,
		CANCEL		= 8,	//	취소 / 메뉴키
		//	입력용 키:
		ENTER		= 13,
		SPACE		= 32,	
		BACKSPACE	= 8,	//	Backspace
		//	선택 키:
		//		단축키:
		CLOSE		= 27,	//	esc
		MAP			= 71,	//	home
		ADD			= 82,	//	ins
		REMOVE		= 83,	//	del			
		COPY		= 4,	//	CTRL + C
		PASTE		= 22,	//	CTRL + V
		CUT			= 24,	//	CTRL + X
		HELP		= '?',
		//		추가키:
		COMMAND		= '~'
	};
}
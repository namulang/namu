#pragma once 

class CInputConsoleKeyboardAndMouse
{
public:
	CInputConsoleKeyboardAndMouse()
	{}
	~CInputConsoleKeyboardAndMouse()
	{}
	
	WORD	getState(WORD lable)
	{
		return GetAsyncKeyState(lable);
	}
};
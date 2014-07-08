#pragma once

#include "CError.hpp"
#include "define.hpp"
#include "CInputConsoleKeyboardAndMouse.hpp"
#include "CInputConsoleXbox360Pad.hpp"
#include "CInputInterfaceSet.hpp"

class CInputInterface
{
public:
	CInputInterface();
	~CInputInterface();

	CInputInterfaceSet*	getInterfaceSet(int index=0);

	CInputInterface&	operator = (CInputInterface& rhs);
	void	update(CInputConsoleKeyboardAndMouse* keyboard_mouse, CInputConsoleXbox360Pad* xbox360pad);
	
	CInputInterfaceSet	inputLabel(CInputConsoleKeyboardAndMouse* keyboard_mouse, CInputConsoleXbox360Pad* xbox360pad)
	{
		CInputInterfaceSet	new_binding_key;		

		new_binding_key = checkKeyboardMouse(keyboard_mouse);
		if (new_binding_key.getLabel())
			return new_binding_key;

		return checkXbox360Pad(xbox360pad);
	}

protected:
	virtual void	updateKeyboardMouse(CInputConsoleKeyboardAndMouse* keyboard_mouse, int index) = 0;
	virtual	void	updateXbox360Pad(CInputConsoleXbox360Pad* xbox360pad, int index) = 0;
	virtual	CInputInterfaceSet	checkKeyboardMouse(CInputConsoleKeyboardAndMouse* keyboard_mouse) = 0;
	virtual	CInputInterfaceSet	checkXbox360Pad(CInputConsoleXbox360Pad* xbox360pad) = 0;

	bool	isStick(WORD lable)
	{
		//	메인코드:
		if (	lable >= VK_PAD_LTHUMB_UP		&&
				lable <= VK_PAD_RTHUMB_DOWNLEFT	) // 중간에 아무것도 아닌키가 섞여있음
			return true;
		else
			return false;
	}
	bool	isTrigger(WORD lable)
	{		
		//	메인코드:
		if (	lable >= VK_PAD_LTRIGGER	&&
				lable <= VK_PAD_RTRIGGER	) // 중간에 아무것도 아닌키가 섞여있음
			return true;
		else
			return false;
	}
	bool	isKeyboardMouse(WORD label)
	{
		if (	label >= VK_LBUTTON	&&
				label <= VK_OEM_CLEAR)
			return true;
		
		return false;
	}
	bool	isXbox360Pad(WORD label)
	{
		if (	label >= VK_PAD_A				&&
				label <= VK_PAD_RTHUMB_DOWNLEFT	)
			return true;

		return false;
	}

private:
	void	updateOneInterfaceSet(int index, CInputConsoleKeyboardAndMouse* keyboard_mouse, CInputConsoleXbox360Pad* xbox360pad);
	

public:
	bool	_enable;

protected:
	CInputInterfaceSet	_interface_set[DEFAULT_CINPUTINTERFACESET_MAX_KEYSET];
};
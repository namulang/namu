#pragma once

#include <Windows.h>
#include <XInput.h>
#include "define.hpp"
#include "CINI.hpp"
#include "CInputInterface.hpp"

class CInputPressButton : public CInputInterface
{
public:
	CInputPressButton() : _level(0)
	{

	}
	~CInputPressButton()
	{

	}
	CInputPressButton&	operator = (CInputPressButton& rhs)
	{
		_level = rhs.getPressLevel();

		CInputInterface::operator = (rhs);
		return *this;
	}
	BYTE	getPressLevel()
	{
		return _level;
	}
	void	initializeState()
	{
		_level = 0;
	}

protected:
	virtual void	updateKeyboardMouse(CInputConsoleKeyboardAndMouse* keyboard_mouse, int index)
	{
		// nothing
	}
	virtual	void	updateXbox360Pad(CInputConsoleXbox360Pad* xbox360pad, int index)
	{
		setPressLevel(xbox360pad, index);
	}
	virtual	CInputInterfaceSet	checkKeyboardMouse(CInputConsoleKeyboardAndMouse* keyboard_mouse) // 0은 인식 실패. WORD인 이유는, _label이 WORD이므로
	{
		return CInputInterfaceSet(); // 키보드, 마우스에는 감압버튼이 없다
	}
	virtual	CInputInterfaceSet	checkXbox360Pad(CInputConsoleXbox360Pad* xbox360pad) // 0은 인식 실패. WORD인 이유는, _label이 WORD이므로
	{
		for (int n=0; n < DEFAULT_CINPUTCONSOLEXBOX360PAD_MAX_CONTROLLERS ;n++)
		{
			if (xbox360pad->isJoypadPlayerConnected(n))
			{
				if (	xbox360pad->getStateGamepad(n)->bLeftTrigger	||
						xbox360pad->getStateGamepad(n)->bRightTrigger	)
					return	CInputInterfaceSet(VK_PAD_A, 0); // 조이패드에 해당하는 레이블이면 뭐든 좋음.
			}
		}

		return CInputInterfaceSet();
	}

private:
	void	setPressLevel(CInputConsoleXbox360Pad* xbox360pad, int index)
	{
		switch(_interface_set[index].getLabel())
		{
			case VK_PAD_LTRIGGER:
			{
				_level = xbox360pad->getStateGamepad(_interface_set[index].getJoypadPlayer())->bLeftTrigger;
				break;
			}
			case VK_PAD_RTRIGGER:
			{
				_level = xbox360pad->getStateGamepad(_interface_set[index].getJoypadPlayer())->bRightTrigger;
				break;
			}
			default:
			{
				CError e
				(	
					_T("경고XX:\tXBOX360패드에서 감압버튼(?)은 양 트리거만 가능한데, 뭔가 이상한게 들어왔군요?"), 
					_T(""),
					_T(__FUNCTION__)				
				);
				e.log();
				break;
			}
		}
	}


private:
	BYTE	_level;
};
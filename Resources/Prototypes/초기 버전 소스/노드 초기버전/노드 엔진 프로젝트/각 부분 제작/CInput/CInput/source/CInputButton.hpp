#pragma once


#include <Windows.h>
#include <XInput.h>
#include "CInputInterface.hpp"
#include "define.hpp"
#include "CINI.hpp"

class CInputButton : public CInputInterface
{
public:
	CInputButton();
	~CInputButton();

	CInputButton&	operator = (CInputButton& rhs);
	BYTE	getState();
	void	initializeState()
	{
		_before_state = NULL;
		_state = DEFAULT_CINPUTBUTTON_STATE_NOT_PRESSED;
	}
protected:
	virtual void	updateKeyboardMouse(CInputConsoleKeyboardAndMouse* keyboard_mouse, int index);
	virtual	void	updateXbox360Pad(CInputConsoleXbox360Pad* xbox360pad, int index);
	virtual	CInputInterfaceSet	checkKeyboardMouse(CInputConsoleKeyboardAndMouse* keyboard_mouse) // 0은 인식 실패. WORD인 이유는, _label이 WORD이므로
	{
		for(int n=1; n < 256 ;n++) // 1 ~ 255(FF)
		{
			if (GetAsyncKeyState(n))
				return CInputInterfaceSet(n, 0);
		}

		return CInputInterfaceSet();		
	}
	virtual	CInputInterfaceSet	checkXbox360Pad(CInputConsoleXbox360Pad* xbox360pad) // 0은 인식 실패. WORD인 이유는, _label이 WORD이므로
	{
		CInputInterfaceSet new_binding_key;

		new_binding_key = checkXbox360PadButton(xbox360pad);
		if (new_binding_key.getLabel())
			return new_binding_key;
		new_binding_key = checkXbox360PadAnalogstick(xbox360pad);
		if (new_binding_key.getLabel())
			return new_binding_key;		
		
		return checkXbox360PadTrigger(xbox360pad);
	}

private:
	CInputInterfaceSet	checkXbox360PadButton(CInputConsoleXbox360Pad* xbox360pad)
	{
		for (int n=VK_PAD_A; n <= VK_PAD_RTHUMB_DOWNLEFT ;n++)
		{

			for (int n2=0; n2 < DEFAULT_CINPUTCONSOLEXBOX360PAD_MAX_CONTROLLERS ;n2++)
			{
				if (xbox360pad->isJoypadPlayerConnected(n2))
					if (getButtonNowState(xbox360pad->getStateGamepad(n2)->wButtons, n))				
						return CInputInterfaceSet(n, n2);
			}
		}

		return CInputInterfaceSet();
	}
	CInputInterfaceSet	checkXbox360PadAnalogstick(CInputConsoleXbox360Pad* xbox360pad)
	{	
		WORD label = 0;
		for (int n=0; n < DEFAULT_CINPUTCONSOLEXBOX360PAD_MAX_CONTROLLERS ;n++)
		{
			if (xbox360pad->isJoypadPlayerConnected(n))
			{
				label = findXbox360PadAnalogstickBestTilt(xbox360pad->getStateGamepad(n));
				if (label)
					return CInputInterfaceSet(label, n);
			}			
		}
		
		return CInputInterfaceSet();
	}
	//	해당 조이패드에서 아날로그스틱중, 가장 많이 기울여져 있는 레이블을 찾는다.
	WORD	findXbox360PadAnalogstickBestTilt(XINPUT_GAMEPAD* gamepad)
	{
		int	best_tilt_level = 0;
		WORD	best_tilt_label = 0;
		
		//	LTHUMB
		//	LTHUMB_LEFT ( < 0 )
		if (gamepad->sThumbLX < 0)
		{			
			if (gamepad->sThumbLX < -best_tilt_level)
			{
				best_tilt_level = -gamepad->sThumbLX; // 양수로 저장
				best_tilt_label = VK_PAD_LTHUMB_LEFT;
			}
		}
		else
		//	LTHUMB_RIGHT ( > 0 )
		{
			if (gamepad->sThumbLX > best_tilt_level)
			{
				best_tilt_level = gamepad->sThumbLX;
				best_tilt_label = VK_PAD_LTHUMB_RIGHT;
			}
		}
		//	LTHUMB_DOWN ( < 0 )
		if (gamepad->sThumbLY < 0)
		{			
			if (gamepad->sThumbLY < -best_tilt_level)
			{
				best_tilt_level = -gamepad->sThumbLY; // 양수로 저장
				best_tilt_label = VK_PAD_LTHUMB_DOWN;
			}
		}
		else
		//	LTHUMB_UP ( < 0 )
		{
			if (gamepad->sThumbLY > best_tilt_level)
			{
				best_tilt_level = gamepad->sThumbLY;
				best_tilt_label = VK_PAD_LTHUMB_UP;
			}
		}
		//	RTHUMB
		//	RTHUMB_LEFT ( < 0 )
		if (gamepad->sThumbRX < 0)
		{			
			if (gamepad->sThumbRX < -best_tilt_level)
			{
				best_tilt_level = -gamepad->sThumbRX; // 양수로 저장
				best_tilt_label = VK_PAD_RTHUMB_LEFT;
			}
		}
		else
		//	RTHUMB_RIGHT ( > 0 )
		{
			if (gamepad->sThumbRX > best_tilt_level)
			{
				best_tilt_level = gamepad->sThumbRX;
				best_tilt_label = VK_PAD_RTHUMB_RIGHT;
			}
		}
		//	RTHUMB_DOWN ( < 0 )
		if (gamepad->sThumbRY < 0)
		{			
			if (gamepad->sThumbRY < -best_tilt_level)
			{
				best_tilt_level = -gamepad->sThumbRY; // 양수로 저장
				best_tilt_label = VK_PAD_RTHUMB_DOWN;
			}
		}
		else
		//	RTHUMB_UP ( < 0 )
		{
			if (gamepad->sThumbRY > best_tilt_level)
			{
				best_tilt_level = gamepad->sThumbRY;
				best_tilt_label = VK_PAD_RTHUMB_UP;
			}
		}

		return best_tilt_label;
	}
	CInputInterfaceSet	checkXbox360PadTrigger(CInputConsoleXbox360Pad* xbox360pad)
	{
		for (int n=0; n < DEFAULT_CINPUTCONSOLEXBOX360PAD_MAX_CONTROLLERS ;n++)
		{
			if (xbox360pad->isJoypadPlayerConnected(n))
			{
				XINPUT_GAMEPAD* gamepad = xbox360pad->getStateGamepad(n);
				if (gamepad->bLeftTrigger > 0)
					return CInputInterfaceSet(VK_PAD_LTRIGGER, n);
				else if (gamepad->bRightTrigger >0)
					return CInputInterfaceSet(VK_PAD_RTRIGGER, n);
			}
		}

		return CInputInterfaceSet();
	}
	void	getButtonState(WORD button_state, int index);
	WORD	getButtonNowState(WORD button_state, WORD lable);
	void	getStickState(XINPUT_GAMEPAD* stick, int index);
	WORD	getStickNowState(XINPUT_GAMEPAD* stick, WORD lable);
	void	getTriggerState(XINPUT_GAMEPAD* trigger, int index)
	{
		WORD now_state = getTriggerNowState(trigger, _interface_set[index].getLabel());

		if (	(!_before_state)	&& // up event: bef=0, now=0x8000
				(now_state)			)
			_state = DEFAULT_CINPUTBUTTON_STATE_BUTTON_UP;		
		else if (	(_before_state)	&& // press: bef = 0x8000, now 0x8000
					(now_state)		)
			_state = DEFAULT_CINPUTBUTTON_STATE_BUTTON_PRESS_ON;
		else if (	(_before_state)	&& // down: bef = 0x8000, now = 0x0000
					(!now_state)	)
			_state = DEFAULT_CINPUTBUTTON_STATE_BUTTON_DOWN;
		else if (	(!_before_state)	&& // not_pressed
					(!now_state)		)
			_state = DEFAULT_CINPUTBUTTON_STATE_NOT_PRESSED;

		_before_state = now_state;
	}
	WORD	getTriggerNowState(XINPUT_GAMEPAD* trigger, WORD lable)
	{
		if (lable == VK_PAD_LTRIGGER)
		{
			if (trigger->bLeftTrigger > g_ini.getTriggerToButtonDeadzone()) // 트리거는 0~ 255 양수밖에 없으므로
				return 1; // press
			else	
				return 0;
		}
		else if (lable == VK_PAD_RTRIGGER)
		{
			if (trigger->bRightTrigger > g_ini.getTriggerToButtonDeadzone())
				return 1; // press
			else	
				return 0;
		}
		else
		{
			CError e
			(	
				_T("경고XX:\tXBOX360패드는 왼쪽, 오른쪽 2가지 트리거 버튼밖에 없는데, 도대체 무슨 트리거입니까?"), 
				_T(""),
				_T(__FUNCTION__)				
			);
			e.log();

			return 0;
		}
	}



private:
	WORD	_before_state;
	BYTE	_state;
};
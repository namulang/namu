#pragma once

#include <Windows.h>
#include "CINI.hpp"
#include "CInputInterface.hpp"
//	#인풋프리셋#추가#
#include "CInputNodeSample.hpp"
//	#콘솔입력#추가#
#include "CInputConsoleKeyboardAndMouse.hpp"
#include "CInputConsoleXbox360Pad.hpp"


class CInput
{
public:
	CInput() : _activated(true), _setting_interface(NULL), _setting_interface_index(0)
	{
		_sample = *(g_ini._sample);	
	}
	~CInput()
	{}
	
	void	excute()
	{
		activate();
		if (_setting_interface)
			setting_mode();
		else
			update();
	}
	void	inputLabel(CInputInterface* input_interface, int input_interface_index=0) // input_interface_index = 보조키? 메인키?
	{
		//	예외상황처리:
		if (!input_interface)
			return ;

		//	메인코드:
		initializeState();
		_setting_interface = input_interface;
		_setting_interface_index = input_interface_index;
	}
	void	initializeState() // 모든 버튼, 스틱등.. 인터페이스의 상태를 초기화 한다.
	{
		_sample.initializeState();
	}

private:
	void	activate()
	{
		if (g_ini._window_activate)
		{
			if (!_activated)
			{
				_console_xbox360pad.enable();
				_activated = true;
			}
		}
		else
		{	
			if (_activated)
			{
				_console_xbox360pad.disable();
				_activated = false;
			}
		}
	}
	void	setting_mode()
	{
		updateConsole();
		CInputInterfaceSet new_binding_key = _setting_interface->inputLabel(&_console_keyboard_mouse, &_console_xbox360pad);

		if (new_binding_key.getLabel()) // 0보다 크면, 키 인식에 성공했다는 뜻임
		{
			OutputDebugString(_T("\n\tsetting_mode . . . quit"));
			*(_setting_interface->getInterfaceSet(_setting_interface_index)) = new_binding_key;
			_setting_interface = NULL;
			_setting_interface_index = 0;
		}
	}
	void	update()
	{
		updateConsole();		
		updateInterfacePreset();
		_console_xbox360pad.vibrate();
	}
	void	updateInterfacePreset()
	{
		//	#인풋프리셋#추가#
		_sample.update(&_console_keyboard_mouse, &_console_xbox360pad); // #콘솔입력#추가#
	}
	void	updateConsole()
	{
		//	#콘솔입력#추가#
		_console_xbox360pad.update();
	}

public:
	//	#인풋프리셋#추가#
	CInputNodeSample	_sample;
	//	#콘솔입력#추가#
	CInputConsoleKeyboardAndMouse	_console_keyboard_mouse;	
	CInputConsoleXbox360Pad			_console_xbox360pad;

private:
	bool							_activated;
	CInputInterface*				_setting_interface; // 현재 셋모드 중인 인터페이스. 널(0)이 아닐경우는, 다른 입력을 모두 포기하고 셋팅에만 집중하는 셋모드가 된다.
	int								_setting_interface_index;
};
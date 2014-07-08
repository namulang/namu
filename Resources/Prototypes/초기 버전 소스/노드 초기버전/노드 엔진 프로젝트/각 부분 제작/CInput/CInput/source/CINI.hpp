/*
	파일명:	CINI.hpp
	이름:	INI 로더
	기능:	시스템 설정(그래픽, 사운드, 버전) && 게임옵션 을 관리
*/

#pragma once
//	선언:
//		기본 인클루드:
#include <Windows.h>
#include <tchar.h>
#include <atlstr.h> // CString을 API에서 사용하기위해
//		커스텀 인클루드:
#include "CError.hpp"
#include "define.hpp"
//		전방선언:
 class CInputNodeSample; // #인풋프리셋#추가#

//	정의:
//		클래스:
class CINI
{
//	멤버 함수:
public:
	//	생성자:
	CINI();
	//	소멸자:
	~CINI();

	SHORT	getAnalogstickDeadzone()
	{
		return _analog_stick_deadzone;
	}
	void	setAnalogstickDeadzone(float deadzone_percentage)
	{
		_analog_stick_deadzone = (SHORT) (deadzone_percentage * float(0x7FFF));
	}
	SHORT	getAnalogstickMaxDeadzone()
	{
		return _analog_stick_max_deadzone;
	}
	void	setAnalogstickMaxDeadzone(float deadzone_percentage)
	{
		_analog_stick_max_deadzone = (SHORT) (deadzone_percentage * float(0x7FFF));
	}
	SHORT	getAnalogstickToButtonDeadzone()
	{
		return _analog_stick_to_button_deadzone;
	}
	void	setAnalogstickToButtonDeadzone(float deadzone_percentage)
	{
		_analog_stick_to_button_deadzone = (SHORT) (deadzone_percentage * float(0x7FFF));
	}
	BYTE	getTriggerDeadzone()
	{
		return _trigger_deadzone;
	}
	void	setTriggerDeadzone(BYTE deadzone) // max = 255
	{
		_trigger_deadzone = deadzone;
	}
	BYTE	getTriggerToButtonDeadzone()
	{
		return _trigger_to_button_deadzone;
	}
	void	setTriggerToButtonDeadzone(BYTE deadzone)
	{
		_trigger_to_button_deadzone = deadzone;
	}	

//	CInput:
public:
	//	NodeSamplePreset: // #인풋프리셋#추가#
	CInputNodeSample*	_sample;
	HWND				_hWnd;
	bool				_window_activate;
	RECT				_client_rect;

//	개인변수:
private:
	//		화면 비율:
	WINDOW_RATIO	_graphic_ratio;
	SHORT			_analog_stick_deadzone;
	SHORT			_analog_stick_max_deadzone; // 아날로그 스틱의 범위는, deadzone ~ max deadzone 까지가 된다.
	SHORT			_analog_stick_to_button_deadzone;	
	BYTE			_trigger_deadzone;
	BYTE			_trigger_to_button_deadzone;
};

extern CINI g_ini;
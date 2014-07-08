#pragma once

#include <Windows.h>
#include <XInput.h>
#include <MMSystem.h>
#include "define.hpp"
#include "CINI.hpp"

class CInputConsoleXbox360Pad
{
public:
	CInputConsoleXbox360Pad();
	~CInputConsoleXbox360Pad();
	void	disable();
	void	enable();
	void	update();
	XINPUT_GAMEPAD*	getStateGamepad(int index);
	bool	isJoypadPlayerConnected(int index);
	void	setBigMotor(int joypad_number, USHORT level, DWORD duration_miliseconds)
	{
		//	예외상황처리:
		if (!isJoypadPlayerConnected(joypad_number))
			return;

		//	메인코드:
		_pad[joypad_number]._vibration.wLeftMotorSpeed = level;
		_pad[joypad_number]._big_vibration_end_time = timeGetTime() + duration_miliseconds;
	}
	void	setSmallMotor(int joypad_number, USHORT level, DWORD duration_miliseconds)
	{
		//	예외상황처리:
		if (!isJoypadPlayerConnected(joypad_number))
			return;

		//	메인코드:
		_pad[joypad_number]._vibration.wRightMotorSpeed = level;
		_pad[joypad_number]._small_vibration_end_time = timeGetTime() + duration_miliseconds;
	}
	void	setWholeSmallMotor(USHORT level, DWORD duration_miliseconds)
	{
		for (int n=0; n < DEFAULT_CINPUTCONSOLEXBOX360PAD_MAX_CONTROLLERS ;n++)
			setSmallMotor(n, level, duration_miliseconds);
	}
	void	setWholeBigMotor(USHORT level, DWORD duration_miliseconds)
	{
		for (int n=0; n < DEFAULT_CINPUTCONSOLEXBOX360PAD_MAX_CONTROLLERS ;n++)
			setBigMotor(n, level, duration_miliseconds);
	}
	void	vibrate()
	{
		for (int n=0; n < DEFAULT_CINPUTCONSOLEXBOX360PAD_MAX_CONTROLLERS ;n++)
			if (isJoypadPlayerConnected(n))
				vibrateOneJoypad(n);
	}	

private:
	void	vibrateOneJoypad(int joypad_number)
	{
		applyVibration(joypad_number);		
		XInputSetState(joypad_number, &_pad[joypad_number]._vibration);
	}
	void	applyVibration(int joypad_number)
	{	
		DWORD end_time = timeGetTime();

		checkBigMotor(joypad_number, end_time);
		checkSmallMotor(joypad_number, end_time);
	}
	void	checkBigMotor(int joypad_number, DWORD end_time)
	{	
		//	예외상황처리:
		if (_pad[joypad_number]._vibration.wLeftMotorSpeed <= 0)
			return;

		//	메인코드:
		if (_pad[joypad_number]._big_vibration_end_time <= end_time)
		{
			_pad[joypad_number]._big_vibration_end_time = 0;
			_pad[joypad_number]._vibration.wLeftMotorSpeed = 0;
		}
	}
	void	checkSmallMotor(int joypad_number, DWORD end_time)	
	{	
		//	예외상황처리:
		if (_pad[joypad_number]._vibration.wRightMotorSpeed <= 0)
			return;

		//	메인코드:
		if (_pad[joypad_number]._small_vibration_end_time <= end_time)
		{
			_pad[joypad_number]._small_vibration_end_time = 0;
			_pad[joypad_number]._vibration.wRightMotorSpeed = 0;
		}
	}
	void	setDeadzone();
	void	setDeadzoneOnePad(int index);
	void	setAnalogstickDeadzone(int index)
	{
		//	예외상황처리:
		if (g_ini.getAnalogstickDeadzone() <= 0.0f) 
			return; // 디폴트가 "사용안함"으로 되어있을뿐. 오류는 아니다.

		//	메인코드:
		//		min:
		//	왼쪽 아날로그 스틱
		if (	( _pad[index]._state.Gamepad.sThumbLX < g_ini.getAnalogstickDeadzone() && _pad[index]._state.Gamepad.sThumbLX > -(g_ini.getAnalogstickDeadzone()) ) &&
				( _pad[index]._state.Gamepad.sThumbLY < g_ini.getAnalogstickDeadzone() && _pad[index]._state.Gamepad.sThumbLY > -(g_ini.getAnalogstickDeadzone()) ) )
		{
			_pad[index]._state.Gamepad.sThumbLX = 0;
			_pad[index]._state.Gamepad.sThumbLY = 0;
		}
		//	오른쪽 아날로그 스틱
		if (	( _pad[index]._state.Gamepad.sThumbRX < g_ini.getAnalogstickDeadzone() && _pad[index]._state.Gamepad.sThumbRX > -(g_ini.getAnalogstickDeadzone()) ) &&
				( _pad[index]._state.Gamepad.sThumbRY < g_ini.getAnalogstickDeadzone() && _pad[index]._state.Gamepad.sThumbRY > -(g_ini.getAnalogstickDeadzone()) ) )
		{
			_pad[index]._state.Gamepad.sThumbRX = 0;
			_pad[index]._state.Gamepad.sThumbRY = 0;
		}
		//		max:
		//	왼쪽 아날로그 스틱
		//		X축
		if (_pad[index]._state.Gamepad.sThumbLX > g_ini.getAnalogstickMaxDeadzone())
			_pad[index]._state.Gamepad.sThumbLX = g_ini.getAnalogstickMaxDeadzone();
		else if (_pad[index]._state.Gamepad.sThumbLX < -(g_ini.getAnalogstickMaxDeadzone()))
			_pad[index]._state.Gamepad.sThumbLX = -(g_ini.getAnalogstickMaxDeadzone());
		//		Y축
		if (_pad[index]._state.Gamepad.sThumbLY > g_ini.getAnalogstickMaxDeadzone())
			_pad[index]._state.Gamepad.sThumbLY = g_ini.getAnalogstickMaxDeadzone();
		else if (_pad[index]._state.Gamepad.sThumbLY < -(g_ini.getAnalogstickMaxDeadzone()))
			_pad[index]._state.Gamepad.sThumbLY = -(g_ini.getAnalogstickMaxDeadzone());			
		//	오른쪽 아날로그 스틱
		//		X축
		if (_pad[index]._state.Gamepad.sThumbRX > g_ini.getAnalogstickMaxDeadzone())
			_pad[index]._state.Gamepad.sThumbRX = g_ini.getAnalogstickMaxDeadzone();
		else if (_pad[index]._state.Gamepad.sThumbRX < -(g_ini.getAnalogstickMaxDeadzone()))
			_pad[index]._state.Gamepad.sThumbRX = -(g_ini.getAnalogstickMaxDeadzone());
		//		Y축
		if (_pad[index]._state.Gamepad.sThumbRY > g_ini.getAnalogstickMaxDeadzone())
			_pad[index]._state.Gamepad.sThumbRY = g_ini.getAnalogstickMaxDeadzone();
		else if (_pad[index]._state.Gamepad.sThumbRY < -(g_ini.getAnalogstickMaxDeadzone()))
			_pad[index]._state.Gamepad.sThumbRY = -(g_ini.getAnalogstickMaxDeadzone());			

	}
	void	setTriggerDeadzone(int index)
	{
		//	예외상황처리:
		if (g_ini.getTriggerDeadzone() <= 0) 
			return; // 디폴트가 "사용안함"으로 되어있을뿐. 오류는 아니다.

		//	메이코드:
		//	왼쪽 트리거
		if (_pad[index]._state.Gamepad.bLeftTrigger < g_ini.getTriggerDeadzone())
			_pad[index]._state.Gamepad.bLeftTrigger = 0;			
		//	오른쪽 트리거
		if (_pad[index]._state.Gamepad.bRightTrigger < g_ini.getTriggerDeadzone())
			_pad[index]._state.Gamepad.bRightTrigger = 0;
	}


public:
	bool	_enable;
	bool	_deadzone_enable;

private:
	CONTROLLER_STATE	_pad[DEFAULT_CINPUTCONSOLEXBOX360PAD_MAX_CONTROLLERS];
};
#include "CInputConsoleXbox360Pad.hpp"

CInputConsoleXbox360Pad::CInputConsoleXbox360Pad() : _enable(false)
{
	for(int n=0; n < DEFAULT_CINPUTCONSOLEXBOX360PAD_MAX_CONTROLLERS ;n++)
	{
		_pad[n]._bConnected = false;
		_pad[n]._state.dwPacketNumber = NULL;
		_pad[n]._state.Gamepad.bLeftTrigger = NULL;
		_pad[n]._state.Gamepad.bRightTrigger = NULL;
		_pad[n]._state.Gamepad.sThumbLX = NULL;
		_pad[n]._state.Gamepad.sThumbLY = NULL;
		_pad[n]._state.Gamepad.sThumbRX = NULL;
		_pad[n]._state.Gamepad.sThumbRY = NULL;
		_pad[n]._state.Gamepad.wButtons = NULL;

		_pad[n]._vibration.wLeftMotorSpeed = 0;
		_pad[n]._vibration.wRightMotorSpeed = 0;

		_pad[n]._big_vibration_end_time = 0;
		_pad[n]._small_vibration_end_time = 0;
	}
}
CInputConsoleXbox360Pad::~CInputConsoleXbox360Pad()
{}
void	CInputConsoleXbox360Pad::disable()
{
	XInputEnable(false);
}
void	CInputConsoleXbox360Pad::enable()
{
	XInputEnable(true);
}
void	CInputConsoleXbox360Pad::update()
{
	DWORD dwResult;
	for(DWORD n=0; n < DEFAULT_CINPUTCONSOLEXBOX360PAD_MAX_CONTROLLERS; n++)
	{
		// Simply get the state of the controller from XInput.
		dwResult = XInputGetState(n, &_pad[n]._state);

		if(dwResult == ERROR_SUCCESS)
			_pad[n]._bConnected = true;
		else
			_pad[n]._bConnected = false;
	}

	setDeadzone();

	return ;
} 
XINPUT_GAMEPAD*	CInputConsoleXbox360Pad::getStateGamepad(int index) // 에러 발생시, 널을 반환함
{
	//	예외상황처리:
	if (	index < 0												||
			index >= DEFAULT_CINPUTCONSOLEXBOX360PAD_MAX_CONTROLLERS)
	{
		CError e
		(	
			_T("경고XX:\t잘못된 조이패드번호에 접근하려 했습니다."), 
			_T(""),
			_T(__FUNCTION__),
			true // 메세지박스, 로그를 기록하지않는다
		);
		e.log();
		return NULL;
	}
	if (!isJoypadPlayerConnected(index)) // log를 기록하면, 로그메세지가 너무 많이 생기므로 (조이패드가 없을시, 매 프레임마다 생긴다) 생략한다.
		return NULL;

	//	메인코드:
	return &(_pad[index]._state.Gamepad);
}
bool	CInputConsoleXbox360Pad::isJoypadPlayerConnected(int index)
{
	//	예외사항처리:
	if (	index < 0													||
			index >= DEFAULT_CINPUTCONSOLEXBOX360PAD_MAX_CONTROLLERS	)
	{
		CError e
		(	
			_T("경고XX:\t잘못된 조이패드번호에 접근하려 했습니다."), 
			_T(""),
			_T(__FUNCTION__),
			true // 메세지박스, 로그를 기록하지않는다
		);
		e.log();
		return false;
	}

	//	메인코드:
	return _pad[index]._bConnected;
}
void	CInputConsoleXbox360Pad::setDeadzone()
{


	//	메인코드:
	for (int n=0; n < DEFAULT_CINPUTCONSOLEXBOX360PAD_MAX_CONTROLLERS ;n++)
		setDeadzoneOnePad(n);
}
void	CInputConsoleXbox360Pad::setDeadzoneOnePad(int index)
{
	//	예외상황처리:
	if (	index < 0													||
			index >= DEFAULT_CINPUTCONSOLEXBOX360PAD_MAX_CONTROLLERS	)
	{
		CError e
			(	
			_T("경고XX:\t잘못된 조이패드번호에 접근하려 했습니다."), 
			_T(""),
			_T(__FUNCTION__),
			true // 메세지박스, 로그를 기록하지않는다
			);
		e.log();
		return;
	}

	//	메인코드:
	setAnalogstickDeadzone(index);
	setTriggerDeadzone(index);
}
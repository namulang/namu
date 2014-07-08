#include "CInputInterface.hpp"

CInputInterface::CInputInterface() : _enable(false)
{

}
CInputInterface::~CInputInterface()
{}

CInputInterfaceSet*	CInputInterface::getInterfaceSet(int index)
{
	//	예외상황처리:
	if (	index < 0										||
			index >= DEFAULT_CINPUTINTERFACESET_MAX_KEYSET	)
	{
		CError e
		(	
			_T("경고XX:\t이 인풋에 지정할수있는 인터페이스셋을 넘어섰습니다."), 
			_T(""),
			_T(__FUNCTION__),
			true // 메세지박스, 로그를 기록하지않는다
		);
		e.log();
	}

	//	메인코드:
	return &_interface_set[index];
}

CInputInterface&	CInputInterface::operator = (CInputInterface& rhs)
{
	_enable = rhs._enable;
	for (int n=0; n < DEFAULT_CINPUTINTERFACESET_MAX_KEYSET ;n++)
		_interface_set[n] = *(rhs.getInterfaceSet(n));
			
	return *this;
}
void	CInputInterface::update(CInputConsoleKeyboardAndMouse* keyboard_mouse, CInputConsoleXbox360Pad* xbox360pad)
{
	//	예외상황처리:
	if (!_enable)
		return;

	//	메인코드:
	for (int n=0; n < DEFAULT_CINPUTINTERFACESET_MAX_KEYSET ;n++)
		updateOneInterfaceSet(n, keyboard_mouse, xbox360pad);		
}

void	CInputInterface::updateOneInterfaceSet(int index, CInputConsoleKeyboardAndMouse* keyboard_mouse, CInputConsoleXbox360Pad* xbox360pad)
{
	//	메인코드:
	if (isXbox360Pad(_interface_set[index].getLabel()))
	{
		if ( xbox360pad->isJoypadPlayerConnected( _interface_set[index].getJoypadPlayer()) )
			updateXbox360Pad(xbox360pad, index);
	}
	else if (isKeyboardMouse(_interface_set[index].getLabel()))
		updateKeyboardMouse(keyboard_mouse, index);
	else
	{
		CError e
		(	
			_T("경고XX:\t인풋 장치의 상태를 업데이트하려고 했으나, 알수없는 장치입니다. (번호초과)"), 
			_T(""),
			_T(__FUNCTION__),
			true // 메세지박스, 로그를 기록하지않는다
		);
		e.log();		
	}	
}


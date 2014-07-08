#include "CInputNodeSample.hpp"

CInputNodeSample::CInputNodeSample()
{}
CInputNodeSample::~CInputNodeSample()
{}

CInputNodeSample&	CInputNodeSample::operator = (CInputNodeSample& rhs)
{
	_cursor = rhs._cursor;
	_ok	 = rhs._ok;
	_cancle = rhs._cancle;
	_power = rhs._power;

	return *this;
}

void	CInputNodeSample::initializeDefaultInputConsole()
{
	initializeToKeyboardMouse(); // 이게 이 프리셋의 기본 세팅 => 키보드.
}
void	CInputNodeSample::initializeToKeyboardMouse() // 디폴트
{
	// _move
	// _cursor
	_enable = true;
	_ok._enable = true;
	_ok.getInterfaceSet()->setLable(VK_LBUTTON);
	_cancle._enable = true;
	_cancle.getInterfaceSet()->setLable(VK_Z);
	_cursor._enable = true;	
	_cursor.getInterfaceSet()->setLable(VK_PAD_RTHUMB);
}
void	CInputNodeSample::intializeToXbox360Pad()
{
	// _move
	// _cursor
	_enable = true;
	_ok._enable = true;
	_ok.getInterfaceSet()->setLable(VK_PAD_LTHUMB_DOWN);
	_cancle._enable = true;
	_cancle.getInterfaceSet()->setLable(VK_PAD_X);
	_cursor._enable = true;	
	_cursor.getInterfaceSet()->setLable(VK_PAD_RTHUMB);
	_power._enable = true;
	_power.getInterfaceSet()->setLable(VK_PAD_RTRIGGER);
}

void	CInputNodeSample::update(CInputConsoleKeyboardAndMouse* keyboard_mouse, CInputConsoleXbox360Pad* xbox360pad)
{
	//	예외상황처리:
	if (!_enable)
		return ;

	//	메인코드:
	_cursor.update(keyboard_mouse, xbox360pad);
	_ok.update(keyboard_mouse, xbox360pad);
	_cancle.update(keyboard_mouse, xbox360pad);
	_power.update(keyboard_mouse, xbox360pad);
}

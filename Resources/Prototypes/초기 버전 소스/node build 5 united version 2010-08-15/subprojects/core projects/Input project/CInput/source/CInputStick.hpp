/*	
	스틱이란?
	0,0을 기준으로, 좌, 우, 상, 하, 대각선등 8개의 방향을 나타내는 게 가능하다.
	그리고, 그 강도를 조절가능해야하며,
	그 강도와 방향을 토대로, 게임좌표의 커서의 위치를 반환하게 된다.
	인풋값: 콘솔 입력 장치 (키보드&마우스 || 조이패드)
			강도
	아웃풋값: 커서의 위치
*/
#pragma once

#include "CInputInterface.hpp"
#include "CINI.hpp"
#include "define.hpp"
#include <XInput.h>

class CInputStick : public CInputInterface
{
public:
	CInputStick()
	{
		_cursor.x = 0;
		_cursor.y = 0;
	}
	~CInputStick()
	{}

	CInputStick&	operator = (CInputStick& rhs)
	{
		_cursor.x = 0;
		_cursor.y = 0;

		CInputInterface::operator =(rhs);
		return *this;
	}
	void	setCursor(int x, int y)
	{
		_cursor.x = x;
		_cursor.y = y;
	}
	int		getRealCursorX() // 실제좌표에서 커서
	{
		return _cursor.x;
	}
	int		getRealCursorY()
	{
		return _cursor.y;
	}
	// 게임에서 사용되는 커서좌표. 카메라의 줌과 평행이동좌표로, 게임상에서 커서의 좌표를 계산한다.
	int		getCursorX(float camera_x = 0.0f, float camera_y = 0.0f, float camera_zoom = 1.0f)
	{
		return 0;
	}
	int		getCursorY(float camera_x = 0.0f, float camera_y = 0.0f, float camera_zoom = 1.0f)
	{
		return 0;
	}
	void	initializeState()
	{
		// #작업# y = g_ini.halfHeight;
	}
protected:
	virtual void	updateKeyboardMouse(CInputConsoleKeyboardAndMouse* keyboard_mouse, int index)
	{
		// 여기서 전체화면인지 체크한다. if (g_ini)
		// 전체화면시 GetCursorPos(&_cursor); 만 실행
		GetCursorPos(&_cursor);
		ScreenToClient(g_ini._hWnd, &_cursor); // 윈도우를 옮겨도 자동으로 원점 보정
		// if (ini로부터 클라이언트 너비와 높이를 비교해서 그것보다 크면, 너비와 높이로 세팅한다.)
		// WM_SIZE를 못하게 하던가... 아니면, WM_SIZE시, 클라이언트영역을 ini에 갱신하던가.
		setMouseCursorDeadzone();
	}
	virtual	void	updateXbox360Pad(CInputConsoleXbox360Pad* xbox360pad, int index)
	{
		//	예외상황처리:
		XINPUT_GAMEPAD*	gamepad_state = xbox360pad->getStateGamepad(_interface_set[index].getJoypadPlayer());	
		if (!gamepad_state)
			return; // 게임패드의 상태를 얻는데 실패했다.
		if ( !isStick(_interface_set[index].getLabel()) ) // 스틱이 아니다
			return; 

		POINT	tilt;
		tilt = getStickTilt(xbox360pad->getStateGamepad(_interface_set[index].getJoypadPlayer()), _interface_set[index].getLabel()); // 어느쪽 스틱인지 판단한뒤, 그 값을 가져온다
		//	좌표계산
		setStickCursorPos(tilt);
	}
	virtual	CInputInterfaceSet	checkKeyboardMouse(CInputConsoleKeyboardAndMouse* keyboard_mouse) // 0은 인식 실패. WORD인 이유는, _label이 WORD이므로
	{
		if (	GetAsyncKeyState(VK_LBUTTON)	|| // 마우스의 움직임으로 하면, 마우스로 메뉴를찍다가 조이패드를 선택못하는 경우가 생길수 있기에 좌/우 클릭을 대신함. 그러나 보통은, 이렇게 하지 않고 메뉴상에서 선택이 가능하게 되겠지.
				GetAsyncKeyState(VK_RBUTTON)	)
			return	CInputInterfaceSet(VK_LBUTTON, 0); // 키보드에 해당하는 레이블이면 뭐든 좋음.

		return CInputInterfaceSet();
	}
	virtual	CInputInterfaceSet	checkXbox360Pad(CInputConsoleXbox360Pad* xbox360pad) // 0은 인식 실패. WORD인 이유는, _label이 WORD이므로
	{
		for (int n=0; n < DEFAULT_CINPUTCONSOLEXBOX360PAD_MAX_CONTROLLERS ;n++)
		{
			if (xbox360pad->isJoypadPlayerConnected(n))
			{
				if (	xbox360pad->getStateGamepad(n)->sThumbLX	||
						xbox360pad->getStateGamepad(n)->sThumbLY	||
						xbox360pad->getStateGamepad(n)->sThumbRX	||
						xbox360pad->getStateGamepad(n)->sThumbRY	)
					return	CInputInterfaceSet(VK_PAD_A, n); // 조이패드에 해당하는 레이블이면 뭐든 좋음.
			}
		}

		return CInputInterfaceSet();
	}
	POINT	getStickTilt(XINPUT_GAMEPAD* gamepad, WORD label)
	{
		POINT	container;
		container.x = 0;
		container.y = 0;

		if (isLeftStick(label))
		{
			container.x = (LONG) gamepad->sThumbLX;
			container.y = (LONG) -(gamepad->sThumbLY); // Y는 부호가 반대로 되어있다. 좌상이 ++ 인것.
			return container;
		}
		else if (isRightStick(label))
		{
			container.x = (LONG) gamepad->sThumbRX;
			container.y = (LONG) -(gamepad->sThumbRY); 
			return container;
		}
		else
		{
			container.x = 0;
			container.y = 0;
			CError e
			(	
				_T("경고XX:\tXBOX360패드는 왼쪽, 오른쪽 2가지 아날로그 스틱밖에 없는데, 도대체 무슨 스틱입니까?"), 
				_T(""),
				_T(__FUNCTION__)				
			);
			e.log();

			return container;
		}
	}
	bool	isLeftStick(WORD label)
	{
		if (	label >= VK_PAD_LTHUMB_UP	&&
				label <= VK_PAD_LTHUMB		)
			return true;
		else
			return false;
	}
	bool	isRightStick(WORD label)
	{
		if (	label >= VK_PAD_RTHUMB			&&
				label <= VK_PAD_RTHUMB_DOWNLEFT	)
			return true;
		else
			return false;
	}
	//	험난한-_-; 필터링을 거쳐서 도착한 기울임 정도를 이용해서 게임의 마우스 커서를 정한다.
	void	setStickCursorPos(POINT tilt_level) 
	{
		float	x_percentage = 0.0f,
				y_percentage = 0.0f;
		
		x_percentage = getStickTiltPercentage(tilt_level.x);
		y_percentage = getStickTiltPercentage(tilt_level.y);		
		//	게임커서좌표 구하기 #작업#
		//_cursor.x = (g_ini.getHalfHeight * x_percentage) + g_ini.getHalfHeight;
		_cursor.x = (LONG) (400 * x_percentage) + 400;
		_cursor.y = (LONG) (300 * y_percentage) + 300;
		
		POINT	filtered_pos;	
		filtered_pos.x = 0;
		filtered_pos.y = 0;
		//ScreenToClient(g_ini._hWnd, &_cursor); // #테스트# 원래는 필요없음
		//SetCursorPos(_cursor.x, _cursor.y);
	}
	float	getStickTiltPercentage(LONG tilt_level)
	{
		//	예외상황처리
		if (!tilt_level) // 데드존 처리되어 있을 경우 
			return 0.0f;

		//	메인코드:	
		//	퍼센티지 => 그냥, 맥스데드존 ~ 최소치 간의 퍼센티지로 한다.
		//			 =  (틸트값 - 민 데드존) / (맥스데드존-민데드존) 로 할경우, 데드존이 있는 곳과 없는 부분이 퍼센티지가 다르게되기때문이다. (주석이 더 필요)		
		return (float) tilt_level / g_ini.getAnalogstickMaxDeadzone();
	}
	void	setMouseCursorDeadzone()
	{
		if (_cursor.x < 0)
			_cursor.x = 0;
		if (_cursor.x > g_ini._client_rect.right)
			_cursor.x = g_ini._client_rect.right;
		if (_cursor.y < 0)
			_cursor.y = 0;
		if (_cursor.y > g_ini._client_rect.bottom)
			_cursor.y = g_ini._client_rect.bottom;
	}



private:
	POINT	_cursor; 
};
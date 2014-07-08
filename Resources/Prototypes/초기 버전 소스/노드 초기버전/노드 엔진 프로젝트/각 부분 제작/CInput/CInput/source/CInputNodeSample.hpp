#pragma once

#include "CInputButton.hpp" // #인터페이스#추가#
#include "CInputStick.hpp"
#include "CInputPressButton.hpp"
#include "CInputPreset.hpp"

class CInputNodeSample : public CInputPreset
{
public:
	CInputNodeSample();
	~CInputNodeSample();

	CInputNodeSample&	operator = (CInputNodeSample& rhs);

	void	initializeDefaultInputConsole();
	void	initializeToKeyboardMouse();
	void	intializeToXbox360Pad();

	void	update(CInputConsoleKeyboardAndMouse* keyboard_mouse, CInputConsoleXbox360Pad* xbox360pad);
	void	initializeState()
	{
		_cursor.initializeState();
		_ok.initializeState();
		_cancle.initializeState();
		_power.initializeState();
	}
public:
	CInputStick		_cursor;
	CInputButton	_ok,
					_cancle;
	CInputPressButton _power;
};
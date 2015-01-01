#pragma once

#include "../../Includes/Includes.hpp"

class NameInputWindow : public ::LG::InputWindow
{
public:
	NameInputWindow(NETString& target) : InputWindow("새로운 문자열을 입력해주시기 바랍니다.", BLACK, LIGHTCYAN, target), _target(target) {}

	FUNC_CLONE(NameInputWindow)
	virtual void onInputed()
	{
		_target = input.text;
		delete_me = true;
	}

	NETString& _target;
};
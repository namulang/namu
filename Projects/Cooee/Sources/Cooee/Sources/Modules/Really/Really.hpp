#pragma once

#include "../../Includes/Includes.hpp"

class Really : public ::LG::QueryWindow
{
public:
	Really()
		: QueryWindow("종료할려고요? 이렇게 재밌는 프로그램을 놔두고?", WHITE, LIGHTBLUE)
	{
		panel.text = "그만할래ㅜ";
		panel.width = 15;
		no.text = "버튼 실수~";
		no.width = 13;
	}
	virtual void onButtonPressed(bool witch_button);
	NEObject& clone() const { return *(new Really(*this)); }
};
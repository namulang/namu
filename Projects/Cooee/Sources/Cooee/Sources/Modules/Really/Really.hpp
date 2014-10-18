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
		no.text = "버튼을 잘못 눌렀음";
		no.width = 20;
	}
	virtual void onButtonPressed(bool witch_button)
	{
		if(witch_button)
		{
			for(LG::WindowList::Iterator* itr = LG::Core::windows.getIterator(0); itr ;itr=itr->getNext())
				itr->getValue().delete_me = true;
		}

		delete_me = true;
	}
	NEObject& clone() const { return *(new Really(*this)); }
};
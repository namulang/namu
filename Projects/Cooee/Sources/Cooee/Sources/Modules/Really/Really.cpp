#include "Really.hpp"
#include "../Core/Core.hpp"

void Really::onButtonPressed(bool witch_button)
{
	if(witch_button)
	{
		for(LG::WindowList::Iterator* itr = ::Core::debug_windows.getIterator(0); itr ;itr=itr->getNext())
			itr->getValue().delete_me = true;
	}

	delete_me = true;
}
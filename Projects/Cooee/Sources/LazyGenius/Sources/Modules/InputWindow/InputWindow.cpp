#include "InputWindow.hpp"

namespace LG
{
	void InputWindow::InputBox::onKeyPressed(char inputed)
	{
		switch(inputed)
		{
		case CLOSE:
			toOwner()->delete_me = true;
			break;

		case ENTER:
			toOwner()->onInputed();
			return;
			break;
		}

		TextGliph::onKeyPressed(inputed);
	}
}
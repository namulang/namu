#include "InputWindow.hpp"

namespace LG
{
	void InputWindow::InputBox::onKeyPressed(char inputed)
	{
		switch(inputed)
		{
		case CANCEL:
			toOwner()->delete_me = true;
			break;
		case CONFIRM:
			toOwner()->onInputed();
			return;
			break;
		}

		TextGliph::onKeyPressed(inputed);
	}
}
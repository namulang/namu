#include "MessageWindow.hpp"
#include "../Core/Core.hpp"

namespace LG
{
	void MessageWindow::onKeyPressed(int inputed)
	{
		if (inputed == CONFIRM) {
			Core::play(Core::SND_CONFIRM);
			delete_me = true;
		}	
		else
			Core::play(Core::SND_BLOCKED);
	}
}
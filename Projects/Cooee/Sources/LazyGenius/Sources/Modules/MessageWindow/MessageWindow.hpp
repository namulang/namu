#pragma once

#include "../Window/Window.hpp"
#include "../Button/Button.hpp"

namespace LG
{	
	class NE_DLL MessageWindow : public Window 
	{
	public:
		FUNC_CLONE(MessageWindow)
			MessageWindow(	const NEString& new_text, type_ushort fore, type_ushort back, const NEString& new_button_text = "  OK", 
			type_ushort x=20, type_ushort y=12, type_ushort width=40, type_ushort height=5)
			: Window(x, y, width, height, fore, back), panel(new_button_text, true, 0, 35, 15, 10, 2, fore, back)
		{ 
			text = new_text;
			panel.onUpdateData();
			regist(1, &panel);
		}
		MessageWindow(const MessageWindow& rhs) : Window(rhs), panel(rhs.panel) { regist(1, &panel); }

		virtual void onKeyPressed(char inputed);

		Button panel;
	};
}
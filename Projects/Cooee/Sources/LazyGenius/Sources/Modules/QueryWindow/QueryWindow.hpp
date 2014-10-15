#pragma once

#include "../MessageWindow/MessageWindow.hpp"

namespace LG
{
	class NE_DLL QueryWindow : public MessageWindow
	{
	public:			
		typedef type_ushort u2;
		QueryWindow(const NEString& new_text, u2 fore, u2 back, bool default_focus_on_no = true)
			: MessageWindow(new_text, fore, back, "  YES"), no("  NO", false, 0, 45, 15, 10, 2, fore, back)
		{	
			regist(1, &no);
			panel.x = 25;
			panel.width = 10;
			default_focus_on_no ? no.setFocus(true) : panel.setFocus(true);			
		}
		QueryWindow(const QueryWindow& rhs)
			: MessageWindow(rhs), no(rhs.no)
		{
			regist(1, &no);
		}
		virtual void onKeyPressed(char inputed) 
		{
			switch(inputed)
			{
			case CONFIRM:
				onButtonPressed(panel.isFocused());				
				break;
			case LEFT:
				if( ! panel.isFocused())
					panel.setFocus(true);
				break;
			case RIGHT:
				if( ! no.isFocused())
					no.setFocus(true);
				break;
			}
		}
		virtual void onButtonPressed(bool witch_button) = 0;

		Button no;
	};
}
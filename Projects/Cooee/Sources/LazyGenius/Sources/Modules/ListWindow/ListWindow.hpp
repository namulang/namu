#pragma once

#include "../Window/Window.hpp"
#include "../ListGliph/ListGliph.hpp"

namespace LG
{
	class NE_DLL ListWindow : public Window
	{
	public:
		typedef type_ushort u2;
		ListWindow(const NEString& title, u2 x, u2 y, u2 w, u2 h, u2 fore, u2 back, u2 focused_fore = UNKNOWN, u2 focused_back = UNKNOWN, const NEStringSet& new_items = NEStringSet()) 
			: Window(x, y, w, h, fore, back), header(0, x, y, w, 1, WHITE, BLACK, title), list(0, x+1, y+2, w-1, h-1, fore, back, focused_fore, focused_back)
		{
			list.items = new_items;
			regist(2, &header, &list);
			list.choosed_back = focused_back == UNKNOWN ? list.fore : focused_back;
			list.choosed_fore = focused_fore == UNKNOWN ? list.back : focused_fore;
		}
		ListWindow(const ListWindow& rhs) : Window(rhs), header(rhs.header), list(rhs.list) 
		{
			regist(2, &header, &list);
		}

		virtual void onKeyPressed(char inputed)
		{
			Window::onKeyPressed(inputed);

			switch(inputed)
			{
			case CANCEL:
				delete_me = true;
				break;
			case CONFIRM:
				onItemChoosed(list.choosed, list.items[list.choosed]);
				break;
			}
		}
		virtual void onItemChoosed(type_index item_index, const NEString& chosen_content) = 0;

		Gliph header;
		ListGliph list;
	};
}
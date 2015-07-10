#pragma once

#include "../Window/Window.hpp"
#include "../TextList/TextList.hpp"

namespace LG
{
	class NE_DLL TextListWindow : public Window
	{
	public:
		typedef type_ushort u2;

		class NE_DLL MyTextList : public TextList
		{
		public:
			MyTextList(Window* new_owner, type_ushort new_x, type_ushort new_y, type_ushort new_width, type_ushort new_height, type_ushort new_fore, type_ushort new_back, type_ushort new_choosed_fore, type_ushort new_choosed_back, bool new_use_matching = true, bool new_use_sound = true)
				: TextList(new_owner, new_x, new_y, new_width, new_height, new_fore, new_back, new_choosed_fore, new_choosed_back, new_use_matching, new_use_sound)
			{

			}
			virtual void onInputed(const NEString& inputed) 
			{
				master->onInputed(inputed);
			}

			TextListWindow* master;
		};

		TextListWindow(const NEString& title, u2 x, u2 y, u2 w, u2 h, u2 fore, u2 back, u2 focused_fore = UNKNOWN, u2 focused_back = UNKNOWN, const NEStringSet& new_items = NEStringSet())
			: Window(x, y, w, h, fore, back), header(0, x, y, w, 1, WHITE, BLACK, title), list(0, x + 1, y + 2, w - 1, h - 3, fore, back, focused_fore, focused_back)
		{
			list.master = this;
			list.items = new_items;
			list.width--;
			regist(2, &header, &list);
			list.choosed_back = focused_back == UNKNOWN ? list.fore : focused_back;
			list.choosed_fore = focused_fore == UNKNOWN ? list.back : focused_fore;
			list.use_sound = true;
		}
		TextListWindow(const TextListWindow& rhs) : Window(rhs), header(rhs.header), list(rhs.list)
		{
			list.master = this;
			regist(2, &header, &list);
			list.use_sound = true;
		}

		virtual void onKeyPressed(int inputed)
		{
			Window::onKeyPressed(inputed);

			switch (inputed)
			{
			case ESCAPE:
				delete_me = true;
				break;			
			}
		}
		virtual void onInputed(const NEString& inputed) = 0;

		Gliph header;

		MyTextList list;
	};
}
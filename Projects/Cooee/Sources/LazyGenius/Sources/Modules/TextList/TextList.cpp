#include "TextList.hpp"

namespace LG
{
	TextList::TextList(Window* new_owner, type_ushort new_x, type_ushort new_y, type_ushort new_width, type_ushort new_height, type_ushort new_fore, type_ushort new_back, type_ushort new_choosed_fore, type_ushort new_choosed_back, bool new_use_matching, bool new_use_sound)
		: ListGliph(new_owner, new_x, new_y, new_width, new_height, new_fore, new_choosed_fore, new_choosed_back, new_use_matching, new_use_sound)
	{
		text.Gliph::operator=(*this);		
		text.fore = LIGHTCYAN;
		text.back = CYAN;
		text.height = 1;		
		text.width--;
		y++;		
		height--;	
	}
	TextList::TextList(const TextList& rhs)
		: ListGliph(rhs), text(rhs.text)
	{

	}

	void TextList::onDraw()
	{
		text.onDraw();
		ListGliph::onDraw();
	}
	void TextList::onUpdateData()
	{
		text.onUpdateData();
		ListGliph::onUpdateData();
	}
	void TextList::onKeyPressed(int inputed)
	{
		switch(inputed)
		{
		case UP: case DOWN:
			ListGliph::onKeyPressed(inputed);
			text.text = items[choosed];
			break;

		case CONFIRM:			
			onInputed(text.text);
			ListGliph::onKeyPressed(inputed);
			text.onKeyPressed(inputed);
			break;

		case BACKSPACE:
		default:
			text.onKeyPressed(inputed);
			match(text.text);
		}

	}	
}
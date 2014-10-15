#include "TextGliph.hpp"

namespace LG
{
	TextGliph::TextGliph(	Window* new_owner, type_ushort new_x, type_ushort new_y, type_ushort new_width, type_ushort new_height, 
							type_ushort new_fore, type_ushort new_back)
		: Gliph(new_owner, new_x, new_y, new_width, new_height, new_fore, new_back), history_idx(-1) 
	{

	}
	TextGliph::TextGliph(const TextGliph& rhs)
		: Gliph(rhs), history(rhs.history), history_idx(rhs.history_idx) 
	{

	}

	void TextGliph::makeToHistory() 
	{
		int index = history.find(text);
		if(index == NE_INDEX_ERROR)
			history.pushFront(text);
		else
		{
			NEString picked = history[index];
			history.remove(index);
			history.pushFront(picked);
		}
		history_idx = -1;
	}

	void TextGliph::onKeyPressed(char inputed) 
	{
		switch(inputed) 
		{
		case '\t': case -32: case UP: case DOWN:
			break;

		case BACKSPACE:
			if(history_idx != -1) {
				text.release();
				history_idx = -1;
			}
			else if(text.getLength() > 1)
			{
				if(text[text.getLengthLastIndex()] == '\0')
				{
					text.pop();
					text[text.getLengthLastIndex()] = '\0';
				}
			}
			else if(text.getLength() == 1)
				text[0] = '\0';
				

			break;

		case ENTER:
			makeToHistory();
			break;

		case LEFT: 
			if(history_idx > 0) {
				history_idx--;
				text = history[history_idx];
			}
			break;

		case RIGHT: 
			if(history_idx < history.getLengthLastIndex()) {
				history_idx++;
				text = history[history_idx];
			}
			break;			

		default:
			if(text.getSize() <= 0)
				text.create(50);			
			if(text.getLength() == text.getSize())
				text.resize(text.getSize() * 2);
			if(text.getLength() > 0 && text[text.getLengthLastIndex()] == '\0')
				text.pop();
			text.push(inputed);
			if(text[text.getLengthLastIndex()] != '\0')
				text.push('\0');
			history_idx = -1;
		}
	}
}
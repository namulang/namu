#include "ListGliph.hpp"
#include "../Core/Core.hpp"

namespace LG
{
	ListGliph::ListGliph(	Window* new_owner, type_ushort new_x, type_ushort new_y, type_ushort new_width, 
							type_ushort new_height, type_ushort new_fore, type_ushort new_back, 
							type_ushort new_choosed_fore, type_ushort new_choosed_back)
		: Gliph(new_owner, new_x, new_y, new_width, new_height, new_fore, new_back), 
		choosed_back(new_choosed_back), choosed_fore(new_choosed_fore), choosed(0) 
	{

	}
	ListGliph::ListGliph(const ListGliph& rhs)
		: Gliph(rhs), items(rhs.items), choosed(rhs.choosed), choosed_back(rhs.choosed_back), 
		choosed_fore(rhs.choosed_fore) 
	{

	}

	void ListGliph::onDraw() {

		Gliph::onDraw();

		COORD backup_pos = Core::getCursorPosition();
		WORD backup_color = Core::getColor();
		BackBuffer& buf = Core::back_buffer;

		int half_height = (height / 2),
			list_head_index = choosed - half_height,
			bottom_limit_index = items.getLength()-height;	//	무조건 이거보단 list_head가 커야 한다.
		if(bottom_limit_index < 0)
			bottom_limit_index = 0;
		if(list_head_index < 0)
			list_head_index = 0;
		if(list_head_index > bottom_limit_index)
			list_head_index = bottom_limit_index;

		int last_index = list_head_index + height-1;
		for(int y1=list_head_index; y1 <= last_index ;y1++) {
			if(y1 > items.getLengthLastIndex())	continue;

			int y_coordinate = y1 - list_head_index;
			buf.setBufferPointer(x, y + y_coordinate);
			if(y1 == choosed)
				buf.setColor(choosed_fore, choosed_back);
			else
				buf.setColor(fore, back);

			bool	is_there_more_contents_after	= items.getLengthLastIndex() > last_index,
					is_there_more_contents_before	= list_head_index != 0;

			NEString s = 
				(	(is_there_more_contents_after && y1 == last_index)			||
					(is_there_more_contents_before && y1 == list_head_index)	)	? 
				" . . . " 
				: 
			items[y1];
			s.resize(width + 1);
			s.pop();
			if(s.getLength() < width)
				for(int n=s.getLength(); n < width ;n++) 
					s.push(' ');				
			s.push('\0');

			buf << s.toCharPointer();
		}

		Core::setColor(backup_color);
		Core::setCursorTo(backup_pos);
	}


	void ListGliph::onKeyPressed(char inputed) {
		switch(inputed) {
	case UP: if(choosed > 0) choosed--;
		break;
	case DOWN: if(choosed < items.getLengthLastIndex()) choosed++;
		break;
		}		
	}
}
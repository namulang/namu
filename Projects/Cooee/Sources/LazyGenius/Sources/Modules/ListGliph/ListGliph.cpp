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

		for(int y1=0; y1 < items.getLength() ;y1++) {
			if(y1+1 > height)	continue;			

			Core::setCursorTo(x, y + y1);
			if(y1 == choosed)
				Core::setColor(choosed_fore, choosed_back);
			else
				Core::setColor(fore, back);

			NEString s = (items.getLength() > height && y1+1 == height) ? " . . . " : items[y1];
			s.resize(width + 1);
			s.pop();
			if(s.getLength() < width)
				for(int n=s.getLength(); n < width ;n++) 
					s.push(' ');				
			s.push('\0');

			std::cout << s.toCharPointer();
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
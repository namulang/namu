#pragma warning(push)
#pragma warning(disable: 4482)
#include "Gliph.hpp"
#include "../Core/Core.hpp"

namespace LG
{

	type_ushort Gliph::getRealX() 
	{
		return ! owner ? x : x + owner->x;		
	}
	type_ushort Gliph::getRealY() 
	{
		return ! owner ? y : y + owner->y;
	}
	void Gliph::onDraw() 
	{
		WORD backup = Core::getColor();
		COORD backup_pos = Core::getCursorPosition();
		Core::setColor(fore, back);

		int count = 0;
		int skip = 0;
		for(int y1=y; y1 < y+height ;y1++) {
			Core::setCursorTo(x, y1);
			for(int x1=x; x1 < x+width ;x1++) {

				if(skip > 0) 
				{
					skip--;
					std::cout << " ";
					continue;
				}
				if(text.getLength() <= count) {
					std::cout << " ";
					continue;
				}
				switch(text[count]) {
				case '\t':	skip = 4-1; std::cout << " ";
					break;
				case '\n':	skip = x+width - x1-1; std::cout << " ";
					break;
				default: std::cout << text[count];

				}

				count++;
			}
		}

		Core::setColor(backup);
		Core::setCursorTo(backup_pos);
	}

	void Gliph::onUpdateData()
	{
		if( &owner && owner->isShowing())
			onDraw();
	}

}
#pragma warning(pop)
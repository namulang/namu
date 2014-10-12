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

		BackBuffer& buf = Core::back_buffer;

		buf.setColor(fore, back);

		int count = 0;
		int skip = 0;
		for(int y1=y; y1 < y+height ;y1++) {
			buf.setBufferPointer(x, y1);
			for(int x1=x; x1 < x+width ;x1++) {

				if(skip > 0) 
				{
					skip--;
					buf << " ";
					continue;
				}
				if(text.getLength() <= count) {
					buf << " ";
					continue;
				}
				switch(text[count]) {
				case '\t':	skip = 4-1; buf << " ";
					break;
				case '\n':	skip = x+width - x1-1; buf << " ";
					break;
				default: buf << text[count];

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
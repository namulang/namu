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

		int printed_text_count = 0,
			max_printed_text_count = text.getLength() - 1;
		int count_to_skip = 0;
		for(int y1=y; y1 < y+height ;y1++) 
		{
			buf.setBufferPointer(x, y1);

			int caret			= x,
				caret_length	= x + width;
			while(caret < caret_length)
			{				
				if(count_to_skip > 0)
				{
					count_to_skip--;
					buf << ' ';
					caret++;
				}
				else if(printed_text_count >= max_printed_text_count)
				{
					buf << ' ';
					caret++;
				}
				else
				{
					char character = text[printed_text_count++];
					switch(character)
					{
					case '\t':	count_to_skip = 4; break;
					case '\n':	count_to_skip = x + width - caret; break;
					default: 
						{
							if((character & 0x80) == 0x80)	//	한글 검출 하는 코드. 한글은 sign bit이 1이다.
							{
								int carets_to_be_printed = caret_length - caret;
								if(carets_to_be_printed >= 2)
								{
									buf << character;
									buf << text[printed_text_count++];
									caret += 2;
								}
								else
								{
									count_to_skip = carets_to_be_printed;
									printed_text_count--;
								}
							}
							else
							{
								buf << character;
								caret++;
							}							
						}
					}					
				}
			}			
		}

		Core::setColor(backup);
		Core::setCursorTo(backup_pos);

		if(_has_frames)
			_drawFrames();
	}

	void Gliph::onUpdateData()
	{
	
	}

	bool Gliph::hasFrames() const
	{
		return _has_frames;
	}

	void Gliph::setHavingFrames(bool have_frames)
	{
		_has_frames = have_frames;
	}

	void Gliph::_drawFrames() const
	{
		WORD backup = Core::getColor();
		COORD backup_pos = Core::getCursorPosition();

		BackBuffer& buf = Core::back_buffer;
		buf.setColor(WHITE, BLACK);

		int frame_x = x + width,
			frame_y = y + height;
		for(int d=1; d < height+1 ;d++)
		{
			buf.setBufferPointer(frame_x, y+d);
			buf << ' ';
		}
		for(int d=1; d < width+1 ;d++)
		{
			buf.setBufferPointer(x+d, frame_y);
			buf << ' ';
		}
	}

}
#pragma warning(pop)
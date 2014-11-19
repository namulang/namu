#include "BackBuffer.hpp"
#include "../../Commons/Enumerations/CommonEnumerations.hpp"
#include "../Core/Core.hpp"

namespace LG
{
	LG::BackBuffer::BackBuffer()
	{
		toDefault();
	}

	LG::BackBuffer::~BackBuffer()			
	{
		release();
	}

	void LG::BackBuffer::toDefault()
	{
		BackBuffer::create(24, 80);
		_focused_buffer_index = 0;
		_fore_pointer = LIGHTGRAY;
		_back_pointer = BLACK;
		_focused_buffer_index = 0;
		_is_color_locked = false;
	}

	void LG::BackBuffer::create( int height, int width )
	{
		release();

		_buffer[0].create(height);
		for(int w=0; w < _buffer[0].getSize() ;w++)
		{
			_buffer[0].push(RowBuffer());
			_buffer[0][w].create(width);
			for(int h=0; h < _buffer[0][w].getSize() ;h++)
			{
				Pixel to_put;
				to_put.character = '\0';
				to_put.fore_color = LIGHTGRAY;
				to_put.back_color = BLACK;
				_buffer[0][w].push(to_put);
			}
		}

		_buffer[1] = _buffer[0];
	}

	BackBuffer& LG::BackBuffer::operator<<( char datum )
	{
		if(	_y_buffer_pointer < 0				||
			_x_buffer_pointer < 0				||
			_y_buffer_pointer > getHeight()-1	||
			_x_buffer_pointer > getWidth()-1	||
			datum == 0							)
			return *this;

		if(datum == 0)
			datum = 32;
		Pixel new_one;
		new_one.character = datum;
		new_one.fore_color = _fore_pointer;
		new_one.back_color = _back_pointer;

		getBackBuffer()[_y_buffer_pointer][_x_buffer_pointer] = new_one;
		if(++_x_buffer_pointer >= getWidth())
		{
			_x_buffer_pointer = 0;
			_y_buffer_pointer++;
		}

		return *this;
	}

	BackBuffer& LG::BackBuffer::operator<<( const char* string )
	{
		char chr=0;
		while(chr = *string++)
			operator<<(chr);

		return *this;
	}

	void LG::BackBuffer::setXBufferPointer( int new_x_buffer_pointer ) 
	{
		_x_buffer_pointer = new_x_buffer_pointer;
	}

	void LG::BackBuffer::setYBufferPointer( int new_y_buffer_pointer )
	{
		_y_buffer_pointer = new_y_buffer_pointer;
	}

	void LG::BackBuffer::setBufferPointer( int new_x, int new_y )
	{
		setXBufferPointer(new_x);
		setYBufferPointer(new_y);
	}

	int LG::BackBuffer::getXBufferPointer() const
	{
		return _x_buffer_pointer;
	}

	int LG::BackBuffer::getYBufferPointer() const
	{
		return _y_buffer_pointer;
	}

	void LG::BackBuffer::setForeColor(int new_fore)
	{
		if( ! _is_color_locked)
			_fore_pointer = new_fore;
	}

	void LG::BackBuffer::setBackColor(int new_back)
	{
		if( ! _is_color_locked)
			_back_pointer = new_back;
	}

	void LG::BackBuffer::setColor( int new_fore, int new_back )
	{
		setForeColor(new_fore);
		setBackColor(new_back);
	}

	void LG::BackBuffer::setColorLock(bool locking)
	{
		_is_color_locked = locking;
	}

	void LG::BackBuffer::readyBufferToDraw()
	{
		setXBufferPointer(0);
		setYBufferPointer(0);
		setColor(LIGHTGRAY, BLACK);
		
		Pixel p;
		p.character = ' ';
		p.fore_color = 0;
		p.back_color = 0;
		fill(p);
	}

	int LG::BackBuffer::getWidth() const
	{
		int min = 99999999;
		const Buffer& back = getBackBuffer();
		for(int n=0; n < back.getLength() ;n++)
			if(back[n].getLength() < min)
				min = back[n].getLength();

		return min;
	}

	int LG::BackBuffer::getHeight() const
	{
		return getBackBuffer().getLength();
	}

	void LG::BackBuffer::release()
	{
		_buffer[0].release();
		_buffer[1].release();

		readyBufferToDraw();
	}

	void LG::BackBuffer::draw()
	{
		Buffer& front = getFrontBuffer(),
			back = getBackBuffer();

		for(int h=0; h < back.getLength() ;h++)
			for(int w=0; w < back[h].getLength() ;w++)
			{
				Pixel& new_p = back[h][w],
					& old_p = front[h][w];
				bool is_new_one_korean = (new_p.character & 0x80) == 0x80;

				//	HiddenPixel 조사:
				//		HiddenPixel이란:
				//			2BYTE문자는 앞과 뒤 바이트(= 픽셀)이 한 몸으로 이루어져 있기 때문에,
				//			둘 중 하나만 찍히면 제대로 출력이 되지 않는다.
				//			그런데 새로 갱신된 문자가 하필히면 앞 바이트가 동일하게 된 경우는
				//			뒷 문자만 cout 출력이 되므로 제대로 된 출력이 안된다.
				//
				//		해결방법:
				//			픽셀이 같으면 뛰어넘는 코드에서, 2BYTE 문자라고 추정되는 경우(sign bit이 1)
				//			next pixel 까지도 검색을 한번에 수행한다.
				//			둘 중 하나라도 갱신이 필요한 경우는 둘 모두를 출력한다.
				if(is_new_one_korean && w < back[h].getLengthLastIndex())
				{
					Pixel&	next_new = back[h][w+1],
						next_old = front[h][w+1];
					if(	next_new != next_old	||
						new_p != old_p			)
					{
						Core::setCursorTo(w, h);
						Core::setColor(new_p.fore_color, new_p.back_color);
						std::cout << new_p.character << next_new.character;						
						next_old = next_new;
						old_p = new_p;
					}
					w++;
				}
				else if(new_p != old_p)
				{
					Core::setCursorTo(w, h);
					Core::setColor(new_p.fore_color, new_p.back_color);
					std::cout << new_p.character;
				}
			}

			_swapBuffer();
	}

	void BackBuffer::fill(const Pixel& pixel)
	{
		Buffer& buf = getBackBuffer();
		for(int r=0; r < buf.getLength() ;r++)
			for(int c=0; c < buf[r].getLength() ; c++)
				buf[r][c] = pixel;
	}

	bool BackBuffer::isColorLocked() const
	{
		return _is_color_locked;
	}

}
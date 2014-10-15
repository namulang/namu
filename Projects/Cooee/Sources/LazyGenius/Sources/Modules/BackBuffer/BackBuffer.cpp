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

	void LG::BackBuffer::setForeColor( int new_fore )
	{
		_fore_pointer = new_fore;
	}

	void LG::BackBuffer::setBackColor( int new_back )
	{
		_back_pointer = new_back;
	}

	void LG::BackBuffer::setColor( int new_fore, int new_back )
	{
		setForeColor(new_fore);
		setBackColor(new_back);
	}

	void LG::BackBuffer::readyBufferToDraw()
	{
		setXBufferPointer(0);
		setYBufferPointer(0);
		setColor(LIGHTGRAY, BLACK);
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
				if(new_p == old_p)
					continue;

				old_p = new_p;
				Core::setCursorTo(w, h);
				Core::setColor(new_p.fore_color, new_p.back_color);
				std::cout << new_p.character;
				if((new_p.character & 0x80) == 0x80)
				{				
					w++;
					Pixel& next_new_p = back[h][w],
						& next_old_p = front[h][w];
					next_old_p = next_new_p;
					std::cout << next_new_p.character;
				}
			}

		_swapBuffer();
	}
}
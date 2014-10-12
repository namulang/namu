#pragma once

#include "../../Includes/Includes.hpp"

namespace LG
{
	using namespace NE;
	class NE_DLL BackBuffer : public NEObject
	{
	public:
		struct Pixel : public NEObject
		{
			char character;
			int fore_color;
			int back_color;
			bool operator==(const Pixel& rhs) const
			{
				return	character == rhs.character &&
					fore_color == rhs.fore_color &&
					back_color == rhs.back_color;
			}
			bool operator!=(const Pixel& rhs) const
			{
				return ! operator==(rhs);
			}
			virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
			{
				return saver;
			}
			virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
			{
				return loader;
			}
			virtual NEObject& clone() const
			{
				return *(new Pixel(*this));
			}
			virtual void release()
			{
				back_color = fore_color = character = 0;
			}
			virtual type_result isValid() const
			{
				return RESULT_SUCCESS;
			}
		};

		template
		class NE_DLL NEArrayTemplate<Pixel>;
		typedef NEArrayTemplate<Pixel> RowBuffer;
		template
		class NE_DLL NEArrayTemplate<RowBuffer>;
		typedef NEArrayTemplate<RowBuffer> Buffer;


		BackBuffer();
		~BackBuffer();

		void toDefault();

		void create(int height, int width);


		BackBuffer& operator<<(char datum);
		BackBuffer& operator<<(const char* string);

		void draw();
		void _fillBuffer();
		Buffer& getBackBuffer()
		{
			return _buffer[getBackBufferIndex()];
		}
		const Buffer& getBackBuffer() const
		{
			return _buffer[getBackBufferIndex()];
		}
		Buffer& getFrontBuffer()
		{
			return _buffer[_focused_buffer_index];
		}
		const Buffer& getFrontBuffer() const
		{
			return _buffer[_focused_buffer_index];
		}
		type_index getBackBufferIndex() const
		{
			return ! _focused_buffer_index ? 1 : 0;
		}
		type_index getFrontBufferIndex() const
		{
			return _focused_buffer_index;
		}
		void _swapBuffer()
		{
			_focused_buffer_index = (_focused_buffer_index+1) % 2;
		}

		void setXBufferPointer(int new_x_buffer_pointer);
		void setYBufferPointer(int new_y_buffer_pointer);
		void setBufferPointer(int new_x, int new_y);
		int getXBufferPointer() const;
		int getYBufferPointer() const;
		void setForeColor(int new_fore);
		void setBackColor(int new_back);
		void setColor(int new_fore, int new_back);
		void readyBufferToDraw();
		Buffer& getBuffer();
		const Buffer& getBuffer() const;
		int getWidth() const;
		int getHeight() const;
		virtual void release();
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
		{
			return saver;
		}
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
		{
			return loader;
		}
		virtual NEObject& clone() const 
		{
			return *(new BackBuffer(*this));
		}
		virtual type_result isValid() const
		{
			return _buffer[0].isValid() && _buffer[1].isValid();
		}

	private:
		int _height,	_width;
		int _x_buffer_pointer, _y_buffer_pointer;
		int _fore_pointer, _back_pointer;

		Buffer _buffer[2];
		int _focused_buffer_index;
	};
}
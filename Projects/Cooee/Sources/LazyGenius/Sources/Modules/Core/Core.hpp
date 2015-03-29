#pragma once

#include "../WindowList/WindowList.hpp"
#include "../BackBuffer/BackBuffer.hpp"

namespace LG
{
	class NE_DLL Core
	{
	public:
		enum SoundList 
		{
			SND_UNDEFINED = -1,
			SND_DEFAULT = 0,
			SND_TICK = SND_DEFAULT,
			SND_CONFIRM,
			SND_TRANSITE,
			SND_BLOCKED
		};
		static void play(SoundList snd) 
		{
			TCHAR* target_name = _T("./fx/tick.wav");

			switch (snd) 
			{
				case SND_CONFIRM:	target_name = _T("./fx/confirm.wav");	break;
				case SND_BLOCKED:	target_name = _T("./fx/blocked.wav");	break;
				case SND_TRANSITE:	target_name = _T("./fx/transite.wav");	break;
			}

			PlaySound(target_name, NULL, SND_FILENAME | SND_ASYNC);
		}
		static void initializeBackBuffer()
		{
			back_buffer.create(80, 25);
		}
		static bool sendKeyPipe()
		{
			if( _kbhit()) {
				inputed = _getch();				
				return true;
			}		

			return false;
		}
		static void collectGarbages(LG::WindowList& windows)
		{
			windows.collectGarbages();
		}
		static void open(Window& window)
		{
			getWindowList().pushFront(window);
		}
		static void setColor(int tcolor, int bcolor)
		{
			if(color_lock) return;
			SetConsoleTextAttribute(output_handle, bcolor << 4 | tcolor);
		}
		static void setColor(WORD color)
		{
			if(color_lock) return;
			SetConsoleTextAttribute(output_handle, color);
		}
		static WORD getColor()
		{
			CONSOLE_SCREEN_BUFFER_INFO cs = {0, };
			GetConsoleScreenBufferInfo(output_handle, &cs);		
			return cs.wAttributes;
		}
		static COORD getCursorPosition()
		{
			CONSOLE_SCREEN_BUFFER_INFO cs = {0, };
			GetConsoleScreenBufferInfo(output_handle, &cs);		
			COORD temp = {cs.dwCursorPosition.X, cs.dwCursorPosition.Y};

			return temp;
		}

		static COORD getMaxCursorPosition()
		{
			CONSOLE_SCREEN_BUFFER_INFO cs = {0, };
			GetConsoleScreenBufferInfo(output_handle, &cs);		
			COORD temp = {cs.dwMaximumWindowSize.X, cs.dwMaximumWindowSize.Y};
			return temp;
		}
		
		static void setColorLock(bool to_lock)
		{
			color_lock = to_lock;
		}

		static void setCursorTo(type_ushort x, type_ushort y)
		{
			x = (x > max_width) ? max_width : x;
			y = (y > max_height) ? max_height : y;
			COORD pos = {x, y};
			SetConsoleCursorPosition(output_handle, pos);
		}
		static void setCursorTo(COORD coord)
		{
			SetConsoleCursorPosition(output_handle, coord);
		}
		static WindowList& getWindowList()
		{
			return *_windows;
		}
		static void setWindowList(WindowList& windows)
		{
			_windows = &windows;
		}
		static WindowList* _windows;
		static HANDLE output_handle;
		static type_ushort max_width;
		static type_ushort max_height;
		static bool color_lock;
		static const int WIDTH;
		static const int HEIGHT;
		static BackBuffer back_buffer;

		static char inputed;
	};
}
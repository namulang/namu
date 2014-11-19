#include "FloatingGliph.hpp"
#include <Windows.h>
#pragma comment(lib, "winmm.lib")

namespace LG
{
	FloatingGliph::FloatingGliph(type_ushort new_x, type_ushort new_y, type_ushort new_width, type_ushort new_height,
		type_ushort new_fore, type_ushort new_back, const NEString& new_text)
		: Gliph(0, new_x, new_y, new_width, new_height, new_fore, new_back, new_text, true)
	{
		term_for_hiding = timeGetTime();
	}
	FloatingGliph::FloatingGliph(const FloatingGliph& rhs)
		: Gliph(rhs), term_for_hiding(rhs.term_for_hiding)
	{

	}

	void FloatingGliph::onDraw()
	{
		if(timeGetTime() - term_for_hiding >= 2500)
			return;

		Gliph::onDraw();
	}

	void FloatingGliph::onKeyPressed(char inputed)
	{
		term_for_hiding = timeGetTime();
	}
}
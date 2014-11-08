#pragma once

#include "../Gliph/Gliph.hpp"

namespace LG
{
	class NE_DLL ListGliph : public Gliph
	{
	public:
		ListGliph(Window* new_owner=0, type_ushort new_x = 0, type_ushort new_y=0, type_ushort new_width=0, type_ushort new_height=0, type_ushort new_fore = LIGHTGRAY, type_ushort new_back = 0, type_ushort new_choosed_fore = BLACK, type_ushort new_choosed_back = WHITE);
		ListGliph(const ListGliph& rhs);

		virtual void onDraw();
		virtual void onUpdateData();
		virtual void onKeyPressed(char inputed);

		type_short choosed;
		NEStringSet items;
		int choosed_fore, choosed_back;
	};
}
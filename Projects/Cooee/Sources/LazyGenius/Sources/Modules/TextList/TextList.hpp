#pragma once

#include "../ListGliph/ListGliph.hpp"
#include "../TextGliph/TextGliph.hpp"

namespace LG
{
	class NE_DLL TextList : public ListGliph
	{
	public:
		TextList(Window* new_owner = 0, type_ushort new_x = 0, type_ushort new_y = 0, type_ushort new_width = 0, type_ushort new_height = 0, type_ushort new_fore = LIGHTGRAY, type_ushort new_back = 0, type_ushort new_choosed_fore = BLACK, type_ushort new_choosed_back = WHITE, bool new_use_matching = false, bool new_use_sound = false);
		TextList(const TextList& rhs);

		virtual void onDraw();
		virtual void onUpdateData();
		virtual void onKeyPressed(int inputed);		

		virtual void onInputed(const NEString& inputed) {}

		TextGliph text;
	};
}

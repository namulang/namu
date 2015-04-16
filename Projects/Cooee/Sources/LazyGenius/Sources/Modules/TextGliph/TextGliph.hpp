#pragma once

#include "../Gliph/Gliph.hpp"

namespace LG
{
	class NE_DLL TextGliph : public Gliph
	{
	public:
		TextGliph(	Window* new_owner=0, type_ushort new_x = 0, type_ushort new_y=0, 
					type_ushort new_width=0, type_ushort new_height=0, type_ushort new_fore = LIGHTGRAY, 
					type_ushort new_back = 0);
		TextGliph(const TextGliph& rhs);
		FUNC_CLONE(TextGliph)

		void makeToHistory();
		virtual void onKeyPressed(int inputed);

		NEStringList history;
		int history_idx;
	};
}
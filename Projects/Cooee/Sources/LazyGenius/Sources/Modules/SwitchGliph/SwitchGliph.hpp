#pragma once

#include "../Gliph/Gliph.hpp"

namespace LG
{
	class NE_DLL SwitchGliph : public Gliph
	{
	public:		
		typedef type_ushort u2;
		SwitchGliph(Window* new_owner = 0, u2 new_x = 0, u2 new_y=0, u2 new_width=3, u2 new_fore = LIGHTGRAY, u2 new_back = 0)
			: Gliph(new_owner, new_x, new_y, new_width, 1, new_fore, new_back),
			nobe(0, x, y, 1, 1, new_back, new_fore), back(0, x, y, width - 1, 1, new_fore, new_back)
		{
			setValue(false);
		} 

		virtual void onUpdateData()
		{
			back.y = nobe.y = y;
			back.fore = nobe.back = fore;
			back.back = nobe.fore = this->Gliph::back;

			if( ! _value)
			{
				nobe.x = x;
				back.x = x + 1;
				back.y = y;
				nobe.text = "X";
			}
			else
			{
				nobe.x = x + width - 1;
				back.x = x;
				nobe.text = "O";
			}
		}
		virtual void onKeyPressed(char inputed)
		{
			switch(inputed)
			{
			case LEFT:
				if(getValue())
					setValue(false, true);
				break;
			case RIGHT:
				if( ! getValue())
					setValue(true, true);
				break;
			}
		}
		virtual void onDraw()
		{
			nobe.onDraw();
			back.onDraw();
		}

		bool getValue() const { return _value; }
		void setValue(bool new_value, bool drawing = false);

		Gliph nobe, back;

	private:
		bool _value;
	};
}
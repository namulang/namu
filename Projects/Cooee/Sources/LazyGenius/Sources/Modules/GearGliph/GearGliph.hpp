#pragma once

#include "../Gliph/Gliph.hpp"

namespace LG
{
	class NE_DLL GearGliph : public Gliph
	{
	public:		
		typedef type_ushort u2;
		GearGliph(Window* new_owner = 0, u2 new_x = 0, u2 new_y=0, u2 new_width=3, u2 new_fore = LIGHTGRAY, u2 new_back = 0)
			: Gliph(new_owner, new_x, new_y, new_width, 1, new_fore, new_back),
			nobe(0, x, y, 3, 1, new_back, new_fore), back(0, x, y, width, 1, new_fore, new_back)
		{
			setValue(0);
		} 

		virtual NEObject& clone() const
		{
			return *(new GearGliph(*this));
		}

		virtual void onUpdateData()
		{
			back.y = nobe.y = y;
			back.fore = nobe.back = fore;
			back.back = nobe.fore = this->Gliph::back;

			int neutral_x = (back.width - nobe.width) / 2;

			if(_value < 0)
			{
				nobe.x = x;
				nobe.text = "<--";
				nobe.back = this->Gliph::back;
				nobe.fore = fore;
			}
			if( ! _value)
			{
				nobe.x = neutral_x;
				nobe.text = "OFF";
				nobe.back = DARKGRAY;
				nobe.fore = LIGHTGRAY;
			}
			else
			{
				nobe.x = x + width - nobe.width;
				nobe.text = "-->";
				nobe.back = this->Gliph::back;
				nobe.fore = fore;
			}
		}
		virtual void onKeyPressed(char inputed)
		{
			switch(inputed)
			{
			case LEFT:
				if(getValue() > 0)
					setValue(0);
				else if(getValue() == 0)
					setValue(-1);
				break;

			case RIGHT:
				if(getValue() < 0)
					setValue(0);
				else if(getValue() == 0)
					setValue(1);
				break;
			}
		}
		virtual void onDraw()
		{
			nobe.onDraw();
			back.onDraw();
		}

		int getValue() const { return _value; }
		void setValue(int new_value)
		{
			_value = new_value;
			onUpdateData();
		}

		Gliph nobe, back;

	private:
		int _value;
	};
}
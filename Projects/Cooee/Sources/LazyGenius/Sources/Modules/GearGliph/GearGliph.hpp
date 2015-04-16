#pragma once

#include "../Gliph/Gliph.hpp"

namespace LG
{
	class NE_DLL GearGliph : public Gliph
	{
	public:		
		typedef type_ushort u2;
		GearGliph(Window* new_owner = 0, u2 new_x = 0, u2 new_y=0, u2 new_width=3, u2 new_fore = LIGHTGRAY, u2 new_back = 0, const NEString& new_text = "")
			: Gliph(new_owner, new_x, new_y, new_width, 1, new_fore, new_back, new_text),
			nobe(0, x, y, 1, 1, new_back, new_fore)
		{
			setValue(false);
		} 

		virtual NEObject& clone() const
		{
			return *(new GearGliph(*this));
		}

		virtual void onUpdateData()
		{	
			switch(_value)
			{
			case -1:
				nobe.x = x;
				nobe.text = "<";
				break;

			case 0:
				nobe.x = (width-1) / 2 + x;
				nobe.text = "O";
				break;

			case 1:
				nobe.x = x + width - 1;
				nobe.text = ">";
				break;
			}
		}
		virtual void onKeyPressed(int inputed)
		{
			switch(inputed)
			{
			case LEFT:
				if(getValue() > 0)
					setValue(0);
				else if( ! getValue())
					setValue(-1);
				break;

			case RIGHT:
				if(getValue() < 0)
					setValue(0);
				else if( ! getValue())
					setValue(1);
				break;
			}
		}
		virtual void onDraw()
		{
			Gliph::onDraw();

			nobe.onDraw();
		}

		int getValue() const { return _value; }
		void setValue(int new_value)
		{
			if(new_value < 0)
				new_value = -1;
			if(new_value > 0)
				new_value = 1;

			_value = new_value;

			onUpdateData();
		}

		Gliph nobe;

	private:
		int _value;
	};
}
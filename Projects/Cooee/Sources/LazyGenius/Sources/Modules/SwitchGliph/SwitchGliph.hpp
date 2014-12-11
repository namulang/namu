#pragma once

#include "../Gliph/Gliph.hpp"

namespace LG
{
	class NE_DLL SwitchGliph : public Gliph
	{
	public:		
		typedef type_ushort u2;
		SwitchGliph(Window* new_owner = 0, u2 new_x = 0, u2 new_y=0, u2 new_width=3, u2 new_fore = LIGHTGRAY, u2 new_back = 0, const NEString& new_text = "")
			: Gliph(new_owner, new_x, new_y, new_width, 1, new_fore, new_back, new_text),
			nobe(0, x, y, 1, 1, new_back, new_fore)
		{
			setValue(false);
		} 

		virtual NEObject& clone() const
		{
			return *(new SwitchGliph(*this));
		}

		virtual void onUpdateData()
		{
			if( ! _value)
			{
				nobe.x = x;
				nobe.text = "X";
			}
			else
			{
				nobe.x = x + width - 1;
				nobe.text = "O";
			}
		}
		virtual void onKeyPressed(char inputed)
		{
			switch(inputed)
			{
			case LEFT:
				if(getValue())
					setValue(false);
				break;
			case RIGHT:
				if( ! getValue())
					setValue(true);
				break;
			}
		}
		virtual void onDraw()
		{
			Gliph::onDraw();

			nobe.onDraw();
		}

		bool getValue() const { return _value; }
		void setValue(bool new_value);

		Gliph nobe;

	private:
		bool _value;
	};
}
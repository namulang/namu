#pragma once

#include "../Gliph/Gliph.hpp"

namespace LG
{
	class NE_DLL Button : public Gliph
	{
	public:
		typedef type_ushort u2;
		Button(	const NEString& new_text = "OK", bool is_focused=false, Window* new_owner=0, u2 new_x=0, u2 new_y=0, u2 new_width=0, u2 new_height=0,
				u2 new_fore = LIGHTGRAY, u2 new_back = BLACK, u2 new_unfocused_fore=UNKNOWN, u2 new_unfocused_back=UNKNOWN,
				u2 new_focused_fore=UNKNOWN, u2 new_focused_back=UNKNOWN)
			: Gliph(new_owner, new_x, new_y, new_width, new_height, new_fore, new_back, new_text), _is_focused(is_focused)
		{
			unfocused_back = new_unfocused_back == UNKNOWN ? new_back : new_unfocused_back;
			unfocused_fore = new_unfocused_fore == UNKNOWN ? new_fore : new_unfocused_fore;
			focused_back = new_focused_back == UNKNOWN ? new_fore : new_focused_back;
			focused_fore = new_focused_fore == UNKNOWN ? new_back : new_focused_fore;
		}
		Button(const Button& rhs)
			: Gliph(rhs), _is_focused(rhs._is_focused), focused_back(rhs.focused_back), focused_fore(rhs.focused_fore),
			unfocused_back(rhs.unfocused_back), unfocused_fore(rhs.unfocused_fore) {}

		FUNC_CLONE(Button)
		FUNC_TO_OWNER(Window)

		type_result setFocus(bool to_be)
		{
			return (to_be ? _focus() : _Unfocus());
		}
		bool isFocused() const { return _is_focused; }
		virtual void onUpdateData()
		{
			if(_is_focused)
			{
				fore = focused_fore;
				back = focused_back;
			}
			else
			{
				fore = unfocused_fore;
				back = unfocused_back;
			}

			Gliph::onUpdateData();
		}

	private:
		type_result _focus();
		type_result _Unfocus();

		bool _is_focused;
		int focused_fore,	focused_back,	
			unfocused_fore,	unfocused_back;
	};
}
#pragma once

#include "../Window/Window.hpp"

namespace LG
{
	template
	class NE_DLL NETList<Window*, true>;

	class NE_DLL WindowList : public NETList<Window*, true>
	{
	public:
		typedef NETList<Window*, true> SuperClass;

		virtual type_index insert(type_index index, const Window* const source) 
		{
			type_index n = SuperClass::insert(index, source);

			getElement(n).onUpdateData();
			if(n == 0)
				getElement(n).onFocused();
			return n;
		}

		virtual type_index remove(type_index index)
		{
			type_index n = SuperClass::remove(index);
			_focusNewWindow();
			return n;
		}
		void _focusNewWindow() {
			Window* itr = 0;
			if(itr = &getElement(0))
				itr->onFocused();
		}
		void collectGarbages();
		void draw();
	};
}
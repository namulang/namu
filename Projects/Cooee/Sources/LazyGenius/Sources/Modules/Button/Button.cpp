#include "Button.hpp"
#include "../Window/Window.hpp"

namespace LG
{
	type_result LG::Button::_focus()
	{
		if( ! owner) return RESULT_TYPE_ERROR;

		GliphList& list = owner->gliphs;

		Button* castable = 0;
		for(GliphList::Iterator* itr=list.getIterator(0); itr ;itr=itr->getNext())
		{
			castable = dynamic_cast<Button*>(&itr->getValue());
			if(	castable		&&
				castable != this)
				castable->_Unfocus();
		}

		_is_focused = true;
		Button::onUpdateData();
		return RESULT_SUCCESS;
	}

	type_result Button::_Unfocus()
	{
		_is_focused = false;
		Button::onUpdateData();
		return RESULT_SUCCESS;
	}
}
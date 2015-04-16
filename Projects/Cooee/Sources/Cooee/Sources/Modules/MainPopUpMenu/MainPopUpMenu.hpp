#pragma once

#include "../../Includes/Includes.hpp"

class MainPopUpMenu : public LG::ListWindow
{
public:
	MainPopUpMenu(Window& new_caller);
	FUNC_CLONE(MainPopUpMenu)

	virtual void onUpdateData();
	virtual void onKeyPressed(int inputed);
	virtual void onItemChoosed(type_index index, const NEString& chosen_content);

	Window& caller;
};
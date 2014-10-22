#pragma once

#include "../MainPopUpMenu/MainPopUpMenu.hpp"

class EditPopUpMenu : public LG::ListWindow
{
public:
	EditPopUpMenu();
	FUNC_CLONE(EditPopUpMenu)
	FUNC_TO_CALLER(MainPopUpMenu)

	virtual void onUpdateData();
	virtual void onItemChoosed(type_index index, const NEString& chosen_content);
};
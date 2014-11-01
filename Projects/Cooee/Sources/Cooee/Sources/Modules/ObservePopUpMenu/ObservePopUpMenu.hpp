#pragma once

#include "../MainPopUpMenu/MainPopUpMenu.hpp"

class ObservePopUpMenu : public LG::ListWindow
{
public:
	ObservePopUpMenu();
	FUNC_CLONE(ObservePopUpMenu)
	FUNC_TO_CALLER(MainPopUpMenu)
	
	virtual void onUpdateData();
	virtual void onItemChoosed(type_index item_index, const NEString& chosen_content);
};
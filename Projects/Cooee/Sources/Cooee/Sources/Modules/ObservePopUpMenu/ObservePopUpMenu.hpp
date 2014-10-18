#pragma once

#include "../../Includes/Includes.hpp"

class ObservePopUpMenu : public LG::ListWindow
{
public:
	ObservePopUpMenu();
	FUNC_CLONE(ObservePopUpMenu)
	
	virtual void onUpdateData();
	virtual void onItemChoosed(type_index item_index, const NEString& chosen_content);
};
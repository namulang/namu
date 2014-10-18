#pragma once

#include "../../Includes/Includes.hpp"

class HelpPopUpMenu : public LG::ListWindow
{
public:
	HelpPopUpMenu();
	FUNC_CLONE(HelpPopUpMenu)

	virtual void onUpdateData();
	virtual void onItemChoosed(type_index item_index, const NEString& chosen_content);
};
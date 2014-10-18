#pragma once

#include "../../Includes/Includes.hpp"

class RunDebuggingPopUpMenu : public LG::ListWindow
{
public:
	RunDebuggingPopUpMenu();
	FUNC_CLONE(RunDebuggingPopUpMenu)

	virtual void onUpdateData();
	virtual void onItemChoosed(type_index item_index, const NEString& chosen_content);
};
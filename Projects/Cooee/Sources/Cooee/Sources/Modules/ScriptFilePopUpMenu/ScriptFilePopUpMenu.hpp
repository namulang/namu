#pragma once

#include "../../Includes/Includes.hpp"

class ScriptFilePopUpMenu : public LG::ListWindow
{
public:
	ScriptFilePopUpMenu();
	FUNC_CLONE(ScriptFilePopUpMenu)

	virtual void onUpdateData();
	virtual void onItemChoosed(type_index index, const NEString& chosen_content);
};
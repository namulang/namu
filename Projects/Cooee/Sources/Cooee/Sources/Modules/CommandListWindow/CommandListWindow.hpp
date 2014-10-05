#pragma once

#include "../../Includes/Includes.hpp"

class CommandListWindow : public LG::ListWindow
{
public:
	CommandListWindow()
		: LG::ListWindow("Command List", 15, 4, 10, 10, BLACK, WHITE, WHITE, BROWN) {}

	FUNC_CLONE(CommandListWindow)
	virtual void onUpdateData();

	virtual void onItemChoosed(type_index item_index, const NEString& chosen_content);
};
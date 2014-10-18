#pragma once

#include "../../Includes/Includes.hpp"

class CommandInputWindow : public LG::InputWindow
{
public:
	CommandInputWindow();

	FUNC_CLONE(CommandInputWindow)
	virtual void onInputed();
};
#pragma once

#include "../CommandSet/CommandSet.hpp"

class Commander : public CommandSet
{
public:		
	Commander()
		: CommandSet() 
	{
		_initializeCommands();
	}
	Commander(type_count size)
		: CommandSet(size)
	{
		_initializeCommands();
	}
	Commander(const Commander& rhs)
		: CommandSet()
	{
		_initializeCommands();
	}

	NEString command(const NEString& commandline);
	Command& getCommand(const NEString& command_name);

private:
	void _initializeCommands()
	{

	}
};
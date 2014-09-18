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

	NEString command(const NEString& commandline) {

		NEStringSet splited;
		commandline.split(" ", splited);
		if(commandline.getLength() <= 0) return "";
		NEString command_name = commandline[0];
		commandline.remove(0);

		for(int n=0; n < getLength() ; n++) {
			Command& command = getElement(n);
			NEStringSet& names = command.names;

			if(names.find(command_name))
				return command.execute(commandline);
		}

		return command_name + "이란 명령어는 없다구요.\n오타? 아님 착각?";
	}

private:
	void _initializeCommands()
	{

	}
};
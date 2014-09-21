#include "Commander.hpp"
#include "../Core/Core.hpp"

NEString Commander::command(const NEString& commandline)
{
	NEStringSet splited;
	commandline.split(" ", splited);
	if(splited.getLength() <= 0) return "";
	NEString command_name = splited[0];
	splited.popFront();

	for(int n=0; n < getLength() ; n++) 
	{
		Command& command = getElement(n);
		NEStringSet& names = command.names;

		if(names.find(command_name))
		{
			NEString result = command.execute(splited);
			if(result.extract(0, 5) == "ERROR:")
				::Core::pushMessage(result);
		}
	}

	return command_name + "이란 명령어는 없다구요.\n오타? 아님 착각?";
}
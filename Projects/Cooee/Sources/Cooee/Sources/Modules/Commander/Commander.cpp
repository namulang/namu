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

		if(names.find(command_name) >= 0)
		{
			NEString result = command.execute(splited);
			if(result.extract(0, 5) == "ERROR:")
				::Core::pushMessage(result);
		}
	}

	return command_name + "이란 명령어는 없다구요.\n오타? 아님 착각?";
}

Command& Commander::getCommand(const NEString& command_name)
{
	for(int n=0; n < getLength(); n++)
		if(getElement(n).names.find(command_name) != NE_INDEX_ERROR)
			return getElement(n);

	Command* nullpointer = 0x00;
	return *nullpointer;
}

void Commander::_initializeCommands()
{
	create(17);
	push(HelpCommand());
	push(ListCommand());
	push(CloseCommand());
	push(VersionCommand());
	push(PlanetarizeCommand());

	push(CopyCommand());
	push(AddCommand());
	push(DeleteCommand());
	push(PasteCommand());
	push(RunCommand());

	push(SaveCommand());
	push(LoadCommand());
	push(NewCommand());
	push(HeaderCommand());
	push(CutCommand());

	push(ObserveCommand());
	push(ExitCommand());
}

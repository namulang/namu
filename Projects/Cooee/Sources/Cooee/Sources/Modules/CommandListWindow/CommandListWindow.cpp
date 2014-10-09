#include "CommandListWindow.hpp"
#include "../Core/Core.hpp"

void CommandListWindow::onUpdateData()
{
	ListWindow::onUpdateData();

	type_count command_count = ::Core::commander.getLength();
	list.items.create(command_count);
	for(int n=0; n < command_count ;n++)
		list.items.push(::Core::commander[n].names[0]);
}

void CommandListWindow::onItemChoosed(type_index item_index, const NEString& chosen_content)
{
	LG::Core::open(LG::MessageWindow(::Core::commander.getCommand(chosen_content).help, 
		WHITE, MAGENTA, "   OK", 10, 8, 60, 9));
}
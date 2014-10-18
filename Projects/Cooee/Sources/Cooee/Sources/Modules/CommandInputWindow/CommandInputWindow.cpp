#include "CommandInputWindow.hpp"
#include "../Core/Core.hpp"

CommandInputWindow::CommandInputWindow()
: LG::InputWindow("실행할 명령어를 입력하세요. (잘 모르면 help를 입력하세요)", WHITE, DARKGRAY, "") 
{
	for(int n=0; n < ::Core::commander.getLength() ;n++)
		input.history.push(::Core::commander[n].names[0]);		
}

void CommandInputWindow::onInputed()
{
	::Core::commander.command(input.text);
	delete_me = true;
}
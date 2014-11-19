#include "HelpPopUpMenu.hpp"
#include "../Core/Core.hpp"

void HelpPopUpMenu::onUpdateData()
{
	list.items.create(3);
	list.items.push("콘솔명령어 목록 > ");
	list.items.push("모듈 사전 > ");
	list.items.push("초보자를 위한 가이드 > ");
}

void HelpPopUpMenu::onItemChoosed(type_index item_index, const NEString& chosen_content)
{
	switch(item_index)
	{
	case 0:
		::Core::commander.command("help -command");
		break;

	case 1:
		::Core::commander.command("help -module");
		break;

	case 2:
		::Core::commander.command("help");
		break;
	}

	getCaller().delete_me = delete_me = true;
}

HelpPopUpMenu::HelpPopUpMenu()
: LG::ListWindow("도움말 > ", 30, 8, 24, 6, BLACK, WHITE, BLACK, YELLOW)
{

}
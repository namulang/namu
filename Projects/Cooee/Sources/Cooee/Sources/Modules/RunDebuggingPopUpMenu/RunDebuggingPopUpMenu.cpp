#include "RunDebuggingPopUpMenu.hpp"

RunDebuggingPopUpMenu::RunDebuggingPopUpMenu()
: LG::ListWindow("실행 & 디버깅 > ", 30, 8, 15, 5, BLACK, WHITE, WHITE, LIGHTBLUE)
{

}

void RunDebuggingPopUpMenu::onUpdateData()
{
	list.items.create(3);
	list.items.push("실행");
	list.items.push("한 프레임 디버깅");
	list.items.push("디버깅 종료");
}

void RunDebuggingPopUpMenu::onItemChoosed(type_index item_index, const NEString& chosen_content)
{

}
#include "ObservePopUpMenu.hpp"
#include "../Core/Core.hpp"

ObservePopUpMenu::ObservePopUpMenu()
: LG::ListWindow("관측 > ", 30, 8, 19, 5, BLACK, WHITE, WHITE, LIGHTGREEN)
{

}

void ObservePopUpMenu::onUpdateData()
{
	list.items.create(2);
	list.items.push("플라네타리움");
	NEEventHandler& handler = Editor::getInstance().getEventHandler();
	if(	handler.getHeader().getName() == "CooeeHandler"	&&
		handler.getHeader().getDeveloper() == "kniz"	)
		if( ::Core::isObservingDebug() )
			list.items.push("스크립트 영역 관측");
		else
			list.items.push("테스트 영역 관측");			
}

void ObservePopUpMenu::onItemChoosed(type_index item_index, const NEString& chosen_content)
{
	NEEventHandler& handler = Editor::getInstance().getEventHandler();

	switch(item_index)
	{
	case 0:	//	플라네타리움
		::Core::commander.command("planetarium");
		toCaller().delete_me = delete_me = true;
		break;

	case 1:	//	관측
		::Core::commander.command("observe");
		toCaller().delete_me = delete_me = true;
		break;
	}
}

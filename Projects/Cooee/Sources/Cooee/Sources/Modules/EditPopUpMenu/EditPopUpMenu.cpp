#include "EditPopUpMenu.hpp"
#include "../HeaderModifier/HeaderModifier.hpp"
#include "../Core/Core.hpp"

void EditPopUpMenu::onUpdateData()
{
	list.items.create(5);
	list.items.push("여기에 추가");
	list.items.push("이거 삭제");
	list.items.push("여기에 복사");
	list.items.push("이걸 잘라내기");	
	list.items.push("여기에 붙여넣기");
}

void EditPopUpMenu::onItemChoosed(type_index index, const NEString& chosen_content)
{
	NEEventHandler& handler = Editor::getInstance().getEventHandler();

	Window& caller = toCaller().caller;

	switch(index)
	{
	case 0:	//	여기에 추가
		caller.onKeyPressed(ADD);
		toCaller().delete_me = delete_me = true;
		break;

	case 1:	//	이거 삭제
		caller.onKeyPressed(REMOVE);
		toCaller().delete_me = delete_me = true;
		break;

	case 2:	//	여기에 복사
		caller.onKeyPressed(COPY);
		toCaller().delete_me = delete_me = true;
		break;

	case 3:	//	이걸 잘라내기
		caller.onKeyPressed(CUT);
		toCaller().delete_me = delete_me = true;
		break;

	case 4:	//	여기에 붙여넣기
		caller.onKeyPressed(PASTE);
		toCaller().delete_me = delete_me = true;
		break;
	}
}

EditPopUpMenu::EditPopUpMenu()
: LG::ListWindow("편집 > ", 30, 8, 17, 8, BLACK, WHITE, WHITE, LIGHTGRAY)
{

}

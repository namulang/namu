#include "ScriptFilePopUpMenu.hpp"
#include "../HeaderModifier/HeaderModifier.hpp"
#include "../Core/Core.hpp"

void ScriptFilePopUpMenu::onUpdateData()
{
	list.items.create(4);
	list.items.push("새로 시작");
	list.items.push("불러오기");
	list.items.push("저장하기");
	list.items.push("헤더 관리");
}

void ScriptFilePopUpMenu::LoadScript::onItemChoosed(type_index chosen, const NEString& content)
{
	if (chosen < 0) return;
	if (!&content) return;

	::Core::commander.command("load " + content);

	delete_me = true;

	if(&getCaller())
		getCaller().delete_me = true;
}

void ScriptFilePopUpMenu::SaveScript::onInputed()
{
	::Core::commander.command("save " + input.text);

	delete_me = true;

	if(&getCaller())
		getCaller().delete_me = true;
}

void ScriptFilePopUpMenu::onItemChoosed(type_index index, const NEString& chosen_content)
{
	NEEventHandler& handler = Editor::getInstance().getEventHandler();

	switch(index)
	{
	case 0:	//	새로 시작		
		::Core::commander.command("new");
		break;

	case 1:	//	불러 오기
		call( LoadScript() );
		break;

	case 2:	//	저장하기
		call(SaveScript(Kernal::getInstance().getScriptManager().getScriptFilePath()) );
		break;

	case 3:	//	헤더 관리
		call(HeaderModifier());
		delete_me = true;
		break;
	}
}

ScriptFilePopUpMenu::ScriptFilePopUpMenu()
: LG::ListWindow("스크립트 파일 > ", 30, 8, 11, 7, BLACK, WHITE, WHITE, LIGHTCYAN)
{

}

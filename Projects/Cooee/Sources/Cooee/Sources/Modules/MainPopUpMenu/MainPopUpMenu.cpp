#include "MainPopUpMenu.hpp"
#include "../ScriptFilePopUpMenu/ScriptFilePopUpMenu.hpp"
#include "../RunDebuggingPopUpMenu/RunDebuggingPopUpMenu.hpp"
#include "../ObservePopUpMenu/ObservePopUpMenu.hpp"
#include "../HelpPopUpMenu/HelpPopUpMenu.hpp"
#include "../CommandInputWindow/CommandInputWindow.hpp"
#include "../EditPopUpMenu/EditPopUpMenu.hpp"
#include "../Really/Really.hpp"
#include "../Core/Core.hpp"

void MainPopUpMenu::onUpdateData()
{
	ListWindow::onUpdateData();

	list.items.create(9);
	list.items.push("스크립트 파일 >");	
	/*
		list.items.push("새로 시작");
		list.items.push("불러오기");
		list.items.push("저장하기");		
		list.items.push("헤더 관리");
	*/		
	list.items.push("편집 > ");
	/*
		list.items.push("여기에 추가");
		list.items.push("이거 삭제");
		list.items.push("복사");
		list.items.push("잘라내기");
		list.items.push("붙여넣기");		
	*/
	list.items.push("실행 & 디버깅 >");
	/*
		list.items.push("실행");
		list.items.push("한 프레임 디버깅");
		list.items.push("디버깅 종료");
	*/
	list.items.push("관측 > ");
	/*
		list.items.push("플라네타리움");			
		list.items.push("관측 영역 전환");
	*/
	list.items.push("콘솔 윈도우");
	list.items.push("--------");
	list.items.push("도움말 >");
	list.items.push("--------");
	list.items.push("뒤로가기");
}


void MainPopUpMenu::onKeyPressed(char inputed)
{
	ListWindow::onKeyPressed(inputed);

	const NEString& chosen = list.items[list.choosed];

	switch(inputed)
	{
	case UP:		
		if(chosen == "--------")
			list.choosed--;
		break;
	case DOWN:
		if(chosen == "--------")
			list.choosed++;
		break;
	}
}

void MainPopUpMenu::onItemChoosed(type_index index, const NEString& chosen_content)
{ 
	switch(index)
	{
	case 0:	//	스크립트 파일 >
		call(ScriptFilePopUpMenu());
		break;

	case 1:	//	편집 >
		call(EditPopUpMenu());
		break;

	case 2:	//	실행 & 디버깅 >
		call(RunDebuggingPopUpMenu());
		break;

	case 3:	//	관측 >
		call(ObservePopUpMenu());
		break;

	case 4:	//	콘솔 윈도우
		call(CommandInputWindow());
		break;

	case 6:	//	현자의 말
		call(HelpPopUpMenu());
		break;

	case 8:	//	뒤로가기
		if(LG::Core::getWindowList().getLength() <= 2)
			::Core::commander.command("exit");
		else
			LG::Core::getWindowList()[1].delete_me = true;
		delete_me = true;
		break;		
	}
}

MainPopUpMenu::MainPopUpMenu(Window& new_caller)
	: LG::ListWindow("Main Menu", 20, 5, 20, 12, BLACK, WHITE, WHITE, LIGHTRED), 
	caller(new_caller)
{

}

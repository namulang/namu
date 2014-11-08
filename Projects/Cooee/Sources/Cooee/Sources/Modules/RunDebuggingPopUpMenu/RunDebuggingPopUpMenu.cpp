#include "RunDebuggingPopUpMenu.hpp"
#include "../Core/Core.hpp"

RunDebuggingPopUpMenu::RunDebuggingPopUpMenu()
: LG::ListWindow("실행 & 디버깅 > ", 30, 8, 15, 5, BLACK, WHITE, WHITE, LIGHTBLUE)
{

}

void RunDebuggingPopUpMenu::onUpdateData()
{
	list.items.create(3);
	bool is_test_running = Editor::getInstance().getEventHandler().isTestRunning();
	if(is_test_running)
		list.items.push("계속 디버깅");
	else
		list.items.push("새롭게 디버깅");
	if(is_test_running)
		list.items.push("특정 횟수만 계속 디버깅");
	else
		list.items.push("특정 횟수만 새롭게 디버깅");
	list.items.push("디버깅 종료");
}

void RunDebuggingPopUpMenu::onItemChoosed(type_index item_index, const NEString& chosen_content)
{
	switch(item_index)
	{
	case 0:    //    계속 / 새롭게 디버깅
		if(chosen_content == "계속 디버깅")
			::Core::commander.command("run");
		else
			::Core::commander.command("run -new");
		break;

	case 1:    //    특정 횟수만 디버깅    
		class DebuggingCount : public LG::InputWindow
		{
		public:
			DebuggingCount(bool is_debugging_newly) 
				: LG::InputWindow("스크립트를 몇 번 실행할지 횟수를 지정하세요.", WHITE, LIGHTRED, "1"),
				_is_debugging_newly(is_debugging_newly) {}
			virtual NEObject& clone() const
			{
				return *(new DebuggingCount(*this));
			}

			virtual void onInputed()
			{
				int count = input.text.toInt();

				NEString command = "run ";
				if(_is_debugging_newly)
					command += "-new ";

				::Core::commander.command(command + count);

				getCaller().delete_me = delete_me = true;
			}

			bool _is_debugging_newly;
		};

		if(chosen_content == "특정 횟수만 계속 디버깅")
			call(DebuggingCount(false));
		else
			call(DebuggingCount(true));
		break;        

	case 2:    //    디버깅 종료
		::Core::commander.command("run -stop");
		delete_me = true;
		break;
	}
}
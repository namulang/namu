#include "NodeSetTerminal.hpp"
#include "../ModuleEncyclo/ModuleEncyclo.hpp"
#include "../Core/Core.hpp"
#include "../NodeTerminal/NodeTerminal.hpp"

class NodeNameInputWindow : public ::LG::InputWindow
{
public:
	NodeNameInputWindow(const NEString& default_string) : InputWindow("새로운 키의 이름을 입력해주시기 바랍니다.", BLACK, LIGHTCYAN, default_string) {}

	FUNC_TO_CALLER(NodeSetTerminal)
	FUNC_CLONE(NodeNameInputWindow)

	virtual void onInputed()
	{
		toCaller().real_key->getName() = input.text;
		delete_me = true;
	}
};

void NodeSetTerminal::ContentList::onKeyPressed(char inputed) 
{
	ListGliph::onKeyPressed(inputed);

	switch(inputed) 
	{
	case ADD:
		break;

	case CONFIRM:
		{
			if(text == "" || text.getLength() <= 0)
				text = toOwner()->contents.createCommand();

			type_index	choosed = toOwner()->contents.choosed,
				index = toOwner()->real_key ? choosed-1 : choosed;
			if(index == -1)
				toOwner()->call(NodeNameInputWindow(toOwner()->real_key->getName()));
			else
				LG::Core::windows.pushFront(NodeTerminal(toOwner()->getPath() + "/" + index));
			return;
		}
		break;

	case CANCEL:
		class Really : public ::LG::QueryWindow
		{
		public:
			Really()
				: QueryWindow("종료할려고요? 이렇게 재밌는 프로그램을 놔두고?", WHITE, LIGHTBLUE)
			{
				panel.text = "그만할래ㅜ";
				panel.width = 15;
				no.text = "버튼을 잘못 눌렀음";
				no.width = 20;
			}
			virtual void onButtonPressed(bool witch_button)
			{
				if(witch_button)
					getCaller().delete_me = delete_me = true;

				delete_me = true;
			}
			NEObject& clone() const { return *(new Really(*this)); }
		};

		if(LG::Core::windows.getLength() == 1)
			toOwner()->call(Really());
		else
			toOwner()->delete_me = true;		
		break;

	case REMOVE:
		NEString& msg = ::Core::commander.command(NEString("remove ") + choosed);
		if(msg.getLength() > 0)
			Core::pushMessage(msg);
		break;
	}			


}
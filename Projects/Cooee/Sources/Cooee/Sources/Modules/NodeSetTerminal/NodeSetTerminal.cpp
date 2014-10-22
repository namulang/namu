#include "NodeSetTerminal.hpp"
#include "../ModuleEncyclo/ModuleEncyclo.hpp"
#include "../Core/Core.hpp"
#include "../NodeTerminal/NodeTerminal.hpp"
#include "../MainPopUpMenu/MainPopUpMenu.hpp"
#include "../Really/Really.hpp"

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

	type_index	choosed = toOwner()->contents.choosed,
				index	= toOwner()->real_key ? choosed-1 : choosed;
	NEString path = toOwner()->getPath() + "/" + choosed;

	switch(inputed) 
	{
	case CONFIRM:
		{
			if(text == "" || text.getLength() <= 0)
				text = toOwner()->contents.createCommand();

			if(index == -1)
				toOwner()->call(NodeNameInputWindow(toOwner()->real_key->getName()));
			else
				LG::Core::windows.pushFront(NodeTerminal(toOwner()->getPath() + "/" + index));
			return;
		}
		break;

	case CANCEL:
		LG::Core::open(MainPopUpMenu(*toOwner()));
		break;

	case REMOVE:
		if(index >= 0)
			::Core::commander.command(NEString("delete ") + path);
		else
			::Core::commander.command("delete " + toOwner()->getPath());
		toOwner()->onUpdateData();
		break;

	case ADD:
		if(index >= 0)
			::Core::commander.command(NEString("add -node ") + path);
		else
			::Core::commander.command("add -node " + toOwner()->getPath());
		toOwner()->onUpdateData();
		break;

	case COPY:
		if(index >= 0)
			::Core::commander.command("copy " + path);
		else
			::Core::commander.command("copy " + toOwner()->getPath());
		break;

	case PASTE:
		if(index >= 0)
			::Core::commander.command("paste " + path);
		else
			::Core::commander.command("paste " + toOwner()->getPath());
		toOwner()->onUpdateData();
		break;

	case CUT:
		if(index >= 0)
			::Core::commander.command("cut " + path);
		else
			::Core::commander.command("cut " + toOwner()->getPath());
		break;
	}
}

void NodeSetTerminal::onKeyPressed(char inputed)
{
	if(inputed == CLOSE)
	{
		if(LG::Core::windows.getLength() == 1)
			call(Really());
	}
	else
		Terminal::onKeyPressed(inputed);
}

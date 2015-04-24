#include "NodeSetTerminal.hpp"
#include "../ModuleEncyclo/ModuleEncyclo.hpp"
#include "../Core/Core.hpp"
#include "../NodeTerminal/NodeTerminal.hpp"
#include "../MainPopUpMenu/MainPopUpMenu.hpp"
#include "../Really/Really.hpp"
#include "../HeaderModifier/HeaderModifier.hpp"

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

void NodeSetTerminal::ContentList::onKeyPressed(int inputed) 
{
	ListGliph::onKeyPressed(inputed);

	type_index	choosed = toOwner()->contents.choosed,
				index   = toOwner()->real_key ? choosed-1 : choosed;
	if(index > items.getLengthLastIndex()) 
		index = items.getLengthLastIndex();
	NEString	path	= toOwner()->getPath() + "/" + index;

	switch(inputed) 
	{
	case CONFIRM:
		{
			//if(text == "" || text.getLength() <= 0)
			//    text = toOwner()->contents.createCommand();

			if(index == -1)
			{
				if(toOwner()->real_key)
					toOwner()->call(NodeNameInputWindow(toOwner()->real_key->getName()));
			}
			else
				if(items.getLength() > 0)
					::Core::commander.command("list " + toOwner()->getPath() + "/" + index);
			return;
		}
		break;

	case LG::RENAME:
		{
			NENode& chosen = toOwner()->castObject()[index];
			if (!&chosen) {
				::Core::pushMessage(NEString("인덱스 ") + index + NEString("에서 객체를 가져올 수 없었습니다."));
				return;
			}
			NEScriptEditor& se = Editor::getInstance().getScriptEditor();
			NECode new_one(se.getScriptHeader().getMaxCode(NECodeType::NAME));

			if (chosen.getNameCode() <= 0) {
				se.insertCode(++new_one);
				chosen.setCodes(new_one);
			}

			NETString& bank = se.getBanks().getBank(NECodeType::NAME)[chosen.getNameCode()];
			if (! &bank) {
				::Core::pushMessage(NEString("인덱스 ") + index + "에 해당하는 NameBank를 찾을 수 없습니다.");
				return;
			}

			toOwner()->call(HeaderModifier::StringInputWindow(bank));
		}
		break;

	case CANCEL:
		LG::Core::open(MainPopUpMenu(*toOwner()));
		break;

	case REMOVE:
		if(index >= 0 && items.getLength() > 0)
			::Core::commander.command(NEString("delete ") + path);        
		break;

	case ADD:
		if(index >= 0)
			::Core::commander.command(NEString("add -node ") + toOwner()->getPath() + "/" + (index+1));
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
			::Core::commander.command("paste " + toOwner()->getPath() + "/" + (index+1));
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
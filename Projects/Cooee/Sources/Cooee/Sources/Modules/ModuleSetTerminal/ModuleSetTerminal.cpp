#include "ModuleSetTerminal.hpp"
#include "../ModuleEncyclo/ModuleEncyclo.hpp"
#include "../ModuleTerminal/ModuleTerminal.hpp"
#include "../MainPopUpMenu/MainPopUpMenu.hpp"
#include "../NameInputWindow/NameInputWindow.hpp"
#include "../HeaderModifier/HeaderModifier.hpp"

void ModuleSetTerminal::ModuleNameList::onKeyPressed(int inputed) 
{
	ListGliph::onKeyPressed(inputed);

	int index = toOwner()->real_key ? choosed-1 : choosed;
	if (index > items.getLengthLastIndex())
		index = items.getLengthLastIndex();
	NEString	path = toOwner()->getPath() + "/" + index,
				push_path = toOwner()->getPath() + "/" + (index + 1);

	switch(inputed) {
	case CONFIRM:
		{
			const NEModuleSet& ms = Kernal::getInstance().getModuleManager().getModuleSet();

			if(choosed < 0 || choosed > ms.getLengthLastIndex())	return;

			if(index == -1)
				toOwner()->call(NameInputWindow(toOwner()->real_key->getName()));
			else
			{
				if(index <= items.getLengthLastIndex())
					::Core::commander.command("list " + toOwner()->getPath() + "/" + index);
			}
			//LG::Core::getWindowList().pushFront(ModuleEncyclo(false, &toOwner()->castObject()[index]));
		}	
		break;

	case LG::RENAME:
		{
			NEModule& chosen = toOwner()->castObject()[index];
			if (!&chosen) {
				::Core::pushMessage(NEString("선택한 Module을 찾을 수 없었습니다."));
				return;
			}

			NEScriptEditor& se = Editor::getInstance().getScriptEditor();
			NEBank& bank = se.getBanks().getBank(NECodeType::MODULE_NAME);

			if (chosen.getNameCode() == NE_DEFAULT) {
				bank.push(NETString("unamed"));
				chosen.setNameCode(bank.getLengthLastIndex());
			}

			NETString& name = bank[chosen.getNameCode()];
			if (!&bank) {
				::Core::pushMessage("이 노드에 해당하는 NameBank를 찾을 수 없습니다.");
				return;
			}
			toOwner()->call(HeaderModifier::StringInputWindow(name));
		}
		break;

	case CANCEL:
		LG::Core::open(MainPopUpMenu(*toOwner()));
		break;

	case ADD:		
		{
			int index = toOwner()->real_key ? choosed - 1 : choosed;
			NEString path = toOwner()->getPath() + "/";
			NEObject& obj = ::Core::getObjectBy(path);
			NEModuleCodeSet& mcs = static_cast<NEModuleCodeSet&>(obj);
			if( ! obj.isSubClassOf(NEType::NEMODULE_CODESET))
				return;

			LG::Core::getWindowList().pushFront(ModuleEncyclo(0, push_path));
		}
		break;

	case REMOVE:
		if(choosed >= 0)
			::Core::commander.command(NEString("delete ") + toOwner()->getPath() + "/" + index);
		break;

	case COPY:
		if(choosed >= 0)
			::Core::commander.command("copy " + path);
		break;

	case CUT:
		if(choosed >= 0)
			::Core::commander.command("cut " + path);
		break;

	case PASTE:
		if(choosed >= 0)
			::Core::commander.command("paste " + push_path);
		break;
	}	
}
#include "ModuleSetTerminal.hpp"
#include "../ModuleEncyclo/ModuleEncyclo.hpp"
#include "../ModuleTerminal/ModuleTerminal.hpp"
#include "../MainPopUpMenu/MainPopUpMenu.hpp"
#include "../NameInputWindow/NameInputWindow.hpp"

void ModuleSetTerminal::ModuleNameList::onKeyPressed(int inputed) 
{
	ListGliph::onKeyPressed(inputed);

	int index = toOwner()->real_key ? choosed-1 : choosed;
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
	case CANCEL:
		LG::Core::open(MainPopUpMenu(*toOwner()));
		break;

	case ADD:		
		{	
			NEString path = toOwner()->getPath() + "/";
			NEObject& obj = ::Core::getObjectBy(path);
			NEModuleCodeSet& mcs = static_cast<NEModuleCodeSet&>(obj);
			if( ! obj.isSubClassOf(NEType::NEMODULE_CODESET))
				return;

			path += (choosed < 0 || items.getLength() <= 0) ? mcs.getLength() : choosed + 1;
			LG::Core::getWindowList().pushFront(ModuleEncyclo(0, path));
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
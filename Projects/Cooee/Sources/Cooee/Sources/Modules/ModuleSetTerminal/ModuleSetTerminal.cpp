#include "ModuleSetTerminal.hpp"
#include "../ModuleEncyclo/ModuleEncyclo.hpp"

void ModuleSetTerminal::ModuleNameList::onKeyPressed(char inputed) 
{
	ListGliph::onKeyPressed(inputed);

	switch(inputed) {
	case CONFIRM:
		{
			const NEModuleSet& ms = Kernal::getInstance().getModuleManager().getModuleSet();
		
			if(choosed < 0 || choosed > ms.getLengthLastIndex())	return;

			LG::Core::windows.pushFront(ModuleEncyclo(false, &toOwner()->castObject()[choosed]));
		}	
		break;
	case CANCEL:
		if(LG::Core::windows.getLength() == 1)
			Core::pushMessage("여기가 최상위 노드.\n우리에겐, 더 돌아갈 장소따윈 없어요.");
		else
			toOwner()->delete_me = true;
		break;
	case UP:
	case DOWN:
		onDraw();
	}	
}


#include "KeySetTerminal.hpp"
#include "../Core/Core.hpp"
#include "../MainPopUpMenu/MainPopUpMenu.hpp"
#include "../KeyEncyclo/KeyEncyclo.hpp"

void KeySetTerminal::KeyNameList::onKeyPressed(char inputed)
{
	ListGliph::onKeyPressed(inputed);

	switch(inputed) {
	case CONFIRM:
		{
			NEKeyCodeSet& ks = toOwner()->castObject();
			if(choosed >= 0 || choosed <= items.getLengthLastIndex())				
			{
				if( ! &ks[choosed])
					return;
				if(	ks[choosed].isSubClassOf(NEType::NEMODULE_CODESET_KEY)	||
					ks[choosed].isSubClassOf(NEType::NENODE_CODESET_KEY)	)
					::Core::openModifierFrom(toOwner()->getPath() + "/" + choosed, &ks[choosed]);
				else				
					::Core::openModifierFrom(ks[choosed]);
			}
		}
		break;
	case CANCEL:
		LG::Core::open(MainPopUpMenu());
		break;

	case ADD:
		LG::Core::open(KeyEncyclo(toOwner()->getPath() + "/" + choosed));
		break;

	case REMOVE:
		::Core::commander.command(NEString("delete ") + toOwner()->getPath() + "/" + choosed);
		break;
	}	
}
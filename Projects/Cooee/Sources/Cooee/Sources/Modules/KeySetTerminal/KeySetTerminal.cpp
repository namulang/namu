#include "KeySetTerminal.hpp"
#include "../Core/Core.hpp"
#include "../MainPopUpMenu/MainPopUpMenu.hpp"
#include "../KeyEncyclo/KeyEncyclo.hpp"

void KeySetTerminal::KeyNameList::onKeyPressed(char inputed)
{
	ListGliph::onKeyPressed(inputed);

	NEString path = toOwner()->getPath() + "/" + choosed;

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
		LG::Core::open(MainPopUpMenu(*toOwner()));
		break;

	case ADD:
		LG::Core::open(KeyEncyclo(path));
		toOwner()->onUpdateData();
		break;

	case REMOVE:
		::Core::commander.command(NEString("delete ") + path);
		toOwner()->onUpdateData();
		break;

	case COPY:
		::Core::commander.command("copy " + path);
		break;

	case PASTE:
		::Core::commander.command("paste " + path);
		toOwner()->onUpdateData();
		break;

	case CUT:
		::Core::commander.command("cut " + path);
		break;
	}	
}
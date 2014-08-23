#include "KeySetTerminal.hpp"
#include "../Core/Core.hpp"

void KeySetTerminal::KeyNameList::onKeyPressed(char inputed)
{
	ListGliph::onKeyPressed(inputed);

	switch(inputed) {
	case CONFIRM:
		{
			NEKeyCodeSet& ks = toOwner()->castObject();
			if(choosed >= 0 || choosed <= items.getLengthLastIndex())				
				if(	ks[choosed].isSubClassOf(NEType::NEMODULE_CODESET_KEY)	||
					ks[choosed].isSubClassOf(NEType::NENODE_CODESET_KEY)	)
					::Core::openModifierFrom(toOwner()->path + "/" + choosed, &ks[choosed]);
				else				
					::Core::openModifierFrom(ks[choosed]);
		}
		break;
	case CANCEL:
		toOwner()->delete_me = true;
		break;

	case UP:
	case DOWN:
		onDraw();
	}	
}
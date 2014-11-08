#include "NodeTerminal.hpp"
#include "../MainPopUpMenu/MainPopUpMenu.hpp"

void NodeTerminal::onKeyPressed(char inputed)
{
	switch(inputed)
	{
	case CANCEL:
		LG::Core::open(MainPopUpMenu(*this));
		break;

	case CLOSE:
		delete_me = true;
		break;

	case LEFT:
		if(focused == 0 && attributes.choosed == 1)
			if(codelist_display_index > -2)
				codelist_display_index--;
		else if(focused > 0)
			focused--;
		break;

	case RIGHT:
		if(focused == 0 && attributes.choosed == 1)
			if(codelist_display_index < castObject().getGroupCode().getLengthLastIndex())
				codelist_display_index++;
		else if(focused < 2)
			focused++;
		break;

	default:
		switch(focused)
		{
		case 0:
			Terminal::onKeyPressed(inputed);
			break;

		case 1:
			ks_terminal.onKeyPressed(inputed);
			break;

		case 2:
			ms_terminal.onKeyPressed(inputed);
			break;
		}
		break;
	}
}

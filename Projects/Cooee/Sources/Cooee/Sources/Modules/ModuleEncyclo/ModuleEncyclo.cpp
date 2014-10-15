#include "ModuleEncyclo.hpp"

void ModuleEncyclo::ModuleList::_focusWhatWantToBrowse()
{
	if( ! want_to_browse) return;

	type_code scr_idx = want_to_browse->getScriptCode();
	if(scr_idx < 0 || scr_idx > items.getLengthLastIndex())	return ;

	choosed = scr_idx;
}

void ModuleEncyclo::ModuleList::onKeyPressed(char inputed) 
{
	ListGliph::onKeyPressed(inputed);

	switch(inputed) 
	{
	case UP:
	case DOWN:
		setPanelsTextByChoosed();
		break;

	case CONFIRM:
		if(toOwner()->isAddingMode())
		{
			const NEModule& selected_module = Kernal::getInstance().getModuleManager().getModuleSet()[choosed];
			if( ! &selected_module) return;
			const NEExportable::ModuleHeader& mh = selected_module.getHeader();

			Core::commander.command("add -module " + 
				mh.getName() + " " + mh.getDeveloper() + " " + mh.getRevision() + " " + 
				toOwner()->path_to_added);
		}
		toOwner()->delete_me = true;
		break;

	case CANCEL:
		toOwner()->delete_me = true;
		break;
	}
}

void ModuleEncyclo::ModuleList::setPanelsTextByChoosed()
{
	const NEModule& t = Kernal::getInstance().getModuleManager().getModuleSet()[choosed];
	if( ! &t)
	{
		toOwner()->content.text = "\n\tThere is no data to display";
		return;
	}

	toOwner()->panel.text = createModulePanelText(t);
	toOwner()->content.text = t.getHeader().getComment();
}

NE::NEString ModuleEncyclo::ModuleList::createModulePanelText( const NEModule& target )
{
	const NEExportable::ModuleHeader& h = target.getHeader();
	return	"\n"
		"\t>\t" + h.getName() + "\n"
		"\t \tby " + h.getDeveloper() + " on " + h.getReleaseDate() + "\n"
		"\n";
}

void ModuleEncyclo::ModuleList::onUpdateData() 
{
	const NEModuleSet& ms = Kernal::getInstance().getModuleManager().getModuleSet();
	items.create(ms.getLength());
	for(int n=0; n < ms.getLength() ;n++)
		items.push(ms[n].getHeader().getName());

	_focusWhatWantToBrowse();
	setPanelsTextByChoosed();
}
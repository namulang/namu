#include "GuideEncyclo.hpp"

void GuideEncyclo::GuideList::onKeyPressed(int inputed) 
{
	ListGliph::onKeyPressed(inputed);

	switch(inputed) 
	{
	case CONFIRM:
		setPanelsTextByChoosed();
		break;

	case CANCEL:
		toOwner()->delete_me = true;
		break;
	}
}

void GuideEncyclo::GuideList::setPanelsTextByChoosed()
{
	const NEModule& t = Kernal::getInstance().getModuleManager().getModuleSet()[choosed];
	if( ! &t)
	{
		toOwner()->content.text = "\n\tThere is no data to display";
		return;
	}

	toOwner()->panel.text = toOwner()->guides[choosed].title;
	toOwner()->content.text = toOwner()->guides[choosed].content;
}

void GuideEncyclo::GuideList::onUpdateData() 
{
	ListGliph::onUpdateData();

	NETArray<Guide>& guides = toOwner()->guides;
	items.create(guides.getLength());

	for(int n=0; n < guides.getLength(); n++)
		items.push(guides[n].title);
}
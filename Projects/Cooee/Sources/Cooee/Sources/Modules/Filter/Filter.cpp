#include "Filter.hpp"
#include "../Planetarium/Planetarium.hpp"

Filter::Filter() 
: LG::ListWindow("", 4, 17, 20, 5, LIGHTGRAY, DARKGRAY)
{			

}

Filter::Filter(const Filter& rhs ) : LG::ListWindow(rhs)
{
}

Filter::~Filter()
{
}

NE::NEString Filter::createModifierStateString( NENodeSelector& filter, type_bool is_user_choosed )
{
	if( ! &filter)
		return "NOT SUPPORTED";

	NEString to_return = ! is_user_choosed ? "[X]" : "[O]";

	return to_return + filter.getTypeName();
}

void Filter::onUpdateData()
{
	LG::ListWindow::onUpdateData();
	NEBooleanSet& switches = toCaller().switches;

	type_count to_create = 1;
	if( &toCaller().getModuleFilter())
		to_create++;
	if( &toCaller().getKeyFilter())
		to_create++;

	list.items.create(to_create);
	NENodeSelector dummy = toCaller().getNodeFilter();	//	getType을 했을때 다형성을 무시하고 NodeSelector가 나오게 하기 위해서
	list.items.push(createModifierStateString(dummy, switches[0]));
	list.items.push(createModifierStateString(toCaller().getModuleFilter(), switches[1]));
	list.items.push(createModifierStateString(toCaller().getKeyFilter(), switches[2]));
}

void Filter::_updateSwitchWhenFilterExisted( NENodeSelector& filter )
{
	NEBooleanSet& switches = toCaller().switches;

	if( ! &filter) return;
	type_index n = 0;
	if(filter.isSubClassOf(NEType::NEKEY_SELECTOR))
		n = 2;
	else if(filter.isSubClassOf(NEType::NEMODULE_SELECTOR))
		n = 1;
	else
		return;	//	여기에 들어오면 안됨.

	type_index other = n == 1 ? 2 : 1;
	if( ! switches[n])
	{
		switches[n] = true;
		switches[0] = true;
		if(switches[other])
			switches[other] = false;
		onUpdateData();
		onDraw();
		toCaller().onUpdateData();
		toCaller().onDraw();
	}
}

void Filter::onKeyPressed( char inputed )
{
	LG::ListWindow::onKeyPressed(inputed);

	NEBooleanSet& switches = toCaller().switches;
	
	switch(inputed)
	{
	case LEFT:
		if( ! switches[list.choosed]) 
			return;
		switches[list.choosed] = false;
		if(list.choosed == 0)
			switches[1] = switches[2] = false;
		onUpdateData();
		onDraw();
		toCaller().onUpdateData();
		toCaller().onDraw();
		break;

	case RIGHT:
		_switchOn();
		break;
	}
}

void Filter::_switchOn()
{
	NEBooleanSet& switches = toCaller().switches;
	switch(list.choosed)
	{
	case 0:
		switches[0] = true;
		onUpdateData();
		onDraw();
		toCaller().onUpdateData();
		toCaller().onDraw();
		break;

	case 1:
		{
			NEModuleSelector& ms = toCaller().getModuleFilter();
			_updateSwitchWhenFilterExisted(ms);
		}
		break;

	case 2:
		{
			NEKeySelector& ks = toCaller().getKeyFilter();
			_updateSwitchWhenFilterExisted(ks);
		}
		break;
	}
}

void Filter::onItemChoosed(type_index item_index, const NEString& chosen_content)
{
	NEBooleanSet& switches = toCaller().switches;
	if( ! switches[item_index])
		_switchOn();
	
	switch(item_index)
	{
	case 0:
		call(Modifier<NENodeSelector>());
		break;

	case 1:
		call(Modifier<NEModuleSelector>());
		break;

	case 2:
		call(Modifier<NEKeySelector>());
		break;
	}
}
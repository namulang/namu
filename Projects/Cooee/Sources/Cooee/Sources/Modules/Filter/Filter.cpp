#include "Filter.hpp"
#include "../Planetarium/Planetarium.hpp"

Filter::Filter() 
: ListWindow("", 4, 17, 10, 8, LIGHTGRAY, DARKGRAY), node_modifier(toCaller().getNodeFilter()), 
module_modifier(0), key_modifier(0), focused_index(-1)
{			
	if(&toCaller().getModuleFilter())
	{
		module_modifier = new Modifier<NEModuleSelector>(toCaller().getModuleFilter());
		module_modifier->owner = this;
	}
	if(&toCaller().getKeyFilter())
	{
		key_modifier = new Modifier<NEKeySelector>(toCaller().getKeyFilter());
		key_modifier->owner = this;
	}
}

Filter::Filter( const Filter& rhs ) : LG::ListWindow(rhs), node_modifier(rhs.node_modifier),
module_modifier(0), key_modifier(0)
{
	if(rhs.module_modifier)
	{
		module_modifier = new Modifier<NEModuleSelector>(*rhs.module_modifier);
		module_modifier->owner = this;
	}
	if(rhs.key_modifier)
	{
		key_modifier = new Modifier<NEKeySelector>(*rhs.key_modifier);
		key_modifier->owner = this;
	}
}

Filter::~Filter()
{
	if(module_modifier)
		delete module_modifier;
	if(key_modifier)
		delete key_modifier;
}

NE::NEString Filter::createModifierStateString( NENodeSelector& filter, type_bool is_user_choosed )
{
	if( ! &filter)
		return "NOT SUPPORTED";

	NEString to_return = ! is_user_choosed ? to_return = "[X]" : to_return = "[O]";

	return to_return + filter.getTypeName();
}

void Filter::onUpdateData()
{
	ListWindow::onUpdateData();
	NEBooleanSet& switches = toCaller().switches;

	type_count to_create = 1;
	if( &toCaller().getModuleFilter())
		to_create++;
	if( &toCaller().getKeyFilter())
		to_create++;

	list.items.create(to_create);
	list.items.push(createModifierStateString(toCaller().getNodeFilter(), switches[0]));
	list.items.push(createModifierStateString(toCaller().getModuleFilter(), switches[1]));
	list.items.push(createModifierStateString(toCaller().getKeyFilter(), switches[2]));

	switch(focused_index)
	{
	case 0:	return node_modifier.onUpdateData();
	case 1: if(module_modifier)	return module_modifier->onUpdateData();
	case 2: if(key_modifier) return key_modifier->onUpdateData();
	}
}

void Filter::onDraw()
{
	ListWindow::onDraw();

	switch(focused_index)
	{
	case 0: return node_modifier.onDraw();
	case 1: if(module_modifier) return module_modifier->onDraw();
	case 2: if(key_modifier) return key_modifier->onDraw();
	}
}

void Filter::_updateSwitchWhenFilterExisted( NENodeSelector& filter )
{
	NEBooleanSet& switches = toCaller().switches;

	if( ! &filter) return;
	type_index n = 0;
	if(filter.isSubClassOf(NEType::NEMODULE_SELECTOR))
		n = 1;
	else if(filter.isSubClassOf(NEType::NEKEY_SELECTOR))
		n = 2;
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
	}
}

void Filter::onKeyPressed( char inputed )
{
	NEBooleanSet& switches = toCaller().switches;
	switch(focused_index)
	{
	case -1:
		switch(inputed)
		{
		case LEFT:
			if( ! switches[focused_index]) 
				return;
			switches[focused_index] = false;
			if(focused_index == 0)
				switches[1] = switches[2] = false;
			onUpdateData();
			onDraw();
			break;

		case RIGHT:
			switch(focused_index)
			{
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

			ListWindow::onKeyPressed(inputed);
			break;
		}
		break;

	case 0: 
		if(inputed == LG::CANCEL)
		{
			focused_index = -1;
			onDraw();
		}
		else
			node_modifier.onKeyPressed(inputed);
		break;

	case 1: 
		if(inputed == LG::CANCEL)
		{
			focused_index = -1;
			onDraw();
		}
		else
			if(module_modifier)
				module_modifier->onKeyPressed(inputed);
		break;

	case 2: 
		if(inputed == LG::CANCEL)
		{
			focused_index = -1;
			onDraw();
		}
		else
			if(key_modifier)
				key_modifier->onKeyPressed(inputed);
		break;
	}
}

void Filter::onItemChoosed( type_index item_index, const NEString& chosen_content )
{
	if(item_index == 1 && ! module_modifier) return;
	if(item_index == 2 && ! key_modifier) return;

	focused_index = item_index;
	onUpdateData();
	onDraw();
}
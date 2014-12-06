#include "Filter.hpp"
#include "../Planetarium/Planetarium.hpp"

namespace 
{
	class NameInputWindow : public ::LG::InputWindow
	{
	public:
		NameInputWindow(const NEString& default_string) : InputWindow("새로운 키의 이름을 입력해주시기 바랍니다.", BLACK, LIGHTCYAN, default_string) {}

		FUNC_TO_CALLER(Filter)
		FUNC_CLONE(NameInputWindow)

		virtual void onInputed()
		{
			Planetarium& planetarium = toCaller().toCaller();
			if(planetarium.specified_filter)
				planetarium.specified_filter->getName() = input.text;
			delete_me = true;
		}
	};
}
Filter::Filter() 
: LG::ListWindow("", 4, 17, 20, 6, LIGHTGRAY, DARKGRAY)
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
	Planetarium& caller = toCaller();
	NEBooleanSet& switches = caller.switches;

	type_count to_create = 1;
	if( &caller.getModuleFilter())
		to_create++;
	if( &caller.getKeyFilter())
		to_create++;

	list.items.create(to_create + 1);
	if(caller.isSelectorModifingMode())
		list.items.push(caller.specified_filter->getName());

	NENodeSelector dummy = caller.getNodeFilter();	//	getType을 했을때 다형성을 무시하고 NodeSelector가 나오게 하기 위해서
	list.items.push(createModifierStateString(dummy, switches[0]));
	if(&caller.getModuleFilter())
		list.items.push(createModifierStateString(caller.getModuleFilter(), switches[1]));
	if(&caller.getKeyFilter())
		list.items.push(createModifierStateString(caller.getKeyFilter(), switches[2]));
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
	type_index	other = n == 1 ? 2 : 1;
	if( ! switches[n])
	{
		switches[n] = true;
		switches[0] = true;
		if(switches[other])
			switches[other] = false;
		onUpdateData();
		toCaller().onUpdateData();
	}
}

void Filter::onKeyPressed( char inputed )
{
	LG::ListWindow::onKeyPressed(inputed);

	NEBooleanSet& switches = toCaller().switches;
	int index = toCaller().specified_filter ? list.choosed-1 : list.choosed;
	
	switch(inputed)
	{
	case LEFT:
		if( ! switches[index]) 
			return;
		switches[index] = false;
		if(index == 0)
			switches[1] = switches[2] = false;
		onUpdateData();
		toCaller().onUpdateData();
		break;

	case RIGHT:
		_switchOn();
		break;
	}
}

void Filter::_switchOn()
{
	NEBooleanSet& switches = toCaller().switches;
	int index = toCaller().specified_filter ? list.choosed-1 : list.choosed;
	switch(index)
	{
	case 0:
		switches[0] = true;
		onUpdateData();
		toCaller().onUpdateData();
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
	int index = toCaller().specified_filter ? item_index-1 : item_index;
	if(index == -1)
	{
		call(NameInputWindow(toCaller().specified_filter->getName()));
		return;
	}

	NEBooleanSet& switches = toCaller().switches;
	if( ! switches[index])
		_switchOn();
	
	switch(index)
	{
	case 0:
		call(Modifier<NENodeSelector>());
		break;

	case 1:		
		{
			NEString parsed = chosen_content.extract(3, chosen_content.getLengthLastIndex());
			if(parsed == NEType::getTypeName(NEType::NEMODULE_SELECTOR))
				call(Modifier<NEModuleSelector>());
			else if(parsed == NEType::getTypeName(NEType::NEKEY_SELECTOR))
				call(Modifier<NEKeySelector>());
		}
		
		break;

	case 2:
		call(Modifier<NEKeySelector>());
		break;
	}
}
#pragma once

#include "../Planet/Planet.hpp"
#include "../Modifier/Modifier.hpp"
#pragma warning(push)
#pragma warning(disable: 4355)

class Filter : public LG::ListWindow
{
public:
	Filter() : ListWindow("", 4, 17, 10, 8, LIGHTGRAY, DARKGRAY),
		node_modifier(toCaller().getNodeFilter()), module_modifier(0), key_modifier(0), focused_index(-1)
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
	~Filter()
	{
		if(module_modifier)
			delete module_modifier;
		if(key_modifier)
			delete key_modifier;
	}
	Filter(const Filter& rhs) : LG::ListWindow(rhs), node_modifier(rhs.node_modifier),
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

	FUNC_CLONE(Filter)
		FUNC_TO_CALLER(Planetarium)

		NEString createModifierStateString(NENodeSelector& filter, type_bool is_user_choosed)
	{
		if( ! &filter)
			return "NOT SUPPORTED";

		NEString to_return = ! is_user_choosed ? to_return = "[X]" : to_return = "[O]";

		return to_return + filter.getTypeName();
	}

	virtual void onUpdateData()
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
	virtual void onDraw()
	{
		ListWindow::onDraw();

		switch(focused_index)
		{
		case 0: return node_modifier.onDraw();
		case 1: if(module_modifier) return module_modifier->onDraw();
		case 2: if(key_modifier) return key_modifier->onDraw();
		}
	}
	void _updateSwitchWhenFilterExisted(NENodeSelector& filter)
	{
		if( ! &filter) return;
		type_index n = 0;
		if(filter.isSubClassOf(NEType::NEMODULE_SELECTOR))
			type_index = 1;
		else if(filter.isSubClassOf(NEType::NEKEY_SELECTOR))
			type_index = 2;
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

	virtual void onKeyPressed(char inputed)
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
						_updateSwitchWhenFilterExisted(&ms);
					}
					break;

				case 2:
					{
						NEKeySelector& ks = toCaller().getKeyFilter();
						_updateSwitchWhenFilterExisted(&ks);
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
	virtual void onItemChoosed(type_index item_index, const NEString& chosen_content)
	{
		if(item_index == 1 && ! module_modifier) return;
		if(item_index == 2 && ! key_modifier) return;

		focused_index = item_index;
		onUpdateData();
		onDraw();
	}

	Modifier<NENodeSelector> node_modifier;
	Modifier<NEModuleSelector>* module_modifier;
	Modifier<NEKeySelector>* key_modifier;
	int focused_index;
};

class Planetarium : public Window
{
public:
	Planetarium(int new_x = 1, int new_y = 1, int new_width = 78, int new_height = 23, int fore = WHITE, int back = BLUE, NENodeSelector* new_specified = 0)
		: Window(), root(this, 0), switches(3), specified_filter(new_specified)
	{
		x = new_x;
		y = new_y;
		width = new_width;
		height = new_height;
		focusing = &root;
		setFocus(root);

		for(int n=0; n < switches.getSize() ;n++)
			switches.push(false);
	}
	Planetarium(const Planetarium& rhs)
		: Window(rhs), root(this, 0), screen_x(rhs.screen_x), screen_y(rhs.screen_y),
		default_key_filter(rhs.default_key_filter), default_module_filter(rhs.default_module_filter), 
		switches(rhs.switches), specified_filter(rhs.specified_filter)
	{
		focusing = &root;
		setFocus(root);
	}

	FUNC_CLONE(Planetarium)

		void synchroSelectors()
	{
		//	내부에서 셀렉터를 사용하는 경우, ModuleFilter, KeyFilter 2개를 사용하게 된다.
		//	이때는 ,ModuleFilter와 KeyFilter의 NodeSelector의 데이터가 틀려지므로 이를 통일 시킨다.

		if(specified_filter) return;

		getKeyFilter().NENodeSelector::operator=(getModuleFilter());
	}

	void getSelectedByFilter(NEArrayTemplate<NEObject*>& selected)
	{
		NEListTemplate<NEObject*> buffer;

		//	현재 어떤 Filter가 활성화 되어있는 지를 판단한다:
		if(switches[2])
			while(NEKey* itr = &getKeyFilter().getKey())
				buffer.push(itr);
		else if(switches[1])
			while(NEModule* itr = &getModuleFilter().getModule())
				buffer.push(itr);
		else if(switches[0])
			while(NENode* itr = &getNodeFilter().getNode())
				buffer.push(itr);
	}

	virtual void onUpdateData()
	{
		synchroSelectors();

		NEArrayTemplate<NEObject*> selected;
		getSelectedByFilter(selected);

		generate(Editor::getInstance().getScriptEditor().getScriptNodes(),);
		root.updateLines(0);
		root.markColor(selected);
	}

	virtual void onKeyPressed(char inputed);

	virtual void onDraw()
	{
		Window::onDraw();

		root.onDraw();
	}

	void generate(NEObject& real_root_object)
	{
		if(root.planets.getLength() <= 0)
			root.generate(real_root_object);
	}
	void setFocus(Planet& planet)
	{
		focusing = &planet;
		setFocus(planet.x, planet.y);
	}
	bool setFocus(NEObject& obj, Planet* targ = 0)
	{
		if( ! targ) targ = &root;

		if(targ->real == &obj)
		{
			setFocus(*targ);
			return true;
		}

		typedef Planet::PlanetList List;		
		List& l = targ->planets;
		for(List::Iterator* itr=l.getIterator(0); itr ;itr=itr->getNext())
			if(setFocus(obj, &itr->getValue())) return true;

		return false;
	}
	void setFocus(int x, int y)
	{
		screen_x = x - (width / 2);
		screen_y = y - (height / 2);
		onDraw();
	}

	NEKeySelector& getKeyFilter()
	{
		if(specified_filter)
		{
			NEKeySelector* nullpointer = 0;
			if(specified_filter->isSubClassOf(NEType::NEKEY_SELECTOR))
				return static_cast<NEKeySelector&>(*specified_filter);

			return *nullpointer;
		}

		return default_key_filter;
	}
	NEModuleSelector& getModuleFilter()
	{
		if(specified_filter)
		{
			NEModuleSelector* nullpointer = 0;
			if(specified_filter->isSubClassOf(NEType::NEMODULE_SELECTOR))
				return static_cast<NEModuleSelector&>(*specified_filter);

			return *nullpointer;
		}

		return default_module_filter;
	}
	NENodeSelector& getNodeFilter()
	{
		if(specified_filter)
			return *specified_filter;

		return default_module_filter;
	}


	Planet root;
	int screen_x, screen_y;
	Planet* focusing;
	NEModuleSelector default_module_filter;
	NEKeySelector default_key_filter;
	NENodeSelector* specified_filter;
	NEBooleanSet switches;
};
#pragma warning(pop)
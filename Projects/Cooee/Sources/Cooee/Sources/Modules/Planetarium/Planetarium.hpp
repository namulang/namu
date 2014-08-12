#pragma once

#include "../Planet/Planet.hpp"
#include "../Modifier/Modifier.hpp"
#include "../Filter/Filter.hpp"
#pragma warning(push)
#pragma warning(disable: 4355)

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
		//	현재 어떤 Filter가 활성화 되어있는 지를 판단한다:
		if(switches[2])
			while(NEKey* itr = &getKeyFilter().getKey())
				selected.push(itr);
		else if(switches[1])
			while(NEModule* itr = &getModuleFilter().getModule())
				selected.push(itr);
		else if(switches[0])
			while(NENode* itr = &getNodeFilter().getNode())
				selected.push(itr);
	}

	virtual void onUpdateData()
	{
		synchroSelectors();

		NEArrayTemplate<NEObject*> selected;
		getSelectedByFilter(selected);

		generate(Editor::getInstance().getScriptEditor().getScriptNodes());
		root.updateLines(0);
		root.markColor(selected);
	}

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
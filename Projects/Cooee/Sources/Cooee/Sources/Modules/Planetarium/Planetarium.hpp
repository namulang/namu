#pragma once

#include "../Planet/Planet.hpp"
#include "../Modifier/Modifier.hpp"
#include "../Filter/Filter.hpp"
#pragma warning(push)
#pragma warning(disable: 4355)

class Planetarium : public Window
{
public:
	Planetarium(NENodeSelector* new_specified = 0, int new_x = 1, int new_y = 1, int new_width = 78, int new_height = 23, int fore = WHITE, int back = BLUE)
		: Window(), root(this, 0), switches(3), specified_filter(new_specified), header(0, new_x+5, new_y+1, new_width-10, 1, BLACK, LIGHTCYAN, "\t~ Planetarium ~")
	{
		regist(1, &header);
		x = new_x;
		y = new_y;
		width = new_width;
		height = new_height;
		focusing = &root;
		setFocus(root);

		for(int n=0; n < switches.getSize() ;n++)
			switches.push(false);
		if(specified_filter)
		{
			header.text += NEString("\tModifying...") + specified_filter->getTypeName();
			switches[0] = true;
			if(specified_filter->isSubClassOf(NEType::NEKEY_SELECTOR))
				switches[2] = true;
			else if(specified_filter->isSubClassOf(NEType::NEMODULE_SELECTOR))
				switches[1] = true;
		}
	}
	Planetarium(const Planetarium& rhs)
		: Window(rhs), root(this, 0), screen_x(rhs.screen_x), screen_y(rhs.screen_y),
		default_key_filter(rhs.default_key_filter), default_module_filter(rhs.default_module_filter), 
		switches(rhs.switches), specified_filter(rhs.specified_filter), header(rhs.header)
	{
		focusing = &root;
		setFocus(root);
		regist(1, &header);
	}

	FUNC_CLONE(Planetarium)

	void synchroSelectors()
	{
		//	내부에서 셀렉터를 사용하는 경우, ModuleFilter, KeyFilter 2개를 사용하게 된다.
		//	이때는 ,ModuleFilter와 KeyFilter의 NodeSelector의 데이터가 틀려지므로 이를 통일 시킨다.

		if(specified_filter) return;

		getKeyFilter().NENodeSelector::operator=(getModuleFilter());
	}

	void getSelectedByFilter(NEListTemplate<NEObject*>& selected)
	{
		//	현재 어떤 Filter가 활성화 되어있는 지를 판단한다:
		if(switches[2])
		{
			NEType::Type backup = getKeyFilter().getManagerType();
			getKeyFilter().setManager(NEType::NESCRIPT_EDITOR);
			while(NEKey* itr = &getKeyFilter().getKey())
				selected.push(itr);
			getKeyFilter().setManager(backup);
		}
		if(switches[1])
		{
			NEType::Type backup = getModuleFilter().getManagerType();
			getModuleFilter().setManager(NEType::NESCRIPT_EDITOR);
			while(NEModule* itr = &getModuleFilter().getModule())
				selected.push(itr);
			getModuleFilter().setManager(backup);
		}
		if(switches[0])
		{
			NEType::Type backup = getNodeFilter().getManagerType();
			getNodeFilter().setManager(NEType::NESCRIPT_EDITOR);
			while(NENode* itr = &getNodeFilter().getNode())
				selected.push(itr);
			getNodeFilter().setManager(backup);
		}
	}

	virtual void onUpdateData();
	virtual void onKeyPressed(char inputed);
	virtual void onFocused();

	virtual void onDraw();

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
	bool isSelectorModifingMode() const 
	{
		return specified_filter != 0x00;
	}

	Gliph header;
	Planet root;
	int screen_x, screen_y;
	Planet* focusing;
	NEModuleSelector default_module_filter;
	NEKeySelector default_key_filter;
	NENodeSelector* specified_filter;
	NEBooleanSet switches;
};
#pragma warning(pop)
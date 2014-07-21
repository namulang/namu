#pragma once

#include "../../Includes/Includes.hpp"

class Planetarium;

class Planet : public Gliph
{
public:
	enum 
	{
		INDENT_X = 4
	};
	struct Position
	{
		int x;
		int y;
	};

	Planet(Planetarium* new_planetarium, Planet* new_parent=0) : Gliph(), planetarium(new_planetarium), parent(new_parent), real(0), is_closed(false) 
	{
		fore = back = LG::UNKNOWN;
	}
	Planet(const Planet& rhs) : Gliph(rhs), planetarium(rhs.planetarium), parent(rhs.parent), planets(rhs.planets), real(rhs.real), is_closed(rhs.is_closed) {}
	FUNC_TO_OWNER(Planet)
		FUNC_CLONE(Planet)

		bool operator==(const Planet& rhs) const
	{
		return &rhs == this;
	}
	bool operator!=(const Planet& rhs) const
	{
		return ! operator==(rhs);
	}

	virtual void onDraw();

	int updateLines(int your_y)
	{
		y = your_y++;
		if(is_closed) return your_y;

		for(PlanetList::Iterator* itr=planets.getIterator(0); itr ;itr=itr->getNext())
			your_y = itr->getValue().updateLines(your_y);

		return your_y;
	}

	bool isPixelInScreen(int x, int y) const;
	void putPixel(int virtual_x, int virtual_y, const NEString& text, int fore=LG::UNKNOWN, int back=LG::UNKNOWN);
	void putPixel(int virtual_x, int virtual_y, char shape, int fore=LG::UNKNOWN, int back=LG::UNKNOWN);

	//	반환값:	마지막에 값이 채워진 라인.
	//			자식의 열은 항상 내 위치 + 4 이기때문에 계산이 가능하다. 따라서 반환할 필요도 없지.
	int generate(NEObject& obj, NEArrayTemplate<NEObject*>& selected, Planet* parent = 0, int your_y = 0)
	{
		planets.release();
		updateMe(obj, parent, your_y);

		//	OBJ Casting 해서 Container 혹은 Module, Key로 뽑아내기
		//	그 구체클래스에 맞게 generate함수를 호출하기
		int n = _generateMorphing(obj, selected);
		markWhenISelected(selected);
		return n;
	}
	void markWhenISelected(NEArrayTemplate<NEObject*>& selected)
	{
		if(selected.find(this) >= 0)
		{
			fore = CYAN;
			back = LIGHTCYAN;
		}		
	}
	int _generateMorphing(NEObject& obj, NEArrayTemplate<NEObject*>& selected)
	{
		if(obj.isSubClassOf(NEType::NEKEY))
			return _generate((NEKey&) obj);
		else if(obj.isSubClassOf(NEType::NEKEY_CODESET))
			return _generate((NEKeyCodeSet&) obj, selected);
		else if(obj.isSubClassOf(NEType::NEMODULE))
			return _generate((NEModule&) obj);
		else if(obj.isSubClassOf(NEType::NEMODULE_CODESET_KEY))
			return _generate((NEModuleCodeSetKey&) obj, selected);
		else if(obj.isSubClassOf(NEType::NEMODULE_CODESET))
			return _generate((NEModuleCodeSet&) obj, selected);
		else if(obj.isSubClassOf(NEType::NENODE))
			return _generate((NENode&) obj, selected);
		else if(obj.isSubClassOf(NEType::NENODE_CODESET))
			return _generate((NENodeCodeSet&) obj, selected);
		else if(obj.isSubClassOf(NEType::NENODE_CODESET_KEY))
			return _generate((NENodeCodeSetKey&) obj, selected);

		return y;
	}
	int _generate(NEKey& key)
	{
		setText(key.getName());
		fore = WHITE;
		back = DARKGRAY;

		return y + 1;
	}
	int _generate(NEKeyCodeSet& keyset, NEArrayTemplate<NEObject*>& selected)
	{
		setText("KeySet");
		fore = BLACK;
		back = LIGHTGRAY;

		int next_vacant = y + 1;
		for(int n=0; n < keyset.getLength() ;n++)
			next_vacant = ((Planet&)planets[planets.push(Planet(planetarium, this))]).generate(keyset[n], selected, this, next_vacant);

		return next_vacant;
	}
	int _generate(NEModule& module)
	{
		setText(module.getHeader().getName());
		fore = WHITE;
		back = RED;

		return y + 1;
	}
	int _generate(NEModuleCodeSet& ms, NEArrayTemplate<NEObject*>& selected)
	{
		setText("ModuleSet");
		fore = BLACK;
		back = LIGHTRED;

		int next_vacant = y + 1;
		for(int n=0; n < ms.getLength() ;n++)
			next_vacant = ((Planet&)planets[planets.push(Planet(planetarium, this))]).generate(ms[n], selected, this, next_vacant);

		return next_vacant;
	}
	int _generate(NEModuleCodeSetKey& msk, NEArrayTemplate<NEObject*>& selected)
	{
		int to_return = _generate(msk.getValue(), selected);
		setText("[MS]" + msk.getName());

		return to_return;
	}
	int _generate(NENode& node, NEArrayTemplate<NEObject*>& selected)
	{
		const NETString& name = Editor::getInstance().getScriptEditor().getBanks().getScriptBank()[node.getScriptCode()];
		setText(name);
		fore = WHITE;
		back = GREEN;

		int next_vacant = ((Planet&)planets[planets.push(Planet(planetarium, this))]).generate(node.getKeySet(), selected, this, y + 1);		
		return ((Planet&)planets[planets.push(Planet(planetarium, this))]).generate(node.getModuleSet(), selected, this, next_vacant);
	}
	int _generate(NENodeCodeSetKey& nsk, NEArrayTemplate<NEObject*>& selected)
	{
		int to_return = _generate(nsk.getValue(), selected);

		setText("[NS]" + nsk.getName());
		return to_return;
	}

	int _generate(NENodeCodeSet& ns, NEArrayTemplate<NEObject*>& selected)
	{
		setText("NodeSet");
		fore = BLACK;
		back = LIGHTGREEN;

		int next_vacant = y + 1;
		for(int n=0; n < ns.getLength() ;n++)
			next_vacant = ((Planet&)planets[planets.push(Planet(planetarium, this))]).generate(ns[n], selected, this, next_vacant);

		return next_vacant;
	}

	void setText(const NEString& new_name)
	{
		text = new_name;
		width = text.getLength();
	}
	void updateMe(NEObject& obj, Planet* parent, int your_y)
	{
		real = &obj;
		x = parent ? parent->x + INDENT_X : 0;
		y = your_y;
		setText(obj.getTypeName());
		height = 1;
	}

	typedef NEListTemplate<Planet*, true> PlanetList;
	PlanetList planets;
	NEObject* real;
	Planet* parent;
	Planetarium* planetarium;
	bool is_closed;
};
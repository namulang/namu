#pragma once

#include "../Planet/Planet.hpp"
#pragma warning(push)
#pragma warning(disable: 4355)

class Planetarium : public Window
{
public:
	Planetarium(int new_x, int new_y, int new_width, int new_height, int fore = WHITE, int back = BLUE)
		: Window(), root(this, 0)
	{
		x = new_x;
		y = new_y;
		width = new_width;
		height = new_height;
		focusing = &root;
		setFocus(root);
	}
	Planetarium(const Planetarium& rhs)
		: Window(rhs), root(this, 0)
	{
		focusing = &root;
		setFocus(root);
	}

	FUNC_CLONE(Planetarium)

	virtual void onUpdateData()
	{
		generate(Editor::getInstance().getScriptEditor().getScriptNodes());
		root.updateLines(0);
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

	Planet root;
	int screen_x, screen_y;
	Planet* focusing;
};
#pragma warning(pop)

/*
class Planet : public Gliph // has x, y, text, color, gliphs.
{
public:
//	Planet의 owner는 항상 Planet이라 가정하면 모든게 편해진다.
Planet(int x, int y, int w, int h, int fore, int back, const NEString& text)
: Gliph(0, x, y, w, h, fore, back, text)
{
}
private:

public:
~Planet()
{
Planet::release();
}
FUNC_TO_OWNER(Planet)


virtual void release()
{
// 여기서 주의할 점은, GliphList는 <Gliph*, false> 라는 점이다.
while(gliphs.getLength() > 0)
{
delete &gliphs[0];
gliphs.popFront();
}
}

};

void main()
{
A a, b(a);
}
*/
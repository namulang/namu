#include "Planet.hpp"
#include "../Planetarium/Planetarium.hpp"

void Planet::putPixel(int virtual_x, int virtual_y, char shape, int fore/*=UNKNOWN*/, int back/*=UNKNOWN*/)
{
	int real_x = virtual_x - planetarium->screen_x,
		real_y = virtual_y - planetarium->screen_y;
	if( ! isPixelInScreen(real_x, real_y)) return;
	fore = fore == LG::UNKNOWN ? planetarium->fore : fore;
	back = back == LG::UNKNOWN ? planetarium->back : back;

	LG::Core::setCursorTo(real_x, real_y);
	WORD backup = LG::Core::getColor();
	LG::Core::setColor(fore, back);
	cout << shape;
	LG::Core::setColor(backup);
}

void Planet::putPixel(int virtual_x, int virtual_y, const NEString& text, int fore/*=LG::UNKNOWN*/, int back/*=LG::UNKNOWN*/)
{
	fore = fore == LG::UNKNOWN ? planetarium->fore : fore;
	back = back == LG::UNKNOWN ? planetarium->back : back;
	
	for(int n=0; n < text.getLength() ;n++)
		if(text[n] != 0)
			putPixel(virtual_x + n, virtual_y, text[n], fore, back);
}

bool Planet::isPixelInScreen(int x, int y) const
{
	return	0 <= x && x <= planetarium->width	&&
			0 <= y && y <= planetarium->height;
}

void Planet::onDraw()
{
	if(parent && parent->is_closed)
		return;

	int local_fore = fore,
		local_back = back;
	if(planetarium->focusing == this)
	{
		local_fore = LG::BLACK;
		local_back = LG::YELLOW;
	}
	NEString lever = is_closed ? "[+] " : "[-] ";	
	putPixel(x, y, lever + text, local_fore, local_back);

	if(is_closed) return;

	for(PlanetList::Iterator* itr=planets.getIterator(0); itr ;itr=itr->getNext())
	{
		NEString edge = itr->getNext() ? "汝收收" : "汎收收";
		putPixel(x, itr->getValue().y, edge, LG::UNKNOWN, LG::UNKNOWN);
		itr->getValue().onDraw();			
	}
}

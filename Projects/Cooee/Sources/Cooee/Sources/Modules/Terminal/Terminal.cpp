#include "Terminal.hpp"
#include "../Core/Core.hpp"
#include "../Planetarium/Planetarium.hpp"

Terminal::Terminal(const NEString& new_path, NEType::Type new_to_chk_valid, int x, int y, int w, int h, int back, int fore)
: Window(x, y, w, h, back, fore), path(new_path), to_chk_valid(new_to_chk_valid), instance(0)
{
	regist(1, &status);
	_setObject();
}

Terminal::Terminal(const Terminal& rhs) : Window(rhs), path(rhs.path), to_chk_valid(rhs.to_chk_valid), instance(0) 
{
	regist(1, &status);
	_setObject();
}

void Terminal::_setObject()
{
	instance = &::Core::getObjectBy(path);
	if( ! instance)	
		return;
	
	if( ! instance->isSubClassOf(to_chk_valid))
	{
		//::Core::pushMessage("이런, Terminal에 들어온 경로가 타입이 틀려요");	
		instance = 0x00;
	}
}

void Terminal::onUpdateData() 
{
	if( ! instance)
	{
		::Core::pushMessage("주어진 경로 : " + path + "에 적합한 객체가 없습니다.");
		delete_me = true;
	}

	Window::onUpdateData();
}

void Terminal::onKeyPressed(char inputed)
{
	Window::onKeyPressed(inputed);

	if(inputed == LG::SPACE)
	{
		call(Planetarium());
		(dynamic_cast<Planetarium&>(LG::Core::windows[0])).setFocus(::Core::getObjectBy(path));
	}
}

void Terminal::Status::onUpdateData()
{
	Terminal& owner = *toOwner();
	x = owner.x;
	y = owner.y;
	width = owner.width;
	height = 1;
	back = RED;
	fore = BLACK;

	text = " > " + NEString(NEType::getTypeName(owner.to_chk_valid));

	onDraw();
}
#include "Terminal.hpp"
#include "../Core/Core.hpp"
#include "../Planetarium/Planetarium.hpp"

Terminal::Terminal(const NEString& new_path, NEType::Type new_to_chk_valid, int x, int y, int w, int h, int back, int fore)
: Window(x, y, w, h, back, fore), to_chk_valid(new_to_chk_valid), instance(0)
{
	regist(2, &status, &navigator);
	setPath(new_path);
}

Terminal::Terminal(const Terminal& rhs) 
: Window(rhs), _path(rhs._path), to_chk_valid(rhs.to_chk_valid), instance(0), navigator(rhs.navigator), status(rhs.status)

{
	regist(2, &status, &navigator);
	setPath(rhs._path);
}

void Terminal::_setObject()
{
	instance = &::Core::getObjectBy(_path);
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
		::Core::pushMessage("주어진 경로 : " + _path + "에 적합한 객체가 없습니다.");
		delete_me = true;
	}

	Window::onUpdateData();
}

void Terminal::onKeyPressed(char inputed)
{
	Window::onKeyPressed(inputed);

	if(inputed == LG::MAP)
	{
		call(Planetarium());
		(dynamic_cast<Planetarium&>(LG::Core::windows[0])).setFocus(::Core::getObjectBy(_path));
	}
}

void Terminal::setPath(const NEString& new_path)
{
	_path = new_path;

	for(int n=0; n < _path.getLength() ;n++)
		if(	_path[n] == '\\'||
			_path[n] == '/'	)
		{
			int slash_n = n;
			while(	++slash_n < _path.getLengthLastIndex()		&&
				(_path[slash_n] == '\\' || _path[slash_n] == '/'))
				_path.remove(slash_n--);
		}

	if(_path.getSize() > _path.getLength())
		_path.resize(_path.getLength());

	_setObject();
}

const NEString& Terminal::getPath() const
{
	return _path; 
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

void Terminal::Navigator::onUpdateData()
{
	width = toOwner()->width;
	x = toOwner()->x;
	y = toOwner()->y + toOwner()->height - 1;
	height = 1;

	NEString type_name = toOwner()->instance ? toOwner()->instance->getTypeName() : NEType::getTypeName(NEType::UNDEFINED);
	text = NEString("[") + type_name + NEString("] : ") + 
		toOwner()->getPath();
}
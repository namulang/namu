#include "Classer.hpp"
#include "TClass.hpp"

namespace wrd
{
#define THIS Classer
	WRD_CLASS_DEF(THIS)

	Res& THIS::init()
	{
		if(isInit()) return wascancel;
		_isPreloaded() = true;
		for(Class* e : _getPreloads())
			e->init();
		return wasgood;
	}

	Res& THIS::release()
	{
		//TODO: _release();
		return Super::release();
	}

	Res& THIS::_preload(const Class& it)
	{
		_getPreloads().push_back((Class*) &it);
		return wasgood;
	}
}	

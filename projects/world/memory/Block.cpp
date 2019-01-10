#include "Block.hpp"
#include "../meta.hpp"

namespace wrd
{
#define THIS Block
	WRD_CLASS_DEF(THIS)

	Res& THIS::setSerial(wcnt new1)
	{
		if( ! _pt)
			return wasnull;
		_pt->_id.sep.serial = new1;
		return wasgood;
	}

	wcnt THIS::getSerial() const { return _pt ? _pt->getId().sep.serial : WRD_INDEX_ERROR; }

	Res& THIS::unbind()
	{
		//	TODO:
		return wasgood;
	}

	wbool THIS::isBind() const { return _pt; }

	const Class& THIS::getBindable() const
	{
		static TClass<Instance> inner;
		return inner;
	}

	wbool THIS::canBind(const Class& cls) const { return cls.isSub(getBindable()); }
	wbool THIS::isHeap() const { /*TODO: */ return false; }

	Res& THIS::_onWeak(wcnt vote)
	{
		//	TODO:
		return wasgood;
	}
	
	Res& THIS::_onStrong(wcnt vote)
	{
		//	TODO:
		return wasgood;
	}

	Instance& THIS::_get() { return *_pt; }

	Res& THIS::_bind(const Instance& new1)
	{
		//	TODO:
		return wasgood;
	}
 }

#include "Block.hpp"
#include "../meta.hpp"

namespace wrd
{
#define THIS Block
	WRD_CLASS_DEF(THIS)

	THIS::THIS() : Super() {}
	THIS::THIS(Id id) : Super(id) {}

	Res& THIS::setSerial(wcnt new1)
	{
		if( ! _pt)
			return wasnull;
		_pt->_id.sep.serial = new1;
		return wasgood;
	}

	wcnt THIS::getSerial() const { return _pt ? _pt->getId().sep.serial : WRD_INDEX_ERROR; }

	const Chunk& THIS::getChunk() const
	{
		if( ! _wrd)
			return nulr<Chunk>();

		return Instance::_getMgr().getPool()[*_pt][*_pt];
	}

	Res& THIS::unbind()
	{
		WRD_IS_SUPER(unbind())
		_weak = _strong = 0;
		return wasgood;
	}

	wbool THIS::isBind() const { return _pt; }

	const Class& THIS::getBindable() const
	{
		static TClass<Instance> inner;
		return inner;
	}

	wbool THIS::canBind(const Class& cls) const { return cls.isSub(getBindable()); }

	wbool THIS::isHeap() const
	{
		const Chunk& chk = WRD_GET(getChunk(), false);
		return chk.has(*_pt);
	}

	Res& THIS::release() { return unbind(); }

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

	Res& THIS::_bind(const Instance& it)
	{
		unbind();

		_pt = (Instance*) &it;
		_pt->_id = getId();
		return wasgood;
	}
 }

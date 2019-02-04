#include "Block.hpp"
#include "../meta.hpp"
#include "TStrong.hpp"
#include "Instancer.hpp"
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

		Id got = getId();
		got.s.serial = new1;
		return _sync(got);
	}

	wcnt THIS::getSerial() const { return _pt ? _pt->getId().s.serial : WRD_INDEX_ERROR; }

	const Chunk& THIS::getChunk() const
	{
		if( ! _pt)
			return nulr<Chunk>();

		return Instance::_getMgr().getPool()[*_pt][*_pt];
	}

	Res& THIS::unbind()
	{
		_pt = 0;
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

	Id THIS::getId() const { return _id; }

	wbool THIS::isHeap() const
	{
		const Chunk& chk = getChunk();
		WRD_IS_NULL(chk, wasnull, false)

		return chk.has(*_pt);
	}

	Strong THIS::toStrong() { return Strong((Node*)_pt); }
	Weak THIS::toWeak() { return Weak((Node*)_pt); }
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
		return _completeId(*_pt);
	}

	Res& THIS::_completeId(Instance& it)
	{
		//	complete mine:
		Id mine = getId();
		mine.s.chk_n = it._id.s.chk_n;
		//	propagate it:
		return _sync(mine);
	}

	Res& THIS::_sync(Id new1)
	{
		if(_pt)
			_pt->_setId(new1);
		return _setId(new1);
	}
 }

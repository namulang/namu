#include "Instance.hpp"
#include "../world.hpp"

namespace
{
	Instancer& getMgr() { return World::get().getInstancer(); }
}

namespace wrd
{
#define THIS Instance
	WRD_CLASS_DEF(Instance)

	THIS::Instance()
	{
		//	TODO: we need to optimize this. this ganna hotspot.
		getMgr().stamp(*this);
	}

	Id THIS::getId() const { return _id; }
	wcnt THIS::getSerial() const { getBlock().getSerial(); }

	wbool THIS::isHeap() const
	{
		const Block& blk = WRD_GET(getBlock(), false)
		return blk.isHeap();
	}

	Strong THIS::toStrong()
	{
		if (isHeap()
			return Strong(*this);
		return clone();
	}

	CStrong THIS::toStrong() const { return CStrong(*this); }
	Weak THIS::toWeak() { return Weak(*this); }
	CWeak THIS::toWeak() const { return CWeak(*this); }

	const Block& THIS::getBlock() const
	{
		WRD_UNCONST()
		return unconst._getBlock(_id);
	}
	Block& THIS::_getBlock() { return _getBlock(_id); }
	Block& THIS::_getBlock(Id id)
	{
		WRD_IS_THIS(Block)
		return const_cast<Block&>(getMgr()[id]);
	}
	Res& THIS::_setId(Id new1)
	{
		_id = new1;
		return wasgood;
	}
}

#include "Instance.hpp"
#include "../world.hpp"

namespace wrd
{
#define THIS Instance
	WRD_CLASS_DEF(Instance)

	namespace {
		Instancer& getMgr() { return World::get().getInstancer(); }
	}

	THIS::THIS() { _bind(false); }
	THIS::~THIS() { getMgr().unbind(*this); }

	void* THIS::operator new(size_t size) { return _bind(true).getHeap(); }

	Id THIS::getId() const { return _id; }

	wbool THIS::isHeap() const
	{
		const Block& blk = WRD_GET(getBlock(), false)
		return blk.isHeap();
	}

	CStrong THIS::toStrong() const
	{
		WRD_UNCONST()
		return unconst.toStrong();
	}

	CWeak THIS::toWeak() const
	{
		WRD_UNCONST()
		return unconst.toWeak();
	}

	const Block& THIS::getBlock() const { return _getBlock(_id); }
	Block& THIS::_getBlock(Id id) { return const_cast<Block&>(getMgr()[id]); }

	Res& THIS::_setId(Id new1)
	{
		_id = new1;
		return wasgood;
	}

	Block& THIS::_bind(wbool from_heap)
	{	//	TODO: we need to optimize this. this gonna hotsopt.
		WRD_ASSERT(_id.num != WRD_INDEX_ERROR)
		return getMgr().bind(*this, is_heap)
	}
}

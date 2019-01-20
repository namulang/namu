#include "Instance.hpp"
#include "../world.hpp"

namespace wrd
{
#define THIS Instance
	WRD_CLASS_DEF(Instance)

	Id THIS::_from_dtor;
	widx THIS::_chk_n_from_alloc = WRD_INDEX_ERROR;

	THIS::THIS() { _getMgr().bind(*this); } 
	THIS::THIS(Id id) : _id(id) {} // no binding required.
	THIS::~THIS()
	{
		_getMgr().unbind(*this);
		_from_dtor = _id;
	}

	wbool THIS::operator==(const This& rhs) const { return _id.num == rhs._id.num; }
	wbool THIS::operator!=(const This& rhs) const { return ! operator==(rhs); }
	void* THIS::operator new(size_t sz) { return _getMgr()._new1(sz); }
	void THIS::operator delete(void* pt, size_t sz) { _getMgr()._del(pt, sz); }

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

	Res& THIS::release()
	{
		_id.num = WRD_INDEX_ERROR;
		return wasgood;
	}

	Block& THIS::_getBlock(Id id) { return const_cast<Block&>(_getMgr().getAkashic()[id].blk); }

	Res& THIS::_setId(Id new1)
	{
		_id = new1;
		return wasgood;
	}

	Instancer& THIS::_getMgr() { return World::get().getInstancer(); }
}

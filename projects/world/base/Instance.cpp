#include "Instance.hpp"
#include "../world.hpp"

namespace wrd
{
#define THIS Instance
	WRD_CLASS_DEF(Instance)

	THIS::THIS() { _id.s.chk_n = _vault.get(this); }
	THIS::THIS(Id id) : _id(id) {} // no binding required.
	THIS::~THIS() { _getMgr().unbind(*this); }

	wbool THIS::operator==(const This& rhs) const { return _id.num == rhs._id.num; }
	wbool THIS::operator!=(const This& rhs) const { return ! operator==(rhs); }
	void* THIS::operator new(size_t sz) { return _getMgr()._new1(sz); }
	void THIS::operator delete(void* pt, size_t sz) { _getMgr()._del(pt, sz); }

	Id THIS::getId() const
	{
		if(_id.s.blk_n == WRD_INDEX_ERROR)
			_getMgr().bind((This&)*this);
		return _id;
	}

	wbool THIS::isHeap() const
	{
		const Block& blk = getBlock();
		WRD_IS_NULL(blk, wasnull, false)

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

	const Block& THIS::getBlock() const { return _getBlock(getId()); }

	// release() have not to reset Id. it's regarding to instance info.
	// as long as instance keep alive, that info need to be stuck to instance.

	Block& THIS::_getBlock(Id id) { return WRD_GET((Block&) _getMgr().getAkashic()[id], blk); }

	Res& THIS::_setId(Id new1)
	{
		_id = new1;
		return wasgood;
	}

	Instancer& THIS::_getMgr() { return World::get().getInstancer(); }

#undef THIS
#define THIS Instance::Vault
	THIS Instance::_vault;

	WRD_CLASS_DEF(THIS)

	Res& THIS::set(void* rcver, widx chk_n)
	{
		_rcver = rcver;
		_chk_n = chk_n;
		return wasgood;
	}

	widx THIS::get(void* rcver)
	{
		widx ret = _chk_n;
		set(NULL, WRD_INDEX_ERROR);
		if(rcver != _rcver)
		{
			WRD_WARN("rcver(%x) != _rcver(%x)", rcver, _rcver);
			return _chk_n;
		}

		return ret;
	}

	Res& THIS::release() { return set(NULL, WRD_INDEX_ERROR); }
}

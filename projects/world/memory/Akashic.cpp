#include "Akashic.hpp"
#include "../meta.hpp"
#include "../pretypes.hpp"

namespace wrd
{
#define THIS Akashic
	WRD_CLASS_DEF(THIS)

	THIS::THIS() : Chunk(sizeof(Unit), false) {}

	Unit& THIS::operator[](widx n) { return get(n); }
	Unit& THIS::operator[](Id id) { return get(id.sep.blk_n); }
	const Unit& THIS::operator[](widx n) const { return get(n); }
	const Unit& THIS::operator[](Id id) const { return get(id.sep.blk_n); }

	Unit& THIS::get(widx n) { return *(Unit*)_get(n); }
	const Unit& THIS::get(widx n) const { return ((Akashic*)this)->get(n); }

	void* THIS::new1()
	{
			Unit* res = (Unit*)Chunk::new1();
		if (!res)
			return res;

		::new (&res->blk) Block(_genId(res));
		return res;
	}

	Id THIS::_genId(void* pt) const
	{
		static wcnt serial = 0;
		widx chk_n = Instance::_chk_n_from_alloc;
		Instance::_chk_n_from_alloc = -1;
		return Id(_getIdx(pt), chk_n, ++serial);
	}

	widx THIS::_getIdx(void* it) const
	{
		if (!has(*(Instance*)it)) // "has" func will treat it as void*, too.
			return -1;

		widx ret = ((wuchar*)it - getHeap()) / getBlkSize();
		return ret;
	}
}

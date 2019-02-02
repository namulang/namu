#include "Akashic.hpp"
#include "../meta.hpp"
#include "../pretypes.hpp"

namespace wrd
{
#define THIS Akashic
	WRD_CLASS_DEF(THIS)

	THIS::THIS() : Chunk(sizeof(Unit), false) {}

	Unit& THIS::operator[](widx n) { return get(n); }
	Unit& THIS::operator[](Id id) { return get(id.s.blk_n); }
	const Unit& THIS::operator[](widx n) const { return get(n); }
	const Unit& THIS::operator[](Id id) const { return get(id.s.blk_n); }

	Unit& THIS::get(widx n) { return *(Unit*)_get(n); }
	const Unit& THIS::get(widx n) const { return ((Akashic*)this)->get(n); }

	void* THIS::new1()
	{
		Unit* res = (Unit*)Chunk::new1();
		if( ! res)
			return res;

		::new (&res->blk) Block(_genId(res));
		return res;
	}

	Id THIS::_genId(void* pt) const
	{
		static wcnt serial = 0;
		// Akashic concern about bkl_n at Id. on the other hand, Chunk is chk_n.
		// eventually, if Instance was born from heap, first it take chk_n from chunk when it borns.
		// and take blk_n from Akashic when user try to access its Block instance.
		return Id(_getIdx(pt), WRD_INDEX_ERROR, ++serial);
	}

	widx THIS::_getIdx(void* it) const
	{
		if( ! has(*(Instance*)it)) // "has" func will treat it as void*, too.
			return -1;

		widx ret = ((wuchar*)it - getHeap()) / getBlkSize();
		return ret;
	}
}

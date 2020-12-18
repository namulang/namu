#include "Watcher.hpp"

namespace wrd { namespace memlite {

	WRD_DEF_THIS(Watcher, Chunk)

	This::Watcher() : Chunk(sizeof(Unit), false) {}

	Unit& This::operator[](widx n) { return get(n); }
	Unit& This::operator[](Id id) { return get(id); }
	const Unit& This::operator[](widx n) const { return get(n); }
	const Unit& This::operator[](Id id) const { return get(id); }

	Unit& This::get(widx n) { return *(Unit*)_get(n); }
	const Unit& This::get(widx n) const { return ((Watcher*)this)->get(n); }

	Unit& This::get(Id id) {
		Unit& got = get(id.s.tag_n);
		if(nul(got)) {
            WRD_W("can't return Unit(%x): it's nul!", &got);
            return nulr<Unit>();
        }
        if(got.blk.getId().num != id.num) {
            WRD_W("can't return Unit.blk.getId(%d) != id.num(%d)",
                    got.blk.getId().num, id.num);
			return nulr<Unit>();
        }

		return got;
	}

	const Unit& This::get(Id id) const WRD_UNCONST_FUNC(get(id))

	void* This::new1() {
		Unit* res = (Unit*)Chunk::new1();
		if(!res)
			return res;

		::new (&res->blk) BindTag(_genId(res));
		return res;
	}

	Id This::_genId(void* pt) const {
		static wcnt serial = 0;
		// Watcher concern about bkl_n at Id. on the other hand, Chunk is chk_n.
		// eventually, if Instance was born from heap, first it take chk_n from chunk when it borns.
		// and take tag_n from Watcher when user try to access its Block instance.
		return Id(_getIdx(pt), WRD_INDEX_ERROR, ++serial);
	}

	widx This::_getIdx(void* it) const {
		if(!has(*(Instance*)it)) // "has" func will treat it as void*, too.
			return -1;

		widx ret = ((wuchar*)it - getHeap()) / getBlkSize();
		return ret;
	}
}}

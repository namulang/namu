#include "Watcher.hpp"

namespace wrd {

	WRD_DEF_THIS(Watcher, Chunk)

	This::Watcher() : Chunk(sizeof(WatchCell), false) {}

	WatchCell& This::operator[](widx n) { return get(n); }
	WatchCell& This::operator[](Id id) { return get(id); }
	const WatchCell& This::operator[](widx n) const { return get(n); }
	const WatchCell& This::operator[](Id id) const { return get(id); }

	WatchCell& This::get(widx n) { return *(WatchCell*)_get(n); }
	const WatchCell& This::get(widx n) const { return ((Watcher*)this)->get(n); }

	WatchCell& This::get(Id id) {
		WatchCell& got = get(id.s.tagN);
        WRD_NUL(got, nulr<WatchCell>());

        if(got.blk.getId().num != id.num) {
            WRD_W("can't return WatchCell.blk.getId(%d) != id.num(%d)",
                    got.blk.getId().num, id.num);
			return nulr<WatchCell>();
        }

		return got;
	}

	const WatchCell& This::get(Id id) const WRD_UNCONST_FUNC(get(id))

	void* This::new1() {
		WatchCell* res = (WatchCell*)Super::new1();
		if(!res)
			return res;

		::new (&res->blk) BindTag(_genId(res));
		return res;
	}

	Id This::_genId(void* pt) const {
		static wcnt serial = 0;
		// Watcher concern about bkl_n at Id. on the other hand, Chunk is chkN.
		// eventually, if Instance was born from heap, first it take chkN from chunk when it borns.
		// and take tagN from Watcher when user try to access its Block instance.
		return Id(_getIdx(pt), WRD_INDEX_ERROR, ++serial);
	}

	widx This::_getIdx(void* it) const {
		if(!has(*(Instance*)it)) // "has" func will treat it as void*, too.
			return -1;

		widx ret = ((wuchar*)it - getHeap()) / getBlkSize();
		return ret;
	}
}

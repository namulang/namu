#include "Watcher.hpp"

namespace wrd {

    WRD_DEF_ME(Watcher, Chunk)

    me::Watcher() : Chunk(sizeof(WatchCell), false) {}

    WatchCell& me::operator[](widx n) { return get(n); }
    WatchCell& me::operator[](Id id) { return get(id); }

    WatchCell& me::get(widx n) { return *(WatchCell*)_get(n); }

    WatchCell& me::get(Id id) {
        WatchCell& got = get(id.tagN);
        if(nul(got)) return nulOf<WatchCell>();

        Id gotId = got.blk.getId();
        if(gotId.tagN != id.tagN) {
            WRD_W("BindTag was corrupted! WatchCell.id(%d.%d.%d) != id(%d.%d.%d)",
                    gotId.tagN, gotId.chkN, gotId.serial, id.tagN, id.chkN, id.serial);
            return nulOf<WatchCell>();
        }
        if(gotId.chkN != id.chkN || gotId.serial != id.serial)
            // BindTag has been changed its instance to bind.
            return nulOf<WatchCell>();

        return got;
    }

    void* me::new1() {
        if(isFull())
            if(!_resize(getSize()*2 + 1))
                return WRD_E("resize Watcher failed! this damage system seriously !!!!"), nullptr;

        WatchCell* res = (WatchCell*)super::new1();
        if(!res)
            return res;

        ::new (&res->blk) BindTag(_genId(res));
        return res;
    }

    wbool me::del(void* used, wcnt sz) {
        WatchCell& cell = *((WatchCell*) used);
        cell.~WatchCell();

        return super::del(used, sz);
    }

    Id me::_genId(void* pt) const {
        static wcnt serial = 0;
        // Watcher concern about bkl_n at Id. on the other hand, Chunk is chkN.
        // eventually, if Instance was born from heap, first it take chkN from chunk when it borns.
        // and take tagN from Watcher when user try to access its Block instance.
        return Id(_getIdx(pt), WRD_INDEX_ERROR, ++serial);
    }

    widx me::_getIdx(void* it) const {
        if(!has(*(Instance*)it)) // "has" func will treat it as void*, too.
            return -1;

        widx ret = ((wuchar*)it - _getHeap()) / getBlkSize();
        return ret;
    }
}

#include "instancer.hpp"

namespace namu {

    WRD_DEF_ME(instancer)

    wbool me::bind(const instance& new1) {
        watchCell& un = *(watchCell*) _watcher.new1();
        return un.blk.bind(new1);
    }

    wbool me::rel(const instance& old) {
        if(!_hasBindTag(old)) return true; // optimization.

        watchCell& un = _watcher[old.getId()];
        if(nul(un)) return false;
        return _watcher.del(&un, sizeof(watchCell));
    }

    void* me::_new1(size_t sz) { return _pool[sz].new1(); }
    void me::_del(void* pt, wcnt sz) { _pool[sz].del(pt, sz); }
    const pool& me::getPool() const { return _pool; }
    const watcher& me::getWatcher() const { return _watcher; }
    wbool me::_hasBindTag(const instance& it) const { return it._id.tagN != WRD_INDEX_ERROR; }

}

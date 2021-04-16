#include "Instancer.hpp"

namespace wrd {

    WRD_DEF_ME(Instancer)

    wbool me::bind(const Instance& new1) {
        WatchCell& un = *(WatchCell*) _watcher.new1();
        return un.blk.bind(new1);
    }

    wbool me::unbind(const Instance& old) {
        if(!_hasBindTag(old)) return true; // optimization.

        WatchCell& un = _watcher[old.getId()];
        return _watcher.del(&un, sizeof(WatchCell));
    }

    void* me::_new1(size_t sz) { return _pool[sz].new1(); }
    void me::_del(void* pt, wcnt sz) { _pool[sz].del(pt, sz); }
    const Pool& me::getPool() const { return _pool; }
    const Watcher& me::getWatcher() const { return _watcher; }
    wbool me::_hasBindTag(const Instance& it) const { return it._id.tagN != WRD_INDEX_ERROR; }

}

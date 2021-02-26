#include "Instancer.hpp"

namespace wrd {

    WRD_DEF_THIS(Instancer)

    wbool This::bind(const Instance& new1) {
        WatchCell& un = *(WatchCell*) _watcher.new1();
        return un.blk.bind(new1);
    }

    wbool This::unbind(const Instance& old) {
        if(!_hasBindTag(old)) return true; // optimization.

        WatchCell& un = _watcher[old.getId()];
        return _watcher.del(&un, sizeof(WatchCell));
    }

    void* This::_new1(size_t sz) { return _pool[sz].new1(); }
    void This::_del(void* pt, wcnt sz) { _pool[sz].del(pt, sz); }
    const Pool& This::getPool() const { return _pool; }
    const Watcher& This::getWatcher() const { return _watcher; }
    wbool This::_hasBindTag(const Instance& it) const { return it._id.tagN != WRD_INDEX_ERROR; }

}

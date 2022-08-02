#include "pool.hpp"
#include "../interface/instance.hpp"

namespace namu {

    WRD_DEF_ME(pool, memoryHaver)

    me::pool() {}
    me::~pool() { rel(); }

    chunks& me::operator[](widx n) { return get(n); }
    chunks& me::operator[](const instance& inst) { return get(inst); }
    chunks& me::get(const instance& inst) { return get(inst.getType().size()); }
    chunks& me::get(widx n) { return *(chunks*)_get(n); }

    wbool me::has(const instance& it) const {
        const chunks& got = get(it.getType().size());
        if(nul(got))
            return WRD_W("got == null"), false;

        return got.has(it);
    }

    wcnt me::size() const { return _chunks.capacity(); }
    wcnt me::len() const { return _chunks.size(); }

    wbool me::rel() {
        for(chunks* e : _chunks) {
            if (!e) continue;
            e->rel();
            delete e;
        }

        _chunks.clear();
        return true;
    }

    void* me::_get(widx n) {
        while((int)_chunks.size() - 1 < n)
            _chunks.push_back(NULL);

        if(!_chunks[n])
            _chunks[n] = new chunks(n);

        return _chunks[n];
    }
}

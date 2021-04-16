#include "Pool.hpp"
#include "../interface/Instance.hpp"

namespace wrd {

    WRD_DEF_ME(Pool, MemoryHaver)

    me::Pool() {}
    me::~Pool() { rel(); }

    Chunks& me::operator[](widx n) { return get(n); }
    Chunks& me::operator[](const Instance& inst) { return get(inst); }
    Chunks& me::get(const Instance& inst) { return get(inst.getType().getSize()); }
    Chunks& me::get(widx n) { return *(Chunks*)_get(n); }

    wbool me::has(const Instance& it) const {
        const Chunks& got = get(it.getType().getSize());
        WRD_NUL(got, false)

        return got.has(it);
    }

    wcnt me::getSize() const { return _chunks.capacity(); }
    wcnt me::getLen() const { return _chunks.size(); }

    wbool me::rel() {
        for(Chunks* e : _chunks) {
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
            _chunks[n] = new Chunks(n);

        return _chunks[n];
    }
}

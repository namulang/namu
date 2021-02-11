#include "Pool.hpp"
#include "../interface/Instance.hpp"

namespace wrd {

    WRD_DEF_THIS(Pool, MemoryHaver)

    This::Pool() {}
    This::~Pool() { rel(); }

    Chunks& This::operator[](widx n) { return get(n); }
    Chunks& This::operator[](Instance& inst) { return get(inst); }
    Chunks& This::get(Instance& inst) { return get(inst.getType().getSize()); }
    Chunks& This::get(widx n) { return *(Chunks*)_get(n); }

    wbool This::has(Instance& it) {
        Chunks& got = get(it.getType().getSize());
        WRD_NUL(got, false)

        return got.has(it);
    }

    wcnt This::getSize() { return _chunks.capacity(); }
    wcnt This::getLen() { return _chunks.size(); }

    wbool This::rel() {
        for(Chunks* e : _chunks) {
            if (!e) continue;
            e->rel();
            delete e;
        }

        _chunks.clear();
        return true;
    }

    void* This::_get(widx n) {
        while((int)_chunks.size() - 1 < n)
            _chunks.push_back(NULL);

        if(!_chunks[n])
            _chunks[n] = new Chunks(n);

        return _chunks[n];
    }
}

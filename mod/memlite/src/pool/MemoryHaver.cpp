#include "MemoryHaver.hpp"

namespace wrd {

    WRD_DEF_THIS(MemoryHaver)

    void* This::_get(widx n) {
        // this guards cant exist at Chunk::_get().
        // we should put here.
        if(n < 0 || n >= getLen()) return WRD_NULL;

        return _onGet(n);
    }

    wbool This::isFull() { return getLen() >= getSize(); }
    wbool This::isCapable() { return getLen() < getSize(); }
}

#include "MemoryHaver.hpp"

namespace wrd {

    WRD_DEF_THIS(MemoryHaver)

    wbool This::isFull() const { return getLen() >= getSize(); }
    wbool This::isCapable() const { return getLen() < getSize(); }
}

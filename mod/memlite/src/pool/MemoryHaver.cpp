#include "MemoryHaver.hpp"

namespace wrd {

    WRD_DEF_THIS(MemoryHaver)

    wbool This::isFull() { return getLen() >= getSize(); }
    wbool This::isCapable() { return getLen() < getSize(); }
}

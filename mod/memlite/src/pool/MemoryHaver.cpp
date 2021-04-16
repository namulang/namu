#include "MemoryHaver.hpp"

namespace wrd {

    WRD_DEF_ME(MemoryHaver)

    wbool me::isFull() const { return getLen() >= getSize(); }
    wbool me::isCapable() const { return getLen() < getSize(); }
}

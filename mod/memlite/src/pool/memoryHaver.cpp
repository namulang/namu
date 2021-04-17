#include "memoryHaver.hpp"

namespace wrd {

    WRD_DEF_ME(memoryHaver)

    wbool me::isFull() const { return getLen() >= getSize(); }
    wbool me::isCapable() const { return getLen() < getSize(); }
}

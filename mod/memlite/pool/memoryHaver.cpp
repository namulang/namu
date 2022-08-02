#include "memoryHaver.hpp"

namespace namu {

    WRD_DEF_ME(memoryHaver)

    wbool me::isFull() const { return len() >= size(); }
    wbool me::isCapable() const { return len() < size(); }
}

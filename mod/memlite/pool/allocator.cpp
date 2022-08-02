#include "allocator.hpp"

namespace namu {

    WRD_DEF_ME(allocator, memoryHaver)

    me::allocator(wcnt blksize) : _blksize(blksize) {}
    wcnt me::getBlkSize() const { return _blksize; }
}

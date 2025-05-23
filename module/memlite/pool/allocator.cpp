#include "memlite/pool/allocator.hpp"

namespace nm {

    NM_DEF_ME(allocator, memoryHaver)

    me::allocator(ncnt blksize): _blksize(blksize) {}

    ncnt me::getBlkSize() const { return _blksize; }
}

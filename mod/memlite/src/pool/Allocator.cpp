#include "Allocator.hpp"

namespace wrd {

    WRD_DEF_THIS(Allocator, MemoryHaver)

    This::Allocator(wcnt blksize) : _blksize(blksize) {}
    wcnt This::getBlkSize() { return _blksize; }
}

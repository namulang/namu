#include "Allocator.hpp"

namespace wrd { namespace memlite {

	WRD_DEF_THIS(Allocator, MemoryHaver)

	This::Allocator(wcnt blksize) : _blksize(blksize) {}
	wcnt This::getBlkSize() const { return _blksize; }
}}

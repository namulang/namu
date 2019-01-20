#include "Allocator.hpp"
#include "../meta.hpp"
#include "../pretypes.hpp"

namespace wrd
{
#define THIS Allocator
	WRD_CLASS_DEF(Allocator)

	THIS::THIS(wcnt blksize) : _blksize(blksize) {}
	wcnt THIS::getBlkSize() const { return _blksize; }	

	Res& THIS::release()
	{
		_blksize = 1;
		return wasgood;
	}
}

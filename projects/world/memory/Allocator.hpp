#pragma once

#include "MemoryHaver.hpp"

namespace wrd
{
	class Allocator : public MemoryHaver
	{	WRD_CLASS_DECL(Allocator, MemoryHaver)
	public:
		Allocator(wcnt blkbyte = 1) : _blkbyte(blkbyte) {}

	public:
		virtual void* new1() = 0;
		virtual Res& del(void* used, wcnt sz) = 0;
		virtual Res& resize(wcnt new1) = 0;
		wcnt getBlkSize() const { return _blkbyte; }

	private:
		wcnt _blkbyte;
	};
}

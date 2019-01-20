#pragma once

#include "MemoryHaver.hpp"

namespace wrd
{
	class Allocator : public MemoryHaver
	{	WRD_CLASS_DECL(Allocator, MemoryHaver)
	public:
		Allocator(wcnt blksize = 1);

	public:
		//	Allocator:
		virtual void* new1() = 0;
		virtual Res& del(void* used, wcnt sz) = 0;
		virtual Res& resize(wcnt new1) = 0;
		wcnt getBlkSize() const;
		//	Thing:
		virtual Res& release();

	private:
		wcnt _blksize;
	};
}

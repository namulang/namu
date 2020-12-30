#pragma once

#include "MemoryHaver.hpp"

namespace wrd { namespace memlite {

	class Allocator : public MemoryHaver {
        WRD_DECL_THIS(Allocator, MemoryHaver)
        WRD_INIT_META(This)

	public:
        //  Allocator:
		Allocator(wcnt blksize = 1);

		virtual void* new1() = 0;
		virtual wbool del(void* used, wcnt sz) = 0;
		virtual wbool resize(wcnt new1) = 0;
		wcnt getBlkSize() const;

	private:
		wcnt _blksize;
	};
}}

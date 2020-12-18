#pragma once

#include "Allocator.hpp"

namespace wrd { namespace memlite {

	class Chunk : public Allocator {
        WRD_DECL_THIS(Chunk, Allocator)

	public:
		static constexpr wcnt INIT_SZ = 20;

		Chunk(wcnt blksize = 1, wbool is_fixed = true);
		virtual ~Chunk();

		virtual wcnt getLen() const;
		virtual wcnt getSize() const;
		virtual void* new1();
		virtual wbool del(void* used, wcnt);
		virtual wbool rel();
		/// @remark	@ref Chunk can resize its data. but can't persist whole memory allocated before,
		///			it's a kind of memory flashing and can't give a way for accessing it.
		///			at outside, ptr for them should be daggled.
		virtual wbool resize(wcnt new_sz);
		virtual wbool has(const Instance& it) const;
		const wuchar* getEOB() const;
		const wuchar* getHeap() const;
		wbool isFixed() const;

	protected:
		/// @return	returns regarding current size, not length.
		///			can return garbage if size is bigger than n.
		virtual void* _get(widx n);

	private:
		wuchar* _getEOB();
		wbool _index(widx start);
		wcnt _getRealBlkSize() const;
		void* _allocHeap(wcnt new_sz);
		wbool _freeHeap(wuchar** heap);

		widx _head;
		wcnt _len, _sz;
		wuchar* _heap;
		wbool _isFixed;
	};
}}

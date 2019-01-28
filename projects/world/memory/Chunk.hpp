#pragma once

#include "Allocator.hpp"

namespace wrd
{
	class Chunk : public Allocator
	{	WRD_CLASS_DECL(Chunk, Allocator)
	public:
		static constexpr wcnt INIT_SZ = 20;

	public:
		Chunk(wcnt blksize = 1, wbool is_fixed = true);
		virtual ~Chunk();

	public:
		virtual wcnt getLen() const;
		virtual wcnt getSize() const;
		virtual void* new1();
		virtual Res& del(void* used, wcnt);
		virtual Res& release();
		virtual Res& resize(wcnt new_size);
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
		Res& _index(widx start);
		wcnt _getRealBlkSize() const;
		void* _allocHeap(wcnt new_size);
		Res& _freeHeap(wuchar** heap);
		Res& _release();

	private:
		widx _head;
		wcnt _len, _sz;
		wuchar* _heap;
		wbool _is_fixed;
	};
}

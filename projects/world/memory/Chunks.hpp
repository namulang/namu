#pragma once

#include "Chunk.hpp"

namespace wrd
{
	class Chunks : public Allocator
	{	WRD_CLASS_DECL(Chunks, Allocator)
	public:
		Chunks(wcnt blkbyte = 0);
		virtual ~Chunks();

	public:
		//	MemoryHaver:
		Chunk& operator[](widx n);
		Chunk& operator[](const Instance& inst);
		const Chunk& operator[](widx n) const;
		const Chunk& operator[](const Instance& inst) const;

	public:
		//	Allocator:
		virtual void* new1();
		virtual Res& del(void* pt, wcnt sz);
		virtual wbool has(const Instance& it) const;
		virtual Res& resize(wcnt new1);
		//	MemoryHaver:
		Chunk& get(widx n);
		Chunk& get(const Instance& it);
		const Chunk& get(const Instance& it) const;
		const Chunk& get(widx n) const;
		virtual wcnt getLen() const;
		virtual wcnt getSize() const;
		//	Thing:
		virtual Res& release();

	private:
		widx _findCapable();
		Res& _release();
		void* _get(widx n);

	private:
		std::vector<Chunk*> _chunks;
		int _s;
	};
}

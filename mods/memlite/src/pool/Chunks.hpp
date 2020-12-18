#pragma once

#include "Chunk.hpp"

namespace wrd { namespace memlite {

	class Chunks : public Allocator {
        WRD_DECL_THIS(Chunks, Allocator)

	public:
		Chunks(wcnt blkbyte = 0);
		virtual ~Chunks();

		//	MemoryHaver:
		Chunk& operator[](widx n);
		Chunk& operator[](const Instance& inst);
		const Chunk& operator[](widx n) const;
		const Chunk& operator[](const Instance& inst) const;

		//	Allocator:
		virtual void* new1();
		virtual wbool del(void* pt, wcnt sz);
		virtual wbool has(const Instance& it) const;
		virtual wbool resize(wcnt new1);
		//	MemoryHaver:
		Chunk& get(widx n);
		Chunk& get(const Instance& it);
		const Chunk& get(const Instance& it) const;
		const Chunk& get(widx n) const;
		virtual wcnt getLen() const;
		virtual wcnt getSize() const;
		virtual wbool rel();

	private:
		widx _findCapable();
		wbool _rel();
		virtual void* _get(widx n);

		std::vector<Chunk*> _chunks;
		int _s;
	};
}}

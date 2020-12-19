#pragma once

#include "Chunk.hpp"

namespace wrd { namespace memlite {

	class Chunks : public Allocator {
        WRD_DECL_THIS(Chunks, Allocator)
        WRD_INIT_META(This)

	public:
        //  Chunks:
		Chunks(wcnt blkbyte = 0);
		virtual ~Chunks();

		Chunk& operator[](widx n);
		Chunk& operator[](const Instance& inst);
		const Chunk& operator[](widx n) const;
		const Chunk& operator[](const Instance& inst) const;

		//	Chunks:
		Chunk& get(widx n);
		Chunk& get(const Instance& it);
		const Chunk& get(const Instance& it) const;
		const Chunk& get(widx n) const;
		//	Allocator:
		void* new1();
		wbool del(void* pt, wcnt sz);
		wbool resize(wcnt new1);
        //  MemoryHaver:
		wbool has(const Instance& it) const;
		wcnt getLen() const;
		wcnt getSize() const;
		wbool rel();

	private:
        //  Chunks:
		widx _findCapable();
		wbool _rel();
        //  MemoryHaver:
		void* _get(widx n);

		std::vector<Chunk*> _chunks;
		int _s;
	};
}}

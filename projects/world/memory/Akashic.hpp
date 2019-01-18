#pragma once

#include "Chunk.hpp"
#include "Unit.hpp"

namespace wrd
{
	class Akashic : public Chunk
	{	WRD_CLASS_DECL(Akashic, Chunk)
		friend class Instancer;
		friend class Block;
	public:
		Akashic();

	public:
		//	Chunk:
		Unit& operator[](widx n);
		Unit& operator[](Id id);
		const Unit& operator[](widx n) const;
		const Unit& operator[](Id id) const;

	public:
		//	Chunk:
		virtual void* new1();
		Unit& get(widx n);
		const Unit& get(widx n) const;

	protected:
		//	Chunk:
		Id _genId(void* pt) const;
		widx _getIdx(void* it) const;
	};
}

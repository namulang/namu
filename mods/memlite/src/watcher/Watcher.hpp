#pragma once

#include "../pool/Chunk.hpp"
#include "Unit.hpp"

namespace wrd { namespace memlite {

	class Watcher : public Chunk {
        WRD_DECL_THIS(Watcher, Chunk)
        WRD_INIT_META(This)
		friend class Instancer;
		friend class BindTag;

	public:
		Watcher();

		//	Chunk:
		Unit& operator[](widx n);
		Unit& operator[](Id id);
		const Unit& operator[](widx n) const;
		const Unit& operator[](Id id) const;

		//	Chunk:
		virtual void* new1();
		Unit& get(widx n);
		Unit& get(Id id);
		const Unit& get(widx n) const;
		const Unit& get(Id id) const;

	protected:
		//	Chunk:
		Id _genId(void* pt) const;
		widx _getIdx(void* it) const;
	};
}}

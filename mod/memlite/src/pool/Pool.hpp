#pragma once

#include "Chunks.hpp"

namespace wrd {

	class Pool : public MemoryHaver {
        WRD_DECL_THIS(Pool, MemoryHaver)
        WRD_INIT_META(This)

	public:
        //  Pool:
		Pool();
		virtual ~Pool();

		Chunks& operator[](widx n);
		Chunks& operator[](const Instance& inst);
		const Chunks& operator[](widx n) const;
		const Chunks& operator[](const Instance& inst) const;

		Chunks& get(const Instance& inst);
		const Chunks& get(const Instance& inst) const;
		const Chunks& get(widx n) const;
		Chunks& get(widx n);
        //  MemoryHaver:
		wbool has(const Instance& it) const;
		wcnt getSize() const;
		wcnt getLen() const;
		wbool rel();

	protected:
        //  MemoryHaver:
		void* _get(widx n);

	private:
		std::vector<Chunks*> _chunks;
	};
}

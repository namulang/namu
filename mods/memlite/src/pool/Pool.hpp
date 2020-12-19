#pragma once

#include "Chunks.hpp"

namespace wrd { namespace memlite {

	class Pool : public MemoryHaver {
        WRD_DECL_THIS(Pool, MemoryHaver)
        WRD_INIT_META(This)

	public:
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
		virtual wbool has(const Instance& it) const;
		virtual wcnt getSize() const;
		virtual wcnt getLen() const;
		virtual wbool rel();

	protected:
		virtual void* _get(widx n);

	private:
		std::vector<Chunks*> _chunks;
	};
}}

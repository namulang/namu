#pragma once

#include "Chunks.hpp"

namespace wrd
{
	class Pool : public MemoryHaver
	{	WRD_CLASS(Pool, MemoryHaver)
	public:
		Pool();
		virtual ~Pool();

	public:
		Chunks& operator[](widx n);
		Chunks& operator[](const Instance& inst);
		const Chunks& operator[](widx n) const;
		const Chunks& operator[](const Instance& inst) const;

	public:
		Chunks& get(const Instance& inst);
		const Chunks& get(const Instance& inst) const;
		const Chunks& get(widx n) const;
		Chunks& get(widx n);
		virtual wbool has(const Instance& it) const;
		virtual wcnt getSize() const;
		virtual wcnt getLen() const;
		virtual Res& release();

	protected:
		virtual void* _get(widx n);

	private:
		std::vector<Chunks*> _chunkset;
	};
}

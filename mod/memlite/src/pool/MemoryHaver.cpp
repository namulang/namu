#include "MemoryHaver.hpp"

namespace wrd { namespace memlite {

	WRD_DEF_THIS(MemoryHaver)

	void* This::operator[](widx n) { return get(n); }
	const void* This::operator[](widx n) const { return get(n); }

	void* This::get(widx n) {
		// this guards cant exist at Chunk::_get().
		// we should put here.
		if(n < 0 || n >= getLen()) return WRD_NULL;

		return _get(n);
	}

	const void* This::get(widx n) const WRD_UNCONST_FUNC(get(n))
	wbool This::isFull() const { return getLen() >= getSize(); }
	wbool This::isCapable() const { return getLen() < getSize(); }
}}

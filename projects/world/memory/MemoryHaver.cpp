#include "MemoryHaver.hpp"
#include "../meta.hpp"

namespace wrd
{
#define THIS MemoryHaver
	WRD_CLASS_DEF(THIS)

	void* THIS::operator[](widx n) { return get(n); }
	const void* THIS::operator[](widx n) const { return get(n); }
	void* THIS::get(widx n)
	{
		// this guards cant exist at Chunk::_get().
		// we should put here.
		if(n < 0 || n >= getLen())
			return NULL;
		return _get(n);
	}
	const void* THIS::get(widx n) const { return ((MemoryHaver*)this)->get(n); }
	wbool THIS::isFull() const { return getLen() >= getSize(); }
	wbool THIS::isCapable() const { return getLen() < getSize(); }
}

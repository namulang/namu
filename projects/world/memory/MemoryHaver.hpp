#pragma once

#include "../base/Thing.inl"

namespace wrd
{
	class MemoryHaver : public Thing
	{	WRD_CLASS_DECL(MemoryHaver, Thing)
	public:
		void* operator[](widx n) { return get(n); }
		const void* operator[](widx n) const { return get(n); }

	public:
		void* get(widx n) { return _get(n); }
		const void* get(widx n) const { return ((MemoryHaver*)this)->_get(n); }
		virtual wcnt getLen() const = 0;
		virtual wcnt getSize() const = 0;
		wbool isFull() const { return getLen() >= getSize(); }
		wbool isCapable() const { return getLen() < getSize(); }
		virtual wbool has(const Instance& it) const = 0;

	protected:
		virtual void* _get(widx n) = 0;
	};

}

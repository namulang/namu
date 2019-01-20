#pragma once

#include "../base/Thing.inl"

namespace wrd
{
	class MemoryHaver : public Thing
	{	WRD_CLASS_DECL(MemoryHaver, Thing)
	public:
		void* operator[](widx n);
		const void* operator[](widx n) const;

	public:
		void* get(widx n);
		const void* get(widx n) const;
		virtual wcnt getLen() const = 0;
		virtual wcnt getSize() const = 0;
		wbool isFull() const;
		wbool isCapable() const;
		virtual wbool has(const Instance& it) const = 0;

	protected:
		virtual void* _get(widx n) = 0;
	};
}

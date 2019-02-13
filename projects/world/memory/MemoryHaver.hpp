#pragma once

#include "../base/Thing.inl"
#include "../containers/Lengthable.hpp"

namespace wrd
{
	class MemoryHaver : public Thing, public Lengthable
	{	WRD_CLASS_DECL(MemoryHaver, Thing)
	public:
		void* operator[](widx n);
		const void* operator[](widx n) const;

	public:
		void* get(widx n);
		const void* get(widx n) const;
		virtual wbool has(const Instance& it) const = 0;

	protected:
		virtual void* _get(widx n) = 0;
	};
}

#pragma once

#include "../base/Thing.hpp"

namespace wrd
{
	class Instance;
	class Res;

	class Bindable
	{	WRD_INHERIT(Bindable)
	public:
        const Instance* operator->() const;
        Instance* operator->();
        const Instance* operator*() const;
        Instance* operator*();
        operator wbool() const;
	
	public:
		Res& bind(const Instance& it);
		Res& bind(Instance& it);
		virtual Res& unbind() = 0;
		virtual wbool isBind() const = 0;
		Instance& get();
		const Instance& get() const;
		template <typename T> T& get() {
			Instance& got = WRD_GET(_get(), nulr<T>())
			return got.down<T>();
		}
		template <typename T> const T& get() const {
			WRD_UNCONST();
			return unconst.get<T>();
		}

	protected:
		virtual Instance& _get() = 0;
		virtual Res& _bind(const Instance& it) = 0;
	};
}



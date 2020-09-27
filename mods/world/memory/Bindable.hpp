#pragma once

#include "../base/Instance.hpp"

namespace wrd
{
	class Instance;
	class Res;

	class Bindable
	{	WRD_INHERIT(Bindable)
	public:
        const Instance* operator->() const;
        Instance* operator->();
        const Instance& operator*() const;
        Instance& operator*();
        operator wbool() const;
	
	public:
		Res& bind(const Instance& it);
		virtual const Class& getBindable() const = 0;
		wbool canBind(const Instance& it);
		virtual wbool canBind(const Class& it) const = 0;
		virtual Res& unbind() = 0;
		virtual wbool isBind() const = 0;
		Instance& get();
		const Instance& get() const;
		template <typename T> T& get() {
			Instance& got = _get(); 
			if(got.isNull())
				return nulr<T>();
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



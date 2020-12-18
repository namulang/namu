#pragma once

#include "../interface/Instance.hpp"

namespace wrd { namespace memlite {

	class Bindable {
        WRD_DECL_THIS(Bindable)

	public:
        const Instance* operator->() const;
        Instance* operator->();
        const Instance& operator*() const;
        Instance& operator*();
        operator wbool() const;

		wbool bind(const Instance& it);
		virtual const Type& getBindable() const = 0;
		wbool canBind(const Instance& it);
		virtual wbool canBind(const Type& it) const = 0;
		virtual wbool unbind() = 0;
		virtual wbool isBind() const = 0;
		Instance& get();
		const Instance& get() const;

		template <typename T> T& get() {
			Instance& got = WRD_GETS(_get());
            WRD_NUL(got, nulr<T>())

            if(!got.getType().isSub(TType<T>::get()))
                return nulr<T>();

            return (T&) got;
		}

		template <typename T> const T& get() const WRD_UNCONST_FUNC(get<T>())

	protected:
		virtual Instance& _get() = 0;
		virtual wbool _bind(const Instance& it) = 0;
	};
}}

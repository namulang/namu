#pragma once

#include "../interface/Instance.hpp"

namespace wrd {

    template <typename T>
	class TBindable {
        WRD_DECL_THIS(TBindable)
        WRD_INIT_META(This)

	public:
        //  TBindable:
        const T* operator->() const;
        T* operator->();
        const T& operator*() const;
        T& operator*();
        operator wbool() const;

		wbool bind(T& it) { return _bind(it); }
        virtual wbool unbind() = 0;
		wbool canBind(const T& it);
		virtual wbool canBind(const Type& it) const = 0;
		virtual wbool isBind() const = 0;
		T& get();
		const T& get() const;

		template <typename E> E& get() {
			T& got = _get();
            WRD_NUL(got, nulr<E>())

            if(!got.getType().isSub(TType<E>::get()))
                return nulr<E>();

            return (E&) got;
		}

		template <typename E> const E& get() const WRD_UNCONST_FUNC(get<E>())

	protected:
        //  TBindable:
		virtual T& _get() = 0;
        virtual wbool _bind(const T& it) = 0;
	};
}

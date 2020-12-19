#pragma once

#include "Bind.hpp"

namespace wrd { namespace memlite {

	template <typename T>
	class TWeak : public Bind {
        WRD_DECL_THIS(TWeak)
        WRD_INIT_META(This)
		friend class BindTag;

	public:
        /// TWeak:
		TWeak();
		TWeak(T& it);
		TWeak(T* it);
		TWeak(const This& rhs);

        const T* operator->() const;
        const T& operator*() const;
        T* operator->();
        T& operator*();
		This& operator=(const This& rhs);
		T& get();
		const T& get() const;

		wbool bind(T& new1);
        //  Bindable:
		const Type& getBindable() const;
        using Bindable::get;
		wbool isConst() const;
        //  TypeProvidable:
        const Type& getType() const {
            return TType<This>::get();
        }
	};
	template <typename T>
	class TWeak<const T> : public Bind {
        WRD_DECL_THIS(TWeak, Bind)
        WRD_INIT_META(This)
		friend class BindTag;

	public:
        /// TWeak:
		TWeak();
		TWeak(T& it);
		TWeak(T* it);
		TWeak(const T& it);
		TWeak(const T* it);
		TWeak(const This& rhs);
		TWeak(const TWeak<T>& rhs);

        const T* operator->() const;
        const T& operator*() const;
		This& operator=(const This& rhs);
		This& operator=(const TWeak<T>& rhs);

		wbool bind(T& new1);
		wbool bind(const T& new1);
		const T& get() const;
        //  Bindable:
		const Type& getBindable() const;
        using Bindable::get;
		wbool isConst() const;
        //  TypeProvidable:
        const Type& getType() const {
            return TType<This>::get();
        }
	};
}}

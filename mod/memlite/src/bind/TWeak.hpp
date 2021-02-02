#pragma once

#include "Bind.hpp"

namespace wrd { namespace memlite {

	template <typename T>
	class TWeak : public Bind {
        WRD_DECL_THIS(TWeak, Bind)
        WRD_INIT_META(This)
		friend class BindTag;

	public:
        /// TWeak:
		TWeak();
		TWeak(T& it);
		TWeak(T* it);
		TWeak(const Bind& rhs);

        const T* operator->() const;
        const T& operator*() const;
        T* operator->();
        T& operator*();
		This& operator=(const Bind& rhs);
		T& get();
		const T& get() const;

		wbool bind(T& new1);
        //  Bindable:
        using Bindable::get;

    protected:
        TWeak(BindTacticable* tactic);
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
		TWeak(const Bind& rhs);

        const T* operator->() const;
        const T& operator*() const;
		This& operator=(const Bind& rhs);

		wbool bind(T& new1);
		wbool bind(const T& new1);
		const T& get() const;
        //  Bindable:
        using Bindable::get;

    protected:
        TWeak(BindTacticable* tactic);
	};
}}

#pragma once

#include "Bind.hpp"

namespace wrd {

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
		TWeak(const T& it);
		TWeak(const T* it);
		TWeak(const Bind& rhs);

        const T* operator->() const;
        const T& operator*() const;
        T* operator->();
        T& operator*();
		This& operator=(const Bind& rhs);
		T& get();
		const T& get() const;

		wbool bind(T& new1);
        //  TBindable:
		wbool bind(T& new1);
        using TBindable::get;
        using TBindable::bind;

    protected:
        TWeak(BindTacticable* tactic);
	};
}

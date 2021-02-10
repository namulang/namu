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
        TWeak(Bind& rhs);

        T* operator->();
        T& operator*();
        This& operator=(Bind& rhs);
        T& get();

        wbool bind(T& new1);
        //  TBindable:
        using TBindable::get;
        using TBindable::bind;

    protected:
        TWeak(BindTacticable* tactic);
    };
}

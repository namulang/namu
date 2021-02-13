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
        TWeak(const T& it);
        TWeak(const T* it);
        TWeak(const Bind& rhs);

        T* operator->() override;
        T& operator*() override;
        const T* operator->() const WRD_UNCONST_FUNC(operator->())
        const T& operator*() const WRD_UNCONST_FUNC(operator*())
        This& operator=(const Bind& rhs);
        //  TBindable:
        using TBindable::get;
        T& get() override;
        const T& get() const WRD_UNCONST_FUNC(get())

        using TBindable::bind;
        wbool bind(const T& new1);

    protected:
        TWeak(BindTacticable& tactic);
    };
}

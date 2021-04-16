#pragma once

#include "Bind.hpp"

namespace wrd {

    template <typename T>
    class TWeak : public Bind {
        WRD_DECL_ME(TWeak, Bind)
        WRD_INIT_META(me)
        friend class BindTag;

    public:
        /// TWeak:
        TWeak();
        explicit TWeak(const T& it);
        explicit TWeak(const T* it);
        TWeak(const me& rhs);
        explicit TWeak(const Bind& rhs);

        T* operator->() override;
        T& operator*() override;
        const T* operator->() const WRD_UNCONST_FUNC(operator->())
        const T& operator*() const WRD_UNCONST_FUNC(operator*())
        me& operator=(const Bind& rhs);
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

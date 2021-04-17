#pragma once

#include "binder.hpp"

namespace wrd {

    template <typename T>
    class tweak : public binder {
        WRD_DECL_ME(tweak, binder)
        WRD_INIT_META(me)
        friend class bindTag;

    public:
        /// tweak:
        tweak();
        explicit tweak(const T& it);
        explicit tweak(const T* it);
        tweak(const me& rhs);
        explicit tweak(const binder& rhs);

        T* operator->() override;
        T& operator*() override;
        const T* operator->() const WRD_UNCONST_FUNC(operator->())
        const T& operator*() const WRD_UNCONST_FUNC(operator*())
        me& operator=(const binder& rhs);
        //  tbindable:
        using tbindable::get;
        T& get() override;
        const T& get() const WRD_UNCONST_FUNC(get())

        using tbindable::bind;
        wbool bind(const T& new1);

    protected:
        tweak(bindTacticable& tactic);
    };
}

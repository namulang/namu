#pragma once

#include "binder.hpp"
#include "weakTactic.hpp"

namespace namu {

    template <typename T, typename TACTIC = weakTactic>
    class tweak : public binder {
        WRD_DECL_ME(tweak, binder)
        WRD_INIT_META(me)
        friend class bindTag;

    public:
        /// tweak:
        tweak();
        tweak(const type& subtype);
        tweak(const T& it);
        tweak(const T* it);
        tweak(const me& rhs);
        explicit tweak(const binder& rhs);

        T* operator->();
        T& operator*();
        const T* operator->() const WRD_UNCONST_FUNC(operator->())
        const T& operator*() const WRD_UNCONST_FUNC(operator*())
        me& operator=(const binder& rhs);

        using super::get;
        T& get();
        const T& get() const WRD_UNCONST_FUNC(get())

        using tbindable::bind;
        wbool bind(const T& new1);
    };
}

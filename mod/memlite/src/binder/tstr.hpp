#pragma once

#include "tweak.hpp"

namespace wrd {

    template <typename T>
    class tstr : public tweak<T> {
        WRD_DECL_ME(tstr, tweak<T>)
        WRD_INIT_META(me)

    public:
        //  tstr:
        tstr();
        tstr(const T& it);
        tstr(const T* it);
        tstr(const me& rhs);
        tstr(const binder& rhs);

        using super::operator=;
    };
}

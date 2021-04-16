#pragma once

#include "TWeak.hpp"

namespace wrd {

    template <typename T>
    class TStr : public TWeak<T> {
        WRD_DECL_ME(TStr, TWeak<T>)
        WRD_INIT_META(me)

    public:
        //  TStr:
        TStr();
        explicit TStr(const T& it);
        explicit TStr(const T* it);
        TStr(const me& rhs);
        explicit TStr(const Bind& rhs);

        using super::operator=;
    };
}

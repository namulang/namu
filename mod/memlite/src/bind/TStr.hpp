#pragma once

#include "TWeak.hpp"

namespace wrd {

    template <typename T>
    class TStr : public TWeak<T> {
        WRD_DECL_THIS(TStr, TWeak<T>)
        WRD_INIT_META(This)

    public:
        //  TStr:
        TStr();
        explicit TStr(const T& it);
        explicit TStr(const T* it);
        TStr(const This& rhs);
        explicit TStr(const Bind& rhs);

        using Super::operator=;
    };
}

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
        TStr(T& it);
        TStr(T* it);
        TStr(const T& it);
        TStr(const T* it);
        TStr(const Bind& rhs);

        using Super::operator=;
    };
}

#pragma once

#include "Gettable.hpp"

namespace wrd
{
    template <typename T, typename S>
    class TGettable : public S
    {  WRD_CLASS(TGettable, S)
    public:
        T& get() { return _get().cast<T>(); }
        const T& get() const { return _get().cast<const T>(); }
    };
}

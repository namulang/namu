#pragma once

#include "TBindable.inl"

namespace wrd
{
    template <typename T, typename S>
    class TBindable : public S
    {  WRD_CLASS(TBindable, S)
    public:
        const T* operator->() const { return &get(); }
        T* operator->() { return &get(); }
        const T* operator*() const { return &get(); }
        T* operator*() { return &get(); }
    };
}

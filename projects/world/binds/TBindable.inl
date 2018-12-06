#pragma once

#include "Bindable.hpp"
#include "../bases/Instance.hpp"

namespace wrd
{
    template <typename T>
    class TBindable : public Bindable
    {
    public:
        const T* operator->() const;
        T* operator->();
        const T* operator*() const;
        T* operator*();

    public:
        T& get();
        const T& get() const;

    private:
        virtual Instance& _get() = 0;
    };
}

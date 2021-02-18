#pragma once

#include "../common.hpp"

namespace wrd {

    template <typename T>
    class TIter : public Iter {
        WRD_CLASS(TIter, Iter)

    public:
        /// @return true if there are more data to proceed
        T& operator*() override { return (T&) _get(); }
        T* operator->() override { return (T*) &_get(); }
        const T& operator*() const override { return (T&) _get(); }
        const T* operator->() const override { return (T*) &_get(); }

        T& get() override { return (T&) _get(); }
        const T& get() const override { return (T&) _get(); }
    };
}

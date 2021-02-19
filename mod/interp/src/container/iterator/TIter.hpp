#pragma once

#include "../../common.hpp"

namespace wrd {

    template <typename T>
    class TIter : public Iter {
        WRD_CLASS(TIter, Iter)

    public:
        /// @return true if there are more data to proceed
        T& operator*() override { return (T&) get(); }
        T* operator->() override { return (T*) &get(); }
        const T& operator*() const override { return (T&) get(); }
        const T* operator->() const override { return (T*) &get(); }

        T& get() override { return (T&) get(); }
        const T& get() const override { return (T&) get(); }
    };
}

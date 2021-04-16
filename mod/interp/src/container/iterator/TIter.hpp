#pragma once

#include "../../common.hpp"

namespace wrd {

    template <typename T>
    class TIter : public Iter {
        WRD_CLASS(TIter, Iter)

    public:
        TIter() {}
        explicit TIter(Iteration* newStep): super(newStep) {}

        /// @return true if there are more data to proceed
        me operator+(wcnt step) {
            next(step);
            return *this;
        }
        me& operator++() {
            next(1);
            return *this;
        }
        me operator++(int) {
            me ret = *this;
            next(1);
            return ret;
        }
        me& operator+=(wcnt step) {
            next(step);
            return *this;
        }

        T& operator*() override { return (T&) get(); }
        T* operator->() override { return (T*) &get(); }
        const T& operator*() const override { return (const T&) get(); }
        const T* operator->() const override { return (const T*) &get(); }

        T& get() override { return (T&) super::get(); }
        const T& get() const { return (const T&) super::get(); }
    };
}

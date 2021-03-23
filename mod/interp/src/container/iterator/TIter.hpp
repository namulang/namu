#pragma once

#include "../../common.hpp"

namespace wrd {

    template <typename T>
    class TIter : public Iter {
        WRD_CLASS(TIter, Iter)

    public:
        TIter() {}
        TIter(Iteration* newStep): Super(newStep) {}

        /// @return true if there are more data to proceed
        This operator+(wcnt step) {
            next(step);
            return *this;
        }
        This& operator++() {
            next(1);
            return *this;
        }
        This operator++(int) {
            This ret = *this;
            next(1);
            return ret;
        }
        This& operator+=(wcnt step) {
            next(step);
            return *this;
        }

        T& operator*() override { return (T&) get(); }
        T* operator->() override { return (T*) &get(); }
        const T& operator*() const override { return (const T&) get(); }
        const T* operator->() const override { return (const T*) &get(); }

        T& get() override { return (T&) Super::get(); }
        const T& get() const { return (const T&) Super::get(); }
    };
}

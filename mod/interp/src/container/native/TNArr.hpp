#pragma once

#include "NArr.hpp"

namespace wrd {

    template <typename T>
    class TNArr : public NArr {
        WRD_CLASS(TNArr, NArr)

    public:
        T& operator[](widx n) { return get(n); }
        const T& operator[](widx n) { return get(n); }

        using Super::get;
        T& get(widx n) override { return (T&) Super::get(n); }
        const T& get(widx n) const { return (T&) Super::get(n); }

        using Super::set;
        wbool set(widx n, const T& new1) override {
            return Super::set(n, new1);
        }

        TIter<T> head() const override { return iter(0); }
        TIter<T> tail() const override { return iter(getLen()); }
        TIter<T> iter(widx n) const {
        }
        TIter<T> iter(const T& elem) const {
            return Super::iter(elem);
        }

        wbool add(const T& new1) {
            return Super::add(new1);
        }
        wbool add(const Iter& e, const T& new1) override {
            return Super::add(e, new1);
        }

        wcnt del(const T& it) {
            return Super::del(it);
        }
    };
}

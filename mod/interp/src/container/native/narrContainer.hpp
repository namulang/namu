#pragma once

#include "ncontainer.hpp"
#include "../arrContainable.hpp"

namespace wrd {

    class narrContainer : public ncontainer, public arrContainable {
        WRD_INTERFACE(narrContainer, ncontainer)

    public:
        node& operator[](widx n) override { return get(n); }
        const node& operator[](widx n) const override { return get(n); }

        using super::get;
        using arrContainable::get;

        using super::set;
        using arrContainable::set;

        iterator iter(widx n) const override {
            return iterator(_onIter(n));
        }
        iterator iter(const node& elem) const;

        using super::add;
        using arrContainable::add;

        using super::del;
        using arrContainable::del;
        wbool del(const node& it) override { return del(iter(it)); }
    };
}

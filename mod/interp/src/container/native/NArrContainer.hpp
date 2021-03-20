#pragma once

#include "NContainer.hpp"
#include "../ArrContainable.hpp"

namespace wrd {

    class NArrContainer : public NContainer, public ArrContainable {
        WRD_INTERFACE(NArrContainer, NContainer)

    public:
        Node& operator[](widx n) override { return get(n); }
        const Node& operator[](widx n) const override { return get(n); }

        using Super::get;
        using ArrContainable::get;
        const Node& get(widx n) const override WRD_UNCONST_FUNC(get(n))

        using Super::set;
        using ArrContainable::set;

        Iter iter(widx n) const override {
            return Iter(_onIter(n));
        }
        Iter iter(const Node& elem) const;

        using Super::add;
        using ArrContainable::add;

        using Super::del;
        using ArrContainable::del;
        wbool del(const Node& it) override { return del(iter(it)); }
    };
}

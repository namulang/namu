#pragma once

#include "ncontainer.hpp"
#include "../ucontainable.hpp"

namespace wrd {

    class narrContainer : public ncontainer, public ucontainable {
        WRD(INTERFACE(narrContainer, ncontainer))

    public:
        using super::get;
        using ucontainable::get;

        using super::set;
        using ucontainable::set;

        using super::add;
        using ucontainable::add;

        using super::del;
        using ucontainable::del;
    };
}

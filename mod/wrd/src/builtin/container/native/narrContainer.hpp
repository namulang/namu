#pragma once

#include "ncontainer.hpp"
#include "../arrContainable.hpp"

namespace wrd {

    class narrContainer : public ncontainer, public arrContainable {
        WRD(INTERFACE(narrContainer, ncontainer))

    public:
        using super::get;
        using arrContainable::get;

        using super::set;
        using arrContainable::set;

        using super::add;
        using arrContainable::add;

        using super::del;
        using arrContainable::del;
    };
}

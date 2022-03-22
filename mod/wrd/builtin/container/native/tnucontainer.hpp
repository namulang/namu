#pragma once

#include "../tucontainable.hpp"

namespace wrd {

    template <typename T>
    class tnucontainer : public instance, public tucontainable<T>, public clonable {
        WRD(INTERFACE(tnucontainer, instance))
    };

    class node;
    typedef tnucontainer<node> nucontainer;
}

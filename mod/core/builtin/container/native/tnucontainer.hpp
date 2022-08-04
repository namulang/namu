#pragma once

#include "../tucontainable.hpp"

namespace namu {

    template <typename T>
    class tnucontainer : public instance, public tucontainable<T>, public clonable {
        NAMU(ADT(tnucontainer, instance))
    };

    class node;
    typedef tnucontainer<node> nucontainer;
}

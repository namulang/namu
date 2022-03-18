#pragma once

#include "../tucontainable.hpp"
#include "../tarrayable.hpp"

namespace wrd {

    template <typename T>
    class tuncontainer : public instance, public tucontainable<T>, public tarrayable<T>, public clonable {
        WRD(INTERFACE(tuncontainer, instance))
    };
}

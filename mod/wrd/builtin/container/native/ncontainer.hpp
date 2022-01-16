#pragma once

#include "../containable.hpp"

namespace wrd {

    class ncontainer : public instance, public containable, public clonable {
        WRD(INTERFACE(ncontainer, instance))
    };
}

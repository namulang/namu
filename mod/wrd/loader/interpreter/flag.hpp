#pragma once

#include "../../common.hpp"

namespace wrd {

    class interpreter;
    class flag : public instance, public clonable {
        WRD(INTERFACE(flag, instance))

    public:
        virtual void update(interpreter& ip) = 0;
    };

    typedef std::vector<tstr<flag>> flags;
}

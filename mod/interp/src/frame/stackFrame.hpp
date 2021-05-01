#pragma once

#include "../builtin/container/mgd/tarr.hpp"
#include "frame.hpp"

namespace wrd {

    class stackFrame : public tarr<frame> {
        WRD_CLASS(stackFrame, arr)

    public:
        frame& getCurrentFrame() {
            return get(len() - 1);
        }
    };
}

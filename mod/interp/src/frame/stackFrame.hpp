#pragma once

#include "../builtin/container/mgd/tarr.hpp"
#include "frame.hpp"

namespace wrd {

    class stackFrame : public tarr<frame> {
        WRD(CLASS(stackFrame, tarr<frame>))

    public:
        frame& getCurrentFrame() {
            return get(len() - 1);
        }
    };
}

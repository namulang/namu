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

        const frame& getCurrentFrame() const WRD_UNCONST_FUNC(getCurrentFrame())
    };
}

#pragma once

#include "../builtin/container/TArr.hpp"
#include "Frame.hpp"

namespace wrd {

    class StackFrame : public TArr<Frame> {
        WRD_CLASS(StackFrame, Arr)

    public:
        Frame& getCurrentFrame() {
            return get(getLen() - 1);
        }
    };
}

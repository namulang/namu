#pragma once

#include "../builtin/container/Arr.hpp"
#include "Frame.hpp"

namespace wrd {

    class StackFrame : public TArr<Frame> {
        WRD_CLASS(StackFrame, Arr)

    public:
    };
}

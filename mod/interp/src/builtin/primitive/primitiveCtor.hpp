#pragma once

#include "../../ast/func.hpp"

namespace wrd {

    class primitiveCtor : public func {
        WRD_INTERFACE(primitiveCtor, func)

    public:
        primitiveCtor(): super("") {}

    protected:
        wbool _onInFrame(frame& sf, const ncontainer& args) override { return true; }
        wbool _onOutFrame(frame& sf, const ncontainer& args) override { return true; }
    };

}

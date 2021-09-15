#pragma once

#include "../func.hpp"

namespace wrd {

    class mgdFunc : public func {
        WRD(INTERFACE(mgdFunc, func))

    public:
        explicit mgdFunc(const std::string& name): super(name) {}

    protected:
        str _onCast(narr& castedArgs) override;
        virtual str _onRun(narr& args) = 0;

        wbool _onInFrame(frame& sf, const ncontainer& args) override;
        wbool _onOutFrame(frame& sf, const ncontainer& args) override;
    };
}

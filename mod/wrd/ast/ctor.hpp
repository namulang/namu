#pragma once

#include "func.hpp"

namespace wrd {

    class ctor: public func {
        WRD(ADT(ctor, func))

    public:
        ctor(const wtype& t): _type(t) {}

    public:
        const wtype& getRetType() const override { return _type; }
        const wtype& getEvalType() const override { return getRetType(); }

    private:
        const wtype& _type;
    };
}

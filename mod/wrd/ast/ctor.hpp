#pragma once

#include "func.hpp"

namespace wrd {

    class ctor: public func {
        WRD(ADT(ctor, func))

    public:
        ctor(const node& org): _org(org) {}

    public:
        const wtype& getRetType() const override { return _org->getEvalType(); }
        const wtype& getEvalType() const override { return getRetType(); }
        const node& getOrigin() const { return *_org; }

    private:
        str _org;
    };
}

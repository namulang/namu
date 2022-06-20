#pragma once

#include "func.hpp"

namespace wrd {

    class makeCtor: public func {
        WRD(ADT(makeCtor, func))

    public:
        makeCtor(const node& org): _org(org) {}

    public:
        const wtype& getRetType() const override { return _org->getEvalType(); }
        const wtype& getEvalType() const override { return getRetType(); }
        const node& getOrigin() const { return *_org; }

    private:
        str _org;
    };
}

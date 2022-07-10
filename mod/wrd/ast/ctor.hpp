#pragma once

#include "func.hpp"

namespace wrd {

    class ctor: public func {
        WRD(ADT(ctor, func))

    public:
        ctor(const node& org): _org(org) {}

    public:
        str getRet() const override { return _org->getEval(); }
        str getEval() const override { return getRet(); }
        const node& getOrigin() const { return *_org; }

    private:
        str _org;
    };
}

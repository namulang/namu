#pragma once

#include "func.hpp"

namespace namu {

    class ctor: public func {
        NAMU(ADT(ctor, func))
        friend class generalizer; // for _setOrigin()

    public:
        ctor(const node& org): _org(org) {}

    public:
        const node& getRet() const override { return _org->getEval(); }
        const node& getEval() const override { return getRet(); }
        const node& getOrigin() const { return *_org; }

    private:
        void _setOrigin(const node& newOrg) {
            _org.bind(newOrg);
        }

    private:
        str _org;
    };
}

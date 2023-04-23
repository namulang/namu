#pragma once

#include "func.hpp"

namespace namu {

    class ctor: public func {
        NAMU(ADT(ctor, func), VISIT())
        friend class generalizer; // for _setOrigin()

    public:
        ctor(const node& org);

    public:
        str getRet() const override;
        str getEval() const override;
        const node& getOrigin() const;

    private:
        void _setOrigin(const node& newOrg);

    private:
        str _org;
    };
}

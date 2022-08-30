#pragma once

#include "ctor.hpp"

namespace namu {

    class visitor;

    class _nout defaultCtor : public ctor {
        NAMU(CLASS(defaultCtor, ctor), VISIT())

    public:
        defaultCtor(const node& org): super(org) {}

    public:
        using super::run;
        str run(const args& a) override {
            if(a.len() >= 1) return str();

            return str((node*) getOrigin().clone());
        }
    };
}

#pragma once

#include "ctor.hpp"

namespace namu {

    class _nout defaultCtor : public ctor {
        NAMU(CLASS(defaultCtor, ctor))

    public:
        defaultCtor(const node& org): super(org) {}

    public:
        using super::run;
        str run(const ucontainable& args) override {
            if(args.len() >= 1) return str();

            return str((node*) getOrigin().clone());
        }
    };
}

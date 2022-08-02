#pragma once

#include "ctor.hpp"

namespace namu {

    class _nout defaultCopyCtor : public ctor {
        WRD(CLASS(defaultCopyCtor, ctor))

    public:
        defaultCopyCtor(const node& org): super(org) {}

    public:
        using super::run;
        str run(const ucontainable& args) override {
            if (!canRun(args)) return str();

            return str((node*) args.begin()->clone());
        }

        const params& getParams() const override {
            static params inner(*new param("rhs", getOrigin()));
            return inner;
        }
    };
}

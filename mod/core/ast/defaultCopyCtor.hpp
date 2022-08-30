#pragma once

#include "ctor.hpp"

namespace namu {

    class visitor;

    class _nout defaultCopyCtor : public ctor {
        NAMU(CLASS(defaultCopyCtor, ctor), VISIT())

    public:
        defaultCopyCtor(const node& org): super(org) {}

    public:
        using super::run;
        str run(const args& a) override {
            if (!canRun(a)) return str();

            return str((node*) a.begin()->clone());
        }

        const params& getParams() const override {
            static params inner(*new param("rhs", getOrigin()));
            return inner;
        }
    };
}

#pragma once

#include "ctor.hpp"

namespace namu {

    class visitor;

    class _nout defaultCopyCtor : public ctor {
        NAMU(CLASS(defaultCopyCtor, ctor), VISIT())

    public:
        defaultCopyCtor(const node& org): super(org) {
            _params.add(*new param("rhs", org));
        }

    public:
        using super::run;
        str run(const args& a) override {
            if (!canRun(a)) return str();

            return str((node*) a.begin()->clone());
        }

        const params& getParams() const override {
            return _params;
        }

    public:
        params _params;
    };
}

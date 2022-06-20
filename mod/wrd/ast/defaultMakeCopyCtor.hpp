#pragma once

#include "makeCtor.hpp"

namespace wrd {

    class _wout defaultMakeCopyCtor : public makeCtor {
        WRD(CLASS(defaultMakeCopyCtor, makeCtor))

    public:
        defaultMakeCopyCtor(const node& org): super(org) {}

    public:
        using super::run;
        str run(const ucontainable& args) override {
            if (!canRun(args)) return str();

            return str((node*) args.begin()->clone());
        }

        const params& getParams() const override {
            static params inner(*new param("rhs", getEvalType()));
            return inner;
        }
    };
}

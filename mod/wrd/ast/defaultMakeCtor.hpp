#pragma once

#include "makeCtor.hpp"

namespace wrd {

    class _wout defaultMakeCtor : public makeCtor {
        WRD(CLASS(defaultMakeCtor, makeCtor))

    public:
        defaultMakeCtor(const node& org): super(org) {}

    public:
        using super::run;
        str run(const ucontainable& args) override {
            if(args.len() >= 1) return str();

            str ret((node*) getOrigin().clone());
            ret->run(baseObj::CTOR_NAME, args);
            return ret;
        }

        wbool canRun(const ucontainable& args) const override {
            return !nul(getOrigin().sub<mgdFunc>(baseObj::CTOR_NAME, args));
        }
    };
}

#pragma once

#include "ctor.hpp"

namespace wrd {

    class _wout defaultCtor : public ctor {
        WRD(CLASS(defaultCtor, ctor))

    public:
        defaultCtor(const wtype& t): super(t) {}
        ~defaultCtor() {
            WRD_I("~defaultCtor");
        }

    public:
        using super::run;
        str run(const ucontainable& args) override {
            if(args.len() >= 1) return str();

            return str((node*) getEvalType().make());
        }
    };
}

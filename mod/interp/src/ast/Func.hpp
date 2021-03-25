#pragma once

#include "Scope.hpp"

namespace wrd {

    class Func : public Scope {
        WRD_INTERFACE(Func, Scope)

    public:
        explicit Func(const std::string& name): Super(name) {}

        using Super::subs;
        NContainer& subs() override {
            return _shares;
        }

        Str run(NContainer& args) override;

        virtual Str _onRun(NContainer& args) = 0;

        wbool canRun(const WTypes& types) const override {
            // TODO: check types
            return true;
        }

    protected:
        wbool _onInStackFrame(StackFrame& sf, NContainer& args) override;
        wbool _onOutStackFrame(StackFrame& sf, NContainer& args) override;

    private:
        NArr _shares; // shared nodes container.
    };

}

#pragma once

#include "Scope.hpp"

namespace wrd {

    class Func : public Scope {
        WRD_INTERFACE(Func, Scope)

    public:
        explicit Func(const std::string& name): Super(name) {}

        Str run(NContainer& args) override;
        wbool canRun(const WTypes& types) const override;

        /// @return object and parameter types.
        virtual const WTypes& getTypes() const;
        virtual const WType& getReturnType() const = 0;

    protected:
        virtual Str _onRun(NContainer& args) = 0;

        wbool _onInStackFrame(StackFrame& sf, NContainer& args) override;
        wbool _onOutStackFrame(StackFrame& sf, NContainer& args) override;
    };
}

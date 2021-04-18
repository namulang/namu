#pragma once

#include "scope.hpp"

namespace wrd {

    class func : public scope {
        WRD_INTERFACE(func, scope)

    public:
        explicit func(const std::string& name): super(name) {}

        str run(ncontainer& args) override;
        wbool canRun(const wtypes& types) const override;

        /// @return object and parameter types.
        virtual const wtypes& getTypes() const;
        virtual const wtype& getReturnType() const = 0;

    protected:
        virtual str _onRun(ncontainer& args) = 0;

        wbool _onInStackFrame(stackFrame& sf, ncontainer& args) override;
        wbool _onOutStackFrame(stackFrame& sf, ncontainer& args) override;
    };
}

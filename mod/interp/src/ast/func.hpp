#pragma once

#include "scope.hpp"
#include "../frame/frameInteractable.hpp"

namespace wrd {

    class func : public scope, public frameInteractable {
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

        wbool _onInFrame(frame& sf, ncontainer& args) override;
        wbool _onOutFrame(frame& sf, ncontainer& args) override;
    };
}

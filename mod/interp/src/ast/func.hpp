#pragma once

#include "node.hpp"
#include "../frame/frameInteractable.hpp"

namespace wrd {

    class func : public node, public frameInteractable {
        WRD_INTERFACE(func, node)

    public:
        explicit func(const std::string& name): _name(name) {}

        str run(ncontainer& args) override;

        using super::canRun;
        wbool canRun(const wtypes& types) const override;

        /// @return object and parameter types.
        virtual const wtypes& getTypes() const;
        virtual const wtype& getReturnType() const = 0;
        const std::string& getName() const override {
            return _name;
        }

    protected:
        virtual str _onRun(ncontainer& args) = 0;

        wbool _onInFrame(frame& sf, ncontainer& args) override;
        wbool _onOutFrame(frame& sf, ncontainer& args) override;

    private:
        std::string _name;
    };
}

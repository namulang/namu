#pragma once

#include "node.hpp"
#include "../builtin/container/native/tnarr.hpp"
#include "../frame/frameInteractable.hpp"

namespace wrd {

    class func : public node, public frameInteractable {
        WRD(INTERFACE(func, node))

    public:
        explicit func(const std::string& name): _name(name) {}

        using super::subs;
        ncontainer& subs() override { return _shares; }

        using super::run;
        str run(const containable& args) override;

        using super::canRun;
        wbool canRun(const wtypes& typs) const override;

        /// @return object and parameter types.
        virtual const wtypes& getTypes() const;
        virtual const wtype& getReturnType() const = 0;
        const std::string& getName() const override {
            return _name;
        }

    protected:
        virtual str _onCast(narr& castedArgs) = 0;

    private:
        tstr<narr> _asArgs(const containable& args);

    private:
        std::string _name;
        narr _shares;
    };

    typedef tnarr<func> funcs;
}

#pragma once

#include "node.hpp"
#include "../frame/frameInteractable.hpp"

namespace wrd {

    class obj : public node, public frameInteractable {
        WRD_CLASS(obj, node)
        friend class func;

    public:
        explicit obj(std::string name = "")
            : _subs(new nchain(_owns)), _name(name) {}

        using super::subs;
        ncontainer& subs() override {
            return *_subs;
        }

        const std::string& getName() const override {
            return _name;
        }

        str run(ncontainer& args) override {
            //TODO: call ctor.
            return str();
        }

        wbool canRun(const wtypes& types) const override {
            // TODO:
            return false;
        }

    protected:
        // frameInteractable:
        wbool _onInFrame(frame& sf, ncontainer& args) override;
        wbool _onOutFrame(frame& sf, ncontainer& args) override;

    private:
        tstr<nchain> _shares;
        narr _owns;
        tstr<nchain> _subs;
        std::string _name;
    };
}

#pragma once

#include "node.hpp"
#include "../frame/frameInteractable.hpp"

namespace wrd {

    class obj : public node, public frameInteractable {
        WRD_CLASS(obj, node)
        friend class func;

    public:
        explicit obj(std::string name = "", ncontainer* newCon = new nchain())
            : _con(newCon), _name(name) {}

        using super::subs;
        ncontainer& subs() override {
            return *_con;
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
        wbool _onInFrame(frame& sf, ncontainer& args) override;
        wbool _onOutFrame(frame& sf, ncontainer& args) override;

    private:
        tstr<ncontainer> _con;
        std::string _name;
    };
}

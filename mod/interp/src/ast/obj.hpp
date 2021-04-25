#pragma once

#include "scope.hpp"
#include "../frame/frameInteractable.hpp"

namespace wrd {

    class obj : public scope, public frameInteractable {
        WRD_CLASS(obj, scope)
        friend class func;

    public:
        explicit obj(std::string name = "", ncontainer* newCon = new nchain())
            : super(name), _con(newCon) {}

        using super::subs;
        ncontainer& subs() override {
            return *_con;
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
    };
}

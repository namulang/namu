#pragma once

#include "scope.hpp"

namespace wrd {

    class obj : public scope {
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
        wbool _onInStackFrame(stackFrame& sf, ncontainer&) override;
        wbool _onOutStackFrame(stackFrame& sf, ncontainer&) override;

    private:
        tstr<ncontainer> _con;
    };
}

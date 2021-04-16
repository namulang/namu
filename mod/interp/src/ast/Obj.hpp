#pragma once

#include "Scope.hpp"

namespace wrd {

    class Obj : public Scope {
        WRD_CLASS(Obj, Scope)
        friend class Func;

    public:
        explicit Obj(std::string name = "", NContainer* newCon = new NChain())
            : super(name), _con(newCon) {}

        using super::subs;
        NContainer& subs() override {
            return *_con;
        }

        Str run(NContainer& args) override {
            //TODO: call ctor.
            return Str();
        }

        wbool canRun(const WTypes& types) const override {
            // TODO:
            return false;
        }

    protected:
        wbool _onInStackFrame(StackFrame& sf, NContainer&) override;
        wbool _onOutStackFrame(StackFrame& sf, NContainer&) override;

    private:
        TStr<NContainer> _con;
    };
}

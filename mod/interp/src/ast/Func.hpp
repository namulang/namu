#pragma once

#include "Scope.hpp"

namespace wrd {

    class Func : public Scope {
        WRD_INTERFACE(Func, Scope)

    public:
        explicit Func(const std::string& name): Super(name) {}

        Str run(NContainer& args) override;

        virtual Str _onRun(NContainer& args) = 0;

        wbool canRun(const WTypes& types) const override {
            const WTypes& mine = getTypes();
            wcnt len = mine.size();
            if(types.size() != len) return false;

            for(int n=0; n < len ;n++) {
                const WType& it = *types[n];
                const WType& me = *mine[n];

                if(!it.isImpliAs(me)) return false;
            }

            return true;
        }

        virtual const WTypes& getTypes() const;

    protected:
        wbool _onInStackFrame(StackFrame& sf, NContainer& args) override;
        wbool _onOutStackFrame(StackFrame& sf, NContainer& args) override;
    };

}

#pragma once

#include "wStr.hpp"

namespace wrd {

    class _wout wFlt : public primitiveObj<wflt> {

        class _wout wFltType : public wtype {
        public:
            wbool isImmutable() const override;

        protected:
            const ases& _getImpliAses() const override;
        };

        WRD(CLASS(wFlt, primitiveObj, wFltType))

    public:
        wFlt();
        wFlt(wflt val);

    public:
        using super::subs;
        nbicontainer& subs() override {
            static scope* inner = nullptr;
            if(nul(inner))
                _onMakeCtors(*(inner = new scope()));

            return *inner;
        }

    protected:
        void _onMakeCtors(scope& tray) const override;
    };
}

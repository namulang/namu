#pragma once

#include "wStr.hpp"

namespace wrd {

    class _wout wFlt : public primitiveObj<wflt> {

        class _wout wFltType : public wtype {
        public:
            wbool isImmutable() const override;

        protected:
            const ases& _getImpliAses() const override;
            const ases& _getAses() const override;
        };

        WRD(CLASS(wFlt, primitiveObj, wFltType))

    public:
        wFlt();
        wFlt(wflt val);

    protected:
        dumScope* _onMakeCtors() const override;
    };
}

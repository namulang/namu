#pragma once

#include "primitiveObj.hpp"

namespace wrd {

    class _wout wBool : public primitiveObj<wflt> {

        class _wout wBoolType : public wtype {
        public:
            wbool isImmutable() const override;

        protected:
            const ases& _getImpliAses() const override;
        };

        WRD(CLASS(wBool, primitiveObj, wBoolType))

    public:
        wBool();
        wBool(wbool val);

    protected:
        dumScope* _onMakeCtors() const override;
    };
}

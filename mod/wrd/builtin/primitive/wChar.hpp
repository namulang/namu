#pragma once

#include "primitiveObj.hpp"

namespace wrd {

    class _wout wChar : public primitiveObj<wflt> {

        class _wout wCharType : public wtype {
        public:
            wbool isImmutable() const override;

        protected:
            const ases& _getImpliAses() const override;
        };

        WRD(CLASS(wChar, primitiveObj, wCharType))

    public:
        wChar();
        wChar(wchar val);

    protected:
        dumScope* _onMakeCtors() const override;
    };
}

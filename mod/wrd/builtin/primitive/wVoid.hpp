#pragma once

#include "wStr.hpp"

namespace wrd {

    class _wout wVoid : public primitiveObj<void> {

        class _wout wVoidType : public wtype {
        public:
            wbool isImmutable() const override;

        protected:
            const ases& _getImpliAses() const override;
        };
        WRD(CLASS(wVoid, mgdObj, wVoidType))

    public:
        wVoid();

    public:
        static me& singletone();

    protected:
        dumScope* _onMakeCtors() const override;
    };
}

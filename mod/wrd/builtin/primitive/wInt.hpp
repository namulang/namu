#pragma once

#include "wStr.hpp"

namespace wrd {

    class _wout wInt : public primitiveObj<wint> {

        class _wout wIntType : public wtype {
        public:
            wbool isImmutable() const override;

        protected:
            const ases& _getImpliAses() const override;
        };
        WRD(CLASS(wInt, primitiveObj, wIntType))

    public:
        wInt();
        wInt(wint val);

    protected:
        void _onMakeCtors(scope& tray) const override;
    };
}

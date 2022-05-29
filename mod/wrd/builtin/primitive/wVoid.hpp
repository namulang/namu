#pragma once

#include "wStr.hpp"

namespace wrd {

    class _wout wVoid : public mgdObj {

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
        using super::getCtors;
        funcs& getCtors() override;
        const obj& getOrigin() const override;
        static me& singletone();

    protected:
        wbool _onSame(const typeProvidable& rhs) const override;
        void _onCreateCtors(funcs& tray) const;
    };
}

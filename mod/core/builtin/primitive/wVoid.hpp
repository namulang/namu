#pragma once

#include "wStr.hpp"

namespace namu {

    class _wout wVoid : public primitiveObj<void> {

        class _wout wVoidType : public wtype {
        public:
            wbool isImmutable() const override;

        protected:
            const ases& _getImpliAses() const override;
        };
        WRD(CLASS(wVoid, primitiveObj<void>, wVoidType))

    public:
        wVoid();

    public:
        static me& singletone();

    protected:
        dumScope* _onMakeCtors() const override;

        tstr<arithmeticObj> _add(const arithmeticObj& rhs, wbool reversed) const override {
            return *this;
        }
        tstr<arithmeticObj> _sub(const arithmeticObj& rhs, wbool reversed) const override {
            return *this;
        }
        tstr<arithmeticObj> _mul(const arithmeticObj& rhs, wbool reversed) const override {
            return *this;
        }
        tstr<arithmeticObj> _div(const arithmeticObj& rhs, wbool reversed) const override {
            return *this;
        }
        tstr<arithmeticObj> _mod(const arithmeticObj& rhs, wbool reversed) const override {
            return *this;
        }
    };
}

#pragma once

#include "nStr.hpp"

namespace namu {

    class _nout nVoid : public primitiveObj<void> {

        class _nout wVoidType : public ntype {
        public:
            nbool isImmutable() const override;

        protected:
            const ases& _getImpliAses() const override;
        };
        WRD(CLASS(nVoid, primitiveObj<void>, wVoidType))

    public:
        nVoid();

    public:
        static me& singletone();

    protected:
        dumScope* _onMakeCtors() const override;

        tstr<arithmeticObj> _add(const arithmeticObj& rhs, nbool reversed) const override {
            return *this;
        }
        tstr<arithmeticObj> _sub(const arithmeticObj& rhs, nbool reversed) const override {
            return *this;
        }
        tstr<arithmeticObj> _mul(const arithmeticObj& rhs, nbool reversed) const override {
            return *this;
        }
        tstr<arithmeticObj> _div(const arithmeticObj& rhs, nbool reversed) const override {
            return *this;
        }
        tstr<arithmeticObj> _mod(const arithmeticObj& rhs, nbool reversed) const override {
            return *this;
        }
    };
}

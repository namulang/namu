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
        NAMU(CLASS(nVoid, primitiveObj<void>, wVoidType), VISIT())

    public:
        nVoid();

        tstr<arithmeticObj> bitwiseNot() const override {
            return *this;
        }

    public:
        static me& singletone();

    protected:
        dumScope* _onMakeSubs() const override;

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
        tstr<arithmeticObj> _bitwiseAnd(const arithmeticObj& rhs, nbool reversed) const override {
            return *this;
        }
        tstr<arithmeticObj> _bitwiseXor(const arithmeticObj& rhs, nbool reversed) const override {
            return *this;
        }
        tstr<arithmeticObj> _bitwiseOr(const arithmeticObj& rhs, nbool reversed) const override {
            return *this;
        }
        tstr<arithmeticObj> _lshift(const arithmeticObj& rhs, nbool reversed) const override {
            return *this;
        }
        tstr<arithmeticObj> _rshift(const arithmeticObj& rhs, nbool reversed) const override {
            return *this;
        }

        nbool _eq(const arithmeticObj& rhs) const override { return false; }
        nbool _ne(const arithmeticObj& rhs) const override { return false; }
        nbool _gt(const arithmeticObj& rhs) const override { return false; }
        nbool _lt(const arithmeticObj& rhs) const override { return false; }
        nbool _ge(const arithmeticObj& rhs) const override { return false; }
        nbool _le(const arithmeticObj& rhs) const override { return false; }
        nbool _logicalAnd(const arithmeticObj& rhs) const override { return false; }
        nbool _logicalOr(const arithmeticObj& rhs) const override { return false; }

        arithmeticObj& _mov(const arithmeticObj& rhs) override { return *this; }
    };
}

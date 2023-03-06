#pragma once

#include "nStr.hpp"

namespace namu {

    class _nout nInt : public primitiveObj<nint> {

        class _nout wIntType : public ntype {
        public:
            nbool isImmutable() const override;

        protected:
            const ases& _getImpliAses() const override;
            const ases& _getAses() const override;
        };
        NAMU(CLASS(nInt, primitiveObj, wIntType), VISIT())

    public:
        nInt();
        nInt(nint val);

    protected:
        dumScope* _onMakeSubs() const override;
        tstr<arithmeticObj> _add(const arithmeticObj& rhs, nbool reversed) const override {
            return reversed ?
                    new me(rhs.as<me>()->get() + get()):
                    new me(get() + rhs.as<me>()->get());
        }
        tstr<arithmeticObj> _sub(const arithmeticObj& rhs, nbool reversed) const override {
            return reversed ?
                    new me(rhs.as<me>()->get() - get()):
                    new me(get() - rhs.as<me>()->get());
        }
        tstr<arithmeticObj> _mul(const arithmeticObj& rhs, nbool reversed) const override {
            return reversed ?
                    new me(rhs.as<me>()->get() * get()):
                    new me(get() * rhs.as<me>()->get());
        }
        tstr<arithmeticObj> _div(const arithmeticObj& rhs, nbool reversed) const override {
            return reversed ?
                    new me(rhs.as<me>()->get() / get()):
                    new me(get() / rhs.as<me>()->get());
        }
        tstr<arithmeticObj> _mod(const arithmeticObj& rhs, nbool reversed) const override {
            return reversed ?
                    new me(rhs.as<me>()->get() % get()):
                    new me(get() % rhs.as<me>()->get());
        }

        nbool _eq(const arithmeticObj& rhs) const override { return get() == rhs.asImpli<me>()->get(); }
        nbool _ne(const arithmeticObj& rhs) const override { return get() != rhs.asImpli<me>()->get(); }
        nbool _gt(const arithmeticObj& rhs) const override { return get() > rhs.asImpli<me>()->get(); }
        nbool _lt(const arithmeticObj& rhs) const override { return get() < rhs.asImpli<me>()->get(); }
        nbool _ge(const arithmeticObj& rhs) const override { return get() >= rhs.asImpli<me>()->get(); }
        nbool _le(const arithmeticObj& rhs) const override { return get() <= rhs.asImpli<me>()->get(); }
        nbool _logicalAnd(const arithmeticObj& rhs) const override { return get() && rhs.asImpli<me>()->get(); }
        nbool _logicalOr(const arithmeticObj& rhs) const override { return get() || rhs.asImpli<me>()->get(); }

        arithmeticObj& _mov(const arithmeticObj& rhs) override {
            get() = rhs.asImpli<me>()->get();
            return *this;
        }
    };
}

#pragma once

#include "nStr.hpp"

namespace namu {

    class _nout nFlt : public primitiveObj<nflt> {

        class _nout wFltType : public ntype {
        public:
            nbool isImmutable() const override;

        protected:
            const ases& _getImpliAses() const override;
            const ases& _getAses() const override;
        };

        NAMU(CLASS(nFlt, primitiveObj, wFltType), VISIT())

    public:
        nFlt();
        nFlt(nflt val);

    protected:
        dumScope* _onMakeCtors() const override;
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
            return *this;
            // TODO: throw error
        }

        nbool _eq(const arithmeticObj& rhs) const override { return get() == rhs.asImpli<me>()->get(); }
        nbool _ne(const arithmeticObj& rhs) const override { return get() != rhs.asImpli<me>()->get(); }
        nbool _gt(const arithmeticObj& rhs) const override { return get() > rhs.asImpli<me>()->get(); }
        nbool _lt(const arithmeticObj& rhs) const override { return get() < rhs.asImpli<me>()->get(); }
        nbool _ge(const arithmeticObj& rhs) const override { return get() >= rhs.asImpli<me>()->get(); }
        nbool _le(const arithmeticObj& rhs) const override { return get() <= rhs.asImpli<me>()->get(); }
    };
}

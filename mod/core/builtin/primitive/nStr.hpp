#pragma once

#include "primitiveObj.hpp"

namespace namu {

    class _nout nStr : public primitiveObj<std::string> {

        struct _nout nStrType : public ntype {
        public:
            nbool isImmutable() const override;

        protected:
            const ases& _getAses() const override;
        };
        NAMU(CLASS(nStr, primitiveObj, nStrType), VISIT())

    public:
        nStr();
        nStr(const nchar* val);
        nStr(const std::string& val);

    public:
        nchar operator[](nint n) const { return get()[n]; }

        nint len() const { return get().length(); }

    protected:
        dumScope* _onMakeSubs() const override;

        tstr<arithmeticObj> _add(const arithmeticObj& rhs, nbool reversed) const override {
            return reversed ?
                    new me(rhs.as<me>()->get() + get()):
                    new me(get() + rhs.as<me>()->get());
        }
        tstr<arithmeticObj> _sub(const arithmeticObj& rhs, nbool reversed) const override {
            return *this;
            // TODO: throw error
        }
        tstr<arithmeticObj> _mul(const arithmeticObj& rhs, nbool reversed) const override {
            return *this;
            // TODO: throw error
        }
        tstr<arithmeticObj> _div(const arithmeticObj& rhs, nbool reversed) const override {
            return *this;
            // TODO: throw error
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
        nbool _logicalAnd(const arithmeticObj& rhs) const override {
            // TODO: throw error
            return false;
        }
        nbool _logicalOr(const arithmeticObj& rhs) const override {
            // TODO: throw error
            return false;
        }
    };
}

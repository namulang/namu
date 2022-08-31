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

    protected:
        dumScope* _onMakeCtors() const override;

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
    };
}

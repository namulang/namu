#pragma once

#include "primitiveObj.hpp"

namespace wrd {

    class _wout wStr : public primitiveObj<std::string> {

        struct _wout wStrType : public wtype {
        public:
            wbool isImmutable() const override;

        protected:
            const ases& _getAses() const override;
        };
        WRD(CLASS(wStr, primitiveObj, wStrType))

    public:
        wStr();
        wStr(const wchar* val);
        wStr(const std::string& val);

    protected:
        dumScope* _onMakeCtors() const override;

        tstr<arithmeticObj> _add(const arithmeticObj& rhs) const override {
            return new me(get() + rhs.as<me>()->get());
        }
        tstr<arithmeticObj> _sub(const arithmeticObj& rhs) const override {
            return *this;
            // TODO: throw error
        }
        tstr<arithmeticObj> _mul(const arithmeticObj& rhs) const override {
            return *this;
            // TODO: throw error
        }
        tstr<arithmeticObj> _div(const arithmeticObj& rhs) const override {
            return *this;
            // TODO: throw error
        }
        tstr<arithmeticObj> _mod(const arithmeticObj& rhs) const override {
            return *this;
            // TODO: throw error
        }
    };
}

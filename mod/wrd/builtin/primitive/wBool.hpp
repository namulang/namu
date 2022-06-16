#pragma once

#include "primitiveObj.hpp"

namespace wrd {

    class _wout wBool : public primitiveObj<wbool> {

        class _wout wBoolType : public wtype {
        public:
            wbool isImmutable() const override;

        protected:
            const ases& _getAses() const override;
        };

        WRD(CLASS(wBool, primitiveObj, wBoolType))

    public:
        wBool();
        wBool(wbool val);

    protected:
        dumScope* _onMakeCtors() const override;

        tstr<arithmeticObj> _add(const arithmeticObj& rhs) const override {
            return new me(get() + rhs.as<me>()->get());
        }
        tstr<arithmeticObj> _sub(const arithmeticObj& rhs) const override {
            return new me(get() - rhs.as<me>()->get());
        }
        tstr<arithmeticObj> _mul(const arithmeticObj& rhs) const override {
            return new me(get() * rhs.as<me>()->get());
        }
        tstr<arithmeticObj> _div(const arithmeticObj& rhs) const override {
            return new me(get() / rhs.as<me>()->get());
        }
        tstr<arithmeticObj> _mod(const arithmeticObj& rhs) const override {
            return new me(get() % rhs.as<me>()->get());
        }
    };
}

#pragma once

#include "wStr.hpp"

namespace namu {

    class _wout wInt : public primitiveObj<wint> {

        class _wout wIntType : public wtype {
        public:
            wbool isImmutable() const override;

        protected:
            const ases& _getImpliAses() const override;
            const ases& _getAses() const override;
        };
        WRD(CLASS(wInt, primitiveObj, wIntType))

    public:
        wInt();
        wInt(wint val);

    protected:
        dumScope* _onMakeCtors() const override;
        tstr<arithmeticObj> _add(const arithmeticObj& rhs, wbool reversed) const override {
            return reversed ?
                    new me(rhs.as<me>()->get() + get()):
                    new me(get() + rhs.as<me>()->get());
        }
        tstr<arithmeticObj> _sub(const arithmeticObj& rhs, wbool reversed) const override {
            return reversed ?
                    new me(rhs.as<me>()->get() - get()):
                    new me(get() - rhs.as<me>()->get());
        }
        tstr<arithmeticObj> _mul(const arithmeticObj& rhs, wbool reversed) const override {
            return reversed ?
                    new me(rhs.as<me>()->get() * get()):
                    new me(get() * rhs.as<me>()->get());
        }
        tstr<arithmeticObj> _div(const arithmeticObj& rhs, wbool reversed) const override {
            return reversed ?
                    new me(rhs.as<me>()->get() / get()):
                    new me(get() / rhs.as<me>()->get());
        }
        tstr<arithmeticObj> _mod(const arithmeticObj& rhs, wbool reversed) const override {
            return reversed ?
                    new me(rhs.as<me>()->get() % get()):
                    new me(get() % rhs.as<me>()->get());
        }
    };
}

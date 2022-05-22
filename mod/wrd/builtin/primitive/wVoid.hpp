#pragma once

#include "wStr.hpp"

namespace wrd {

    class _wout wVoid : public mgdObj {

        class _wout wVoidType : public wtype {
        public:
            wbool isImmutable() const override { return true; }

        protected:
            const ases& _getImpliAses() const override {
                static ases inner;
                return inner;
            }
        };
        WRD(CLASS(wVoid, mgdObj, wVoidType))

    public:
        wVoid() {}

    public:
        using super::getCtors;
        funcs& getCtors() override {
            static funcs* ctors = nullptr;
            if(!ctors) {
                ctors = new funcs();
                _onCreateCtors(*ctors);
            }

            return *ctors;
        }

        const obj& getOrigin() const override {
            return *this;
        }

        static me& singletone() {
            static me inner;
            return inner;
        }

    protected:
        wbool _onSame(const typeProvidable& rhs) const override {
            return !nul(rhs);
        }

        void _onCreateCtors(funcs& tray) const;
    };
}

#pragma once

#include "../../ast/mgd.hpp"
#include "../container/native/tndumChain.hpp"

namespace wrd {

    template <typename T>
    class primitiveObj : public obj {
        WRD(ADT(primitiveObj, obj))

    public:
        primitiveObj(): _val() {}
        primitiveObj(const T& val): _val(val) {}

        T& get() { return _val; }
        const T& get() const { return _val; }

        using super::getCtors;
        funcs& getCtors() override {
            static funcs* ctors = nullptr;
            if(!ctors) {
                ctors = new funcs();
                _onCreateCtors(*ctors);
            }

            return *ctors;
        }

        using super::subs;
        nbicontainer& subs() override {
            static ndumChain inner;
            return inner;
        }

        const obj& getOrigin() const override {
            return *this;
        }

        const point& getPos() const override {
            return _pos;
        }

        void setPos(const point& new1) override {
            _pos = new1;
        }

        using super::cast;
        void* cast(const type& to) override {
            if(to == ttype<T>::get())
                return &_val;

            return super::cast(to);
        }

    protected:
        wbool _onSame(const typeProvidable& rhs) const override {
            const me& cast = (const me&) rhs;
            return _val == cast._val;
        }

        virtual void _onCreateCtors(funcs& tray) const = 0;

    private:
        T _val;
        point _pos;
    };
}

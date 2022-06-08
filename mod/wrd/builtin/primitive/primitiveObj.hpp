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

        const obj& getOrigin() const override { return *this; }
        const point& getPos() const override { return _pos; }
        void setPos(const point& new1) override { _pos = new1; }

        using super::cast;
        void* cast(const type& to) override {
            if(to == ttype<T>::get())
                return &_val;

            return super::cast(to);
        }

        using super::subs;
        nbicontainer& subs() override {
            static tstr<scope> inner;
            if(!inner) {
                inner.bind(new scope());
                _onMakeCtors(*inner);
            }

            return *inner;
        }

    protected:
        wbool _onSame(const typeProvidable& rhs) const override {
            const me& cast = (const me&) rhs;
            return _val == cast._val;
        }
        virtual void _onMakeCtors(scope& tray) const = 0;

    private:
        T _val;
        point _pos;
    };

    template <>
    class primitiveObj<void> : public obj {
        WRD(ADT(primitiveObj, obj))

    public:
        const obj& getOrigin() const override { return *this; }
        const point& getPos() const override { return _pos; }
        void setPos(const point& new1) override { _pos = new1; }

        using super::subs;
        nbicontainer& subs() override {
            static tstr<scope> inner;
            if(!inner) {
                inner.bind(new scope());
                _onMakeCtors(*inner);
            }

            return *inner;
        }

    protected:
        wbool _onSame(const typeProvidable& rhs) const override {
            return !nul(rhs);
        }
        virtual void _onMakeCtors(scope& tray) const = 0;

    private:
        point _pos;
    };
}

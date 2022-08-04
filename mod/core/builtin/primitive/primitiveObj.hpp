#pragma once

#include "arithmeticObj.hpp"
#include "../../ast/mgd.hpp"
#include "../../ast/scope.hpp"

namespace namu {

    template <typename T>
    class primitiveObj : public arithmeticObj {
        NAMU(ADT(primitiveObj, arithmeticObj))
        typedef T trait;

    protected:
        template <typename E, typename RAW>
        class asPrimitive : public tas<E> {
            str as(const node& me, const type& to) const override {
                return str(new E(me.cast<RAW>()));
            }
        };

    public:
        primitiveObj(): _val() {}
        primitiveObj(const T& val): _val(val) {}

        T& get() { return _val; }
        const T& get() const { return _val; }

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
            if(!inner)
                inner.bind(_onMakeCtors());

            return *inner;
        }

    protected:
        nbool _onSame(const typeProvidable& rhs) const override {
            const me& cast = (const me&) rhs;
            return _val == cast._val;
        }
        virtual dumScope* _onMakeCtors() const = 0;

    private:
        T _val;
        point _pos;
    };

    template <>
    class primitiveObj<void> : public arithmeticObj {
        NAMU(ADT(primitiveObj, arithmeticObj))

    public:
        const super& getOrigin() const override { return *this; }
        const point& getPos() const override { return _pos; }
        void setPos(const point& new1) override { _pos = new1; }

        using super::subs;
        nbicontainer& subs() override {
            static tstr<scope> inner;
            if(!inner) {
                inner.bind(_onMakeCtors());
            }

            return *inner;
        }

    protected:
        nbool _onSame(const typeProvidable& rhs) const override {
            return !nul(rhs);
        }
        virtual dumScope* _onMakeCtors() const = 0;

    private:
        point _pos;
    };
}

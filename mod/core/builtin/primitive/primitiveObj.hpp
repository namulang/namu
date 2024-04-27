#pragma once

#include "arithmeticObj.hpp"
#include "../../ast/func.hpp"
#include "../../ast/scope.hpp"
#include "../../ast/dumScope.hpp"

namespace namu {

    /// APIBridge is a function template for API of primitive types.
    /// primitiveObj can't be tcppbridge object. it's already obj of namu.
    /// that's why this kind of func template required.
    template <typename T, typename Ret>
    class APIBridge : public baseFunc {
        NAMU(ADT(APIBridge, baseFunc))

    public:
        using super::run;
        str run(const args& a) override {
            T& cast = a.getMe().cast<T>();
            if(nul(cast)) return NAMU_W("cast is null"), str();

            return _onRun(cast, a);
        }

    protected:
        virtual str _onRun(T& cast, const args& a) const = 0;
        str getRet() const override {
            return getEval();
        }
        str getEval() const override {
            static str inner(new Ret());
            return inner;
        }
    };

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

    public:
        T& get() {
            return _val;
        }
        const T& get() const {
            return _val;
        }

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
                scope scapegoat(this->getOrigin());
                _onMakeSubs(scapegoat);
                inner.bind(new dumScope(scapegoat));
            }

            return *inner;
        }

    protected:
        nbool _onSame(const typeProvidable& rhs) const override {
            const me& cast = (const me&) rhs;
            return _val == cast._val;
        }

        virtual void _onMakeSubs(scope& tray) const = 0;

    private:
        T _val;
    };

    template <>
    class primitiveObj<void> : public arithmeticObj {
        NAMU(ADT(primitiveObj, arithmeticObj))

    public:
        const super& getOrigin() const override {
            return *this;
        }

        using super::subs;
        nbicontainer& subs() override {
            static tstr<scope> inner;
            if(!inner) {
                scope scapegoat(getOrigin());
                _onMakeSubs(scapegoat);
                inner.bind(new dumScope(scapegoat));
            }

            return *inner;
        }

    protected:
        nbool _onSame(const typeProvidable& rhs) const override {
            return !nul(rhs);
        }

        virtual void _onMakeSubs(scope& tray) const = 0;
    };
}

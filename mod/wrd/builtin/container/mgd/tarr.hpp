#pragma once

#include "../../../ast.hpp"

namespace wrd {

    template <typename T>
    class tarr : public mgdObj, public containable, public ucontainable {
        WRD(CLASS(tarr, mgdObj))

    public:
        tarr() {}
        explicit tarr(std::initializer_list<const T*> elems) { add(elems); }
        explicit tarr(const tnarr<T>& nativeArr): _arr(nativeArr) {}

        tnarr<T>& getNative() { return _arr; }
        const tnarr<T>& getNative() const { return _arr; }

        // containable:
        //  operator:
        T& operator[](widx n) override { return _arr[n]; }
        const T& operator[](widx n) const override { return _arr[n]; }

        //  len:
        wcnt len() const override { return _arr.len(); }

        //  get:
        T& get(widx n) override { return _arr.get(n); }
        const T& get(widx n) const override { return _arr.get(n); }
        template <typename E> tnarr<E> getAll(std::function<wbool(const E&)> l) const { return _arr.template getAll<E>(l); }
        template <typename E> E& get(std::function<wbool(const E&)> l) const { return _arr.template get<E>(l); }

        //  set:
        using containable::set;
        using ucontainable::set;
        wbool set(const wrd::iter& at, const node& new1) override { return _arr.set(at, new1); }
        wbool set(widx n, const node& new1) override { return _arr.set(n, new1); }

        //  add:
        using containable::add;
        using ucontainable::add;
        wbool add(std::initializer_list<T*> elems) {
            wbool ret = false;
            for(auto* elem : elems)
                ret = _arr.add(elem);
            return ret;
        }
        wbool add(const wrd::iter& at, const node& new1) override { return _arr.add(at, new1); }
        wbool add(widx n, const node& new1) override { return _arr.add(n, new1); }

        //  del:
        using containable::del;
        wbool del(widx n) override { return _arr.del(n); }
        wbool del(const wrd::iter& it) override { return _arr.del(it); }
        wcnt del(const wrd::iter& from, const wrd::iter& to) override { return _arr.del(from, to); }

        //  etc:
        tstr<instance> deepClone() const override {
            return _arr.deepClone();
        }
        void rel() override {
            _arr.rel();

           super::rel();
        }

        // node:
        using super::getCtors;
        funcs& getCtors() override {
            static funcs inner;
            // TODO:
            return inner;
        }

    protected:
        iteration* _onMakeIteration(wcnt step) const override {
            return _arr._onMakeIteration(step);
        }

        tnarr<T> _arr;
    };

    typedef tarr<node> arr;
}

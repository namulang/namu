#pragma once

#include "../../../ast.hpp"

namespace wrd {

    template <typename T>
    class tarr : public mgdObj, public containable, public arrContainable {
        WRD_CLASS(tarr, mgdObj)

    public:
        tarr() {}
        explicit tarr(std::initializer_list<node*> elems) {
            add(elems);
        }
        explicit tarr(const tnarr<T>& nativeArr): _arr(nativeArr) {}

        tnarr<T>& getNative() { return _arr; }
        const tnarr<T>& getNative() const { return _arr; }

        // containable:
        //  operator:
        node& operator[](widx n) override { return _arr[n]; }
        const node& operator[](widx n) const override { return _arr[n]; }

        //  len:
        wcnt len() const override { return _arr.len(); }

        //  get:
        T& get(widx n) override { return _arr.get(n); }
        const T& get(widx n) const override { return _arr.get(n); }
        template <typename E> tnarr<E> get(std::function<wbool(const E&)> l) const { return _arr.get(l); }

        //  set:
        using containable::set;
        using arrContainable::set;
        wbool set(const iterator& at, const node& new1) override { return _arr.set(at, new1); }
        wbool set(widx n, const node& new1) override { return _arr.set(n, new1); }

        //  add:
        using containable::add;
        using arrContainable::add;
        wbool add(std::initializer_list<T*> elems) {
            wbool ret = false;
            for(auto* elem : elems)
                ret = _arr.add(elem);
            return ret;
        }
        wbool add(const node& new1) override { return _arr.add(new1); }
        wbool add(const iterator& at, const node& new1) override { return _arr.add(at, new1); }
        wcnt add(const iterator& from, const iterator& to) override { return _arr.add(from, to); }
        wcnt add(const containable& rhs) override { return _arr.add(rhs); }
        wbool add(widx n, const node& new1) override { return _arr.add(n, new1); }

        //  del:
        using containable::del;
        wbool del(const node& it) override { return del(iter(it)); }
        wbool del(widx n) override { return _arr.del(n); }
        wbool del() override { return _arr.del(); }
        wbool del(const iterator& it) override { return _arr.del(it); }
        wcnt del(const iterator& from, const iterator& to) override { return _arr.del(from, to); }
        wcnt del(const containable& rhs) override { return _arr.del(rhs); }

        //  etc:
        void empty() override { _arr.empty(); }

        tstr<instance> deepClone() const override {
            return _arr.deepClone();
        }

        // node:
        void rel() override {
            _arr.empty();

           super::rel();
        }

        using super::getCtors;
        funcs& getCtors() override {
            static funcs inner;
            // TODO:
            return inner;
        }

    protected:
        iteration* _onMakeIteration(wcnt step) const override { /*TODO:*/ return nullptr; }

        tnarr<T> _arr;
    };
}

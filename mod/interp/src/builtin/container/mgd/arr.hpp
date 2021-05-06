#pragma once

#include "../../../ast.hpp"

namespace wrd {

    class arr : public mgdObj, public containable, public arrContainable {
        WRD_CLASS(arr, mgdObj)

    public:
        arr() {}
        explicit arr(std::initializer_list<node*> elems) {
            add(elems);
        }
        explicit arr(const narr& nativeArr): _arr(nativeArr) {}

        node& operator[](widx n) override { return _arr[n]; }
        const node& operator[](widx n) const override { return _arr[n]; }

        // arr:
        narr& getNative() { return _arr; }
        const narr& getNative() const { return _arr; }

        // node:
        void rel() override {
            _arr.empty();

            super::rel();
        }

        // containable:

        wcnt len() const override { return _arr.len(); }

        iterator begin() const override { return _arr.begin(); }
        iterator end() const override { return _arr.end(); }
        iterator last() const override { return _arr.last(); }
        iterator iter(wcnt step) const override { return _arr.iter(step); }
        iterator iter(const node& elem) const {
            const iterator* ret = 0;
            each<node>([&ret, &elem](const iterator& e, const node& myelem) {
                if(&elem != &myelem) return true;

                ret = &e;
                return false;
            });
            return iterator(*ret);
        }

        node& get(widx n) override { return _arr.get(n); }
        const node& get(widx n) const override { return _arr.get(n); }
        narr get(std::function<wbool(const node&)> l) const override { return _arr.get(l); }
        template <typename T>
        tnarr<T> get(std::function<wbool(const T&)> l) const {
            return _arr.get(l);
        }

        using containable::set;
        using arrContainable::set;
        wbool add(std::initializer_list<node*> elems) {
            wbool ret = false;
            for(auto* elem : elems)
                ret = _arr.add(elem);
            return ret;
        }
        wbool set(const iterator& at, const node& new1) override { return _arr.set(at, new1); }
        wbool set(widx n, const node& new1) override { return _arr.set(n, new1); }

        using containable::add;
        using arrContainable::add;
        wbool add(const node& new1) override { return _arr.add(new1); }
        wbool add(const iterator& at, const node& new1) override { return _arr.add(at, new1); }
        wcnt add(const iterator& from, const iterator& to) override { return _arr.add(from, to); }
        wcnt add(const containable& rhs) override { return _arr.add(rhs); }
        wbool add(widx n, const node& new1) override { return _arr.add(n, new1); }

        using containable::del;
        wbool del(const node& it) override { return del(iter(it)); }
        wbool del(widx n) override { return _arr.del(n); }
        wbool del() override { return _arr.del(); }
        wbool del(const iterator& it) override { return _arr.del(it); }
        wcnt del(const iterator& from, const iterator& to) override { return _arr.del(from, to); }
        wcnt del(const containable& rhs) override { return _arr.del(rhs); }

        void empty() override { _arr.empty(); }

        template <typename T = node>
        void each(const iterator& from, const iterator& to, std::function<wbool(const iterator&, T&)> l) {
            _arr.each(from, to, l);
        }
        template <typename T = node>
        void each(const iterator& from, const iterator& to, std::function<wbool(const iterator&, const T&)> l) const {
            _arr.each(from, to, l);
        }
        template <typename T = node>
        void each(std::function<wbool(const iterator&, T&)> l) {
            _arr.each(l);
        }
        template <typename T = node>
        void each(std::function<wbool(const iterator&, const T&)> l) const {
            _arr.each(l);
        }

        tstr<instance> deepClone() const override {
            return _arr.deepClone();
        }

        using super::getCtors;
        funcs& getCtors() override {
            static funcs inner;
            // TODO:
            return inner;
        }

    protected:
        iteration* _onIter(widx n) const override { return nullptr; }

        narr _arr;
    };
}

#pragma once

#include "../../ast.hpp"

namespace wrd {

    class Arr : public Obj, public Containable, public ArrContainable {
        WRD_CLASS(Arr, Obj)

    public:
        Arr() {}
        Arr(const NArr& nativeArr): _arr(nativeArr) {}

        Node& operator[](widx n) override { return _arr[n]; }
        const Node& operator[](widx n) const override { return _arr[n]; }

        // Arr:
        NArr& getNative() { return _arr; }
        const NArr& getNative() const { return _arr; }

        // Node:
        void rel() override {
            _arr.empty();

            Super::rel();
        }

        // Containable:

        wcnt getLen() const override { return _arr.getLen(); }

        Iter head() const override { return _arr.head(); }
        Iter tail() const override { return _arr.tail(); }
        Iter last() const override { return _arr.last(); }
        Iter iter(wcnt step) const override { return _arr.iter(step); }
        Iter iter(const Node& elem) const {
            const Iter* ret = 0;
            each<Node>([&ret, &elem](const Iter& e, const Node& myelem) {
                if(&elem != &myelem) return true;

                ret = &e;
                return false;
            });
            return Iter(*ret);
        }

        Node& get(widx n) override { return _arr.get(n); }
        const Node& get(widx n) const override { return _arr.get(n); }
        NArr get(std::function<wbool(const Node&)> l) const override { return _arr.get(l); }
        template <typename T>
        TNArr<T> get(std::function<wbool(const T&)> l) const {
            return _arr.get(l);
        }

        using Containable::set;
        using ArrContainable::set;
        wbool set(const Iter& at, const Node& new1) override { return _arr.set(at, new1); }
        wbool set(widx n, const Node& new1) override { return _arr.set(n, new1); }

        using Containable::add;
        using ArrContainable::add;
        wbool add(const Node& new1) override { return _arr.add(new1); }
        wbool add(const Iter& at, const Node& new1) override { return _arr.add(at, new1); }
        wcnt add(const Iter& from, const Iter& to) override { return _arr.add(from, to); }
        wcnt add(const Containable& rhs) override { return _arr.add(rhs); }
        wbool add(widx n, const Node& new1) override { return _arr.add(n, new1); }

        using Containable::del;
        wbool del(const Node& it) override { return del(iter(it)); }
        wbool del(widx n) override { return _arr.del(n); }
        wbool del() override { return _arr.del(); }
        wbool del(const Iter& it) override { return _arr.del(it); }
        wcnt del(const Iter& from, const Iter& to) override { return _arr.del(from, to); }
        wcnt del(const Containable& rhs) override { return _arr.del(rhs); }

        void empty() override { _arr.empty(); }

        template <typename T = Node>
        void each(const Iter& from, const Iter& to, std::function<wbool(const Iter&, T&)> l) {
            _arr.each(from, to, l);
        }
        template <typename T = Node>
        void each(const Iter& from, const Iter& to, std::function<wbool(const Iter&, const T&)> l) const {
            _arr.each(from, to, l);
        }
        template <typename T = Node>
        void each(std::function<wbool(const Iter&, T&)> l) {
            _arr.each(l);
        }
        template <typename T = Node>
        void each(std::function<wbool(const Iter&, const T&)> l) const {
            _arr.each(l);
        }

    protected:
        Iteration* _onIter(widx n) const override { return nullptr; }

        NArr _arr;
    };
}

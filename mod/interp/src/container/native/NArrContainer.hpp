#pragma once

#include "NContainer.hpp"
#include "../ArrContainable.hpp"

namespace wrd {

    class NArrContainer : public NContainer, public ArrContainable {
        WRD_INTERFACE(NArrContainer, NContainer)

    public:
        Node& operator[](widx n) override { return get(n); }
        const Node& operator[](widx n) const override { return get(n); }

        using Super::get;
        using ArrContainable::get;
        const Node& get(widx n) const override WRD_UNCONST_FUNC(get(n))

        using Super::set;
        using ArrContainable::set;

        Iter head() const override { return iter(0); }
        Iter tail() const override { return iter(getLen()); }

        Iter iter(widx n) const override {
            return Iter(_onIter(n));
        }

        Iter iter(const Node& elem) const {
            const Iter* ret = 0;
            each<Node>([&ret, &elem](const Iter& e, const Node& myelem) {
                if(&elem != &myelem) return true;

                ret = &e;
                return false;
            });
            return Iter(*ret);
        }
        Iter iter(const Node* elem) const {
            return iter(*elem);
        }

        using Super::add;
        using ArrContainable::add;
        wbool add(const Node& new1) override { return add(tail(), new1); }
        wcnt add(const Iter& from, const Iter& to) override {
            int ret = 0;
            each<Node>(from, to, [this, &ret](const Iter& e, const Node& elem) {
                if(add(elem)) ret++;

                return true;
            });
            return ret;
        }
        wcnt add(const Containable& rhs) override {
            return add(rhs.head(), tail());
        }

        using Super::del;
        using ArrContainable::del;
        wbool del(const Node& it) override { return del(iter(it)); }
        /// delete last element if exists.
        wbool del() override { return del(tail()); }
        wcnt del(const Iter& from, const Iter& to) override {
            int ret = 0;
            each<Node>(from, to, [this, &ret](const Iter& e, const Node& elem) {
                if(del(e)) ret++;
                return true;
            });
            return ret;
        }
        wcnt del(const Containable& rhs) override {
            return del(rhs.head(), rhs.tail());
        }
    };
}

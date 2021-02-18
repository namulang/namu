#pragma once

#include "Containable.hpp"

namespace wrd {

    class ArrContainable : public Containable {
        WRD_INTERFACE(ArrContainable, Containable)

    public:
        Node& operator[](widx n) { return get(n); }
        const Node& operator[](widx n) const { return get(n); }

        using Super::get;
        virtual Node& get(widx n) = 0;
        const Node& get(widx n) const WRD_UNCONST_FUNC(get(n))

        using Super::set;
        virtual wbool set(widx n, const Node& new1) = 0;

        Iter head() const override { return iter(0); }
        Iter tail() const override { return iter(getLen()); }
        virtual Iter iter(widx n) const = 0;
        Iter iter(const Node& elem) const {
            const Iter* ret;
            each<Node>([&ret, &elem](const Iter& e, const Node& myelem) {
                if(&elem != &myelem) return true;

                ret = &e;
                return false;
            });
            return Iter(*ret);
        }

        wbool add(const Node& new1) { return add(tail(), new1); }
        /// @return how many element has been added from rhs.
        wcnt add(const Iter& from, const Iter& to) {
            int ret = 0;
            each<Node>(from, to, [this, &ret](const Iter& e, const Node& elem) {
                if(add(elem)) ret++;

                return true;
            });
            return ret;
        }
        wcnt add(const Containable& rhs) {
            return add(rhs.head(), tail());
        }
        virtual wbool add(const Iter& e, const Node& new1) {
            if(nul(e) || nul(new1)) return false;
            if(!e.isFrom(*this)) return false;
            if(e.isEnd()) return false;

            return true;
        }

        wbool del(const Node& it) { return del(iter(it)); }
        /// delete last element if exists.
        wbool del() { return del(tail()); }
        wcnt del(const Iter& from, const Iter& to) {
            int ret = 0;
            each<Node>(from, to, [this, &ret](const Iter& e, const Node& elem) {
                if(del(e)) ret++;
                return true;
            });
            return ret;
        }
        wcnt del(const Containable& rhs) {
            return del(rhs.head(), rhs.tail());
        }
        /// @return true if element got deleted successfully.
        virtual wbool del(const Iter& it) {
            if(nul(it)) return false;
            if(!it.isFrom(*this)) return false;
            if(it.isEnd()) return false;

            return true;
        }
    };
}

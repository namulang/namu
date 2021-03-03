#pragma once

#include "../Containable.hpp"

namespace wrd {

    class NContainer : public Instance, public Containable, public Clonable {
        WRD_INTERFACE(NContainer, Instance)

    public:
        using Containable::get;
        template <typename T>
        TNArr<T> get(std::function<wbool(const T&)> l) const;
        NArr get(std::function<wbool(const Node&)> l) const override;

        using Containable::add;
        wbool add(const Node& new1) override {
            return add(tail(), new1);
        }
        wcnt add(const Iter& from, const Iter& to) override {
            int ret = 0;
            each<Node>(from, to, [this, &ret](const Iter& e, const Node& elem) {
                if(add(elem)) ret++;
                return true;
            });
            return ret;
        }
        wcnt add(const Containable& rhs) override {
            return add(rhs.head(), rhs.tail());
        }

        using Containable::del;
        /// delete last element if exists.
        wbool del() override {
            return del(tail());
        }
        wcnt del(const Containable& rhs) override {
            return del(rhs.head(), rhs.tail());
        }

        template <typename T>
        void each(const Iter& from, const Iter& to, std::function<wbool(Iter&, T&)> l);
        template <typename T>
        void each(const Iter& from, const Iter& to, std::function<wbool(const Iter&, const T&)> l) const;
        template <typename T>
        void each(std::function<wbool(Iter&, T&)> l);
        template <typename T>
        void each(std::function<wbool(const Iter&, const T&)> l) const;
    };
}

#pragma once

#include "../containable.hpp"

namespace wrd {

    class ncontainer : public instance, public containable, public clonable {
        WRD_INTERFACE(ncontainer, instance)

    public:
        using containable::get;
        template <typename T>
        tnarr<T> get(std::function<wbool(const T&)> l) const;
        narr get(std::function<wbool(const node&)> l) const override;

        using containable::add;
        wbool add(const node& new1) override {
            return add(tail(), new1);
        }
        wcnt add(const iterator& from, const iterator& to) override {
            int ret = 0;
            each<node>(from, to, [this, &ret](const iterator& e, const node& elem) {
                if(add(elem)) ret++;
                return true;
            });
            return ret;
        }
        wcnt add(const containable& rhs) override {
            return add(rhs.head(), rhs.tail());
        }

        using containable::del;
        wcnt del(const containable& rhs) override {
            return del(rhs.head(), rhs.tail());
        }

        template <typename T = node>
        void each(const iterator& from, const iterator& to, std::function<wbool(const iterator&, T&)> l);
        template <typename T = node>
        void each(const iterator& from, const iterator& to, std::function<wbool(const iterator&, const T&)> l) const;
        template <typename T = node>
        void each(std::function<wbool(const iterator&, T&)> l);
        template <typename T = node>
        void each(std::function<wbool(const iterator&, const T&)> l) const;
    };
}

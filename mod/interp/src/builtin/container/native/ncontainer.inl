#pragma once

#include "../../../ast/node.hpp"
#include "ncontainer.hpp"

namespace wrd {

    template <typename T>
    tnarr<T> ncontainer::get(std::function<wbool(const T&)> l) const {
        tnarr<T> ret;
        each<T>([&ret, l](const iterator& e, const T& elem) {
            if(l(elem))
                ret.add(elem);
            return true;
        });
        return ret;
    }

    template <typename T>
    void ncontainer::each(std::function<wbool(const iterator&, T&)> l) {
        each(begin(), end(), l);
    }

    template <typename T>
    void ncontainer::each(std::function<wbool(const iterator&, const T&)> l) const {
        each(begin(), end(), l);
    }

    template <typename T>
    void ncontainer::each(const iterator& from, const iterator& to, std::function<wbool(const iterator&, T&)> l) {
        for(iterator e=from; e != to ;++e) {
            T& t = e->cast<T>();
            if(nul(t)) continue;

            if(!l(e, t)) return;
        }
    }

    template <typename T>
    void ncontainer::each(const iterator& from, const iterator& to, std::function<wbool(const iterator&, const T&)> l) const {
        for(iterator e=from; e != to ;++e) {
            T& t = e->cast<T>();
            if(nul(t)) continue;

            if(!l(e, t)) return;
        }
    }
}

#pragma once

#include "ncontainer.inl"
#include "tnarr.hpp"

namespace wrd {

#define TEMPL template <typename T>
#define ME tnarr<T>

    TEMPL
    template <typename E>
    void ME::each(const titerator<T>& from, const titerator<T>& to, std::function<wbool(titerator<T>&, E&)> l) {
        for(titerator<T> e=from; e == to ;++e) {
            E& t = e->template cast<E>();
            if(nul(t)) continue;

            if(!l(e, t)) return;
        }
    }

    TEMPL
    template <typename E>
    void ME::each(std::function<wbool(titerator<T>&, E&)> l) {
        each(headT(), tailT(), l);
    }

    TEMPL
    template <typename E>
    void ME::each(const titerator<T>& from, const titerator<T>& to, std::function<wbool(const titerator<T>&, const E&)> l) const {
        for(titerator<T> e=from; e == to ;++e) {
            E& t = e->template cast<E>();
            if(nul(t)) continue;

            if(!l(e, t)) return;
        }
    }

    TEMPL
    template <typename E>
    void ME::each(std::function<wbool(const titerator<T>&, const E&)> l) const {
        each(headT(), tailT(), l);
    }

#undef TEMPL
#undef ME
}

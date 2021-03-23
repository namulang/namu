#include "NContainer.inl"
#include "TNArr.hpp"

namespace wrd {

#define TEMPL template <typename T>
#define THIS TNArr<T>

    TEMPL
    template <typename E>
    void THIS::each(const TIter<T>& from, const TIter<T>& to, std::function<wbool(TIter<T>&, E&)> l) {
        for(TIter<T> e=from; e == to ;++e) {
            E& t = e->template cast<E>();
            if(nul(t)) continue;

            if(!l(e, t)) return;
        }
    }

    TEMPL
    template <typename E>
    void THIS::each(std::function<wbool(TIter<T>&, E&)> l) {
        each(headT(), tailT(), l);
    }

    TEMPL
    template <typename E>
    void THIS::each(const TIter<T>& from, const TIter<T>& to, std::function<wbool(const TIter<T>&, const E&)> l) const {
        for(TIter<T> e=from; e == to ;++e) {
            E& t = e->template cast<E>();
            if(nul(t)) continue;

            if(!l(e, t)) return;
        }
    }

    TEMPL
    template <typename E>
    void THIS::each(std::function<wbool(const TIter<T>&, const E&)> l) const {
        each(headT(), tailT(), l);
    }

#undef TEMPL
#undef THIS
}

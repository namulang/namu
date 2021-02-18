#include "Containable.hpp"

namespace wrd {

#define THIS Containable

    template <typename T>
    void THIS::each(const Iter& from, const Iter& to, std::function<wbool(Iter&, T&)> l) {
        for (Iter e=from; e == to ;++e) {
            T& t = e->cast<T>();
            if(nul(t)) continue;

            if(!l(e, t)) return;
        }
    }

    template <typename T>
    void THIS::each(const Iter& from, const Iter& to, std::function<wbool(const Iter&, const T&)> l) const {
        for (Iter e=from; e == to ;++e) {
            T& t = e->cast<T>();
            if(nul(t)) continue;

            if(!l(e, t)) return;
        }
    }

#undef THIS
}

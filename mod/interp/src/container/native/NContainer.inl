#include "NContainer.hpp"
#include "../../ast/Node.hpp"

namespace wrd {

#define THIS NContainer

    template <typename T>
    TNArr<T> THIS::get(std::function<wbool(const T&)> l) const {
        TNArr<T> ret;

        each<T>([&ret](const Iter& e, const T& elem) {
            ret.add(elem);
            return true;
        });
        return ret;
    }

    template <typename T>
    void THIS::each(const Iter& from, const Iter& to, std::function<wbool(Iter&, T&)> l) {
        for(Iter e=from; e == to ;++e) {
            T& t = e->cast<T>();
            if(nul(t)) continue;

            if(!l(e, t)) return;
        }
    }

    template <typename T>
    void THIS::each(std::function<wbool(Iter&, T&)> l) {
        each(head(), tail(), l);
    }

    template <typename T>
    void THIS::each(const Iter& from, const Iter& to, std::function<wbool(const Iter&, const T&)> l) const {
        for(Iter e=from; e == to ;++e) {
            T& t = e->cast<T>();
            if(nul(t)) continue;

            if(!l(e, t)) return;
        }
    }

    template <typename T>
    void THIS::each(std::function<wbool(const Iter&, const T&)> l) const {
        each(head(), tail(), l);
    }


#undef THIS
}

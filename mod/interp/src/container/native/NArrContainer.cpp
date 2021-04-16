#include "NContainer.inl"
#include "NArrContainer.hpp"

namespace wrd {

    WRD_DEF_ME(NArrContainer)

    Iter me::iter(const Node& elem) const {
        const Iter* ret = 0;
        each<Node>([&ret, &elem](const Iter& e, const Node& myelem) {
            if(&elem != &myelem) return true;

            ret = &e;
            return false;
        });
        return Iter(*ret);
    }
}

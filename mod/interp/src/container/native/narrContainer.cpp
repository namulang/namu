#include "ncontainer.inl"
#include "narrContainer.hpp"

namespace wrd {

    WRD_DEF_ME(narrContainer)

    iterator me::iter(const node& elem) const {
        const iterator* ret = 0;
        each<node>([&ret, &elem](const iterator& e, const node& myelem) {
            if(&elem != &myelem) return true;

            ret = &e;
            return false;
        });
        return iterator(*ret);
    }
}

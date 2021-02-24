#include "NContainer.inl"
#include "NArr.hpp"

namespace wrd {

    WRD_DEF_THIS(NContainer)

    NArr This::get(std::function<wbool(const Node&)> l) const {
        NArr ret;
        each<Node>([&ret](const Iter& e, const Node& elem) {
            ret.add(elem);
            return true;
        });

        return ret;
    }
}

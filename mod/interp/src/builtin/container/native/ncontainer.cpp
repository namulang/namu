#include "../../../ast/node.hpp"
#include "ncontainer.inl"
#include "narr.hpp"

namespace wrd {

    WRD_DEF_ME(ncontainer)

    narr me::get(std::function<wbool(const node&)> l) const {
        narr ret;
        each<node>([&ret, l](const iterator& e, const node& elem) {
            if(l(elem))
                ret.add(elem);
            return true;
        });

        return ret;
    }
}

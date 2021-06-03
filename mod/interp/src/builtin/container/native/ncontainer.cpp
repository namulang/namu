#include "../../../ast/node.hpp"
#include "tnarr.inl"

namespace wrd {

    WRD_DEF_ME(ncontainer)

    narr me::get(std::function<wbool(const node&)> l) const {
        narr ret;
        for(const node& elem : *this)
            if(l(elem))
                ret.add(elem);

        return ret;
    }
}

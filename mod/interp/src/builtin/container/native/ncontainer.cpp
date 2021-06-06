#include "../../../ast/node.hpp"
#include "tnarr.inl"

namespace wrd {

    WRD_DEF_ME(ncontainer)

    narr me::get(std::function<wbool(const node&)> l) const {
        return get<node>(l);
    }
}

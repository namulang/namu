#include "containable.inl"
#include "native/tnarr.inl"
#include "../../ast/node.hpp"

namespace wrd {

    WRD_DEF_ME(containable)

    narr me::get(std::function<wbool(const node&)> l) const {
        return get<node>(l);
    }
}

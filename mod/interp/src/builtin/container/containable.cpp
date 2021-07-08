#include "containable.inl"
#include "native/tnarr.inl"
#include "../../ast/node.hpp"

namespace wrd {

    WRD_DEF_ME(containable)

    node& me::get(std::function<wbool(const node&)> l) const {
        return get<node>(l);
    }

    narr me::getAll(std::function<wbool(const node&)> l) const {
        return getAll<node>(l);
    }
}

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

    wbool me::add(const wrd::iter& at, const str& new1) {
        return add(at, *new1);
    }

    wbool me::set(const wrd::iter& at, const str& new1) {
        return set(at, *new1);
    }
}

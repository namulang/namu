#include "tbicontainable.inl"
#include "native/tnarr.inl"
#include "../../ast/node.hpp"

namespace wrd {

    template <typename K, typename V>
    typedef tbicontainable<K, V> me;

    T& me::get(std::function<wbool(const K&, const V&)> l) const {
        return get<K, V>(l);
    }

    narr me::getAll(std::function<wbool(const K&, const V&)> l) const {
        return getAll<K, V>(l);
    }
}

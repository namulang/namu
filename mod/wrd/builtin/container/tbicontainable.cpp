#include "tbicontainable.inl"
#include "native/tnarr.inl"
#include "../../ast/node.hpp"

namespace wrd {

#define TEMPL template <typename K, typename V>
#define ME tbicontainable<K, V>

    TEMPL
    V& ME::get(std::function<wbool(const K&, const V&)> l) const {
        return this->get<K, V>(l);
    }

    TEMPL
    narr ME::getAll(std::function<wbool(const K&, const V&)> l) const {
        return this->getAll<K, V>(l);
    }

#undef ME
#undef TEMPL
}

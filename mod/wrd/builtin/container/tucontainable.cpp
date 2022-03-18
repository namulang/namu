#include "tucontainable.inl"
#include "native/tnarr.inl"
#include "../../ast/node.hpp"

namespace wrd {

    template <typename T>
    typedef tuncontainable<T> me;

    T& me::get(std::function<wbool(const T&)> l) const {
        return get<T>(l);
    }

    narr me::getAll(std::function<wbool(const T&)> l) const {
        return getAll<T>(l);
    }
}

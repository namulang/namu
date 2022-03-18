#include "../tbicontainable.hpp"

namespace wrd {

    template <typename K, typename V>
    typedef tbicontainable<K, V>::iteration me;

    wbool me::isFrom(const tbicontainable& rhs) const {
        return &getContainer() == &rhs;
    }
}

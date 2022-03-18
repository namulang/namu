#include "../tucontainable.hpp"

namespace wrd {

    template <typename T>
    typedef tucontainable<T>::iteration me;

    wbool me::isFrom(const tucontainable& rhs) const {
        return &getContainer() == &rhs;
    }
}

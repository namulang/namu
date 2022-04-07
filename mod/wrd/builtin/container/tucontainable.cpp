#include "tucontainable.inl"
#include "native/tnarr.inl"
#include "../../ast/node.hpp"

namespace wrd {

#define TEMPL template <typename T>
#define ME tucontainable<T>

    TEMPL
    T& ME::get(std::function<wbool(const T&)> l) const {
        return this->get<T>(l);
    }

    TEMPL
    narr ME::getAll(std::function<wbool(const T&)> l) const {
        return this->getAll<T>(l);
    }

#undef ME
#undef TEMPL
}

#pragma once

#include "tucontainable.hpp"
#include "tbicontainable.hpp"
#include "iter/uiter.inl"
#include "../../ast/node.hpp"
#include "native/tnarr.inl"

namespace namu {

#define TEMPL template <typename T>
#define ME tucontainable<T>

    TEMPL
    template <typename K, typename V>
    ncnt ME::add(const tbicontainable<K, V>& rhs) {
        static_assert(areBaseOfT<T, V>::value, "given type 'V' is not subtype of 'T'");
        ncnt ret = 0;
        for(auto e=rhs.begin(); e ;++e)
            ret += add(*e);
        return ret;
    }

#undef ME
#undef TEMPL
}

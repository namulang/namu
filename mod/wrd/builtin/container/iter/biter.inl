// nested class of tbicontainable.hpp:
//  this file allows to be refered by 'tbicontainable.hpp' file only.
#pragma once

#include "biterable.hpp"
#include "../../../ast/node.hpp"

namespace wrd {

#define TEMPL template <typename K, typename V>
#define ME tbicontainable<K, V>::iter

    TEMPL
    K& ME::getKey() {
        if(!_step) return nulOf<T>();
        return _step->getKey().cast<T>();
    }

    TEMPL
    V& ME::getVal() {
        if(!_step) return nulOf<V>();
        return _step->getVal().cast<V>();
    }

#undef ME
#undef TEMPL
}

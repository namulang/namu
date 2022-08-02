// nested class of tbicontainable.inl:
//  this file allows to be refered by 'tbicontainable.inl' file only.
#pragma once

#include "../../../ast/node.hpp"

namespace namu {

#define TEMPL template <typename K, typename V>
#define ME tbicontainable<K, V>::iter

    TEMPL
    const K& ME::getKey() const {
        if(!_step) return nulOf<K>();
        return _step->getKey();
    }

    TEMPL
    V& ME::getVal() {
        if(!_step) return nulOf<V>();
        return _step->getVal();
    }

    TEMPL
    void ME::setVal(const V& new1) {
        if(!_step) return;
        return _step->setVal(new1);
    }

#undef ME
#undef TEMPL
}

// nested class of tucontainable.inl:
//  this file allows to be refered by 'tucontainable.inl' file only.
#pragma once

#include "../../../ast/node.hpp"

namespace namu {

#define TEMPL template <typename T>
#define ME tucontainable<T>::iter

    TEMPL
    T& ME::get() {
        if(!_step) return nulOf<T>();
        return _step->get().template cast<T>();
    }


#undef ME
#undef TEMPL
}

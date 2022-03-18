// nested class of ucontainable.hpp:
//  this file allows to be refered by 'ucontainable.hpp' file only.
#pragma once

#include "tuiterable.inl"
#include "../../../../ast/node.hpp"

namespace wrd {

#define TEMPL template <typename T>
#define ME tucontainable<T>::iter

    TEMPL
    T& ME::get() {
        if(!_step) return nulOf<T>();
        return _step->get().cast<T>();
    }


#undef ME
#undef TEMPL
}

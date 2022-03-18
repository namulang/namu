// nested class of tucontainable.hpp:
//  this file allows to be refered by 'tucontainable.hpp' file only.
#pragma once

#include "uiterable.hpp"
#include "../../../ast/node.hpp"

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

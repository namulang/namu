#pragma once

#include "titer.hpp"
#include "../../../../ast/node.hpp"

namespace wrd {

#define TEMPL template <typename T>
#define ME titer<T>

    TEMPL
    T& ME::get() {
        if(!_step) return nulOf<T>();
        return _step->get().cast<T>();
    }


#undef ME
#undef TEMPL
}


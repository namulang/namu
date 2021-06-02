#pragma once

#include "titerator.hpp"
#include "../../../../ast/node.hpp"

namespace wrd {

#define TEMPL template <typename T>
#define ME titerator<T>

    TEMPL
    T& ME::get() {
        if(!_step) return nulOf<node>();

        while(!isEnd()) {
            T& ret = _step->get().cast<T>();
            if(!nul(ret)) return ret;

            next(1);
        }

        return nulOf<T>();
    }


#undef ME
#undef TEMPL
}


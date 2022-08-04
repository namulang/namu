#pragma once

#include "../../ast/scope.hpp"
#include "../../builtin/container/native/tnarr.hpp"

namespace namu {

    class defBlock : public instance, public clonable {
        NAMU(CLASS(defBlock, instance))

    public:
        defBlock(): asScope(new scope()), asPreCtor(new narr()) {}

    public:
        tstr<scope> asScope;
        tstr<narr> asPreCtor;
    };
}

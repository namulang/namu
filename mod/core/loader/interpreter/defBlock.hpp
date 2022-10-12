#pragma once

#include "../../ast/scope.hpp"
#include "../../builtin/container/native/tnarr.hpp"

namespace namu {

    class _nout defBlock : public instance {
        NAMU(CLASS(defBlock, instance))

    public:
        defBlock(): asScope(new scope()), asPreCtor(new narr()) {}

    public:
        tstr<scope> asScope;
        tstr<narr> asPreCtor;
    };
}

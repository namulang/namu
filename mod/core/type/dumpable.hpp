#pragma once

#include "../common.hpp"

namespace namu {
    class _nout dumpable {
    public:
        virtual void dump() const = 0;
    };
}

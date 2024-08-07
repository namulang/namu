#pragma once

#include "dep.hpp"

namespace nm {
    enum typeAttr {
        NOTHING,
        CONSTANT,
        COMPLETE_OBJ,
    };

    class _nout util {
        NM(ME(util))

    public:
        static typeAttr checkTypeAttr(const std::string& name);
    };
}

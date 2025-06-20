#pragma once

#include "core/common/dep.hpp"

namespace nm {

    class node;

    enum typeAttr {
        ATTR_ERR,
        ATTR_CONST,
        ATTR_COMPLETE,
        ATTR_INCOMPLETE
    };

    class _nout util {
        NM(ME(util))

    public:
        static typeAttr checkTypeAttr(const std::string& name);
        static typeAttr checkTypeAttr(const std::string* it) NM_SIDE_FUNC(checkTypeAttr);
        static std::string getEvalTypeFrom(const node& n);
        static std::string getEvalTypeFrom(const node* it) NM_SIDE_FUNC(getEvalTypeFrom);
    };
}

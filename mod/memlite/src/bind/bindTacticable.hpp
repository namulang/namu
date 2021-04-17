#pragma once

#include "../common.hpp"

namespace wrd {

    class bind;
    class instance;
    class bindTacticable {
    public:
        virtual wbool unbind(bind& me) = 0;
        virtual wbool bind(bind& me, const instance& it) = 0;
    };
}

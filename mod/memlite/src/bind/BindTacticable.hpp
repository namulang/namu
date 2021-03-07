#pragma once

#include "../common.hpp"

namespace wrd {

    class Bind;
    class Instance;
    class BindTacticable {
    public:
        virtual wbool unbind(Bind& me) = 0;
        virtual wbool bind(Bind& me, const Instance& it) = 0;
    };
}

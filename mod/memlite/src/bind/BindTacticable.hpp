#pragma once

#include "../common.hpp"

namespace wrd {

    class Bind;
    class Instance;
    class BindTacticable {
    public:
        virtual wbool assign(Bind& me, Bind& rhs) = 0;
        virtual wbool unbind(Bind& me) = 0;
        virtual wbool bind(Bind& me, Instance& it) = 0;
    };
}

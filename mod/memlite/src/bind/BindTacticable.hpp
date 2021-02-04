#pragma once

#include "../common.hpp"

namespace wrd {

    class Bind;
    class Instance;
    class BindTacticable {
    public:
		virtual wbool assign(Bind& me, const Bind& rhs) = 0;
        virtual wbool unbind(Bind& me) = 0;
        virtual wbool bind(Bind& me, const Instance& it) = 0;
        virtual const Type& getType() = 0;
        virtual wbool isConst() const = 0;
    };
}

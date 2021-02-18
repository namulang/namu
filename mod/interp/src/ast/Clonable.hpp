#pragma once

#include "../common.hpp"

namespace wrd {

    class Clonable : public TypeProvidable {
        WRD_DECL_THIS(Clonable)
        WRD_INIT_META(This)

    public:
        virtual This* clone() const = 0;
    };
}

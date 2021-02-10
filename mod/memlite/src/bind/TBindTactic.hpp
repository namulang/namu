#pragma once

#include "BindTacticable.hpp"

namespace wrd {

    template <typename T>
    class TBindTactic : public BindTacticable {
    public:
        virtual Type& getType();
    };
}

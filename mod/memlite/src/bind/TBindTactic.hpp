#pragma once

#include "BindTacticable.hpp"

namespace wrd {

    template <typename T>
    class TBindTactic : public BindTacticable {
    public:
        virtual const Type& getType();
        virtual wbool isConst() const;
    };

    template <typename T>
    class TBindTactic<const T> : public BindTacticable {
    public:
        virtual const Type& getType();
        virtual wbool isConst() const;
    };
}

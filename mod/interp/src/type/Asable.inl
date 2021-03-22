#pragma once

#include "Asable.hpp"
#include "../ast/Ref.hpp"

namespace wrd {

#define THIS Asable

    template <typename T>
    TRef<T> THIS::as(const Node& it) const {
        return as(it);
    }

#undef THIS
}

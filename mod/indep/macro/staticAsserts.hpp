#pragma once

#include "../common/typedef.hpp"
#include <type_traits>

namespace namu {

    template <nbool...> struct boolPack;
    template <nbool... bp>
    using allTrues = std::is_same<boolPack<bp..., true>, boolPack<true, bp...>>;
}

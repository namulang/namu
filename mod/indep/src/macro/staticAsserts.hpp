#pragma once

#include "../common/typedef.hpp"
#include <type_traits>

namespace wrd {

    template <wbool...> struct boolPack;
    template <wbool... bp>
    using allTrues = std::is_same<boolPack<bp..., true>, boolPack<true, bp...>>;
}

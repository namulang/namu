#pragma once

#include "err.hpp"

namespace wrd {

    template <typename T>
    struct tres : public tpair<T, err> {};
}

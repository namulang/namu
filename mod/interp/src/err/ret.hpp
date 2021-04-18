#pragma once

#include "err.hpp"

namespace wrd {

    template <typename T>
    struct ret {
        ret(): val() {}
        ret(T newVal, err newErr): val(newVal, err(newErr) {}

        T val;
        err err;
    };

}

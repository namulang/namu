#pragma once

#include "Err.hpp"

namespace wrd {

    template <typename T>
    struct Ret {
        Ret(): val() {}
        Ret(T newVal, Err newErr): val(newVal, err(newErr) {}

        T val;
        Err err;
    };

}

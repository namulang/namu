#pragma once

#include "indep/helper/tmay.hpp"
#include "indep/helper/nulr.hpp"

namespace nm {

#define ME tmay<T>
#define TEMPLATE template <typename T>

    TEMPLATE
    ME::tmay(const T& value): super(value) {}

    TEMPLATE
    T* ME::operator->() { return &get(); }

    TEMPLATE
    T& ME::operator*() { return get(); }

    TEMPLATE
    ME::operator nbool() const { return has(); }

    TEMPLATE
    nbool ME::has() const { return this->has_value(); }

    TEMPLATE
    T& ME::get() { return this->value(); }

    TEMPLATE
    void ME::rel() { this->reset(); }

    TEMPLATE
    void ME::set(const T& args) { this->emplace(args); }

#undef TEMPLATE
#undef ME
} // namespace nm

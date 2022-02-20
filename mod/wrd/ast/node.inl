#pragma once

#include "node.hpp"

namespace wrd {

#define ME node

    template <typename T>
    T& ME::sub(const std::string& name) const {
        return subs().get<T>([&](const T& elem) {
            return elem.getName() == name;
        });
    }

    template <typename T>
    T& ME::sub(const std::string& name, const containable& args) {
        if(nul(args))
            return sub<T>(name);

        return subs().get<T>([&](const T& elem) {
            return elem.getName() == name && elem.canRun(args);
        });
    }

    template <typename T>
    T& ME::sub(const std::string& name, const containable& args) const WRD_UNCONST_FUNC(sub<T>(name, args))

    template <typename T>
    tnarr<T> ME::subAll(const std::string& name) const {
        return subs().getAll<T>([&](const T& elem) {
            return elem.getName() == name;
        });
    }

    template <typename T>
    tnarr<T> ME::subAll(const std::string& name, const containable& args) {
        if(nul(args))
            return subAll<T>(name);

        return subs().getAll<T>([&](const T& elem) {
            return elem.getName() == name && elem.canRun(args);
        });
    }

    template <typename T>
    tnarr<T> ME::subAll(const std::string& name, const containable& args) const WRD_UNCONST_FUNC(subAll<T>(name, args))

#undef ME
}

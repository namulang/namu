#pragma once

#include "node.hpp"

namespace namu {

#define ME node

    template <typename T>
    T& ME::sub() const {
        return subs().get<T>([](const std::string& key, const T& val) {
            return true;
        });
    }

    template <typename T>
    T& ME::sub(const std::string& name) const {
        return subs().get<T>([&](const std::string& key, const T& val) {
            NAMU_DI("this=%s[%x]: key=%s name=%s", getType().getName().c_str(), this, key.c_str(), name.c_str());
            return key == name;
        });
    }

    template <typename T>
    T& ME::sub(const std::string& name, const args& a) {
        if(nul(a))
            return sub<T>(name);

        return subs().get<T>([&](const std::string& key, const T& val) {
            NAMU_DI("this=%s[%x]: key=%s name=%s", getType().getName().c_str(), this, key.c_str(), name.c_str());
            return key == name && val.canRun(a);
        });
    }

    template <typename T>
    T& ME::sub(const std::string& name, const args& a) const NAMU_UNCONST_FUNC(sub<T>(name, a))

    template <typename T>
    tnarr<T, strTactic> ME::subAll() const {
        return subs().getAll<T>([](const std::string& key, const T& val) {
            return true;
        });
    }

    template <typename T>
    tnarr<T, strTactic> ME::subAll(const std::string& name) const {
        return subs().getAll<T>([&](const std::string& key, const T& val) {
            return key == name;
        });
    }

    template <typename T>
    tnarr<T, strTactic> ME::subAll(const std::string& name, const args& a) {
        if(nul(a))
            return subAll<T>(name);

        return subs().getAll<T>([&](const std::string& key, const T& val) {
            NAMU_DI("this=%s[%x]: key=%s name=%s", getType().getName().c_str(), this, key.c_str(), name.c_str());
            return key == name && val.canRun(a);
        });
    }

    template <typename T>
    tnarr<T, strTactic> ME::subAll(const std::string& name, const args& a) const NAMU_UNCONST_FUNC(subAll<T>(name, a))

#undef ME
}

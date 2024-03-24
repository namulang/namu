#pragma once

#include "node.hpp"
#include "baseObj.hpp"
#include "tpriorities.inl"
#include "args.hpp"

namespace namu {

#define ME node
#define TEMPLATE template <typename T>

    TEMPLATE
    T& ME::sub() {
        return subs().get<T>([](const std::string& key, const T& val) {
            return true;
        });
    }

    TEMPLATE
    T& ME::sub(const std::string& name) {
        return subs().get<T>([&](const std::string& key, const T& val) {
            NAMU_DI("this=%s[%x]: key=%s name=%s", getType().getName().c_str(), this, key.c_str(), name.c_str());
            return key == name;
        });
    }

    TEMPLATE
    T& ME::sub(const std::string& name, const args& a) {
        if(nul(a))
            return sub<T>(name);

        return subs().get<T>([&](const std::string& key, const T& val) {
            NAMU_DI("this=%s[%x]: key=%s name=%s", getType().getName().c_str(), this, key.c_str(), name.c_str());
            return key == name && val.canRun(a);
        });
    }

    TEMPLATE
    tnarr<T, strTactic> ME::subAll() const {
        return subs().template getAll<T>([](const std::string& key, const T& val) {
            return true;
        });
    }

    TEMPLATE
    tnarr<T, strTactic> ME::subAll(const std::string& name) const {
        return subs().getAll<T>([&](const std::string& key, const T& val) {
            return key == name;
        });
    }

    TEMPLATE
    tpriorities<T> ME::subAll(const std::string& name, const args& a) const {
        if(nul(a)) return NAMU_W("a == null"), tpriorities<T>();

        NAMU_DI("subAll: %s(%s)", name.c_str(), a.toStr().c_str());
        tpriorities<T> ret;
        subs().each<T>([&](const std::string& key, const T& val, node& owner) {
            /* TODO: is this code needed?
                const baseObj& o = sub.template cast<baseObj>();
                if(!nul(o)) {
                    auto subs = sub.template subAll<T>(baseObj::CTOR_NAME, a);
                    for(const tprior<T>& p : subs)
                        ps.push_back(p);
                    continue;
                }
            */
            priority p = val.prioritize(a);
            NAMU_DI("\tname=%s match=%d", key.c_str(), p);
            if(key == name && p != NO_MATCH)
                ret.add(tprior<T>(val, owner, p));
        });
        return ret.sort();
    }

#undef TEMPLATE
#undef ME
}

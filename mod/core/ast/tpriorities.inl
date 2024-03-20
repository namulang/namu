#pragma once

#include "tpriorities.hpp"

namespace namu {

#define TEMPLATE template <typename T>
#define ME tprior<T>

    TEMPLATE
    ME::tprior(const node& newElem, priority newLv): lv(newLv) {
        elem.bind(newElem);
    }

    TEMPLATE T* ME::operator->() { return &get(); }
    TEMPLATE T& ME::operator*() { return get(); }

    TEMPLATE T& ME::get() { return elem.get(); }

#undef ME
#define ME tpriorities<T>

    TEMPLATE
    ME::tpriorities() {}

    TEMPLATE
    T& ME::getMatched() {
        // assume that this container already got sorted to priority.
        ncnt len = this->len();
        if(len <= 0) return nulOf<T>();

        auto ret = split(this->get(0).lv);
        if(ret.len() != 1) return nulOf<T>();
        return *ret[0].elem;
    }

    TEMPLATE
    ME ME::getAmbigious() const {
        if(this->len() < 2) return ME();
        auto ret = split(this->get(0).lv);
        if(ret.len() <= 1) return ME();

        return ret;
    }

    TEMPLATE
    ME ME::split(priority by) const {
        ME ret;
        priority p = NO_MATCH;
        for(const auto& e : *this) {
            if(p == NO_MATCH)
                p = e.lv;
            else if(p != e.lv)
                break;
            ret.add(e);
        }
        return ret;
    }

#undef ME
#undef TEMPLATE
}

#pragma once

#include "tpriorities.hpp"

namespace namu {

#define TEMPLATE template <typename T>
#define ME tprior<T>

    TEMPLATE
    ME::tprior(const node& newElem, priority newLv): lv(newLv) {
        elem.bind(newElem);
    }

    TEMPLATE
    ME::tprior(const node& newElem, const node& newOwner, priority newLv): lv(newLv) {
        elem.bind(newElem);
        owner.bind(newOwner);
    }

    TEMPLATE T* ME::operator->() { return &get(); }
    TEMPLATE T& ME::operator*() { return get(); }

    TEMPLATE T& ME::get() { return elem.get(); }

    TEMPLATE nbool ME::isSamePrecedence(const ME& rhs) const {
        return lv == rhs.lv && &owner.get() == &rhs.owner.get();
    }

#undef ME
#define ME tpriorities<T>

    TEMPLATE
    ME::tpriorities() {}

    TEMPLATE
    ME::tpriorities(const T& elem) {
        this->add(*new tprior<T>(elem, EXACT_MATCH));
    }

    TEMPLATE
    ME::tpriorities(const T& elem, const node& owner) {
        this->add(*new tprior<T>(elem, owner, EXACT_MATCH));
    }

    TEMPLATE
    tnarr<T> ME::getMatches() const {
        // assume that this container already got sorted to priority.
        // sub node at index 0 is always highest priority.
        tnarr<T> ret;
        ncnt len = this->len();
        if(len <= 0) return ret;

        const tprior<T>* sample = nullptr;
        this->each([&](const auto& p) {
            if(nul(sample)) sample = &p;
            if(!sample->isSamePrecedence(p)) return false;
            return ret.add(*p.elem);
        });
        return ret;
    }

    TEMPLATE
    tstr<T> ME::getMatch() {
        auto matches = getMatches();
        if(matches.len() != 1) return tstr<T>();
        return tstr<T>(matches[0]);
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

#pragma once

#include "tucontainable.hpp"
#include "tbicontainable.hpp"
#include "iter/uiter.inl"
#include "../../ast/node.hpp"
#include "native/tnarr.inl"

namespace namu {

#define TEMPL template <typename T>
#define ME tucontainable<T>

    TEMPL
    template <typename K, typename V>
    ncnt ME::add(const tbicontainable<K, V>& rhs) {
        static_assert(areBaseOfT<T, V>::value, "given type 'V' is not subtype of 'T'");
        ncnt ret = 0;
        for(auto e=rhs.begin(); e ;++e)
            ret += add(*e);
        return ret;
    }

    TEMPL
    template <typename T1>
    T1& ME::get(std::function<nbool(const T1&)> l) {
        for(auto e=begin(); e ;++e) {
            T1& val = e->template cast<T1>();
            if(nul(val) || !l(val)) continue;
                return val;
        }

        return nulOf<T1>();
    }

    TEMPL
    T& ME::get(std::function<nbool(const T&)> l) {
        return this->get<T>(l);
    }

    TEMPL
    template <typename T1>
    T1& ME::get(std::function<nbool(const T1&, node&)> l) {
        for(auto e=begin(); e ;++e) {
            T1& val = e->template cast<T1>();
            if(nul(val) || !l(val, e.getOwner())) continue;
                return val;
        }

        return nulOf<T1>();
    }

    TEMPL
    T& ME::get(std::function<nbool(const T&, node&)> l) {
        return this->get<T>(l);
    }

    TEMPL
    template <typename T1>
    tnarr<T1> ME::getAll(std::function<nbool(const T1&)> l) const {
        tnarr<T1> ret;
        for(auto e=begin(); e ;++e) {
            const T1& val = e->template cast<T1>();
            if(nul(val) || !l(val)) continue;

            ret.add(val);
        }

        return ret;
    }

    TEMPL
    narr ME::getAll(std::function<nbool(const T&)> l) const {
        return this->getAll<T>(l);
    }

    TEMPL
    template <typename T1>
    tnarr<T1> ME::getAll(std::function<nbool(const T1&, node&)> l) const {
        tnarr<T1> ret;
        for(auto e=begin(); e ;++e) {
            T1& val = e->template cast<T1>();
            if(nul(val) || !l(val, e.getOwner())) continue;

            ret.add(val);
        }

        return ret;
    }

    TEMPL
    narr ME::getAll(std::function<nbool(const T&, node&)> l) const {
        return this->getAll<T>(l);
    }

    TEMPL
    template <typename T1>
    void ME::each(std::function<void(T1&)> l) {
        for(auto e=begin(); e ;++e) {
            T1& val = e->template cast<T1>();
            if(nul(val)) continue;

            l(val);
        }
    }

    TEMPL
    void ME::each(std::function<void(T&)> l) {
        this->each<node>(l);
    }

    TEMPL
    template <typename T1>
    void ME::each(std::function<void(T1&, node&)> l) {
        for(auto e=begin(); e ;++e) {
            T1& val = e->template cast<T1>();
            if(nul(val)) continue;

            l(val, e.getOwner());
        }
    }

    TEMPL
    void ME::each(std::function<void(T&, node&)> l) {
        this->each<node>(l);
    }

#undef ME
#undef TEMPL
}

#pragma once

#include "tbicontainable.hpp"
#include "iter/biter.inl"
#include "../../ast/node.hpp"
#include "native/tnarr.inl"

namespace namu {

#define TEMPL template <typename K, typename V>
#define ME tbicontainable<K, V>

    TEMPL
    template <typename V1>
    V1& ME::get(std::function<nbool(const K&, const V1&)> l) {
        for(auto e=begin(); e ;++e) {
            V1& val = e.getVal().template cast<V1>();
            if(nul(val) || !l(e.getKey(), val)) continue;
                return val;
        }

        return nulOf<V1>();
    }

    TEMPL
    V& ME::get(std::function<nbool(const K&, const V&)> l) {
        return this->get<V>(l);
    }

    TEMPL
    template <typename V1>
    V1& ME::get(std::function<nbool(const K&, const V1&, node&)> l) {
        for(auto e=begin(); e ;++e) {
            V1& val = e.getVal().template cast<V1>();
            if(nul(val) || !l(e.getKey(), val, e.getOwner())) continue;
                return val;
        }

        return nulOf<V1>();
    }

    TEMPL
    V& ME::get(std::function<nbool(const K&, const V&, node&)> l) {
        return this->get<V>(l);
    }

    TEMPL
    tnarr<V> ME::getAll(const K& key) const {
        narr ret;
        _getAll(key, ret);
        return ret;
    }

    TEMPL
    template <typename V1>
    tnarr<V1> ME::getAll(std::function<nbool(const K&, const V1&)> l) const {
        tnarr<V1> ret;
        for(auto e=begin(); e ;++e) {
            const V1& val = e.getVal().template cast<V1>();
            if(nul(val) || !l(e.getKey(), val)) continue;

            ret.add(val);
        }

        return ret;
    }

    TEMPL
    tnarr<V> ME::getAll(std::function<nbool(const K&, const V&)> l) const {
        return this->getAll<V>(l);
    }

    TEMPL
    template <typename V1>
    tnarr<V1> ME::getAll(std::function<nbool(const K&, const V1&, node&)> l) const {
        tnarr<V1> ret;
        for(auto e=begin(); e ;++e) {
            const V1& val = e.getVal().template cast<V1>();
            if(nul(val) || !l(e.getKey(), val, e.getOwner())) continue;

            ret.add(val);
        }

        return ret;
    }

    TEMPL
    tnarr<V> ME::getAll(std::function<nbool(const K&, const V&, node&)> l) const {
        return this->getAll<V>(l);
    }

    TEMPL
    template <typename V1>
    void ME::each(std::function<void(const K&, V1&)> l) {
        for(auto e=begin(); e ;++e) {
            V1& val = e.getVal().template cast<V1>();
            if(nul(val)) continue;

            l(e.getKey(), val);
        }
    }

    TEMPL
    void ME::each(std::function<void(const K&, V&)> l) {
        this->each<node>(l);
    }

    TEMPL
    template <typename V1>
    void ME::each(std::function<void(const K&, V1&, node&)> l) {
        for(auto e=begin(); e ;++e) {
            V1& val = e.getVal().template cast<V1>();
            if(nul(val)) continue;

            l(e.getKey(), val, e.getOwner());
        }
    }

    TEMPL
    void ME::each(std::function<void(const K&, V&, node&)> l) {
        this->each<node>(l);
    }

#undef ME
#undef TEMPL
}

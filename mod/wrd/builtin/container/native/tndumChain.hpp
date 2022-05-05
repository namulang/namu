#pragma once

#include "tnchain.inl"

namespace wrd {

    template <typename K, typename V, typename defaultContainer = nmap>
    class tndumChain : public tnchain<K, V, defaultContainer> {
        typedef tnchain<K, V, defaultContainer> __super;
        WRD(CLASS(tndumChain, __super))

    public:
        // add:
        using super::add;
        wbool add(const K& key, const V& val) override { return false; }

        // link:
        using super::link;
        wbool link(const super& new1) override { return false; }

    public:
        static inline me singletone;
    };

    typedef tndumChain<std::string, node> ndumChain;
}

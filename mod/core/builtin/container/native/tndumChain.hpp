#pragma once

#include "tnchain.inl"

namespace namu {

    template <typename K, typename V, typename defaultContainer = nmap>
    class tndumChain : public tnchain<K, V, defaultContainer> {
        typedef tnchain<K, V, defaultContainer> _super_;
        WRD(CLASS(tndumChain, _super_))

    public:
        tndumChain() {}
        tndumChain(const super& rhs): super(rhs) {}

    public:
        // add:
        using super::add;
        wbool add(const K& key, const V& val) override { return false; }

        // link:
        using super::link;
        wbool link(const super& new1) override { return false; }

    public:
        static me singletone;
    };

    typedef tndumChain<std::string, node> ndumChain;
}

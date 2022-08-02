#pragma once

#include "tnmap.inl"

namespace namu {

    template <typename K, typename V, typename TACTIC = strTactic>
    class tndumMap : public tnmap<K, V, TACTIC> {
        typedef tnmap<K, V, TACTIC> _super_;
        WRD(CLASS(tndumMap, _super_))

    public:
        tndumMap() {}
        tndumMap(const super& rhs): super(rhs) {} // initialization is allowed.

        // add:
        using super::add;
        wbool add(const K& key, const V& val) override { return false; }

    public:
        static me singletone;
    };

    typedef tndumMap<std::string, node> ndumMap;
}

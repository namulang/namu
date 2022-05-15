#pragma once

#include "tnmap.inl"

namespace wrd {

    template <typename K, typename V, typename TACTIC = strTactic>
    class tndumMap : public tnmap<K, V, TACTIC> {
        typedef tnmap<K, V, TACTIC> __super;
        WRD(CLASS(tndumMap, __super))

    public:
        // add:
        using super::add;
        wbool add(const K& key, const V& val) override { return false; }

    public:
        static inline me singletone;
    };

    typedef tndumMap<std::string, node> ndumMap;
}

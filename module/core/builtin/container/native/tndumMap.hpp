#pragma once

#include "core/builtin/container/native/tnmap.inl"

namespace nm {

    template <typename K, typename V, typename TACTIC = strTactic>
    class tndumMap: public tnmap<K, V, TACTIC> {
        typedef tnmap<K, V, TACTIC> _super_;
        NM(CLASS(tndumMap, _super_))

    public:
        tndumMap() {}

        tndumMap(const super& rhs): super(rhs) {} // initialization is allowed.

    public:
        using super::add;

        nbool add(const K& key, const V& val) override { return false; }

    public:
        static me singleton;
    };

    typedef tndumMap<std::string, node> ndumMap;
}
